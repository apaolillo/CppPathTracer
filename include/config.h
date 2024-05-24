#pragma once

#define FALSE   0
#define TRUE    1

#define THREAD_IMPL_NAIVE               1
#define THREAD_IMPL_OPENMP_BLOCKS       2
#define THREAD_IMPL_OPENMP_PER_PIXEL    3

#define TRIANGLE_INTERSECTION_MOLLER_TRUMBORE   1
#define TRIANGLE_INTERSECTION_CRAMMER           2

#define AABB_HIT_NAIVE              1
#define AABB_HIT_BRANCHLESS         2
#define AABB_HIT_BRANCHLESS_VECTOR  3

#if __has_include("../custom_config.h")
#include "../custom_config.h"
#endif

#ifndef WORK_SQUARE_SIZE
#define WORK_SQUARE_SIZE 1
#endif

#ifndef MAX_SAMPLE_OUTPUT_COLOR
#define MAX_SAMPLE_OUTPUT_COLOR 20
#endif

#ifndef THREADING_IMPLEMENTATION
#define THREADING_IMPLEMENTATION THREAD_IMPL_OPENMP_BLOCKS
#endif

#ifndef USE_COLOR_BUFFER_PER_THREAD
#define USE_COLOR_BUFFER_PER_THREAD FALSE
#endif

#ifndef ENABLE_PROGRESS_INDICATOR
#define ENABLE_PROGRESS_INDICATOR TRUE
#endif

#ifndef TRIANGLE_INTERSECTION_ALGO
#define TRIANGLE_INTERSECTION_ALGO TRIANGLE_INTERSECTION_MOLLER_TRUMBORE
#endif

#ifndef AABB_HIT_IMPLEMENTATION
#define AABB_HIT_IMPLEMENTATION AABB_HIT_BRANCHLESS_VECTOR
#endif

#ifndef BVH_FIRST_HIT_CACHING
#define BVH_FIRST_HIT_CACHING FALSE
#endif

#ifndef BVH_SAH
#define BVH_SAH TRUE
#endif