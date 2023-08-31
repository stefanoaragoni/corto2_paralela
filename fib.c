#include <stdio.h>
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

    int b = fib_recursive(a);
    printf("El fibonacci de %d es %d\n", a, b);

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