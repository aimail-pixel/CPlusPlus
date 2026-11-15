
#include <iostream>
#include <string>
using namespace std;

class Device {
private:
    int deviceId;
    string name;

public:
    Device(int id, string n)
        : deviceId(id), name(n) {
        cout << "Constructor called\n";
    }

    void show() const {
        cout << deviceId << " : " << name << '\n';
    }

    ~Device() {
        cout << "Destructor called\n";
    }
};

int main() {
    Device d(101, "Sensor");
    d.show();
}
