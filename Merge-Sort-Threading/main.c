#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *arr;
int *sarr;
int arrayLength;

// Struct to pass threads' arguments
typedef struct{
	int left;
	int right;
} threadArgs;

// Merge
void merge(int left, int mid, int right){
	int i = left;
	int j = mid+1;
	int k = left;

	while (i<=mid && j<=right){
		if (arr[i] < arr[j])
			sarr[k++] = arr[i++];
		else
			sarr[k++] = arr[j++];
	}
	
	while(i <= mid){
		sarr[k++] = arr[i];
		i++;
	}
	
	while(j <= right){
		sarr[k++] = arr[j];
		j++;
	}

	for (i= left; i <= right; i++){
		arr[i] = sarr[i];
	}	
}

// Merge sort using multithreading
void* threadingMergeSort(void *arg){
	threadArgs* args = (threadArgs*) arg;
	int left = args->left;  
	int right = args->right;
	
	if (left == right){
		pthread_exit(0);
	}
	
	// Recursively calling merge sort
	
	// Creating two threads for each recursive call (sub-array)
	pthread_t th1,th2;
	threadArgs args1, args2;
	int mid = (left+right)/2;
	args1.left = left;    
	args1.right = mid;
	args2.left = mid+1;  
	args2.right = right;

	pthread_create(&th1, NULL, threadingMergeSort, (void*)&args1);
	pthread_create(&th2, NULL, threadingMergeSort, (void*)&args2);

	// Join the created threads and merge
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	merge(left, mid, right);
	
	pthread_exit(0);
	return NULL;
}

int main(void) {
	// Reading the array from input file
	char filename[30];
	printf("Enter the input file name: ");
	scanf("%s", filename);
	FILE* fp = fopen(filename, "r");
	if(fp == NULL){
		printf("Invalid file\n");
		exit(0);
	}
	fscanf(fp, "%d", &arrayLength);
	arr = (int*) malloc(sizeof(int)*arrayLength);
	int i=0;;
	for (i = 0; i < arrayLength; i++){
		fscanf(fp, "%d", &arr[i]);
	}
	fclose(fp);
	
	// Allocating an auxiliary array for merge
	sarr = (int*)malloc(sizeof(int)*arrayLength);
	
	// Creating the first the thread that issues the rest of the threads
	threadArgs args;
	args.left = 0;
	args.right = arrayLength-1;
	pthread_t th0;
	pthread_create(&th0, NULL, threadingMergeSort, &args);
	pthread_join(th0,NULL);

	// Printing out the sorted array
	FILE *f;
	f = fopen("op.txt", "w");
	fprintf(f, "The sorted array: \n");
	i=0;
	for(i=0; i<arrayLength; i++){
		fprintf(f, "%d ", arr[i]);
	}
	fprintf(f, "\n");
	fclose(f);
	return 0;
}
