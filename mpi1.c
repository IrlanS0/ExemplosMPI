#include <stdio.h>
#include <string.h>  
#include <mpi.h>     

int main(void) {
   int        comm_sz;               /* Número de processos    */
   int        my_rank;               /* Rank   do processo     */
   int a = 2; 
   int b = 3; 

   /* Inicia MPI */
   MPI_Init(NULL, NULL); 

   /* Obter número de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   int total = 0; 
   if  (my_rank == 0){
      total = a + b; 
   }
   else if (my_rank == 1){
      total = b - a; 
   }
   else if (my_rank == 2){
      total = a * b;
   }
   else if (my_rank == 3){
      total = a - b; 
   }

   /* Obter rank (id) do processo */

   printf("Número de processos: %d Rank do processos corrente: %d \n", comm_sz, my_rank);
   printf("TOTAL = %d\n", total);

   /* Encerra MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
