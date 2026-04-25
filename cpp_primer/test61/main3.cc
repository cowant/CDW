#include <iostream>
#include <string>

// 1. Root Base Class
class Animal {
public:
    std::string name;
    void breathe() { std::cout << "Animal is breathing..." << std::endl; }
};

// 2. Middle Layer - Inheriting Normally
class Mammal : public Animal {
public:
    void feedMilk() { std::cout << "Mammal feeding milk..." << std::endl; }
};

class Bird : public Animal {
public:
    void layEggs() { std::cout << "Bird laying eggs..." << std::endl; }
};

// 3. The "Diamond" Bottom - Inheriting from both
class Bat : public Mammal, public Bird {
    // Bat now contains TWO 'Animal' sub-objects:
    // One via Mammal, one via Bird.
};

int main() {
    Bat myBat;

    // ERROR 1: Ambiguous Member Access
    // The compiler doesn't know if you want the 'name' inside the Mammal part 
    // or the 'name' inside the Bird part.
    // myBat.name = "Bruce"; // <--- COMPILER ERROR

    // ERROR 2: Ambiguous Function Call
    // myBat.breathe();      // <--- COMPILER ERROR

    // How to "force" it to work without virtual inheritance (The Ugly Way):
    myBat.Mammal::name = "Mammal-Side Name";
    myBat.Bird::name = "Bird-Side Name";

    std::cout << "Mammal side name: " << myBat.Mammal::name << std::endl;
    std::cout << "Bird side name: " << myBat.Bird::name << std::endl;

    return 0;
}
