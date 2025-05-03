#include <stdio.h>
#define t 10
#define a 42
#include  <sys/time.h>

struct timeval begin, end;

int main() {
    double y[t];
    gettimeofday(&begin, NULL);
    for(int i = 0; i<t; i++) {
        double x[] = {1,2,3,4,5,6,7,8,9,10};
        y[i] = a*x[i]+y[i];
        printf("Y: %f\n",y[i]);
    }
    gettimeofday(&end, NULL);

    double elapsed = (end.tv_sec - begin.tv_sec) +
                    (end.tv_usec - begin.tv_usec) / 1000000.0;

    printf("Elapsed time: %f\n", elapsed);
}