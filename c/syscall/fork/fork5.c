#include <stdio.h>
#include <unistd.h>
# include <sys/wait.h>

//                          (principal)
//                               |
//              +----------------+--------------+
//              |                               |
//           filho_1                         filho_2
//              |                               |
//    +---------+-----------+          +--------+--------+
//    |         |           |          |        |        |
// neto_1_1  neto_1_2  neto_1_3     neto_2_1 neto_2_2 neto_2_3

// ~~~ printfs  ~~~
//      principal (ao finalizar): "Processo principal %d finalizado\n"
// filhos e netos (ao finalizar): "Processo %d finalizado\n"
//    filhos e netos (ao inciar): "Processo %d, filho de %d\n"

// Obs:
// - netos devem esperar 5 segundos antes de imprmir a mensagem de finalizado (e terminar)
// - pais devem esperar pelos seu descendentes diretos antes de terminar

int main(int argc, char** argv) {

	pid_t filho1;
	pid_t filho2;
	pid_t neto1;
	pid_t neto2;
	pid_t projenitor;


	filho1 = fork();

	if(filho1 == 0) { //se filho1 for == 0 quer dizer que estamos rodando ele
		printf("Processo %d, filho de %d\n", getpid(),getppid());
		for(int i = 0; i < 3; i++) { // vamos rodar isso aqui 3x
			neto1 = fork();
			if(neto1 == 0) { // se for o neto
				printf("Processo %d, filho de %d\n", getpid(),getppid());
				projenitor = getppid();
				sleep(5); // espera os 5 segundos
				printf("Processo %d finalizado\n",getpid());
				return(0); // como n queremos q os netos continuem no cC3digo, podemos acabar com eles por aqui por garantia
			} else { // no caso, se nC#o for o neto, sC3 pode ser o filho, pq o pai nao entra aqui
				continue; // acho que n precisamos fazer nada aqui, ent so continuamos
			}
		} // apos aqui quer dizer q o filho jah fez seus 3 netos, e sC3 o filho1 == 0 estC! aqui
		while(wait(NULL) > 0); // para garantir q os netos terminem suas tarefas primero
		printf("Processo %d finalizado\n",getpid());
		return(0); // apos ele ser finalizado podemos dar return nele para evitar possiveis problemas
	} else { // agora quer dizer q eh o principal q estah aqui, ent vamos dar o outro fork
		filho2 = fork();

		if(filho2 == 0) { //se filho2 for == 0 quer dizer que estamos rodando ele
			printf("Processo %d, filho de %d\n", getpid(),getppid());
			for(int i = 0; i < 3; i++) { // vamos rodar isso aqui 3x
				neto2 = fork();

				if(neto2 == 0) { // se for o neto
					printf("Processo %d, filho de %d\n", getpid(),getppid());
					projenitor = getppid();
					sleep(5); // espera os 5 segundos
					printf("Processo %d finalizado\n",getpid());
					return(0); // como n queremos q os netos continuem no cC3digo, podemos acabar com eles por aqui por garantia
				} else { // no caso, se nC#o for o neto, sC3 pode ser o filho, pq o pai nao entra aqui
					continue; // acho que n precisamos fazer nada aqui, ent so continuamos
				}
			} // apos aqui quer dizer q o filho jah fez seus 3 netos, e sC3 o filho2 == 0 estC! aqui
			while(wait(NULL) > 0); // para garantir q os netos terminem suas tarefas primero
			printf("Processo %d finalizado\n",getpid());
			return(0); // apos ele ser finalizado podemos dar return nele para evitar possiveis problemas
		} else {
			// se estamos aqui eh pq filho2 != 0, ou seja, somos o principal(como filho1 deu return, soh pode ser o principal aqui)
			while(wait(NULL) > 0); // para garantir q os filhos terminem suas tarefas primero
			printf("Processo %d finalizado\n",getpid());
			return(0); // acaba o programa
		}
	}

}
// ....

/*************************************************
 * Dicas:                                        *
 * 1. Leia as intruC'C5es antes do main().         *
 * 2. FaC'a os prints exatamente como solicitado. *
 * 3. Espere o tC)rmino dos filhos                *
 *************************************************/


// make submission (comando pra criar um tar.gz na pasta de cima da qual o comando foi executado)