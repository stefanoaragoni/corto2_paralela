#include <iostream>
#include <cmath>
#include <random>
#include <random>
#include <omp.h>

double fib_recursive(int n);
double fib_recursive_openmp(int n);

int main() {
    int a = 0;

    // Revisa que se haya ingresado valores
    if (argc > 0) {
        a = strtod(argv[1], NULL);
    } else {
        printf("Ingrese el valor de a\n");
        return 1;
    }

    // Tomar el tiempo de inicio
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

    int b = fib_recursive(a);
    printf("El fibonacci de %d es %d\n", a, b);

    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
    std::cout << "Tiempo de creación de partículas: " << totalTime.count() << " segundos\n";

}

double fib_recursive(int n) {
    if (n < 2) {
        return n;
    } else {
        int a = fib_recursive(n - 1);
        int b = fib_recursive(n - 2);

        return a + b;
    }
}