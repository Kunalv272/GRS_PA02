// MT25029
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

int MSG_SIZE;
volatile int run=1;
long total_bytes=0;

double now(){
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,&t);
    return t.tv_sec + t.tv_nsec*1e-9;
}

void* recv_worker(void* arg){
    int sock=*(int*)arg;
    char buf[65536];

    while(run){
        ssize_t r = recv(sock,buf,sizeof(buf),0);
        if(r<=0) break;
        __sync_fetch_and_add(&total_bytes,r);
    }
    return NULL;
}

int main(int argc,char**argv){

    if(argc<5){
        printf("client ip port msg_size threads\n");
        exit(1);
    }

    MSG_SIZE = atoi(argv[3]);
    int threads = atoi(argv[4]);

    int sock=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in a={0};
    a.sin_family=AF_INET;
    a.sin_port=htons(9090);
    inet_pton(AF_INET,argv[1],&a.sin_addr);

    connect(sock,(void*)&a,sizeof(a));

    pthread_t T[16];

    double start=now();

    for(int i=0;i<threads;i++)
        pthread_create(&T[i],NULL,recv_worker,&sock);

    sleep(2);
    run=0;

    for(int i=0;i<threads;i++)
        pthread_join(T[i],NULL);

    double end=now();

    double sec=end-start;
    double mbps=(total_bytes*8)/(sec*1e6);
    double latency=(sec*1e6)/(total_bytes/MSG_SIZE);

    printf("LATENCY_US=%f\n",latency);
    printf("THROUGHPUT_MBPS=%f\n",mbps);
}
