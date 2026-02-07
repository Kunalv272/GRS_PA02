// MT25029_Part_A3_Client.c
#define _GNU_SOURCE
#include "MT25029_common.h"
#include <sys/time.h>
#include <time.h>
#include <sched.h>

typedef struct{
    int sock; size_t sz; long bytes;
} arg_t;

void *worker(void *p){
    arg_t *a=(arg_t*)p;
    char *buf=malloc(a->sz);

    struct iovec iov={buf,a->sz};
    struct msghdr msg={0};
    msg.msg_iov=&iov;
    msg.msg_iovlen=1;

    struct timespec st,now;
    clock_gettime(CLOCK_MONOTONIC,&st);

    while(1){
        if(recvmsg(a->sock,&msg,0)<=0) break;
        a->bytes+=a->sz;
        sched_yield();

        clock_gettime(CLOCK_MONOTONIC,&now);
        double t=(now.tv_sec-st.tv_sec)+(now.tv_nsec-st.tv_nsec)/1e9;
        if(t>2.0) break;
    }

    free(buf);
    return NULL;
}

int main(int argc,char **argv){
    if(argc<5)return 0;

    int sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in a={0};
    a.sin_family=AF_INET;
    a.sin_port=htons(atoi(argv[2]));
    inet_pton(AF_INET,argv[1],&a.sin_addr);
    connect(sock,(struct sockaddr*)&a,sizeof(a));

    size_t sz=atoi(argv[3]);
    int threads=atoi(argv[4]);

    send(sock,&sz,sizeof(sz),0);

    pthread_t th[threads];
    arg_t args[threads];

    struct timeval tv1,tv2;
    gettimeofday(&tv1,NULL);

    for(int i=0;i<threads;i++){
        args[i].sock=sock;
        args[i].sz=sz;
        args[i].bytes=0;
        pthread_create(&th[i],NULL,worker,&args[i]);
    }

    long total=0;
    for(int i=0;i<threads;i++){
        pthread_join(th[i],NULL);
        total+=args[i].bytes;
    }

    gettimeofday(&tv2,NULL);

    double us=(tv2.tv_sec-tv1.tv_sec)*1e6+(tv2.tv_usec-tv1.tv_usec);
    printf("LATENCY_US=%f\n",us/(threads*1000.0));
    printf("THROUGHPUT_MBPS=%f\n",(total*8)/us);
    fflush(stdout);
}
