#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int my_rank, comm_size;
    int numero;
    int a = 2, b = 3, tot = 0, r, acc;

    MPI_Init(&argc, &argv);                  // Inicializa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Rank do processo atual

    if (my_rank == 0) tot = a + b;
    else if (my_rank == 1) tot = b - a;
    else if (my_rank == 2) tot = a * b;
    else if (my_rank == 3) tot = a - b; 
    r = tot; 
    int global_sum = 0;

    // Soma todos os 'local_value' no processo 0
    MPI_Reduce(&r, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Bcast(&global_sum, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    printf("Processo %d calculou: %.2f\n", my_rank, (double)global_sum/r);

    MPI_Finalize(); // Finaliza MPI
    return 0;
}
