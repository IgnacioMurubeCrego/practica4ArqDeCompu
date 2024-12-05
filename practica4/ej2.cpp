#include <iostream>
#include <mpi.h>

#define N 4 // Dimensión de la matriz NxN

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != N)
    {
        if (rank == 0)
        {
            std::cerr << "Este programa requiere exactamente " << N << " procesos." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int matrix[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    int send_data[N]; // Cada proceso recibe una fila
    int recv_data[N]; // Cada proceso almacena una columna transpuesta

    // Distribuir las filas entre los procesos
    MPI_Alltoall(matrix, N, MPI_INT, send_data, N, MPI_INT, MPI_COMM_WORLD);

    // Transponer los datos localmente
    for (int i = 0; i < N; i++)
    {
        recv_data[i] = send_data[i];
    }

    // Recolectar las columnas transpuestas
    int result[N][N];
    MPI_Allgather(recv_data, N, MPI_INT, result, N, MPI_INT, MPI_COMM_WORLD);

    // Imprimir el resultado en el proceso raíz
    if (rank == 0)
    {
        std::cout << "Matriz transpuesta:" << std::endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                std::cout << result[j][i] << " ";
            }
            std::cout << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
