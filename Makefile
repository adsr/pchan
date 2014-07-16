all: run_pchan_test

CC=$(shell if test `which colorgcc`; then echo colorgcc; else echo gcc; fi)

pchan.o: pchan.c
	$(CC) -Wall -c pchan.c -fPIC

libpchan.so: pchan.o
	$(CC) -Wall -o libpchan.so pchan.o -shared

pchan_test: libpchan.so
	$(CC) -Wall -o pchan_test pchan_test.c -L. -lpchan

run_pchan_test: pchan_test
	LD_LIBRARY_PATH=. ./pchan_test

clean:
	rm -f *.o *.so pchan_test
