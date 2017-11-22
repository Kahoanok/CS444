// Concurrency 1: The Producer-Consumer Problem
// Shawn Cross and Ryan Crane
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"mt19937.h"
#include<semaphore.h>
#include<stdlib.h>
#include<time.h>

struct node{
   struct node * next;
   int val;
};

struct node * head = NULL;
int size;
int counter_i = 0;
int counter_s = 0;
sem_t insert_mutex;
sem_t no_searcher;
sem_t no_inserter;
pthread_mutex_t s_mutex;
pthread_mutex_t i_mutex;

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

void lightswitch_lock() {
   pthread_mutex_lock(&s_mutex);
   counter_s++;
   if( counter_s == 1) {
      sem_wait(&no_searcher);
   }
   pthread_mutex_unlock(&s_mutex);
}

void lightswitch_unlock() {
   pthread_mutex_lock(&s_mutex);
   counter_s--;
   if( counter_s == 0 ){
      sem_post(&no_searcher);
   }
   pthread_mutex_unlock(&s_mutex);
}

void lightswitch1_lock() {
   pthread_mutex_lock(&i_mutex);
   counter_i++;
   if( counter_i == 1) {
      sem_wait(&no_inserter);
   }
   pthread_mutex_unlock(&i_mutex);
}

void lightswitch1_unlock() {
   pthread_mutex_lock(&i_mutex);
   counter_i--;
   if( counter_i == 0 ){
      sem_post(&no_inserter);
   }
   pthread_mutex_unlock(&i_mutex);
}
void insert(struct node * head, int num){
   struct node * current = head;
   while( current->next != NULL ){
      current = current -> next;
   }

   current -> next = malloc( sizeof(struct node));
   current -> next -> val = num;
   current -> next -> next = NULL;
}

int pop( struct node ** head) {
   int retval = -1;
   struct node * next_node = NULL;

   if( *head == NULL ){
      return -1;
   }

   next_node = (*head) -> next;
   retval = (*head) -> val;
   free(*head);

   return retval;
}

int delete(struct node ** head, int n){
   int i;
   int retval = -1;

   struct node * current = *head;
   struct node * temp_node = NULL;

   if( n = 0 ) {
      return pop(head);
   }

   for( i = 0; i < n - 1; i++ ) {
      if( current -> next == NULL ) {
	 return -1;
      }

      current = current -> next;
   }

   temp_node = current -> next;
   retval = temp_node -> val;
   current -> next = temp_node -> next;
   free( temp_node );

   return retval;   
}

void * searcher_start(void* x){
   
   int v = get_num()%10;
   int flag = 0;
   
   lightswitch_lock();
   
   printf("Beginning search\n");
   struct node * current = head;
   while( current != NULL) {
      if ( current -> val == v ) {
	 flag = 1;
      }
      current = current -> next;
   }
   if ( flag == 1 ) {
      printf("I found what I was looking for %i\n", v);
   } else {
      printf("I didn't find what I was looking for\n");
   }
   
   lightswitch_unlock();

}

void * inserter_start(void* x){
   int num = get_num()%10;
   lightswitch1_lock();
   sem_wait(&insert_mutex);
	printf("Beginning insert\n");
   insert(head, num);
   size++;
   printf("Inserted %i into the list\n", num);
   sem_post(&insert_mutex);
   lightswitch1_unlock();
}

void * deleter_start(void* x){

	int index = size;
   	if ( size > 0 ){
		index = get_num() % size;
	}
	sem_wait(&no_searcher);
	sem_wait(&no_inserter);
	printf("Entering delete only\n");

	if( index > 0 ){
		delete(&head, index);
  		size--;
   		printf("deleted index is %i\n", index);
	} else {
	   	printf("nothing to delete\n");
	}
	sem_post(&no_inserter);
	sem_post(&no_searcher);
}

int main(){
head = malloc( sizeof (struct node));
int c=0;

for ( c = 0; c < 1000; c++ ){
	insert(head, c);
}
size = 1000;
unsigned long seed;
pthread_t searcher[10];
pthread_t inserter[10];
pthread_t deleter[10];

	seed = time(NULL);
	init_genrand(seed);
	sem_init(&no_searcher,0,1);
	sem_init(&no_inserter,0,1);
	sem_init(&insert_mutex,0,1);
	for(c=0;c<10;c++){
		pthread_create(&(searcher[c]),NULL,searcher_start,NULL);
		pthread_create(&(inserter[c]),NULL,inserter_start,NULL);
		pthread_create(&(deleter[c]),NULL,deleter_start,NULL);
	}

	while(1){}

return 0;
}

