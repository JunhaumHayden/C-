#include <stdio.h>
#include <string.h>

int main() {
    int ages[] = {25, 18, 45, 50, 75, 100};

    float avg, sum = 0;


    int length = sizeof(ages)/sizeof(ages[0]);

    int lowestAge = ages[0];

    for (int i=0; i<sizeof(ages)/sizeof(ages[0]); i++) {
        sum += ages[i];
        if (lowestAge > ages[i]) {
            lowestAge = ages[i];
        }
    }

    avg = sum/ length;

    printf("Average age is: %.2f\n", avg);
    printf("Lowest age is: %d", lowestAge);


    printf("len: %lu", strlen("aba"));
    return 0;
}