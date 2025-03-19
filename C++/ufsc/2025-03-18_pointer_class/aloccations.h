#ifndef ALOCCATIONS_H
#define ALOCCATIONS_H

#include <iostream>

using namespace std;

int printAloccation(int opcode) {
    if (opcode == 1) {
        bool condition = true;
        if (condition) {
            int histogram[10] = {4,7,2,1,9,0,8,3,3,5}; // Static Aloccation (maneger by the compiler)
            int *pointerHistogram = histogram;
            cout << "histogram: " << histogram << endl;
            cout << "pointerHistogram: " << pointerHistogram << endl;
            cout << "pointerHistogram value: " << *pointerHistogram << endl;
            cout << "pointerHistogram value on position 1: " << *(pointerHistogram+1) << endl;


            int *pointerInt01 = new int; // Dynamic Aloccation (maneger by the programmer)
            *pointerInt01 = 10;
            cout << "pointerInt01: " << pointerInt01 << endl;
            cout << "pointerInt01 value: " << *pointerInt01 << endl;
            delete pointerInt01;

            int *pointerInt = new int[10]; // Dynamic Aloccation (maneger by the programmer)
            cout << "pointerInt: " << pointerInt << endl;
            cout <<"Interenting on pointerInt value: " << endl;
            for (int i = 0; i < 10; i++) {
                cout << "pointerInt value: " << *pointerInt << endl;
            }
            cout << "Incrementing pointerInt value: " << endl;
            for (int i = 0; i < 10; i++) {
                pointerInt[i] = i + 1;
            }
            for (int i = 0; i < 10; i++) {
                cout << "pointerInt value: " << pointerInt[i] << endl;
            }
            delete[] pointerInt;
        }
    } else {
        cout << "pass Aloccations..." << endl;
    }
        return 0;
};

#endif // ALOCCATIONS_H