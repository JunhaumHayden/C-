#ifndef PESSOA_H
#define PESSOA_H
#include <string>

class Person {
    // Attributes
private:
    std::string name;
    int age;
public:
    Person(std::string name, int age); // Dclaring the constructor
    ~Person(); // Declaring the Destructor 
    // Method to display information
    std::string getName();

    void setName(std::string name);

    int getAge();

    void setAge(int Age);

    std::string showInfo();
};
#endif