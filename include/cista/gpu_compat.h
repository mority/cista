#pragma once

#if defined(__HIP__) || defined(__CUDA_ARCH__)
#define CISTA_GPU_COMPAT __host__ __device__
#define CISTA_GPU_DEVICE_COMPAT __device__
#else
#define CISTA_GPU_COMPAT
#define CISTA_GPU_DEVICE_COMPAT
#endif
