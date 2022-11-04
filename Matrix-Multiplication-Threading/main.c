#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <pthread.h>
#include <time.h>

int mat1[300][300];
int mat2[300][300];
int matRows1, matRows2, matColumns1, matColumns2;
int res[300][300];
int specifyRow = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
	int arr1[300];
	int arr2[300];
} threadArgs;

void* mulApproach1(void *arg){
	threadArgs *args = (threadArgs *)arg;
	int i=0;
	int sum=0;
	for(i=0; i<=matColumns1; i++){
		sum+=args->arr1[i]*args->arr2[i];
	}
	int *p = (int*)malloc(sizeof(int));
        *p = sum;
	pthread_exit(p);
}

void* mulApproach2(void *arg){
	pthread_mutex_lock(&lock);
	int rowCount = specifyRow;
	int i=0;
	int j=0;
	for (i = 0; i < matColumns1; i++){
		for (j = 0; j < matRows2; j++){
			res[rowCount][i] += mat1[rowCount][j] * mat2[j][i];
		}
	}
	specifyRow++;
	pthread_mutex_unlock(&lock);
	pthread_exit(0);
	return NULL;
}

int main(){
	int matrixRows1, matrixColumns1, matrixRows2, matrixColumns2;
	clock_t start1, end1, start2, end2;
     	double cpu_time_used1, cpu_time_used2;
     	char filename[30];
     	printf("Enter the input file name: ");
     	scanf("%s", filename);
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("Invalid file\n");
		exit(0);
	}
	
	// Reading Matrix 1
	fscanf(fp, "%d %d\n", &matrixRows1, &matrixColumns1);
	int i=0;
	int j=0;
	int matrix1[matrixRows1][matrixColumns1];
	for(i=0; i<matrixRows1; i++){
		for(j=0; j<matrixColumns1; j++){
			fscanf(fp, "%d", &matrix1[i][j]);
			mat1[i][j] = matrix1[i][j];
		}
	}
	
	// Reading Matrix 2
	fscanf(fp, "%d %d\n", &matrixRows2, &matrixColumns2);
	i=0;
	j=0;
	int matrix2[matrixRows2][matrixColumns2];
	for(i=0; i<matrixRows2; i++){
		for(j=0; j<matrixColumns2; j++){
			fscanf(fp, "%d", &matrix2[i][j]);
			mat2[i][j] = matrix2[i][j];
		}
	}
	fclose(fp);
	
	matRows1 = matrixRows1;
	matRows2 = matrixRows2;
	matColumns1 = matrixColumns1;
	matColumns2 = matrixColumns2;
	
	// Input validation
	if(matrixRows2 != matrixColumns1){
		printf("Invalid i/p\n");
		exit(0);
	}
	
	// Creating threads for Approach 1
	start1 = clock();
	i=0;
	j=0;
	threadArgs *args;
	int count=0;
	pthread_t *th;
    	th = (pthread_t*)malloc(matrixRows1*matrixColumns2*sizeof(pthread_t));
	for(i=0; i<matrixRows1; i++){
		for(j=0; j<matrixColumns2; j++){
			args = (threadArgs *)malloc((300)*sizeof(threadArgs));
			int m=0;
			for(m=0; m<matrixColumns1; m++){
				args->arr1[m]=matrix1[i][m];
				args->arr2[m]=matrix2[m][j];
			}
			pthread_create(&th[count], NULL, &mulApproach1, (void*)(args));
			count++;
		}
	}
	
	FILE *f;
	f = fopen("op.txt", "w");
	
	// Saving result of Approach 1 to o/p file
	fprintf(f, "Approach 1 (By element) results\n");
	for (i = 0; i<(matrixRows1*matrixColumns2); i++){
		void *sum;
		pthread_join(th[i], &sum);   // Joining threads of Approach 1        
		int *ptr = (int *)sum;
		fprintf(f, "%d ", *ptr);
		if ((i + 1) % matrixColumns2 == 0){
			fprintf(f, "\n");
		}
	}
	fprintf(f, "END1 ");
	end1 = clock();
	cpu_time_used1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
	fprintf(f, "%f\n", cpu_time_used1);
	
	// Creating threads for Approach 2
	start2 = clock();
	pthread_t t[matRows1];
	i=0;
	for (i = 0; i < matRows1; i++) {
        	pthread_create(&t[i], NULL, mulApproach2, NULL);
	}
	
	// Joining threads of Approach 2
	for (i = 0; i < matRows1; i++){
        	pthread_join(t[i], NULL); 
        }
        
        // Saving result of Approach 2 to o/p file
        fprintf(f, "Approach 2 (By row) results\n");
        i=0;
        j=0;
        for(i=0; i<matRows1; i++){
        	for(j=0; j<matColumns2; j++){
        		fprintf(f, "%d ", res[i][j]);
        	}
        	fprintf(f, "\n");
        }
        fprintf(f, "END2 ");
        end2 = clock();
        cpu_time_used2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
	fprintf(f, "%f\n", cpu_time_used2);
	
	// Elapsed time comparison
	if(cpu_time_used1<cpu_time_used2){
		fprintf(f, "Approach 1 is better in this case");
	}
	else if(cpu_time_used1>cpu_time_used2){
		fprintf(f, "Approach 2 is better in this case");
	}
	else{
		fprintf(f, "No approach is better than the other");
	}
	
        fclose(f);
        
	return 0;
}
