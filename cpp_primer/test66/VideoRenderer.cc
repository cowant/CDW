#include "VideoRenderer.h"
#include <iostream>
#include <vector> // 外部头文件不需要包含这些，减少了编译负担

VideoRenderer::~VideoRenderer() = default; // 必须在这里，因为此时Impl的大小才确定

// 3. 嵌套类Impl的具体定义
class VideoRenderer::Impl {
public:
    // 复杂的私有成员，现在被隐藏起来了
    std::vector<uint8_t> frameBuffer;
    int currentResolution[2];

    void internalAlgorithm() {
        std::cout << "Running complex GPU rendering logic..." << std::endl;
    }
};

// 4. 构造与析构
VideoRenderer::VideoRenderer() : pImpl(std::make_unique<Impl>()) {
    pImpl->currentResolution[0] = 1920;
    pImpl->currentResolution[1] = 1080;
}


// 5. 接口实现：通过 pImpl 调用嵌套类的功能
void VideoRenderer::render(const std::string& filename) {
    std::cout << "Rendering: " << filename << std::endl;
    pImpl->internalAlgorithm();
}
