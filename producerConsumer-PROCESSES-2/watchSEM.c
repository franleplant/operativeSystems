#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
	
#define BUFFER_SIZE 5
#define SEM_S  0
#define SEM_N  1
#define SEM_E  2
	
int main() {	
	int semid, i;

	semid = semget(0xa, 0, 0);
	printf("semid = %d\n", semid);
	//si visualiza en pantalla semid = -1 el semget no pudo obtener el semid
	
	if (semid != -1){
		for (i=0; i<3; i++){
			printf("Semaforo = %d\n",semctl(semid,i,GETVAL)); //muestra el valor de semaforo 
		};
	};
	
	exit(0);
};
