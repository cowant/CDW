#include <iostream>
#include "cuda_runtime.h"

__global__ void add(int a, int b, int *c) {
    *c = a + b;
}

int main() {
    int c = 0;
    int *dev_c = nullptr;
    cudaError_t err2 = cudaMalloc(&dev_c, sizeof(int));
    if (err2 == cudaSuccess) {
        printf("cudaMalloc allocate GPU memory at: %p\n", dev_c);
    } else {
        printf("cudaMalloc Failed: %s\n", cudaGetErrorString(err2));
    }

    add<<<1,1>>>(2, 7, dev_c);
    cudaError_t err3 = cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
    if (err3 == cudaSuccess) {
        printf("cudaMemcpy copy data from GPU memory %p to host memory: %p\n", dev_c, &c); 
    } else {
        printf("cudaMemcpy Failed: %s\n", cudaGetErrorString(err3));
    }

    printf("cuda compute result: 2 + 7 = %d\n", c);

    cudaFree(dev_c);

    return 0;
}
