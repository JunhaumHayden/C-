#include <iostream>
#include "pessoa.h"

int main() {
    // Creating an object of the class
    Person p1("Ana", 11);
    Person p2("Bia", 22);

    // Displaying the information
    std::cout << p1.showInfo() << std::endl;
    std::cout << p2.showInfo() << std::endl;
    // Using getters
    std::cout << "#### Nome: " << p1.getName() << ", Idade: " << p1.getAge() << std::endl;

    std::cout << "#### Nome: " << p2.getName() << ", Idade: " << p2.getAge() << std::endl;

    return 0;
}