#include <stdio.h>
#include <stdlib.h>
#include "operIPC.h"
#include <sys/types.h>
#include <sys/shm.h>



int productGET();

int main(){
	int product, semid, bufid, 
		in = 0;
	char * buffer;
	
	semid = semget(0xa, 0, 0);
	bufid = shmget(0xa, 0, 0);
	
	buffer = (char *) shmat(bufid, 0, 0);
	
	while(1){
		product = productGET();
		
		
		P(semid, SEM_E);	
		P(semid, SEM_S);
			buffer [in] = product;
			printf("producer(): inserted %c \n",product);
		V(semid, SEM_S);
		V(semid, SEM_N);
		
		in = (in + 1) % BUFFER_SIZE;
	};
	
	exit(0);
};



int productGET(){
   static int letra = 'A'-1 ;
   
   if (letra == 'Z') { 
        letra = 'A';
   } else {
        letra++ ;
   };
   sleep(1);
   return letra ;
};
