#include <iostream>

class Animal { public: virtual ~Animal() {} }; // 必须有虚函数！
class Dog : public Animal { public: void bark() { std::cout << "Woof!\n"; } };
class Cat : public Animal {};

void feedBone(Animal* a) {
    // 尝试转为 Dog
    Dog* d = dynamic_cast<Dog*>(a);
    
    if (d) { // 转换成功
        d->bark();
    } else {
        std::cout << "This is not a dog, can't feed bone.\n";
    }
}

int main() {
    Animal *animal = new Dog();

    feedBone(animal);

    delete animal;

    return 0;
}
