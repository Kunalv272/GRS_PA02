// MT25029_Part_A2_Server.c
#include "MT25029_common.h"

void *client_thread(void *arg){
    int fd = *(int*)arg;
    size_t sz;

    if(recv(fd, &sz, sizeof(sz), 0) <= 0){
        close(fd);
        return NULL;
    }

    char *buf = malloc(sz);
    memset(buf, 'X', sz);

    struct iovec iov = {
        .iov_base = buf,
        .iov_len  = sz
    };

    struct msghdr msg = {0};
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    while(1){
        if(sendmsg(fd, &msg, 0) <= 0)
            break;
    }

    free(buf);
    close(fd);
    return NULL;
}

int main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in a = {0};
    a.sin_family = AF_INET;
    a.sin_port = htons(9090);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&a, sizeof(a));
    listen(s, 64);

    while(1){
        int c = accept(s, NULL, NULL);
        pthread_t t;
        pthread_create(&t, NULL, client_thread, &c);
        pthread_detach(t);
    }
}
