#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

const int MAX_STRING = 100;

int main(void) {
   char       message[MAX_STRING];  
   int        comm_size;               
   int        my_rank;   
   int a = 2, b = 3;
   int tot = 0;          

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 


   if (my_rank == 1) tot = b - a;
   else if (my_rank == 2) tot = a * b;
   else if (my_rank == 3) tot = a - b; 
   MPI_Send(&tot, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
   
   if (my_rank == 0) {  
      tot = a + b;
      /* Impressão da mensagem do processo centralizador */
      printf("Processo centralizador em execução: %d of %d!\n", my_rank, comm_size);
      printf("O processo %d fez a seguinte operação: %d\n", my_rank, tot);

      int acc = tot;
      for (int q = 1; q < comm_size; q++) {
         /* Recepção da mensagem do processo q */
         MPI_Recv(&tot, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

         /* Impressão da mensagem do processo q */
         printf("O processo %d recebeu a seguinte mensagem: %d\n", my_rank, tot);
         acc += tot; 
      } 
      printf("TOTAL: %d\n", acc); 
   }

   /* Finaliza MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
