#include <stdexcept>
#include <iostream>

using namespace std;

class Calculator {
private:
    int flag;

public:
    double add(double a, double b) {
        flag = 1;
        flag += a;
        return a + b;
    }

    // Method to subtract two numbers
    double subtract(double a, double b) {
        return a - b;
    }

    // Method to multiply two numbers
    double multiply(double a, double b) {
        return a * b;
    }

    // Method to divide two numbers
    double divide(double a, double b) {
        if (b != 0) {
            return a / b;
        } else {
            throw std::invalid_argument("Division by zero");
        }
    }
};

int main() {
    Calculator calculator;
    double a = 10;
    double b = 5;
    cout << "Addition: " << calculator.add(a, b) << endl;
    cout << "Subtraction: " << calculator.subtract(a, b) << endl;
    cout << "Multiplication: " << calculator.multiply(a, b) << endl;
    cout << "Division: " << calculator.divide(a, b) << endl;
    return 0;

}