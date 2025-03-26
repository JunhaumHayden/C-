#include <stdio.h>

int f2 (char other_parameter_hello[]) {
    printf("from main int: %d\n", &other_parameter_hello);
    printf("from f2: %p\n", (void*)&other_parameter_hello); // print the address of the first element of the array
    return 0;
}

int f1(char parameter_hello[]) {
    printf("from main int: %d\n", &parameter_hello);
    printf("from f1: %p\n", (void*)&parameter_hello); // print the address of the first element of the array
    f2(parameter_hello);  // pass by value
    return 0;
}

int main() {
    char hello[] = "Hello, World!";
    printf("from main int: %d\n", &hello);
    printf("from main: %p\n", (void*)&hello); // print the address of the first element of the array
    f1(hello); // pass by value
    return 0;
}

