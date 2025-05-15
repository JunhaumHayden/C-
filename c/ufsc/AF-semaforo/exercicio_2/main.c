#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

/* ---------- Definições Globais. ---------- */
#define TEMPO_BASE 1000000

typedef enum { 
	CONTINENTE, 
	ILHA 
} cabeceira_t;

typedef struct {
	int id;
	cabeceira_t cabeceira;
	pthread_t thread;
} veiculo_t;
/* ---------------------------------------- */

/* ---------- Variáveis Globais. ---------- */
char cabeceiras[2][11] = { { "CONTINENTE" }, { "ILHA" } };
int total_veiculos;
int veiculos_turno;

// ToDo: Adicione aque quaisquer outras variávels globais necessárias.
// variaveis de controle da ponte
pthread_mutex_t mutex; // mutex para controle de acesso a ponte
sem_t sem_continente, sem_ilha;
int veiculos_na_ponte; // contador de veiculos na ponte
int sentido_atual;     // 0 -> CONTINENTE -> ILHA, 1 -> ILHA -> CONTINENTE
int veiculos_turno_atual;
/* ---------------------------------------- */


/* Inicializa a ponte. */
void ponte_inicializar() {
	pthread_mutex_init(&mutex, NULL);
	sem_init(&sem_continente, 0, veiculos_turno);
	sem_init(&sem_ilha, 0, 0);
	veiculos_na_ponte = 0;
	sentido_atual = CONTINENTE;
	veiculos_turno_atual = 0;

	/* Imprime direção inicial da travessia. NÃO REMOVER! */
	printf("\n[PONTE] *** Novo sentido da travessia: CONTINENTE -> ILHA. ***\n\n");
	fflush(stdout);
}

/* Função executada pelo veículo para ENTRAR em uma cabeceira da ponte. */
void ponte_entrar(veiculo_t *v) {
	if (v->cabeceira == CONTINENTE)
	{
		sem_wait(&sem_continente);
	} else
	{
		sem_wait(&sem_ilha);
	}
	pthread_mutex_lock(&mutex);
	veiculos_na_ponte++;
	veiculos_turno_atual++;
	pthread_mutex_unlock(&mutex);
}

/* Função executada pelo veículo para SAIR de uma cabeceira da ponte. */
void ponte_sair(veiculo_t *v) {
	pthread_mutex_lock(&mutex);
	veiculos_na_ponte--;
	if (veiculos_na_ponte == 0 && veiculos_turno_atual >= veiculos_turno)
	{
		// troca sentido
		sentido_atual = !sentido_atual;
		veiculos_turno_atual = 0;
		if (sentido_atual == CONTINENTE)
		{
			for (int i = 0; i < veiculos_turno; i++)
			{
				sem_post(&sem_continente);
			}
		} else
		{
			for (int i = 0; i < veiculos_turno; i++)
			{
				sem_post(&sem_ilha);
			}
		}
	}
	pthread_mutex_unlock(&mutex);
	/* Você deverá imprimir a nova direção da travessia quando for necessário! */	
	printf("\n[PONTE] *** Novo sentido da travessia: %s -> %s. ***\n\n", cabeceiras[v->cabeceira], cabeceiras[!v->cabeceira]);
	fflush(stdout);
}

/* FINALIZA a ponte. */
void ponte_finalizar() {
	sem_destroy(&sem_continente);
	sem_destroy(&sem_ilha);
	pthread_mutex_destroy(&mutex);
	
	/* Imprime fim da execução! */
	printf("[PONTE] FIM!\n\n");
	fflush(stdout);
}

/* Implementa o comportamento de um veículo. */
void * veiculo_executa(void *arg) {
	veiculo_t *v = (veiculo_t *) arg;
	
	printf("[Veiculo %3d] Aguardando para entrar na ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);

	/* Entra na ponte. */
	ponte_entrar(v);
	printf("[Veiculo %3d] ENTROU na ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);

	/* Faz a travessia. */
	usleep(TEMPO_BASE + rand() % 1000);
	
	/* Seta cabeceira oposta para sair. */
	v->cabeceira = !v->cabeceira;

	/* Sai da ponte na cabeceira oposta. */
	printf("[Veiculo %3d] SAIU da ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);
	ponte_sair(v);

	pthread_exit(NULL);
}

int main(int argc, char **argv) {
 
	if (argc < 3) {
		printf("Indique a quantidade total de veiculos e o numero de veiculos que podem atravessar a ponte por turno:\n\n %s [QTD_TOTAL_VEICULOS] [VEICULOS_POR_TURNO]\n\n", argv[0]);
		return 1;
	}

	total_veiculos = atoi(argv[1]);
	veiculos_turno = atoi(argv[2]);

	if (total_veiculos % (veiculos_turno * 2)) {
		printf("ERRO: O valor [QTD_TOTAL_VEICULOS] deve ser divisivel por ([VEICULOS_POR_TURNO] * 2)!\n\n %s [QTD_TOTAL_VEICULOS] [VEICULOS_POR_TURNO]\n\n", argv[0]);
		return 1;
	}

	srand(time(NULL));

	/* Aloca os veículos. */
	veiculo_t veiculos[total_veiculos];

	ponte_inicializar();

	/* Cria os veículos. */
	for (int i = 0; i < total_veiculos; i++) {
		/* Define o id do veículo. */
		veiculos[i].id = i;
		
		/* Escolhe aleatoreamente se o veículo entra pela ILHA ou CONTINENTE. */
		veiculos[i].cabeceira = i % 2; 
		
		/* Cria a thread veículo. */
		pthread_create(&veiculos[i].thread, NULL, veiculo_executa, (void *) &veiculos[i]);		
	}

	/* Aguarda o término da execução de todos os veículos antes de finalizar o programa. */
	for (int i = 0; i < total_veiculos; i++) {
		pthread_join(veiculos[i].thread, NULL);
	}

	ponte_finalizar();

	return 0;
}