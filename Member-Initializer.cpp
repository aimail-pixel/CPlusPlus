#include <iostream>
#include <string>
/*
It directly initializes members, and is required for const members, references and non-default-constructible members. Assignment in the body occurs after member initialization. Members initialize in declaration order, regardless of list order.

*/
// A helper class with NO default constructor
class Engine {
public:
    int horsepower;
    Engine(int hp) : horsepower(hp) {
        std::cout << "1. Engine constructed with " << horsepower << " HP\n";
    }
};

class Car {
private:
    // DECLARATION ORDER determines initialization order (top to bottom):
    const int vin;        // Rule 1: const member (must be initialized in list)
    std::string& owner;   // Rule 2: reference member (must be initialized in list)
    Engine engine;        // Rule 3: non-default-constructible member (must be initialized in list)
    int speed;            // Regular member (to contrast initialization vs. assignment)

public:
    // CONSTRUCTOR MEMBER INITIALIZER LIST
    // Notice we intentionally wrote 'speed' first in the list,
    // even though 'vin' is declared first in the class!
    Car(int v, std::string& o, int hp)
        : speed(0),       // Actually runs FOURTH (because 'speed' is declared 4th)
          vin(v),         // Runs FIRST (direct initialization of const)
          owner(o),       // Runs SECOND (direct initialization of reference)
          engine(hp)      // Runs THIRD (calls Engine(int) directly)
    {
        // CONSTRUCTOR BODY
        // By the time execution reaches here, ALL members are already initialized.
        
        // vin = 999;     // COMPILER ERROR: cannot assign to a const variable
        // owner = ...;   // Would overwrite the caller's string, not rebind the reference
        
        speed = 60;       // ASSIGNMENT: Overwrites the initial value (0) with 60
        std::cout << "2. Car body executed. Final speed: " << speed << "\n";
    }
};

int main() {
    std::string driver = "Alice";
    Car myCar(1042, driver, 300);
    return 0;
}
