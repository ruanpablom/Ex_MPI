#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define TAM 256*10

int main(int argc, char **argv){
	int rank,size;	
	int token[TAM]={0};		
	int i;
	double *start,*end;
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);	
	start=(double*)malloc(size*sizeof(double));
	if(start==NULL)exit(0);
	end=(double*)malloc(size*sizeof(double));
	if(end==NULL)exit(0);

	if(rank==0){
		for(i = 1 ; i < size ; i++){
			MPI_Send(&token, TAM, MPI_INT, i, 0, MPI_COMM_WORLD);
			start[i] = MPI_Wtime();
		}
		for(i = 1 ; i < size ; i++){
			MPI_Recv(&token, TAM, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			end[i] = MPI_Wtime();
			printf("Ping efetuado em: %gs\n",end[i]-start[i]);
		}
	}else{
		MPI_Recv(&token, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Send(&token, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}	

	MPI_Finalize();
	return 0;
}
