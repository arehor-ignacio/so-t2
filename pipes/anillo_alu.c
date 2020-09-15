#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{	
	int status, pid, n;
	int buffer[1];

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
    /* Parsing de los argumentos */
  	/* COMPLETAR */
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer[0], start);
    
   	/* El padre crea n pipes */
   	/* COMPLETAR */

 	/* El padre crea n hijos que conocen todos los pipes */
	/* COMPLETAR */


	/* Si soy un hijo... */
    /* COMPLETAR */

	/* Si soy el padre...  */
	/* COMPLETAR */
}
