#pragma once

// Annotations that make a function usable from a GPU kernel, for both the
// CUDA and the HIP back ends.
//
// This replaces the older cista/cuda_check.h, whose CISTA_CUDA_COMPAT keyed
// off __CUDA_ARCH__ only. HIP never defines __CUDA_ARCH__; its device
// compilation pass is marked by __HIP_DEVICE_COMPILE__ instead, so functions
// annotated by that macro stayed host-only and became uncallable from HIP
// kernels.
//
// The two back ends also need the annotation at different times. nvcc only
// looks at device code in the device pass, so gating on __CUDA_ARCH__ leaves
// ordinary C++ translation units untouched. clang parses and type-checks
// __global__/__device__ bodies in the HIP *host* pass as well, and would
// report every call into an unannotated function there - so on HIP the
// annotation has to be present in both passes (__HIP__ rather than
// __HIP_DEVICE_COMPILE__).
//
// Either way, a translation unit built by a plain C++ compiler sees neither
// macro and the annotations expand to nothing, so headers using them still
// need no GPU compiler.

#if defined(__HIP__) || defined(__CUDA_ARCH__)
#define CISTA_GPU_DEVICE_COMPILE 1
#define CISTA_GPU_COMPAT __host__ __device__
#define CISTA_GPU_DEVICE_COMPAT __device__
#else
#define CISTA_GPU_COMPAT
#define CISTA_GPU_DEVICE_COMPAT
#endif
