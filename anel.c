#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){
	int rank,size;	
	int token;	
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);	

	if(rank==0){
		token = 0;
		printf("Token do mestre: %i\n",token);
		MPI_Send(&token, 1, MPI_INT, (rank+1), 0, MPI_COMM_WORLD);
	}else{
		MPI_Recv(&token, 1, MPI_INT, (rank-1), 0, MPI_COMM_WORLD, &status);
		printf("Token recebido pelo processo %i: %i\n",rank,token);
		if(rank+1<size){		
			token+=rank;
			MPI_Send(&token, 1, MPI_INT, (rank+1), 0, MPI_COMM_WORLD);
		}	
	}	

	MPI_Finalize();
	return 0;
}
