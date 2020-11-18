#include <iostream> // std::ostream, std::cout, std::endl

#include <playground/seesaw.h>

void examples() {

    // You can write some examples here

    std::cout << "Hello from the examples file!" << std::endl;

    playground::Seesaw seesaw;
    std::cout << seesaw.getGreeting() << std::endl;
}

int main() {

    examples();

    return 0;
}
