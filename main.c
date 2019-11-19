#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <pthread.h>

int n;
int totalPrimo = 0;
int numeroAtual = 1;
pthread_mutex_t mutex;

void verificaPrimo(void *arg);

int main(void) {
	setlocale(LC_ALL,"Portuguese");
	int i,j,threads;
    printf("Digite a quantidade de números a processar: ");
	scanf("%d",&n);
	printf("Digite a quantidade de threads a criar: ");
	scanf("%d",&threads);

    if( pthread_mutex_init(&mutex, NULL) != 0){
 		fprintf(stderr, "Erro ao criar mutex.\n");
 		exit(EXIT_FAILURE);
 	}

	pthread_t tid[n];

    for(i = 0; i<threads;i++){
		pthread_create(&tid[i], NULL, verificaPrimo,(int *)i);
	}
	for(j = 0; j<=threads;j++){
    	pthread_join(tid[j],NULL);
	}
	pthread_mutex_lock (&mutex);
   	printf("O número total de números primos encontrados foi: %d",totalPrimo);
   	pthread_mutex_unlock (&mutex);
	pthread_mutex_destroy(&mutex);
  	printf("\n(fim da execução)");
    return 0;
}

void verificaPrimo(void *arg){

	int i,resultado,aux;

    pthread_mutex_lock (&mutex);
    aux = numeroAtual;
    numeroAtual++;
    pthread_mutex_unlock (&mutex);

	while(aux<=n){

		resultado = 1;

	    for( i = 2; i <= (aux-1); i++){

		      if (aux % i == 0){
		            resultado = 0;
		            break;
		       }
	    }
        if(resultado == 1) {
		    printf("Thread %d: O número %d é primo\n",(int*)arg,aux);
			pthread_mutex_lock (&mutex);
		  	totalPrimo++;
	    	pthread_mutex_unlock(&mutex);
	    }else{
		   	printf("Thread %d: O número %d não é primo\n",(int*)arg,aux);
		}

	    pthread_mutex_lock (&mutex);
	    aux = numeroAtual;
	    numeroAtual++;
		pthread_mutex_unlock(&mutex);
	}

}
