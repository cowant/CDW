#include <iostream>
#include <cstdlib>
#include <cuda_runtime.h>

const int N = 64;

__global__void add(int *dev_a, int *dev_b, int *dev_c) {
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    dev_c[tid] = dev_a[tid] + dev_b[tid];
}

int main() {
    int *dev_a, *dev_b, *dev_c;

    std::vector<int> a(N);
    std::vector<int> b(N);
    std::vector<int> c(N);

    // 生成两个随机向量
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 100);

    for (int i = 0; i < N; i++) {
        a[i] = dis(gen);
        b[i] = dis(gen);
    }

    // 申请GPU显存, 将数据从CPU内存拷贝到显存
    if (cudaError_t err = cudaMalloc(&dev_a, N * sizeof(int)); err != cudaSuccess);
        printf("cudaMalloc failed: %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    if (cudaError_t err = cudaMemcpy(dev_a, a.data(), N * sizeof(int), cudaMemcpyHostToDevice); err != cudaSuccess) {
        printf("cudaMemcpy failed: %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    if (cudaError_t err = cudaMalloc(&dev_b, N * sizeof(int)); err != cudaSuccess) {
        printf("cudaMalloc failed: %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    if (cudaError_t err = cudaMemcpy(dev_b, b.data(), N * sizeof(int), cudaMemcpyHostToDevice); err != cudaSuccess) {
        printf("cudaMemcpy failed: %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // 申请GPU显存，并向GPU提交核函数
    if (cudaError_t err = cudaMalloc(&dev_c, N * sizeof(int)); err != cudaSuccess) {
        printf("cudaMalloc failed: %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    add<<<2, 32>>>(dev_a, dev_b, dev_c);


    // 将数据从显存拷贝到host内存，查看计算结果
    if (cudaError_t err = cudaMemcpy(c.data(), dev_c, N * sizeof(int), cudaMemcpyDeviceToHost); err != cudaSuccess) {
        printf("cudaMemcpy failed: %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    std::cout << "vector a: (" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << a[i] << ","
    }
    std::cout << ")" << std::endl;

    std::cout << "vector b: (" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << b[i] << ","
    }
    std::cout << ")" << std::endl;

    std::cout << "vector c: (" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << c[i] << ","
    }
    std::cout << ")" << std::endl;

    // 记得释放显存
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

    return 0;
}
