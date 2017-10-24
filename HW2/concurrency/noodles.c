#include<stdio.h>
#include"mt19937.h"
#include<time.h>
#include<pthread.h>
#include<semaphore.h>

sem_t forks[5];
sem_t badger;
void think(char * name){
unsigned int x;
	printf("%s is now thinking.\n",name);
	x = genrand_int32();
	x = x % 20 + 1;
	sleep(x);
	return;
}

void eat(char * name){
unsigned int x;
	printf("%s is now eating.\n",name);
	x = genrand_int32();
	x = x % 8 + 2;
	sleep(x);
	return;
}

void get_forks(int i, char * name){
	if(i == 0){
		sem_wait(&badger);
		sem_wait(&(forks[i]));
		printf("%s just picked up fork %i\n",name,i);
		sem_wait(&(forks[(i+1)%5]));
		printf("%s just picked up fork %i\n",name,(i+1)%5);
	}
	else{
		sem_wait(&badger);
		sem_wait(&(forks[(i+1)%5]));
		printf("%s just picked up fork %i\n",name,(i+1)%5);
		sem_wait(&(forks[i]));	
		printf("%s just picked up fork %i\n",name,i);
	}
return;
}

void put_forks(int i){
	sem_post(&badger);
	sem_post(&(forks[i]));
	printf("fork %i is now free\n",i);
	sem_post(&(forks[(i+1)%5]));
	printf("fork %i is now free\n",(i+1)%5);
return;
}

void *locke_start(void *x){
while(1){
	think("Locke");
	get_forks(0,"Locke");
	eat("Locke");
	put_forks(0);
}
}
void *descartes_start(void *x){
while(1){
	think("Descartes");
	get_forks(1,"Descartes");
	eat("Descartes");
	put_forks(1);
}
}
void *hobbes_start(void *x){
while(1){
	think("Hobbes");
	get_forks(2,"Hobbes");
	eat("Hobbes");
	put_forks(2);
}
}
void *rand_start(void *x){
while(1){
	think("Rand");
	get_forks(3,"Rand");
	eat("Rand");
	put_forks(3);
}
}
void *marx_start(void *x){
while(1){
	think("Marx");
	get_forks(4,"Marx");
	eat("Marx");
	put_forks(4);
}
}
int main(){
int i = 0;
unsigned long seed;
pthread_t locke;
pthread_t descartes;
pthread_t hobbes;
pthread_t rand;
pthread_t marx;
	
	seed = time(NULL);
	init_genrand(seed);
	sem_init(&badger,0,4);
	for(i = 0;i<5;i++){
		sem_init(&(forks[i]),0,1);
	}

	pthread_create(&locke,NULL,locke_start,NULL);
	pthread_create(&descartes,NULL,descartes_start,NULL);
	pthread_create(&hobbes,NULL,hobbes_start,NULL);
	pthread_create(&rand,NULL,rand_start,NULL);
	pthread_create(&marx,NULL,marx_start,NULL);
	while(1){};

return 0;
}
