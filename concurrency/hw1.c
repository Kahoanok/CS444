// Concurrency 1: The Producer-Consumer Problem
// Shawn Cross and Ryan Crane
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"mt19937ar.c"
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>

struct thing{
   unsigned int value;
   unsigned int work;
};

struct thing *things[32];
int i=0;
sem_t spaces;
sem_t items;
pthread_mutex_t mutex;

unsigned int get_num(){
unsigned int eax;
unsigned int ebx;
unsigned int ecx;
unsigned int edx;
char vendor[13];
unsigned int naan;

	eax=0x01;

   	__asm__ __volatile__(
	    "cpuid;"
	    : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	    : "a"(eax)
	);
   	if(ecx & 0x400000000){
   		__asm__ __volatile__(
	   	   "rdrand %0;"
	   	   : "=r"(naan)
	);
   	}
   	else{
      		naan = genrand_int32();
   	}
	return naan;
}

void * producer_start(void* x){
int wait;
int y,z;
struct thing * temp;

	while(1){
		wait = get_num() % 5 + 3;
		sleep(wait);

		temp = malloc(sizeof(struct thing));
		z = get_num();
		y = get_num() % 8 + 2;
		temp->value = z;
		temp->work = y;

		sem_wait(&spaces);
		pthread_mutex_lock(&mutex);
		things[i] = temp;
		i++;
		pthread_mutex_unlock(&mutex);
		sem_post(&items);
	}   
}


void * consumer_start(void *x){
struct thing* temp;

	while(1){
		sem_wait(&items);
		pthread_mutex_lock(&mutex);
		temp = things[i-1];
		i--;
		pthread_mutex_unlock(&mutex);
		sem_post(&spaces);

		sleep(temp->work);
		printf("The value is: %u\n",temp->value);
		free(temp);
	}
}

int main(){
int c=0;
unsigned long seed;
pthread_t prod[5];
pthread_t cons[5];

	seed = time(NULL);
	init_genrand(seed);
	sem_init(&items,0,0);
	sem_init(&spaces,0,32);

	for(c=0;c<5;c++){
		pthread_create(&(prod[c]),NULL,producer_start,NULL);
	}
	for(c=0;c<5;c++){
		pthread_create(&(cons[c]),NULL,consumer_start,NULL);
	}

	while(1){}

return 0;
}
