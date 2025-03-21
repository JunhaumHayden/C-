#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Inteiros
    int a = 10; // 4 bytes (32 bits) -2^31 a 2^31-1
    cout << pow(2, 31) << endl;
    int test = 65536;
    cout << "Inteiro limite do intevalo: " << test << endl;
    // Modoficadores funcionam com o int, variam o intevalo dos inteiros
    unsigned int b = 10; // 4 bytes (32 bits) 0 a 2^32-1
    short int c = 10; // 2 bytes (16 bits) -2^15 a 2^15-1
    // inteiros extensos
    long int d = 10; // 4 bytes (32 bits) -2^31 a 2^31-1
    long int dd = 10l; // 4 bytes (32 bits) -2^31 a 2^31-1
    long long int e = 10; // 8 bytes (64 bits) -2^63 a 2^63-1  
    // constante sem sinal, utiliza-se a letra 
    unsigned int g = 1000u; // 4 bytes (32 bits) 0 a 2^32-1
    unsigned long long int f = 10u; // 8 bytes (64 bits) 0 a 2^64-1

    cout << "Inteiro: " << a << endl;
    cout << "Inteiro sem sinal: " << b << endl;
    cout << "Inteiro curto: " << c << endl;
    cout << "Inteiro longo: " << d << endl;
    cout << "Inteiro longo longo: " << e << endl;

    // octal
    int octal = 010; // 8
    cout << "Octal: " << octal << endl; 

    // hexadecimal
    int hex = 0x10; // 16
    cout << "Hexadecimal: " << hex << endl;


}