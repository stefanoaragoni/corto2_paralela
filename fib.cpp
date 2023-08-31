#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <chrono>


int fib_recursive(int n);
int fib_recursive_openmp(int n);

int main(int argc, char* argv[]) {
    int a = 0;

    // Revisa que se haya ingresado valores
    if (argc > 0) {
        a = strtod(argv[1], NULL);
    } else {
        printf("Ingrese el valor de a\n");
        return 1;
    }

    // Tomar el tiempo de inicio
    auto start_time = std::chrono::high_resolution_clock::now();

    int b = fib_recursive(a);
    printf("El fibonacci de %d es %d\n", a, b);

    // Tomar el tiempo de fin
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    printf("Tiempo de ejecucion: %ld\n", duration);

    return 0;
}

int fib_recursive(int n) {
    if (n < 2) {
        return n;
    } else {
        int a = fib_recursive(n - 1);
        int b = fib_recursive(n - 2);

        return a + b;
    }
}

int fib_recursive_openmp(int n) {
    if (n < 2) {
        return n;
    } else {
        int a = fib_recursive(n - 1);
        int b = fib_recursive(n - 2);

        return a + b;
    }
}