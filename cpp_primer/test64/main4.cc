#include <iostream>
#include <cstdint> // For uint8_t

enum class Status : uint8_t {
    Success = 0,
    Timeout = 1,
    ServerError = 2
};

int main() {
    Status myStatus = Status::ServerError;

    // 1. Error: This won't compile! 
    // std::cout << myStatus << std::endl; 

    // 2. Correct: Use static_cast to convert to the underlying type
    // We cast it to 'int' so cout knows how to print it as a number
    std::cout << "Status Code: " << static_cast<int>(myStatus) << std::endl;

    // 3. Network Scenario: Converting to a raw byte for a buffer
    uint8_t wireData = static_cast<uint8_t>(myStatus);
    std::cout << "Byte to send over network: " << (int)wireData << std::endl;

    // 4. Reverse: Converting an integer back to an Enum
    int receivedValue = 1;
    Status receivedStatus = static_cast<Status>(receivedValue);
    
    if (receivedStatus == Status::Timeout) {
        std::cout << "Connection Timed Out!" << std::endl;
    }

    return 0;
}
