
// MT25029 - Common definitions
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <time.h>

#define DEFAULT_PORT 9090

typedef struct {
    char *f1; char *f2; char *f3; char *f4;
    char *f5; char *f6; char *f7; char *f8;
} message_t;

static inline message_t *create_message(size_t sz) {
    message_t *m = malloc(sizeof(message_t));
    m->f1 = malloc(sz); m->f2 = malloc(sz); m->f3 = malloc(sz); m->f4 = malloc(sz);
    m->f5 = malloc(sz); m->f6 = malloc(sz); m->f7 = malloc(sz); m->f8 = malloc(sz);
    memset(m->f1,'A',sz); memset(m->f2,'B',sz); memset(m->f3,'C',sz); memset(m->f4,'D',sz);
    memset(m->f5,'E',sz); memset(m->f6,'F',sz); memset(m->f7,'G',sz); memset(m->f8,'H',sz);
    return m;
}

static inline void destroy_message(message_t *m){
    free(m->f1); free(m->f2); free(m->f3); free(m->f4);
    free(m->f5); free(m->f6); free(m->f7); free(m->f8);
    free(m);
}

#endif
