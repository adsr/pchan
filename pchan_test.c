#include <stdio.h>
#include "pchan.h"

int main(int argc, char **argv) {
    pchan_t *chan = NULL;
    int i[3] = { 1, 2, 3 };
    int *j;

    printf("Running pchan_test\n");

    printf("pchan_make\n");
    chan = pchan_make(3, sizeof(int*));

    printf("pchan_write * 3\n");
    pchan_write(chan, (void*)i);
    pchan_write(chan, (void*)(i+1));
    pchan_write(chan, (void*)(i+2));

    printf("pchan_read * 3\n");
    j = (int*)pchan_read(chan); printf("%d\n", *j);
    j = (int*)pchan_read(chan); printf("%d\n", *j);
    j = (int*)pchan_read(chan); printf("%d\n", *j);

    printf("pchan_destroy\n");
    pchan_destroy(chan);

    return 0;
}
