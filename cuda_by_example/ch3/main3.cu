#include <iostream>
#include "cuda_runtime.h"

int main() {
    int count = 0;
    if (cudaError_t err = cudaGetDeviceCount(&count); err == cudaSuccess) {
        printf("device count: %d\n", count);
    } else {
        printf("cudaGetDeviceCount error: %s\n", cudaGetErrorString(err));
    }

    for (int i = 0; i < count; i++) {
        cudaDeviceProp prop;
        if (cudaError_t err = cudaGetDeviceProperties(&prop, i); err == cudaSuccess) {
            printf("--- general information for device %d ---\n", i);
            printf("name: %s\n", prop.name);
            printf("major.minor: %d.%d\n", prop.major, prop.minor);
            printf("totalGlobalMem: %lu\n", prop.totalGlobalMem);
            printf("totalConstMem: %lu\n", prop.totalConstMem);
            printf("sharedMemPerBlock: %lu\n", prop.sharedMemPerBlock);
            printf("multiProcessorCount: %d\n", prop.multiProcessorCount);
            printf("maxThreadsPerBlock: %d\n", prop.maxThreadsPerBlock);
            printf("maxThreadsDim[0]: %d\n", prop.maxThreadsDim[0]);
            printf("maxThreadsDim[1]: %d\n", prop.maxThreadsDim[1]);
            printf("maxThreadsDim[2]: %d\n", prop.maxThreadsDim[2]);
            printf("maxGridSize[0]: %d\n", prop.maxGridSize[0]);
            printf("maxGridSize[1]: %d\n", prop.maxGridSize[1]);
            printf("maxGridSize[2]: %d\n", prop.maxGridSize[2]);
            printf("warpSize: %d\n", prop.warpSize);
            printf("deviceOverlap: %d\n", prop.deviceOverlap);
        } else {
            printf("cudaGetDeviceProp error: %s\n", cudaGetErrorString(err));
        }
    }

    return 0;
}
