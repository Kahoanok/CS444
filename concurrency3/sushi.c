// Concurrency 3 problem 1 
// Shawn Cross and Ryan Crane
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"mt19937.h"
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>

int eating = 0;
int waiting = 0;
sem_t block;
int must_wait = 0;
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

void * sushi_start(void* x){
   while(1){
	sleep((get_num()%10)+1);
	pthread_mutex_lock(&mutex);
	
	if(must_wait == 1){
		waiting++;
		printf("I must wait, there are %d threads waiting\n", waiting);
		pthread_mutex_unlock(&mutex);
		sem_wait(&block);
		waiting--;
	}

	eating++;
	printf("I am now eating, there are %d threads eating\n", eating);
	if(eating == 3){
		must_wait = 1;
	}	   
	if(waiting && !must_wait){
		sem_post(&block);
	}
	else{
		pthread_mutex_unlock(&mutex);
	}
	
	sleep((get_num()%5)+1);

	pthread_mutex_lock(&mutex);
	eating--;
	printf("I am done eating %i\n", eating);
	if(eating==0){
		must_wait = 0;
		printf("everyone left\n");
	}
	if(waiting && !must_wait){
		sem_post(&block);	
	}
	else{
		pthread_mutex_unlock(&mutex);
	}
	sleep((get_num()%5)+1);
   }
}



int main(){
unsigned long seed;
int c = 0;
pthread_t eaters[7];
	seed = time(NULL);
	init_genrand(seed);
	sem_init(&block,0,0);

	for(c = 0; c<7; c++){
		pthread_create(&(eaters[c]),NULL,sushi_start,NULL);
	}

	while(1){}

return 0;
}
