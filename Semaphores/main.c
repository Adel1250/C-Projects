#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

// Queue implementation for buffer
typedef struct{
    	int *items;
    	int head, tail, nitems, capacity;
} Queue;

Queue* initialize(int n){
    	Queue *q = malloc(sizeof(Queue));
    	q->head = 0;
    	q->tail = 0;
    	q->nitems = 0;
    	q->capacity = n;
    	q->items = malloc(n*sizeof(int));
    	return q;
}

int enqueue(Queue *q, int value){
	int tailIndex = q->tail;
    	q->items[q->tail] = value;
    	q->tail = (q->tail+1)%q->capacity;
    	q->nitems++;
    	return tailIndex;
}

int dequeue(Queue *q){
    	int headIndex = q->head;
    	q->head = (q->head+1)%q->capacity;
    	q->nitems--;
    	return headIndex;
}

int isEmpty (Queue *q){
    	if (q->nitems == 0)
        	return 1;
    	else
        	return 0;
}

int isFull (Queue *q){
    	if (q->nitems == q->capacity)
        	return 1;
    	else
        	return 0;
}

int sharedInt = 0;
sem_t counterSem, s, n, e;
Queue *buffer;

void* monitorFunc(void *args){
	while(1){
		int randTime = (rand()%(15-10+1))+10;
		printf("Monitor thread: waiting to read counter\n");
		sleep(randTime);
		sem_wait(&counterSem);
		int sharedIntValue = sharedInt;
		printf("Monitor thread: reading a counter value of %d\n", sharedIntValue);
		sharedInt = 0;
		sem_post(&counterSem);
		if(isFull(buffer)){
			printf("Monitor thread: buffer full!!\n");
		}
		sem_wait(&e);
		sem_wait(&s);
		int tailIndex = enqueue(buffer, sharedIntValue);
		printf("Monitor thread: writing to buffer at position %d\n", tailIndex);
		sem_post(&s);
		sem_post(&n);
	}
}

void* collectorFunc(void *args){
	while(1){
		int randTime = (rand()%(15-10+1))+10;
		sleep(randTime);
		if(isEmpty(buffer)){
			printf("Collector thread: nothing in the buffer!\n");
		}
		sem_wait(&n);
		sem_wait(&s);
		int headIndex = dequeue(buffer);
		printf("Collector thread: reading from buffer at position %d\n", headIndex);
		sem_post(&s);
		sem_post(&e);
	}
}

void* counterFunc(void *args){
	int id = (intptr_t)args;
	while(1){
		int randTime = rand()%8+1;
		printf("Counter thread %d: waiting to write\n", id);
		sleep(randTime);
		printf("Counter thread %d: received a message\n", id);
		sem_wait(&counterSem);
		sharedInt++;
		printf("Counter thread %d: now adding to counter, counter value=%d\n", id, sharedInt);
		sem_post(&counterSem);
	}
}

int main(){
	int i=0;
	pthread_t monitor;
	pthread_t collector;
	pthread_t counter[10];
	buffer = initialize(50);
	
	// Generating different series of pseudo-random numbers
	srand(time(0));
	
	// Initializing semaphores
	sem_init(&counterSem, 0, 1);
	sem_init(&s, 0, 1);
	sem_init(&n, 0, 0);
	sem_init(&e, 0, 50);
	
	// Threads creation
	pthread_create(&monitor, NULL, monitorFunc, NULL);
	pthread_create(&collector, NULL, collectorFunc, NULL);
	for(i=0; i<10; i++){
		pthread_create(&counter[i], NULL, counterFunc, (void *)(intptr_t)i);
	}
	
	// Threads joining
	pthread_join(monitor, NULL);
	pthread_join(collector, NULL); 
	for (i = 0; i < 10; i++){
        	pthread_join(counter[i], NULL); 
        }
}
