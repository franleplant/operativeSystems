#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


#define BUFFER_SIZE 5
#define SEM_S  0
#define SEM_N  1
#define SEM_E  2

int main(){
	int shmid, semid;
	int * dircon;
	char * dirbuf;
	
	//obteins shared circular buffer s shmid to handle it
	shmid = shmget(0xa, 0, 0);
	printf("shmid = %d\n", shmid);
	//if shmid = -1 shmget fails to obtain shmid
	
	if (shmid != -1) {
		dirbuf = (char *) shmat(shmid, 0, 0); //mapea la direccion del shared memory en dirbuf
		if (dirbuf != NULL) {
			memset(dirbuf, '_', BUFFER_SIZE);       
			shmdt(dirbuf);
		};
	};
	
	//obteins shared buffer elements counter s shmid to handle it
	shmid = shmget(0xb, 0, 0);
	printf("shmid = %d\n", shmid);
	//if shmid = -1 shmget fails to obtain shmid
	
	if (shmid != -1) {
		dircon = (int *) shmat(shmid, 0, 0);  //mapea la direccion del shared memory en dircon
		if (dircon != NULL) {
			*dircon = 0;       
			shmdt(dircon);
		};
   };
   
	//Obteins 3 semaphores semid and initialize them
	semid = semget(0xa, 0, 0);
	printf("semid = %d\n", semid); //if semid = -1 semget fails to obtain semid
	
	
	//Initialize semaphores
	if (semid != -1) {
		semctl(semid,SEM_S, SETVAL, 1); //inicializa el semaforo S en 1
		semctl(semid,SEM_N, SETVAL, 0); //inicializa el semaforo N en 0, there are no elements in buffer
		semctl(semid,SEM_E, SETVAL, BUFFER_SIZE); //inicializa el semaforo E en BUFFER_SIZE, there are BUFFER_SIZE empty spaces in buffer
	};

	exit(0);
};
