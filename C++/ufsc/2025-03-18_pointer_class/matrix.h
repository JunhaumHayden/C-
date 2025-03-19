#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

int printMatrixes(int opcode) {
    if (opcode == 1) {
        cout << "Tray to create a matrix..." << endl;

        //int matrix[5000][7000]; // não foi possível espaço contíguo neste caso - zsh: segmentation fault  ./main
        int rows = 5000;
        int cols = 7000;
        int **bigMatrix = new int*[rows];
        for (int i =0; i<cols; i++) {
            bigMatrix[i] = new int[cols];
        }

        // Free allocated memory
        for (int i = 0; i < rows; i++) {
            delete[] bigMatrix[i];
        }
        delete[] bigMatrix;

        rows = 5;
        cols = 7;
        // Make a matrix
        int **matrix = new int*[rows];
        for (int i =0; i<cols; i++) {
            matrix[i] = new int[cols];
        }
        // Fill the matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = i + j;
            }
        }
        // Print the matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        // Free allocated memory
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;


    
    } else {
        cout << "pass..." << endl;
    }
        return 0;
};

#endif // MATRIX_H