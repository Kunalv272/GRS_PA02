// MT25029
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>

#define FIELDS 8

typedef struct {
    char *f[FIELDS];
} message_t;

int MSG_SIZE = 1024;

void* client_handler(void *arg){
    int sock = *(int*)arg;
    free(arg);

    while(1){
        message_t m;

        for(int i=0;i<FIELDS;i++){
            m.f[i] = malloc(MSG_SIZE/FIELDS);
            memset(m.f[i],'A'+i,MSG_SIZE/FIELDS);
        }

        for(int i=0;i<FIELDS;i++){
            ssize_t r = send(sock,m.f[i],MSG_SIZE/FIELDS,0);
            if(r<=0) goto done;
        }

        for(int i=0;i<FIELDS;i++) free(m.f[i]);
    }

done:
    close(sock);
    return NULL;
}

int main(int argc,char**argv){

    if(argc<2){
        printf("usage: server <msg_size>\n");
        exit(1);
    }

    MSG_SIZE = atoi(argv[1]);

    int s = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in a={0};
    a.sin_family=AF_INET;
    a.sin_port=htons(9090);
    a.sin_addr.s_addr=INADDR_ANY;

    bind(s,(void*)&a,sizeof(a));
    listen(s,64);

    while(1){
        int *c = malloc(sizeof(int));
        *c = accept(s,NULL,NULL);

        pthread_t t;
        pthread_create(&t,NULL,client_handler,c);
        pthread_detach(t);
    }
}
