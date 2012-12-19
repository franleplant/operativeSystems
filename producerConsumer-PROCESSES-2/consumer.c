#include <stdio.h>
#include <stdlib.h>
#include "operIPC.h"
#include <sys/types.h>
#include <sys/shm.h>


int main(){
	int product, semid, bufid, 
		out = 0;
	char * buffer;
	
	semid = semget(0xa, 0, 0);
	bufid = shmget(0xa, 0, 0);
	
	buffer = (char *) shmat(bufid, 0, 0);
	
	while(1){
		
		P(semid, SEM_N);	
		P(semid, SEM_S);
			sleep(1);
			product = buffer [out];
			printf("consumer(): removed %c \n",product);
		V(semid, SEM_S);
		V(semid, SEM_E);
		
		out = (out + 1) % BUFFER_SIZE;
	};
	
	exit(0);
};
