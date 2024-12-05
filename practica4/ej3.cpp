#include <iostream>
#include <cmath>
#include <mpi.h>
#include <vector>
#include <algorithm> // Para std::reverse

void binary_to_decimal(const std::string &binary, const std::string &original_binary)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = binary.size();
    if (size != n)
    {
        if (rank == 0)
        {
            std::cerr << "El número de procesos debe ser igual al número de bits del binario (" << n << ")." << std::endl;
        }
        MPI_Finalize();
        return;
    }

    // Cada proceso obtiene su bit correspondiente
    int bit = binary[rank] - '0'; // Convertir carácter a entero

    // Cada proceso calcula su contribución al valor decimal
    int contribution = bit * std::pow(2, rank);

    // Recopilar contribuciones de todos los procesos con MPI_Allgather
    std::vector<int> contributions(size);
    MPI_Allgather(&contribution, 1, MPI_INT, contributions.data(), 1, MPI_INT, MPI_COMM_WORLD);

    // Realizar suma en todos los procesos
    int total = 0;
    for (int val : contributions)
    {
        total += val;
    }

    // Mostrar el resultado en cada proceso
    std::cout << "Proceso " << rank << ": El número binario " << original_binary << " es " << total << " en decimal." << std::endl;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    // Números binarios a convertir
    const std::string binaries[] = {"1010", "1100", "0001", "1111"};

    for (const auto &binary : binaries)
    {
        // Invertir la cadena binaria
        std::string reversed_binary = binary;
        std::reverse(reversed_binary.begin(), reversed_binary.end());

        // Procesar el número binario
        binary_to_decimal(reversed_binary, binary);

        MPI_Barrier(MPI_COMM_WORLD); // Sincronizar antes de procesar el siguiente número
    }

    MPI_Finalize();
    return 0;
}
