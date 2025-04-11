#include "pessoa.h"
#include <iostream>

using namespace std;
// Constructor
Person::Person(string n, int i) {
    name = n;
    age = i;
}
// Destructor
Person::~Person() {

}
// getters and setters
string Person::getName() {
    return name;
}
int Person::getAge() {
    return age;
}
void Person::setName(string n) {
    name = n;
}
void Person::setAge(int i) {
    age = i;
}
string Person::showInfo() {
    return "Nome: " + name + ", Idade: " + to_string(age);
}