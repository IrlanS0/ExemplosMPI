#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int my_rank, comm_size;
    int numero;
    int a = 2, b = 3, tot = 0, r, acc;

    MPI_Init(&argc, &argv);                  // Inicializa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Rank do processo atual
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size); // Número total de processos

    if (my_rank == 0) {
        // Apenas o processo 0 define o valor
        tot = a + b;

        int tmp;
        acc = tot;
        for (int q = 1; q < comm_size; q++) {
         /* Recepção da mensagem do processo q */
         MPI_Recv(&tmp, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

         /* Impressão da mensagem do processo q */
         // printf("O processo %d recebeu a seguinte mensagem: %d\n", my_rank, tot);
         acc += tmp; 
        }  
        printf("Processo %d definiu o número %d para ser enviado aos demais.\n", my_rank, acc);
    }
    else if (my_rank == 1) tot = b - a;
    else if (my_rank == 2) tot = a * b;
    else if (my_rank == 3) tot = a - b; 
    MPI_Send(&tot, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    r = tot; 
    
    // Broadcast: todos os processos recebem o valor de "numero" vindo do processo 0
    MPI_Bcast(&acc, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Cada processo imprime o valor recebido
    // printf("Processo %d recebeu o número: %d e r = %d\n", my_rank, acc, r);

    printf("Processo %d calculou: %.2f\n", my_rank, (double)acc/r);

    MPI_Finalize(); // Finaliza MPI
    return 0;
}
