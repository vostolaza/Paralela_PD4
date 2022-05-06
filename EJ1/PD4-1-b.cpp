#include <iostream>
#include <cmath>
#include <omp.h>
#include <ctime>
using namespace std;

#define SIZE 1000

void normaliza(double A[SIZE][SIZE]){
    int i,j;
    double suma=0.0, factor;
    #pragma omp parallel default(shared) private(i, j)
    {
        #pragma omp for schedule(dynamic) reduction(+:suma)
        for (i=0; i < SIZE; i++) {
            for (j=0; j < SIZE; j++) {
                suma = suma + A[i][j] * A[i][j];
            }
        }
        factor = 1.0/sqrt(suma);
        #pragma omp for schedule(dynamic)
        for (i=0; i < SIZE; i++) {
            for (j=0; j < SIZE; j++) {
                A[i][j] = factor*A[i][j];
            }
        }

    }
}

void print(double A[SIZE][SIZE]){
    int i,j;
    for (i=0; i < SIZE; i++) {
        for (j=0; j < SIZE; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
}

int main(){
    double A[SIZE][SIZE];
    int i,j;
    for (i=0; i < SIZE; i++) {
        for (j=0; j < SIZE; j++) {
            A[i][j] = i*j;
        }
    }
    // print(A);
    clock_t start = clock();
    normaliza(A);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Tiempo de ejecucion: " << time << " segundos" << endl;
    // print(A);

    return 0;
}