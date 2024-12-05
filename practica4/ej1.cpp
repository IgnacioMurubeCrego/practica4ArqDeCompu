#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank, size, numero;
    int buffer[size]; // Buffer para almacenar los números de todos los procesos

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rango del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // número total de procesos

    // Asignar un numero a cada proceso
    numero = rank + 1;

    // MPI_Allgather para recolectar los números en todos los procesos
    MPI_Allgather(&numero, 1, MPI_INT, buffer, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Proceso %d recibió los números: ", rank);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
