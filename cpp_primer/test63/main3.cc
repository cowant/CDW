#include <iostream>
#include <vector>

// 1. Define an Enum for all possible types
enum class ActorType {
    Base,
    Warrior,
    Mage
};

class Actor {
public:
    ActorType type; // The "Manual Tag"
    
    // Constructor sets the type tag
    Actor(ActorType t = ActorType::Base) : type(t) {}
    virtual ~Actor() {} // Virtual destructor is still good practice!
};

class Warrior : public Actor {
public:
    // Initialize with the Warrior tag
    Warrior() : Actor(ActorType::Warrior) {}
    
    void charge() { std::cout << "Warrior is charging!\n"; }
    
    // Helper function for "Safe-ish" casting
    static Warrior* cast(Actor* a) {
        return (a && a->type == ActorType::Warrior) ? static_cast<Warrior*>(a) : nullptr;
    }
};

class Mage : public Actor {
public:
    Mage() : Actor(ActorType::Mage) {}
    
    void teleport() { std::cout << "Mage teleported!\n"; }
    
    static Mage* cast(Actor* a) {
        return (a && a->type == ActorType::Mage) ? static_cast<Mage*>(a) : nullptr;
    }
};

int main() {
    std::vector<Actor*> world;
    world.push_back(new Warrior());
    world.push_back(new Mage());

    for (Actor* a : world) {
        // Instead of dynamic_cast, we check the Enum tag
        if (Warrior* w = Warrior::cast(a)) {
            w->charge();
        } 
        else if (Mage* m = Mage::cast(a)) {
            m->teleport();
        }
    }

    for (Actor* a : world) delete a;
    return 0;
}
