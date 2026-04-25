#### hello cuda

```cpp
// ch3/main1.cu
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
```

#### cudaMalloc函数

`cudaMalloc`是CUDA编程中用于在GPU显存（Device Memory）上分配空间的函数，类似于C语言中的malloc。

**1. 函数原型**

```cpp
cudaError_t cudaMalloc(void** devPtr, size_t size);
```

**2. 参数拆解（为什么是二级指针？）**

这是初学者最容易困惑的地方：

- **devPtr (void**)：** 这是一个指向指针的指针。
  - **原理：** 在C语言中，如果你想让一个函数修改一个指针变量的值（即改变它指向的地址），你必须传递该指针的地址。
  - **操作：** cudaMalloc会在GPU上找一块空地，然后把这块地的“门牌号”（地址）写回到你提供的指针变量里。
- **size (size_t)：** 需要分配的内存大小（字节）。通常建议使用**N * sizeof(类型)**。

**3. 返回值**

返回`cudaError_t`枚举值。

- 如果成功，返回`cudaSuccess`。
- 如果显存不足，返回`cudaErrorMemoryAllocation`。

**4. 核心规则与注意事项**

- **不可直接读写：** `cudaMalloc`分配的地址属于`GPU`空间。绝对不能在`CPU`代码里直接解引用（**如 \*d_ptr = 5.0f**），这会导致程序崩溃（Segmentation Fault）。必须通过`cudaMemcpy`传输数据。
- **生命周期：** 显存不会在函数结束时自动回收。只要程序没退出且没调用`cudaFree`，这块显存就会一直被占用。
- **内存对齐：** `cudaMalloc`自动执行设备内存对齐（通常是`256`字节），以确保`GPU`并行访问时的最高效率。
- **初始化：** `cudaMalloc`只分配空间，不负责清零。如果需要初始化为`0`，请配合使用**cudaMemset**。

#### GPU内存对齐

NVIDIA在CUDA编程指南中明确指出，由`cudaMalloc`或`cudaMallocPitch`分配的线性内存保证至少按`256`字节对齐。可以用一个例子验证。

```cpp
// ch3/main2.cu
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
```

运行结果：
```bash
cudaMalloc allocate GPU memory at 0x7fbfef000000
cudaMalloc allocate GPU memory at 0x7fbfef000200
cudaMalloc allocate GPU memory at 0x7fbfef000400
cudaMalloc allocate GPU memory at 0x7fbfef000600
cudaMalloc allocate GPU memory at 0x7fbfef000800
```

可以看到地址值都是256的倍数。

**为什么是256字节？**

这主要与 GPU 的合并访问 (Memory Coalescing) 机制有关：

- **硬件限制：** GPU的内存控制器在读取显存时，通常是以128字节或256字节为一个 Segment（段） 进行操作的。
- **效率最大化：** 如果起始地址是对齐的，一个线程束（Warp，32个线程）访问连续数据时，可以被合并成最少次数的内存事务。如果不对齐，可能会跨越两个 Segment，导致访问效率减半。

#### cudaMemcpy函数

`cudaMemcpy`是CUDA编程中最重要的内存管理函数，用于在**主机（Host/CPU）** 和**设备（Device/GPU）** 之间，或者**两个设备**之间传输数据。

**1. 函数原型**

```cpp
cudaError_t cudaMemcpy(void* dst, const void* src, size_t count, cudaMemcpyKind kind);
```

**2. 参数详细说明**
- dst (Destination): 目标内存地址。
- src (Source): 源内存地址。
- count: 复制数据的字节数（Byte），通常使用 N * sizeof(T) 计算。
- kind: 指定传输的方向，这是一个枚举值：
  - **cudaMemcpyHostToDevice:** 从 CPU 内存拷贝到 GPU 显存。
  - **cudaMemcpyDeviceToHost:** 从 GPU 显存拷贝回 CPU 内存。
  - **cudaMemcpyDeviceToDevice:** 在两个 GPU 显存地址之间拷贝。
  - **cudaMemcpyDefault:**（CUDA 4.0+ 支持）根据指针地址自动识别方向（需要统一虚拟寻址 UVA）。

**3. 核心行为特征**
- **同步执行 (Synchronous)：** `cudaMemcpy`是阻塞同步的。这意味着在数据拷贝完成之前，CPU线程会一直停在这一行代码处等待，不会向下执行。
**隐式同步：** 它不仅等待当前的拷贝完成，还会确保之前发出的所有GPU指令（如核函数）执行完毕后才开始拷贝。
**错误检查：** 函数返回`cudaError_t`。如果操作成功返回`cudaSuccess`，否则会返回错误码（如 `cudaErrorInvalidValue`代表参数错误）。

#### cuda核函数的__global__声明是什么意思

在CUDA编程中，`__global__`是一个函数类型限定符，用于声明一个核函数 (Kernel)。

它的核心含义可以概括为：**“在CPU上调用，在GPU上执行”**。 

**1. 主要特点**
- **执行与调用：** 被`__global__`修饰的函数由主机端（Host/CPU）代码调用，但在设备端（Device/GPU）上并行运行。
- **返回类型：** 必须返回`void`，不能有其他返回值。
- **异步性：** 在主机端调用核函数后，控制权会立即返回给主机程序，而不需要等待GPU执行完毕。

**2. 调用语法**

调用`__global__`函数时，必须使用特殊的执行配置语法<<<...>>>来指定线程的组织方式（如线程块和网格的大小）。

```cpp
// 定义核函数
__global__ void myKernel(float* data) {
    // 在 GPU 上执行的逻辑
}

// 在 CPU 上调用
myKernel<<<gridSize, blockSize>>>(d_data);
```

**3. 与其他限定符的区别**

为了更好地理解，可以将其与 __device__ 和 __host__ 进行对比：

|限定符 	|执行位置	|调用位置	|常见用途|
|:--|:--|:--|:--|
|**__global__**|	GPU|	CPU|	整个并行任务的入口（核函数）|
|**__device__**|GPU	|GPU	|仅限 GPU 内部调用的子函数|
|**__host__**	|CPU	|CPU	|普通的 C++ 函数（默认缺省）|

**4. 使用限制**

- `__global__`函数内部只能访问GPU的内存（如全局显存、共享内存等），不能直接访问CPU的内存。
- 函数参数通常通过常量内存传递到 GPU，大小有一定限制。

#### cudaGetDeviceProperties

在CUDA编程中，`cudaGetDeviceProperties`是一个非常关键的`Runtime API`函数，用于获取指定GPU设备的硬件详细参数和功能特性。

**1. 函数原型**

```cpp
cudaError_t cudaGetDeviceProperties(struct cudaDeviceProp *prop, int device);
```

**2. 核心结构体`cudaDeviceProp`**

`cudaDeviceProp`结构体包含了数十个成员变量，以下是开发者最常关注的核心属性：

- **设备基础信息**
  - **char name[256]:** 设备的 ASCII 字符串名称（例如 "NVIDIA GeForce RTX 4090"）。
  - **int major, minor:** 计算能力（Compute Capability）的主、次版本号（例如 8.9）。
- **内存资源**
  - **size_t totalGlobalMem:** 设备上全局内存的总量（字节）。
  - **size_t sharedMemPerBlock:** 每个线程块可用的最大共享内存大小。
  - **size_t totalConstMem:** 设备上常量内存的总量。
- **计算资源**
  - **int multiProcessorCount:** 设备上流多处理器(SM)的数量。
  - **int maxThreadsPerBlock:** 每个线程块(Block)允许的最大线程数（通常为 1024）。
  - **int maxThreadsDim[3]:** 线程块(Block)各维度的最大限制。
  - **int maxGridSize[3]:** 网格(Grid)各维度的最大限制。
- **其他特性**
  - **int warpSize:** 线程束（Warp）的大小（目前 NVIDIA 设备统一为 32）。
  - **int deviceOverlap:** 是否支持在执行核函数的同时进行内存拷贝（异步并发）。 

**3. 示例**

**ch3/main3.cu**

```cpp
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
```

运行结果：

```bash
# nvcc  main3.cu   -arch=sm_80   
# ./a.out 
device count: 1
--- general information for device 0 ---
name: NVIDIA GeForce RTX 3080 Ti
major.minor: 8.6
totalGlobalMem: 12489195520
totalConstMem: 65536
sharedMemPerBlock: 49152
multiProcessorCount: 80
maxThreadsPerBlock: 1024
maxThreadsDim[0]: 1024
maxThreadsDim[1]: 1024
maxThreadsDim[2]: 64
maxGridSize[0]: 2147483647
maxGridSize[1]: 65535
maxGridSize[2]: 65535
warpSize: 32
deviceOverlap: 1
```

#### cudaDeviceProp的成员中哪些与thread index的计算有关？

在`CUDA`编程中，`blockIdx、blockDim和threadIdx`是在内核函数（Kernel）中使用的运行时变量，而`cudaDeviceProp`结构体则定义了硬件设备所能支持的最大限制。

以下是它们之间的对应关系及其在`cudaDeviceProp`结构体中的成员：

**1. blockDim对应的限制**

blockDim表示你实际启动的线程块大小。它受限于硬件允许的每块最大线程数和各维度的最大值。

- **maxThreadsPerBlock:** 单个线程块中允许包含的最大线程总数（通常为 1024）。
- **maxThreadsDim[3]:** 线程块在x,y,z三个维度上分别允许的最大尺寸，通常是(1024\*1024\*64)，实际应用中我们要保证Block这三个维度的乘积不能超过`maxThreadsPerBlock`。

**2. gridDim (与 blockIdx 相关) 的限制**

虽然`blockIdx`是当前块的索引，但它的取值范围由`gridDim`决定，而`gridDim`的上限由以下成员定义：
- **maxGridSize[3]:** 网格在x,y,z三个维度上分别允许启动的最大线程块数量。
  - 通常x维度的限制非常大（如$2^{31} - 1$），而y和z维度较小（如 65535）。

**3. threadIdx相关的其他硬件参数**

threadIdx 本身没有直接对应的“成员”，但它的执行效率与以下硬件属性密切相关：
- **warpSize:** 线程束大小（恒为 32）。这决定了`threadIdx`如何被分组执行。为了性能，通常建议`blockDim`是`warpSize`的整数倍。
- **regsPerBlock:** 每个线程块可用的寄存器总数。如果你每个线程（由`threadIdx`标识）使用的寄存器太多，可能会导致你无法启动 `blockDim`所要求的线程数。
- **sharedMemPerBlock:** 每个线程块可用的共享内存总量。这是同个块内所有线程（threadIdx 0 到 blockDim-1）共同分享的资源。

#### 启动核函数的func<<<x,y>>>语法中，x和y指的是什么

在CUDA的核函数启动语法`kernel<<<x, y>>>`中:
- `x`代表网格维度（Grid Dimensions），即线程块（Block）的数量
- `y`代表线程块维度（Block Dimensions），即每个块中线程（Thread）的数量。

由于现代GPU多基于`Compute Capability 2.0`及以上架构，以下是这些参数在三维坐标系（x, y, z）中的最大限制值：

**1. 线程块维度 (Block Dimensions) — y 的限制**

`y`对应的是`blockDim`。虽然你可以传入一个整数，但它本质上是`dim3`结构。
- **单维最大值：** x=1024, y=1024, z=64。
- **总数限制：** 一个线程块内的线程总数（x × y × z）不能超过 1024。
  - 示例：如果你设置 y 为 1024，那么该块在其他维度上的大小必须为 1。


**2. 网格维度 (Grid Dimensions) — x 的限制**

`x`对应的是`gridDim`。
- **`x`维度最大值：** $2^{31}-1$(即 2,147,483,647)。
- **y 和 z 维度最大值：** 65535。
- **注意：** 在非常早期的架构（Compute Capability 1.x）中，`x`维度的最大值也仅为65535。

**实用建议：**
虽然硬件允许很大值，但在性能调优时，线程块大小（`y`）通常设置为`32`的倍数（如 128, 256 或 512），以对齐`Warp`（线程束） 执行单元，从而获得最佳效率。

#### 向量加法

**ch4/main1.cu**

```cpp
#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include "cuda_runtime.h"

const int N = 32;

__global__ void add(int *dev_a, int *dev_b, int *dev_c) {
    if (int tid = blockDim.x * blockIdx.x + threadIdx.x; tid < N) {
        dev_c[tid] = dev_a[tid] + dev_b[tid];
    }
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
    if (cudaError_t err = cudaMalloc(&dev_a, N * sizeof(int)); err != cudaSuccess) {
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
    add<<<1, 32>>>(dev_a, dev_b, dev_c);


    // 将数据从显存拷贝到host内存，查看计算结果
    if (cudaError_t err = cudaMemcpy(c.data(), dev_c, N * sizeof(int), cudaMemcpyDeviceToHost); err != cudaSuccess) {
        printf("cudaMemcpy failed: %s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    std::cout << "vector a: (" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << a[i] << ",";
    }
    std::cout << ")" << std::endl;

    std::cout << "vector b: (" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << b[i] << ",";
    }
    std::cout << ")" << std::endl;

    std::cout << "vector c: (" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << c[i] << ",";
    }
    std::cout << ")" << std::endl;

    // 记得释放显存
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);

    return 0;
}
```

运行结果：

```bash
# nvcc main1.cu -arch=sm_120    
# ./a.out 
vector a: (
85,9,58,3,64,31,27,40,78,33,26,21,53,20,87,30,57,51,17,13,89,41,92,99,83,19,30,8,80,99,78,6,)
vector b: (
21,15,23,29,11,69,41,90,80,98,2,87,94,12,39,6,37,89,2,50,15,61,91,94,28,6,33,82,2,30,31,61,)
vector c: (
106,24,81,32,75,100,68,130,158,131,28,108,147,32,126,36,94,140,19,63,104,102,183,193,111,25,63,90,82,129,109,67,)
```

#### __syncthreads

在 CUDA 编程中，__syncthreads() 是一个线程块级的同步屏障（Barrier Synchronization）。
简单来说，它的作用是：“集合，点名，等齐了再出发。”
以下是它的核心要点和使用场景：
1. 基本功能
当一个线程执行到 __syncthreads() 指令时，它会暂停执行，直到同一个线程块（Thread Block）中的所有线程都到达这个位置。只有当块内最后一个线程也到达了该指令，所有线程才会被释放，继续执行后面的代码。
2. 为什么需要它？（核心用途）
在并行计算中，线程之间的执行速度是不一致的。__syncthreads() 主要用于解决数据竞争（Data Race）和确保内存一致性：

* 防止“读早了”：如果线程 A 要读线程 B 计算出的结果，线程 A 必须等待，直到确定线程 B 已经把数据写进了共享内存（Shared Memory）。
* 防止“写早了”：如果线程 A 要覆盖某个共享变量，必须等所有需要读取该变量旧值的线程都读完。

3. 典型代码结构
它通常配合 __shared__ 内存使用。最经典的模式是：

   1. 所有线程从全局内存加载数据到共享内存。
   2. 调用 __syncthreads()（确保所有数据都搬运完了）。
   3. 所有线程从共享内存读取数据并进行计算。
   4. 再次调用 __syncthreads()（确保计算完成，准备写回或进行下一步）。

4. 致命误区：条件分支中的死锁
这是初学者最容易犯的错误。绝对不能将 __syncthreads() 放在可能导致部分线程无法到达的条件分支中。
错误示例：

```cpp
if (tid < 16) {
    // 只有前16个线程能运行到这里
    __syncthreads(); 
} else {
    // 剩下的线程永远到不了上面的同步点
}
```

后果：GPU 会发生死锁（Deadlock）。硬件会一直等待那些永远不会到达同步点的线程，导致整个程序卡死或报错。
5. 性能影响

* 等待开销：同步会强制执行快的线程等待执行慢的线程，过多使用会降低硬件利用率。
* 范围限制：它只能同步同一个线程块内的线程。如果你需要同步不同线程块之间的线程，通常需要结束当前的 Kernel 启动，或者使用更高级的 cooperative_groups。

#### 常量内存(\_\_constant\_\_)

初学者的错误使用：

```cpp
#include <random>
#include <limits>
#include <opencv2/opencv.hpp>
#include "cuda_runtime.h"
#include "math_constants.h"


#define DIM 1024
#define N 40

struct Sphere {
    float x0 = 0.0;
    float y0 = 0.0;
    float z0 = 0.0;
    float radius = 0.0;

    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    __device__ float hit(float x, float y, float *n) {
        float dx = x - x0;
        float dy = y - y0;

        if (dx * dx + dy * dy < radius * radius) {
            float dz = sqrtf(radius * radius - dx * dx - dy * dy);
            *n = dz / radius;
            return dz + z0;
        }
        return -CUDART_INF_F;
    }
};

__constant__ Sphere s_dev[N]; 

__global__ void kernel(Sphere *s, uchar* ptr) {
    int x = threadIdx.x + blockDim.x * blockIdx.x;
    int y = threadIdx.y + blockDim.y * blockIdx.y;
    int offset = x + blockDim.x * gridDim.x * y;

    float maxz = -CUDART_INF_F;
    float r = 0.0, g = 0.0, b = 0.0;
    float x_norm = x - DIM/2;
    float y_norm = y - DIM/2;
    for (int i = 0; i < N; i++) {
        float scale = 0.0;
        if (float z = s[i].hit(x_norm, y_norm, &scale); z > maxz) {
            r = s[i].r * scale;  
            g = s[i].g * scale;  
            b = s[i].b * scale;  
            maxz = z;
        }
    }

    ptr[offset * 4 + 0] = static_cast<uchar>(b * 255);
    ptr[offset * 4 + 1] = static_cast<uchar>(g * 255);
    ptr[offset * 4 + 2] = static_cast<uchar>(r * 255);
    ptr[offset * 4 + 3] = 255;
}

int main() {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<float> dis(0.0f, 1.0f); 

    Sphere *s_host = new Sphere[N];
    for (int i = 0; i < N; i++) {
        s_host[i].r = dis(gen);
        s_host[i].g = dis(gen);
        s_host[i].b = dis(gen);
        s_host[i].x0 = dis(gen) * 1000.0f - 500.0f;
        s_host[i].y0 = dis(gen) * 1000.0f - 500.0f;
        s_host[i].z0 = dis(gen) * 1000.0f - 500.0f;
        s_host[i].radius = dis(gen) * 100.0f + 20.0f;
    }

    if (cudaError_t err = cudaMemcpyToSymbol(s_dev, s_host, sizeof(Sphere) * N); err != cudaSuccess) {
        printf("%s%d%s: %s\n", __FILE__, __LINE__, __func__, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    cv::Mat bgraImg(cv::Size(DIM, DIM), CV_8UC4);

    uchar *rawData = nullptr;
    if (cudaError_t err = cudaMalloc(&rawData, bgraImg.total() * bgraImg.elemSize()); err != cudaSuccess) {
        printf("%s:%d:%s: cuMalloc error: %s\n", __FILE__, __LINE__, __func__, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    dim3 grid(DIM/16, DIM/16);
    dim3 block(16, 16);
    kernel<<<grid, block>>>(s_dev, rawData);

    if (cudaError_t err = cudaMemcpy(bgraImg.data, rawData, bgraImg.total() * bgraImg.elemSize(), cudaMemcpyDeviceToHost); err != cudaSuccess) {
        printf("%s:%d:%s: cuMalloc error: %s\n", __FILE__, __LINE__, __func__, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    free(s_host);
    cudaFree(rawData);

    cv::imwrite("ray_trace_v1.png", bgraImg);


    return 0;
}
```

上面代码里面的`s_dev`虽然是在全局作用域定义的`__constant__`数组，但在主机端`(Host)`代码中直接使用`s_dev`作为参数传递，编译器会尝试获取它在主机端的符号地址或抛出错误。

- **后果：** 在`CUDA`中，你不能直接把`__constant__`变量名作为设备指针传给核函数。这通常会导致核函数内部访问到非法地址，从而渲染出一张全黑的图或导致驱动程序报错。
- **修正方案：** 既然已经定义了全局的`__constant__ Sphere s_dev[N];`，核函数内部应该直接使用`s_dev`，而不是通过参数`Sphere *s`接收。

##### 为什么不能直接把 \_\_constant\_\_ 变量名作为设备指针传给核函数

简单来说，这是因为 `__constant__` 变量在 GPU 里的“门牌号”（寻址方式）和普通指针完全不是一个体系。
直接传递变量名会失败，核心原因有三点：

###### 它们不在同一个地址空间

- **普通指针：** 指向的是`Global Memory`（全局显存），使用的是通用地址空间。
- **__constant__：** 存储在GPU特有的`Constant Bank`（常量存储库） 中。

如果你把`__constant__`变量名传给核函数，编译器会尝试把它当成一个普通显存地址。但在执行时，核函数去全局显存里找这个地址，自然会发现“查无此人”，导致 Illegal Memory Access。

###### 硬件指令不同

GPU 访问这两种内存时，发的“指令”是不一样的：

- **访问指针：** 使用的是 LD（Load）指令，像是在大仓库里根据地址搬货。
- **访问常量：** 编译器会生成专门的 LDC（Load Constant）指令。这种指令会触发硬件的广播机制，让 Warp 里的 32 个线程一次性读完数据。

如果你通过指针传参，编译器就没法提前知道你要访问常量区，也就没法生成高效的 LDC 指令。

###### 主机端的变量名只是个“符号”

在Host端代码里，`__constant__ Sphere s_dev[N]`中的`s_dev`只是一个符号（Symbol），它在主机端内存里没有合法的设备地址。

- 当你写`kernel<<<...>>>(s_dev)`时，你传过去的既不是有效的主机地址，也不是有效的设备地址，而是一个编译器无法在运行时正确转换的标识符。

##### 那如果我在主机端打印constant变量的地址，那这个地址代表啥

在主机端打印`__constant__`变量的地址，结果往往会让你困惑，因为它代表的意义取决于你如何取地址：

###### 如果直接 printf("%p", &s_dev);

你会得到一个主机端（Host）的虚拟内存地址。

- **含义：** 这个地址仅仅是编译器在主机端为这个“符号”预留的一个占位符。
- **能用吗？：** 绝对不能。如果你把这个地址传给核函数，核函数在GPU上访问这个地址，就像是在北京拿着上海的地图找路，会直接导致程序崩溃。

###### 为什么它不是设备地址？

CUDA的设计逻辑是内存空间隔离。`__constant__`变量在编译阶段就被标记为属于“常量地址空间”。

* 在主机端，它只是一个符号（Symbol）。
* 物理上，它的数据存储在 GPU 内部极其有限的（通常 64KB）专用缓存硬件中，而不是普通的显存条上。

###### 如何获取它在“设备端”的真正地址？

如果你非要获取它在设备端的地址（虽然不推荐这样做），必须使用专用函数：

```cpp
void* devPtr;
cudaGetSymbolAddress(&devPtr, s_dev); 
printf("设备端地址: %p", devPtr);
```

- **这个地址代表啥？：** 这代表该变量在 GPU 常量内存段中的偏移量/物理地址。
- **能传给核函数吗？：** 可以传，但核函数会把它当成普通`Global Memory`指令处理，从而失去常量内存的广播加速特性，性能大幅下降。

###### 总结

你直接打印出的地址只是一个影子（主机端符号地址）。它在 GPU 硬件中没有任何意义，这就是为什么直接传参会报错的根本原因。


##### cudaMemcpyToSymbol

既然你对底层原理这么感兴趣，想了解一下`cudaMemcpyToSymbol`是如何通过这个“符号”定位到 GPU 硬件内存的吗？

`cudaMemcpyToSymbol`的工作原理其实有点像“查表映射”。它之所以不需要你提供设备地址就能精准定位，是因为 编译器 和 驱动程序 在背后达成了一项秘密协议。

以下是它的工作流程：

###### 编译阶段：打标签

当你定义 `__constant__ Sphere s_dev[N]`时，编译器（nvcc）并不知道它在 GPU 上的具体物理地址。

* 它会在生成的 ELF 格式的可执行文件（或 PTX/fatbin 文件）中创建一个符号表。
* 这个表里记录了：变量名（s_dev）、大小（sizeof(Sphere)*N）以及它属于“常量内存段”的属性。

###### 载入阶段：分配空间

当你的程序启动并初始化 CUDA Context 时，驱动程序会将 fatbin 载入 GPU。

* 驱动程序会根据符号表的要求，在 GPU 物理硬件的 64KB 常量区 划出一块地。
* 关键点：此时，驱动程序会建立一个映射：“符号 s_dev 对应 常量区偏移量 0x1234”。

###### 调用阶段：按名寻访

当你调用`cudaMemcpyToSymbol(s_dev, s_host, ...)`时：

   1. 查找符号：驱动程序在内存中的符号表里搜索字符串 "s_dev"。
   2. 获取偏移：查到它对应的物理偏移地址（比如 0x1234）。
   3. 发送指令：通过 PCIe 总线发送一个特殊的“写常量内存”请求。
   4. 硬件写入：GPU 接收到请求，直接将数据写入专用常量缓存中。

###### 为什么它比 cudaMemcpy 更“聪明”？

普通的 cudaMemcpy 需要你手动告诉它 “去哪（地址）”。
而 cudaMemcpyToSymbol 是 “去叫某某某的地方”。驱动程序充当了管家，帮你把“变量名”翻译成了 GPU 硬件能理解的内部地址。

###### 避坑指南

这也是为什么你不能在主机端直接打印 &s_dev。

* &s_dev 在主机端代码编译时，由于它在 C++ 语法里看起来像个全局变量，链接器会随便给它分一个 主机端 的虚拟地址，仅用于占位。
* 而 cudaMemcpyToSymbol 内部并不是直接使用这个主机地址，而是通过 宏定义或特殊的模板重载 提取了这个变量的“符号名”，再交给驱动去查表。

总结：它是一套基于符号名映射的专用通道，避开了普通指针的动态寻址逻辑，从而确保数据能准确送进那块专用的 64KB 高速缓存。


##### 为什么常量内存比全局内存快？

常量内存（Constant Memory）之所以在特定场景下比全局内存（Global Memory）快得多，主要源于硬件架构设计上的三级跳：

###### 专属的“广播机制”（Warp Broadcast）

这是常量内存最核心的性能优势。

- **全局内存：** 当一个 Warp（32个线程）读取 32 个不同的地址时，硬件需要进行复杂的访存合并（Coalescing）。如果 32 个线程读取同一个地址，硬件通常还是会走标准的 L1/L2 缓存路径。
- **常量内存：** 它有一种专用的广播硬件。如果 Warp 内所有线程请求的是同一个常量内存地址，硬件只需要执行一次读取操作，就可以直接将这个值“广播”给所有 32 个线程。这只需要 1 个时钟周期。

###### 专门的常量缓存（Constant Cache）

常量内存不仅仅是内存空间，它在 GPU 核心（SM）内部有独立的 L1 缓存。

- **不争抢空间：** 普通全局内存的读取会占用通用的 L1/L2 缓存。如果你的程序访存密集，通用缓存会频繁发生“换入换出”（Cache Miss）。
- **极高的命中率：** 由于常量内存只有 64KB 且数据只读，它的专用缓存设计得非常精简且高效。一旦数据进入缓存，后续所有 Warp 的访问几乎都是零延迟。

###### 指令层面的优化（LDC 指令）

- **全局内存：** 使用的是 LD (Load) 指令。这种指令需要经过完整的地址计算、缓存一致性检查和内存控制器调度。
- **常量内存：** 编译器会生成专门的 LDC (Load Constant) 指令。在 GPU 指令流水线中，LDC 指令可以在解析阶段就直接从 SM 内部的常量控制器获取数据，路径比去显存找数据短得多。

###### 这里的“快”是有前提的（重要！）

常量内存并不是在所有情况下都更快。它只有在满足以下条件时才表现卓越：

- **单地址广播：** Warp 里的 32 个线程必须在同一时刻访问同一个地址（比如你的球体 s_dev[i]，所有线程都在循环同一个 i）。
- **如果发生“地址分歧”：** 如果 32 个线程分别访问常量数组中 32 个不同的索引，常量内存的读取会被串行化。此时，它反而会比全局内存慢得多。

###### 总结

| 特性 | 全局内存 (Global) | 常量内存 (Constant) |
|---|---|---|
| 硬件缓存 | L1 / L2 通用缓存 | 专用的 Constant Cache |
| 访问模式 | 适合大规模、不同地址 | 适合全 Warp 读同一地址 |
| 读取速度 | 较慢（存在寻址延迟） | 极快（单周期广播） |
| 带宽压力 | 很大（需合并访存） | 很小（一次读取全员共享） |


##### 常量内存广播机制的硬件原理

要理解常量内存广播机制（Broadcast）的硬件原理，我们需要进入 GPU 的核心——流式多处理器（SM）内部。

在全局内存（Global Memory）访存中，硬件主要考虑的是“合并”；而在常量内存中，硬件主要考虑的是“分发”。

###### 硬件层级的“收发室”：常量指令控制器

在每个SM内部，都有一个专门处理常量内存请求的硬件单元，通常称为`Constant Controller`（常量控制器）。

- **普通访存路径：** 线程束（Warp）发出 32 个地址 -> 访存单元检查 L1/L2 -> 去显存取回数据 -> 分配回 32 个寄存器。
- **常量访存路径：** Warp 发出一个 LDC（Load Constant）指令。常量控制器拦截这个指令，它并不急着去取 32 个值，而是先看这 32 个线程请求的是不是同一个地址。

###### 广播的物理实现：单线对多点（Single-ported Access）

常量缓存（Constant Cache）在物理设计上通常是单端口的。这意味着它在一个时钟周期内只能读取一个 32 位（或 64 位）的值。

- **广播模式（理想状态）：**
当常量控制器发现32个线程都要读取`s_dev[5]`时，它只向常量缓存发起一次读取请求。拿到数据后，通过一套专门的内部总线（类似于电路里的“并联”结构），将这一个`32`位的数据同时拷贝到该`Warp`对应的32个寄存器槽位中。
    - **耗时：** 1个时钟周期。
    - **效率：** 极高，带宽利用率瞬间放大32倍。
- **串行化模式（最差状态）：**
如果32个线程分别请求`s_dev[0] 到 s_dev[31]`。由于硬件只有一个读取端口，控制器必须排队：第一周期读 s_dev[0] 给线程 0，第二周期读 s_dev[1] 给线程 1……
    - **耗时：** 32 个时钟周期。
    - **效率：** 比普通全局内存还要慢，因为全局内存至少还能尝试合并访存。

###### 与 L1 Cache 的设计差异

为什么全局内存的 L1 缓存不直接做成这种广播模式？

- **复杂度与功耗：** 全局内存 L1 缓存需要处理复杂的地址合并（Coalescing）、读写同步和缓存一致性。为了支持大吞吐量，它通常被设计成Multi-bank结构。
- **常量缓存的精简化：** 因为常量内存是只读的，它不需要考虑“数据写回”或“其他 SM 修改了数据导致我这里失效”的问题。硬件可以把所有的晶体管都用来优化“单一地址读取”和“广播电路”，从而做到极低的功耗和极高的单点速度。

###### 逻辑上的“拉”与硬件上的“推”

- **全局内存是“拉”：** 每个线程根据自己的指针去内存里“拉”回属于自己的数据。
- **常量内存是“推”：** 硬件检测到大家都要这个数，于是一个人去取，回来后“推”给所有人。

###### 为什么你的球体渲染适合它？

在你的程序循环里：
```cpp
for (int i = 0; i < N; i++) {
    s_dev[i].hit(...); // 每个线程都在算第 i 个球
}
```

当 GPU 执行到第 i=0 次循环时，整个 Warp 的 32 个线程都在请求 s_dev[0]。常量控制器大喊一声：“大家都要 0 号球的数据，我只取一次，大家接好！”这就是性能起飞的原因。

总结：广播机制本质上是利用了“只读”和“地址一致性”这两个前提，用最简单的单端口读取+同步分发电路，绕过了复杂的内存寻址逻辑。

##### 









