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
	int pipePapi[2];
    int cantProcesos = atoi(argv[1]);
    int numeroInicial= atoi(argv[2]); 
    int S            = atoi(argv[3]); 
    //printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer[0], start);
    
   	/* El padre crea n pipes */
   	if(pipe(pipePapi)){
   		perror("Error en generar pipe papi");
   			
   	} 
   	int pipes[cantProcesos][2]; 
   	for (int i = 0; i < cantProcesos; i++){
   		if(pipe(pipes[i])){
   			perror("Error en generar pipe");
   		}	
   	} 
 	
 	/* El padre crea n hijos que conocen todos los pipes */
 	int numeroIndice = 0; 
 	
	for (int i = 0; i < cantProcesos ; i++){
   		pid = fork();
   		
   		if (!pid){
   			break;
   		}	
   		numeroIndice++;
   	} 
	/* Si soy un padre... */
	if(pid){
		int finalCadena;
		read(pipePapi[0],&finalCadena,4);
		printf("El numero final es.... %d\n", finalCadena);	
		//Cerrar procesos
		for (int i = 0; i < cantProcesos; i++) {	
	    	close(pipes[i][0]);
	    	close(pipes[i][1]);
    	}
		close(pipePapi[0]);
		close(pipePapi[1]);
		exit(0);
	}
   	//Si soy hijo 
    if(numeroIndice == S){
    	write(pipes[(numeroIndice +1) % cantProcesos][1], &numeroInicial, 4);
    	printf("Mando el primer numero! %d y lo printea el proceso %d \n", numeroInicial, numeroIndice);	
    }
    int miNumero;
    read(pipes[numeroIndice][0],&miNumero,4);
    if (numeroIndice == S){
    	write(pipePapi[1],&miNumero,4);
    }
    // Si soy cualquier hijo 
    else{miNumero++;
    printf("Vamos por el numero  %d y lo printea el proceso %d \n", miNumero,numeroIndice);	
    write(pipes[(numeroIndice +1) % cantProcesos][1], &miNumero, 4);
    }
    //Cierro TODOS los pipes  
    for (int i = 0; i < cantProcesos; i++) {	
	    close(pipes[i][0]);
	    close(pipes[i][1]);
    }
	close(pipePapi[0]);
	close(pipePapi[1]);
    exit(0);

	/* Si soy el padre...  */
	/* COMPLETAR */
}
