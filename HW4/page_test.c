#define _GNU_OURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include "mt19937.h"
#include <time.h>

#define SYS_test1 359
#define SYS_test2 360

struct thing {
   unsigned int x;
   unsigned int j;
};

int main() {
   printf("syscall 359: %lu\n", syscall(SYS_test1));
   printf("syscall 360: %lu\n", syscall(SYS_test2));

   int i;
   unsigned long seed;
   int * things[10000];
   
   seed = time(NULL);
   init_genrand(seed);

   printf("mallocing\n");
   for( i = 0; i < 10000; i++){
      things[i] = malloc(genrand_int32()*sizeof(int));
      if ( i%1000 == 0 ){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nfreeing\n");
   for( i = 0; i < 10000; i++){
      free(things[i]);
      if(i%1000 == 0){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nmallocing\n");
   for( i = 0; i < 10000; i++){
      things[i] = malloc(genrand_int32()*sizeof(int));
      if ( i%1000 == 0 ){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nfreeing\n");
   for( i = 0; i < 10000; i++){
      free(things[i]);
      if(i%1000 == 0){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nmallocing\n");
   for( i = 0; i < 10000; i++){
      things[i] = malloc(genrand_int32()*sizeof(int));
      if ( i%1000 == 0 ){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nfreeing\n");
   for( i = 0; i < 10000; i++){
      free(things[i]);
      if(i%1000 == 0){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nmallocing\n");
   for( i = 0; i < 10000; i++){
      things[i] = malloc(genrand_int32()*sizeof(int));
      if ( i%1000 == 0 ){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nfreeing\n");
   for( i = 0; i < 10000; i++){
      free(things[i]);
      if(i%1000 == 0){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nmallocing\n");
   for( i = 0; i < 10000; i++){
      things[i] = malloc(genrand_int32()*sizeof(int));
      if ( i%1000 == 0 ){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
   printf("\nfreeing\n");
   for( i = 0; i < 10000; i++){
      free(things[i]);
      if(i%1000 == 0){
      	printf("syscall 359: %f\n", (float)syscall(SYS_test2)/
	      (float)syscall(SYS_test1));
      }
   } 
 
 
 

   return 0;
}
