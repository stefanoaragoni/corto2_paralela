#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>
#include <omp.h>

int fib_recursive(int n);
int fib_recursive_openmp(int n);
int fib_recursive_omp_fix(int n);

int main(int argc, char* argv[]) {
    int a = 0;

    // Revisa que se haya ingresado valores
    if (argc > 0) {
        a = strtod(argv[1], NULL);
    } else {
        printf("Ingrese el valor de a\n");
        return 1;
    }

    // Cantidad de threads a usar
    int threads = 4;
    omp_set_num_threads(threads);

    // Tomar el tiempo de inicio
    auto start_time = std::chrono::high_resolution_clock::now();

    //int b = fib_recursive(a);
    //int b = fib_recursive_openmp(a);
    int b = fib_recursive_omp_fix(a);

    printf("El fibonacci de %d es %d\n", a, b);

    // Obtenemos el tiempo de finalización
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Tiempo de ejecución: " << duration.count() << " microsegundos." << std::endl;

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
        int a, b;

        #pragma omp task shared(a)
        a = fib_recursive_openmp(n - 1);

        #pragma omp task shared(b)
        b = fib_recursive_openmp(n - 2);

        #pragma omp taskwait
        return a + b;
    }
}

int fib_recursive_omp_fix(int n) {
    if (n < 2) {
        return n;
    }

    int a, b;
    int THRESHOLD = 20;

    if (n < THRESHOLD) {
        return fib_recursive(n);
    }
    else {
        #pragma omp task shared(a)
        a = fib_recursive_openmp(n - 1);

        #pragma omp task shared(b)
        b = fib_recursive_openmp(n - 2);

        #pragma omp taskwait
        return a + b;
    }

}


