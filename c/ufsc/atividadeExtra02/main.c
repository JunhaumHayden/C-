#include <stdio.h>

#define MAX_SIZE 10

// read a string from the user
void inputArray(int *arr, int size) {
    for (int i=0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

//print the content of the vector arr with size
void printArray(int *arr, int size) { // pass by reference (int *arr) and pass by value (int size)
    for (int i=0; i < size; i++) {
        printf("%d ", arr[i]);        // %d is the format specifier for an integer
        if (i < size-1) {
            printf(", ");             // print a comma and a space if it is not the last element  
        }
    }
    printf("\n");
}

// function for compere two integer values for ascending order. The function returns the difference between the first and second integers.
int sortAscending(int *num1, int *num2) {  // pass by reference (int *num1) and pass by reference (int *num2)
    return *num1 - *num2;
}

// function for compere two integer values for descending order. The function returns the difference between the second and first integers.
int sortDescending(int *num1, int *num2) { // pass by reference (int *num1) and pass by reference (int *num2)
    return *num2 - *num1;
}

// Function that sorts the vector according to the given comparison function
void sort(int *arr, int size, int (*compare)(int*, int*)) { // pass by reference (int *arr), pass by value (int size) and pass by reference (int (*compare)(int*, int*))
    for (int i=0; i < size; i++) {
        for (int j=i+1; j < size; j++) {
            if (compare(&arr[i], &arr[j]) > 0) { // pass by reference (int *arr[i]) and pass by reference (int *arr[j])
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    // time complexity of the sorting algorithm is O(n^2)
    // space complexity of the sorting algorithm is O(1)
}

int main() {
    // int arr[MAX_SIZE];
    // int size;

    // printf("Enter the size of the array: ");
    // scanf("%d", &size);

    // printf("Enter the elements of the array: ");
    // inputArray(arr, size);

    int arr[MAX_SIZE] = {10, -1, 0, 4, 2, 100, 15, 20, 24, -5};  // Vetor de teste fixo
    int size = MAX_SIZE;

    printf("The original array is: ");
    printArray(arr, size);

    sort(arr, size, sortAscending);
    printf("The array in ascending order is: ");
    printArray(arr, size);

    sort(arr, size, sortDescending);
    printf("The array in descending order is: ");
    printArray(arr, size);

    return 0;
}