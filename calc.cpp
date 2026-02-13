#include <iostream>
#include <sstream>
#include "adder.h"

int main(int argc, char* argv[]) {
    if (argc != 3) return 1;

    int a, b;
    std::stringstream(argv[1]) >> a;
    std::stringstream(argv[2]) >> b;

    std::cout << add(a, b);
    return 0;
}