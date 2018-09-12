/**************************************************
*	Universidade Estadual de Campinas             *
*	Instituto de Computação                       *
*	MC102 - TURMA: WY                             *
*	labSala06 - 08/06/2016                        *
*	ARQUIVO DE SUPORTE - IMPRIMIR HIERARQUIA      *
***************************************************/

/*
	Nome: Rebecca Moreira Messias RA: 186416 Turma: W

	Entrada:
		-> Uma linha contendo o valor k
		-> Uma linha contendo os caracteres separados por espaço

	Saída:
		-> (2^k) - 1 linhas contendo a hierarquia encontrada

	OBSERVAÇÕES:
		1- Decidi explicar aqui as minha condições de paradas da recursão.
		   Para isso utilizei dois if's. No primeiro é caso o vetor tenha 
		   apenas um elemento segundo é para quando o subvetor possuir mais 
		   que 3 elementos e o terceiro é para quando sobrar só 3 elementos, 
		   que é a condição básica.
		2- Boa correção!! o/
*/

#include<stdio.h>
#include<math.h>

void mostraHierarquia(char vet[], int esq, int dir, int nivel, int tam) {
	int i, meio = ((dir+esq)/2), qtdTracos = nivel * 5;
	if (dir-esq == 0){
		printf("%c\n", vet[0]);
	}
	if (dir-esq > 2) {
		/*avanca na recursao pela direita*/
		mostraHierarquia(vet, meio+1, dir, nivel+1, tam);
	
		//escreve a hierarquia do meio, no for printa os traços e depois o caracter
		for (i = 0; i < qtdTracos; i++) {
			printf("-");
		}
		printf("%c\n", vet[meio]);
		
		/*avanca na recursao pela esquerda*/
		mostraHierarquia(vet, esq, meio-1, nivel+1, tam);
	}
	if (dir-esq == 2) {
		//printa a ponta da direita
		for (i = 0; i < qtdTracos+5; i++) {
			printf("-");
		}
		printf("%c\n", vet[dir]);

		//printa o meio
		for (i = 0; i < qtdTracos; i++) {
			printf("-");
		}
		printf("%c\n", vet[meio]);

		//printa a ponta da esquerda
		for (i = 0; i < qtdTracos+5; i++) {
			printf("-");
		}
		printf("%c\n", vet[esq]);
	}
}

int main(void)
{
	int i,k,tam;

	/*leitura da variavel k*/
	scanf(" %d", &k);

	/*encontrar o tamanho do vetor*/
	tam = pow(2, k) - 1; 

	char vetor[tam];
	/*leitura do vetor*/
	for (i = 0; i < tam; i++) {
		scanf(" %c", &vetor[i]);
	}

	/*chamada da funcao*/
	mostraHierarquia(vetor, 0, tam-1, 0, tam);

	return 0;
}

