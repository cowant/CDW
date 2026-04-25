#include <iostream>
#include <cuda_runtime.h>

int main() {
    void *ptrs[5];

    for (int i = 0; i < 5; i++) {
        cudaMalloc(&ptrs[i], 1);
        printf("cudaMalloc allocate GPU memory at %p\n", ptrs[i]);
    }

    for (int i = 0; i < 5; i++) {
        cudaFree(ptrs[i]);
    }

    return 0;
}
