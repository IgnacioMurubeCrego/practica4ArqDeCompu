# Práctica 4: Resolución de problemas mediante el modelo de comunicación colectivo  

## Arquitectura de Computadores  
Grado en Ingeniería Informática  
Grupo A  

---

## Tabla de contenido  
1. [Introducción](#introducción)  
2. [Objetivos](#objetivos)  
3. [Entorno](#entorno)  
   - [Compilación de programas](#compilación-de-programas)  
   - [Ejecución de programas](#ejecución-de-programas)  
4. [Implementación](#implementación)  
   - [Funciones MPI básicas](#funciones-mpi-básicas)  
5. [Entregables](#entregables)  
6. [Criterios de evaluación](#criterios-de-evaluación)  

---

## Introducción  
La presente práctica profundiza en el modelo de comunicación colectivo presentado en la práctica anterior. Se trabajará con las funciones MPI `MPI_Allgather` y `MPI_Alltoall`, que permiten realizar diferentes tipos de comunicaciones entre procesos.  

---

## Objetivos  
- Compilación de programas MPI.  
- Ejecución de programas en varios procesos de forma paralela.  
- Estructura de un programa MPI.  
- Estudio de las funciones aportadas en este documento.  

---

## Entorno  

### Requisitos previos  
Es necesario tener instalado un compilador de C++ como `g++` y el paquete `mpich` en un entorno Unix (máquina virtual o partición en el equipo personal).  

```bash
sudo apt update  
sudo apt install g++  
sudo apt install mpich  
mpicxx --version  # Verifica la instalación
```

Compilación de programas
Para compilar un programa con MPICH:
```bash
mpicxx nombre_del_archivo.cpp -o nombre_del_ejecutable
```
Ejecución de programas
Para ejecutar el archivo compilado:
```bash
mpirun -np numero_procesos_en_paralelo ./nombre_del_ejecutable
```
Implementación
Funciones MPI básicas
La librería MPI incluye funciones como:

Función	Descripción
MPI_Init	Inicializa el entorno MPI
MPI_Comm_rank	Obtiene el rango del proceso actual en un comunicador
MPI_Comm_size	Obtiene el número total de procesos en un comunicador
MPI_Finalize	Finaliza el entorno MPI
MPI_Allgather	Recopila datos de todos los procesos y los distribuye a todos
MPI_Alltoall	Cada proceso envía distintos elementos al resto

Ejemplo de uso:
```cpp
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Finalize();
    return 0;
}
```

MPI_Allgather
Recopila datos de todos los procesos y los distribuye a todos.
```cpp
MPI_Allgather(&sendbuf, sendcount, sendtype, &recvbuf, recvcount, recvtype, MPI_COMM_WORLD);
```

MPI_Alltoall
Distribuye datos diferentes de cada proceso al resto.
```cpp
MPI_Alltoall(&sendbuf, sendcount, sendtype, &recvbuf, recvcount, recvtype, MPI_COMM_WORLD);
```

Entregables
Ejercicio 1 (2 puntos)
Desarrollar un programa con 4 procesos, donde cada proceso cuente con un número conocido solo por él. Usar una función de comunicación para que cada proceso obtenga todos los números, y luego imprimir los valores del buffer de recepción.

Ejercicio 2 (3 puntos)
Implementar un programa que realice la transposición de una matriz inicial en paralelo, distribuyendo la matriz entre 4 procesos:

Matriz inicial:
```cpp
1  2  3  4  
5  6  7  8  
9 10 11 12  
13 14 15 16  
```

Matriz transpuesta:
```cpp
1  5  9  13  
2  6  10 14  
3  7  11 15  
4  8  12 16  
```
