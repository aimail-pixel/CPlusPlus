#include <vector>
#include <iostream>
using namespace std;

struct SafePacket {
    std::vector<unsigned char> bytes;
    explicit SafePacket(size_t n) : bytes(n) {}
};
int main() {
    SafePacket first(128);
    SafePacket second = first; // independent vector data
    second.bytes[0] = 42;
    std::cout << "first.bytes[0]: " << static_cast<int>(first.bytes[0]) << "\n";
    std::cout << "second.bytes[0]: " << static_cast<int>(second.bytes[0]) << "\n";
}