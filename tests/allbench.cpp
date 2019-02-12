
#include <random>

#include <cstdint>
#include <chrono>
#include <ctime>
#include <thread>

#include <omp.h>

#include <benchmark/benchmark.h>

#include "benchhelper.h"

inline long double waste_time(uint64_t i, uint64_t M){
	for(uint64_t j = 0;j<M;++j){
		pow((long double)i, (long double)2.34868);
	}
}

void waste_time_parallel(uint64_t N, uint64_t M){
	#pragma omp parallel for
	for(uint64_t i = 0; i < N; i++) {
		waste_time(i, M);
	}
}

static void BM_OpenMP_timewaste_parallel(benchmark::State& state) {
  int N = state.range(0);
  int M = state.range(1);
  int num_threads = state.range(2);

	omp_set_num_threads(num_threads);

  for (auto _ : state) {
    waste_time_parallel(N, M);
  }
  state.SetItemsProcessed(state.iterations()*int64_t(N)*int64_t(M));

  //TEARDOWN
  state.counters["N"] = N;
  state.counters["M"] = M;
  state.counters["num_threads"] = num_threads;
}

#define TOTAL_N 1000
#define TOTAL_M 1000

BENCHMARK(BM_OpenMP_timewaste_parallel)->UseRealTime()->ArgNames({"N", "M", "num_threads"})
	->Args({TOTAL_N,TOTAL_M,1})
	->Args({TOTAL_N,TOTAL_M,2})
	->Args({TOTAL_N,TOTAL_M,3})
	->Args({TOTAL_N,TOTAL_M,4})
	;
