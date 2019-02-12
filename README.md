# Gbench Threads Patch Need Demo

This project demonstrates the need to patch Google Benchmark to better handle
OpenMP and other user-controlled threading.


## Building and running

```
mkdir bld && cd bld && cmake .. && make && ./bin/run_benchmarks
```

This will start a benchmark that uses OpenMP internally.
When built/run with the existing google benchmark,
the CPU time will only be the CPU time for the master thread.
This is because as far as (current) Google Benchmark knows, this is only
a single-threaded process, and it only probes for the CPU usage of the one
thread under its own direct control, not the threads under control of its
threads.

With my patch, you shoudl see something like:

```
-----------------------------------------------------------------------------------------------------------------------------
Benchmark                                                                   Time             CPU   Iterations UserCounters...
-----------------------------------------------------------------------------------------------------------------------------
BM_OpenMP_timewaste_parallel/N:1000/M:1000/num_threads:1/real_time   53414569 ns     53261223 ns           13 M=1000 N=1000 items_per_second=18.7215M/s num_threads=1
BM_OpenMP_timewaste_parallel/N:1000/M:1000/num_threads:2/real_time   30459037 ns     60712830 ns           24 M=1000 N=1000 items_per_second=32.831M/s num_threads=2
BM_OpenMP_timewaste_parallel/N:1000/M:1000/num_threads:3/real_time   21255306 ns     63475749 ns           33 M=1000 N=1000 items_per_second=47.0471M/s num_threads=3
BM_OpenMP_timewaste_parallel/N:1000/M:1000/num_threads:4/real_time   30377114 ns     67881475 ns           22 M=1000 N=1000 items_per_second=32.9195M/s num_threads=4
```
