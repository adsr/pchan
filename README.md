pchan
=====

pchan is Go-style channels for C, built on pthreads. It's basically just a
thread-safe stack of pointers. Currently, not all features are supported,
e.g., no `close(...)` equivalent, no ability to `select{ ... }` on multiple
channels, and no way to do non-blocking chan operations. But these are all
feasible I think, so maybe in the future...

See pchan.h for the API.

See pchan_test.c for a really dumb single-threaded test application.
