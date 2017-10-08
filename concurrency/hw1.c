#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"mt19937ar.c"
#include<semaphore.h>

struct thing{
   unsigned int value;
   unsigned int work;
};

struct thing things[32];
int i=0;
pthread_mutex_t mutex;
int get_num(){
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
      naan = __builtin_ia32_rdrand32_step(&naan);
   }
   else{
      naan = genrand_int32();
   }
return naan;
}

void * producer_start(void* x){
   
}


int main(){
pthread_t prod;
pthread_t cons[2];


   return 0;
}
