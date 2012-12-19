#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define BUFFER_SIZE 5

void checker(int );

int main(){
	int shmid, semid ;
	//crea memoria compartida para el buffer circular
	shmid = shmget(0xa, BUFFER_SIZE, IPC_CREAT|IPC_EXCL|0600);
	checker(shmid);
	
	//crea memoria compartida para el guardar la cantidad de  producciones  
	shmid = shmget(0xb, sizeof(int), IPC_CREAT|IPC_EXCL|0600);
	checker(shmid);
	
	//creates mutual exclusion Semaphore
	//creates Semaphore to lock producer when buffer is full
	//creates Semaphore to lock consumer when buffer in empty
	semid = semget(0xa,3,IPC_CREAT|IPC_EXCL|0600);
	checker(semid);
	
	exit(0);
};

void checker(int shmid){
	//si shmid = -1 el shmget no tuvo exito
	if (shmid == -1) {
		printf("FAILURE: couldnt get enough memory\n");
	} else {
		printf("SUCCESS\n");
	};	
};
