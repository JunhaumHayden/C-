#include <iostream>
int main(int argc, char **argv)
{
    if (argc > 2) {
        int num1 = std::stoi(argv[1]);
        int num2 = std::stoi(argv[2]);
        int mod = num1 % num2;
        std::cout << num1 << " Mod"<<num2 <<  " é " << mod << std::endl;
    } else {
        std::cerr << "Por favor, forneça dois números como argumentos." << std::endl;
        return 1;
    }
    return 0;
}