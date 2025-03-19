#ifndef POINTERTEST_H
#define POINTERTEST_H

#include <iostream>

using namespace std;

int printPointers(int opcode) {
    if (opcode == 1) {
    
        float myFloatVariable = 10.5;
        float *pointerFloat = &myFloatVariable; // pointer to myFloatVariable - pointer to float
        float myVector[3] = {4.5, 9.5, 5.7}; // Static Aloccation (maneger by the compiler)
        float *pointerFloat02;

        // Atribuição de ponteiro
        pointerFloat = &myFloatVariable; // pointerFloat get the address of myFloatVariable
        cout << "myFloatVariable: " << myFloatVariable << endl;
        cout << "pointerFloat: " << pointerFloat << endl;
        cout << "pointerFloat value: " << *pointerFloat << endl;

        cout << "\n************************\n" << endl;
        pointerFloat02 = myVector; // pointerFloat02 get the address of myVector
        // same as pointerFloat02 = &myVector[0];
        cout << "myVector: " << myVector << endl;
        cout << "pointerFloat02: " << pointerFloat02 << endl;
        cout << "pointerFloat02 value: " << *pointerFloat02 << endl;
        cout << "pointerFloat02 value on posicion 1: " << *(pointerFloat02+1) << endl;

        cout << "\n************POINTER-ARITIMETICS************\n" << endl;
        pointerFloat02++; // pointerFloat02 = pointerFloat02 + 1*sizeof(float) or pointerFloat02 = pointerFloat02 + 4; or pointerFloat02 += 1;
        cout << "New pointerFloat02 content: " << pointerFloat02 << endl;
        cout << "New pointerFloat02 value: " << *pointerFloat02 << endl;
        cout <<"\nOperating on myVector[1]: \n" << endl;
        myVector[2]= 2* *pointerFloat02; // myVector[2] = 2 * value of pointerFloat02
        // or myVector[2] = 2 * myVector[2];
        cout << "New myVector[2] value: " << myVector[2] << endl;
        cout << "New pointerFloat02 value: " << *pointerFloat02 << endl;
    } else {
        cout << "pass Pointers..." << endl;
    }
        return 0;
};

#endif // POINTERTEST_H