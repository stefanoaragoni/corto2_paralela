#include <stdio.h>
#include <omp.h>

int main() {
    int shared_variable = 0;

    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();
        int private_variable = thread_id;

        // Ejemplo de omp critical
        #pragma omp critical
        {
            shared_variable += private_variable;
        }

        // Ejemplo de omp atomic
        #pragma omp atomic
        shared_variable++;

        // Ejemplo de omp master
        #pragma omp master
        {
            printf("Esta sección solo es ejecutada por el hilo maestro (ID: %d)\n", thread_id);
        }

        // Ejemplo de omp single
        #pragma omp single
        {
            printf("Esta sección es ejecutada solo por uno de los hilos (ID: %d)\n", thread_id);
        }

        // Ejemplo de locks explícitos (omitiendo los detalles de la inicialización del lock)
        omp_lock_t my_lock;
        omp_init_lock(&my_lock);
        #pragma omp critical
        {
            omp_set_lock(&my_lock);
            // Sección crítica protegida por el lock
            omp_unset_lock(&my_lock);
        }
        omp_destroy_lock(&my_lock);

        // Ejemplo de omp barrier
        #pragma omp barrier
        printf("Después de la barrera (ID: %d)\n", thread_id);

        // Ejemplo de omp taskwait
        #pragma omp single
        {
            #pragma omp task
            printf("Tarea en paralelo (ID: %d)\n", thread_id);
            #pragma omp taskwait
        }

        // Ejemplo de omp ordered
        #pragma omp ordered
        {
            printf("Sección ordenada (ID: %d)\n", thread_id);
        }

        // Ejemplo de omp flush
        #pragma omp flush(shared_variable)
    }

    printf("El valor final de la variable compartida es: %d\n", shared_variable);

    return 0;
}
