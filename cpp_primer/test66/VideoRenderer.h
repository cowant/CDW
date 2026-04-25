#pragma once
#include <memory>
#include <string>

class VideoRenderer {
public:
    VideoRenderer();
    ~VideoRenderer(); // Pimpl 模式下，析构函数必须在 .cpp 中定义

    void render(const std::string& filename);

private:
    // 1. 嵌套类的前置声明
    class Impl; 
    
    // 2. 唯一的私有成员：指向实现类的智能指针
    std::unique_ptr<Impl> pImpl;
};
