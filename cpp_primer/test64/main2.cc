#include <iostream>

enum class TrafficLight {
    Red,
    Green
};

void check(TrafficLight t) {
    using enum TrafficLight; 
    switch(t) {
        case Red: { // 不需要写 TrafficLight::Red
            std::cout << "Is TradfficLight::Red" << std::endl;
            break;
        }
        case Green: {
            std::cout << "Is TradfficLight::Green" << std::endl;
            break;
        }
    }
}

int main() {
    TrafficLight light = TrafficLight::Red;

    check(light);

    return 0;
}
