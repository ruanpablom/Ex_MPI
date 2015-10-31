#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define TAM 256*100

int main(int argc, char **argv){
	int rank,size;	
	int token[TAM]={0};		
	int i;
	double *start,*end;
	MPI_Status status;
	MPI_Request *request;


	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);	
	
	start=(double*)malloc(size*sizeof(double));
	if(start==NULL)exit(0);
	end=(double*)malloc(size*sizeof(double));
	if(end==NULL)exit(0);

	request=(MPI_Request*)malloc(size*sizeof(MPI_Request));
	if(request==NULL)exit(0);
		
	if(rank==0){
		for(i = 1 ; i < size ; i++){
			MPI_Isend(&token, TAM, MPI_INT, i, 0, MPI_COMM_WORLD, &request[i]);
			start[i] = MPI_Wtime();
		}
		for(i = 1 ; i < size ; i++){
			MPI_Isend(&token, TAM, MPI_INT, i, 0, MPI_COMM_WORLD, &request[i]);
			start[i] = MPI_Wtime();
		}
	}else{
		MPI_Irecv(&token, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, &request[rank]);
		MPI_Isend(&token, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, &request[rank]);
	}	

	MPI_Finalize();
	return 0;
}
