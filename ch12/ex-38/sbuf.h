#ifndef __SBUF_H__
#define __SBUF_H__

#include "csapp.h"

/* define sbuf_t */
typedef struct {
    int *buf; /* Buffer array */
    int n; /* Maximun number of slots */
    int front; /* buf[(front+1)%n] is the first item */
    int rear; /* buf[rear] is the last item */
    sem_t mutex; /* Protects accesses to buf */
    sem_t slots; /* Counts avaliable slots */
    sem_t items; /* Counts avaliable items */
} sbuf_t;

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);
int sbuf_item_counter(sbuf_t *sp);

#endif
