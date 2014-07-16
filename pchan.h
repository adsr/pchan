#ifndef __PCHAN_H
#define __PCHAN_H

#include <pthread.h>

// A channel is a implemented as a thread-safe stack.
//     pchan_write is a push
//     pchan_read is a pop
//     pchan_destroy is a nuclear bomb
typedef struct {
    size_t cap;
    size_t len;
    size_t item_size;
    void **items;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} pchan_t;

// Make a channel with capacity `cap` for items of size `item_size`.
pchan_t *pchan_make(size_t cap, size_t item_size);

// Write to a channel, blocking until space is available.
void pchan_write(pchan_t *chan, void *item);

// Read from a channel, blocking until an item is available.
void *pchan_read(pchan_t *chan);

// Destroy a channel.
void pchan_destroy(pchan_t *chan);

#endif
