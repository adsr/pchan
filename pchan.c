#include <stdlib.h>
#include <pthread.h>
#include "pchan.h"

pchan_t *pchan_make(size_t cap, size_t item_size) {
    pchan_t *chan;
    chan = calloc(1, sizeof(pchan_t));
    chan->items = calloc(cap, sizeof(void*) * item_size);
    chan->item_size = item_size;
    chan->cap = cap;
    chan->len = 0;
    pthread_mutex_init(&chan->mutex, NULL);
    pthread_cond_init(&chan->cond, NULL);
    return chan;
}

void pchan_write(pchan_t *chan, void *item) {
    int done;
    done = 0;
    do {
        pthread_mutex_lock(&chan->mutex);
        if (chan->len < chan->cap) {
            *(chan->items + chan->len) = item;
            chan->len += 1;
            done = 1;
        }
        pthread_cond_signal(&chan->cond);
        pthread_mutex_unlock(&chan->mutex);
    } while (done == 0);
}

void *pchan_read(pchan_t *chan) {
    void *retval;
    int wait;
    retval = NULL;
    wait = 0;
    do {
        pthread_mutex_lock(&chan->mutex);
        if (wait == 1) {
            pthread_cond_wait(&chan->cond, &chan->mutex);
        } else {
            wait = 1;
        }
        if (chan->len > 0) {
            retval = *(chan->items + (chan->len - 1));
            chan->len -= 1;
        }
        pthread_mutex_unlock(&chan->mutex);
    } while (retval == NULL);
    return retval;
}

void pchan_destroy(pchan_t *chan) {
    pthread_mutex_destroy(&chan->mutex);
    pthread_cond_destroy(&chan->cond);
    free(chan->items);
    free(chan);
}
