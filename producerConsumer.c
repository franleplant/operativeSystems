#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_SIZE 10

int producir();

void * productor();
void * consumidor();


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t 	cp = PTHREAD_COND_INITIALIZER,
				cc = PTHREAD_COND_INITIALIZER;


int in = 0,
	out = 0,
	buffer_elements = 0,
	buffer [BUF_SIZE];

int main(){
	pthread_t prod, cons;
	
	pthread_create(&prod, NULL, productor, NULL);
	pthread_create(&cons, NULL, consumidor, NULL);
	
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
		
	exit(0);
};


void * productor(){
	int newProduct;
	while(1){
		newProduct = producir();
		pthread_mutex_lock(&m); 
			if (buffer_elements == BUF_SIZE) { //si esta LLENO entonces espera
				pthread_cond_wait(&cp, &m);
			};
			buffer [in] = newProduct;
			in = (in + 1) % BUF_SIZE;
			buffer_elements ++; 
			printf("productor(): agregué %c\n", newProduct);
			pthread_cond_signal(&cc);
		pthread_mutex_unlock(&m);
	};
};
void * consumidor(){
	int auxProduct;
	sleep(12);
	while(1){
		pthread_mutex_lock(&m);
			if (buffer_elements == 0) { //si esta VACIO entonces espera
				pthread_cond_wait(&cc, &m);
			};
			auxProduct = buffer [out];
			out = (out + 1) % BUF_SIZE;
			buffer_elements --;
			printf("consumidor(): saqué %c\n", auxProduct);
			pthread_cond_signal(&cp);
		pthread_mutex_unlock(&m);
	};
};

int producir(){
   static int letra = 'A'-1 ;
   
   if (letra == 'Z') { 
        letra = 'A';
   } else {
        letra++ ;
   };
   sleep(1);
   return letra ;
};
