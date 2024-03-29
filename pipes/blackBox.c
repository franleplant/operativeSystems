/*
   tp51.c Pipes. Programa que toma por teclado el numero de sucursal y simula la cantidad de venta de la misma             
   Guillermo Cherencio
   SO
   UTN FRD
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER 255
#define SUC_NUMBER 10

int main() {
   // obtengo nro de sucursal de stdin
   char buffer[MAX_BUFFER];
   read(STDIN_FILENO,buffer,MAX_BUFFER);
   int suc = atoi(buffer);
   srandom(time(0)+suc);
   if ( suc >= 0 && suc < SUC_NUMBER ) { // sucursal valida
      double ventas=((double) random())/10000000.0;
      snprintf(buffer,MAX_BUFFER,"suc[%d]=%lf\n",suc,ventas);
   } else { // sucursal invalida
      snprintf(buffer,MAX_BUFFER,"suc[%d]=%lf\n",suc,-1.0);
   }
   // emito salida por stdout
   write(STDOUT_FILENO,buffer,strlen(buffer));
   return 0;
}
