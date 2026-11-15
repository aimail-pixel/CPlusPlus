/*

Construction Order

• Virtual Base Classes: Initialized first in a depth-first, left-to-right traversal of the inheritance graph. The most-derived class is responsible for invoking their constructors, regardless of how deep they sit in the hierarchy.
• Direct Nonvirtual Base Classes: Initialized next in the exact left-to-right order they appear in the class's base-specifier list.
• Non-Static Data Members: Initialized in the exact order they are declared inside the class definition. The order in the constructor's member initializer list does not affect execution order.
• Constructor Body: Executed last, once all bases and members are fully constructed and valid.

Destruction Order

• Strict Reverse Sequence: When an object's lifetime ends, the compiler runs the destructor body first. It then destroys non-static data members in reverse declaration order, direct nonvirtual bases in reverse declaration order, and finally virtual bases in reverse initialization order.
*/
#include <iostream>
#include <string>

class Tracker {
private:
    std::string name;

public:
    Tracker(std::string n) : name(std::move(n)) {
        std::cout << "  [Construct] " << name << '\n';
    }
    ~Tracker() {
        std::cout << "  [Destroy]   " << name << '\n';
    }
};

// 1. Virtual Base
class VirtualBase {
private:
    Tracker m{"VirtualBase::member"};

public:
    VirtualBase()  { std::cout << "  [Construct] VirtualBase body\n"; }
    ~VirtualBase() { std::cout << "  [Destroy]   VirtualBase body\n"; }
};

// 2. Direct Non-Virtual Bases
class Base1 : virtual public VirtualBase {
private:
    Tracker m{"Base1::member"};

public:
    Base1()  { std::cout << "  [Construct] Base1 body\n"; }
    ~Base1() { std::cout << "  [Destroy]   Base1 body\n"; }
};

class Base2 : virtual public VirtualBase {
private:
    Tracker m{"Base2::member"};

public:
    Base2()  { std::cout << "  [Construct] Base2 body\n"; }
    ~Base2() { std::cout << "  [Destroy]   Base2 body\n"; }
};

// 3. Most-Derived Class
class Derived : public Base1, public Base2 {
private:
    // Declared in order: m1, then m2
    Tracker m1;
    Tracker m2;

public:
    // Initializer list intentionally written out of order (m2 before m1, Base2 before Base1)
    Derived() : m2("Derived::m2"), Base2(), m1("Derived::m1"), Base1() {
        std::cout << "  [Construct] Derived body\n";
    }

    ~Derived() {
        std::cout << "  [Destroy]   Derived body\n";
    }
};

int main() {
    std::cout << "--- Creating Derived ---\n";
    {
        Derived d;
        std::cout << "--- Leaving Scope ---\n";
    }
    return 0;
}

