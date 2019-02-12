
#include "naivelinalg.h"

#include "basic.h"

#include "multiply.h"
#include "transpose.h"
#include "openmp.h"

#include "best_tile_size.h"
#ifndef BEST_TILE_SIZE
#define BEST_TILE_SIZE -1
#endif

#include <random>

#include <chrono>
#include <ctime>
#include <thread>

#include <omp.h>

#include <benchmark/benchmark.h>

#include "benchhelper.h"

static void BM_OpenMP_primes_parallel(benchmark::State& state) {
  int N = state.range(0);
  int n_warmup = 3;
  int num_threads = state.range(1);

	//SETUP
	bool* A = (bool*)malloc(N*sizeof(bool));

	//warmup
	for(int i = 0;i<n_warmup;i++){
		primes_warmup(A,N);
	}


  for (auto _ : state) {
    auto start = std::chrono::high_resolution_clock::now();
  	omp_set_num_threads(num_threads);
	primes_parallel(A, N);
    auto end   = std::chrono::high_resolution_clock::now();

    auto elapsed_seconds =
      std::chrono::duration_cast<std::chrono::duration<double>>(
        end - start);



    state.SetIterationTime(elapsed_seconds.count());
  }
  state.SetItemsProcessed(state.iterations()*int64_t(N));

  //TEARDOWN
  free(A);
  state.counters["N"] = N;
  state.counters["num_threads"] = num_threads;
}
BENCHMARK(BM_OpenMP_primes_parallel)->UseManualTime()->ArgNames({"N", "num_threads"})->Args({SQUARES_SIZE,2})
	->Args({SQUARES_SIZE,4});
