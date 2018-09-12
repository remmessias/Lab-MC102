/*
	Nome: Rebecca Moreira Messias RA: 186416 Turma: W

	Objetivo: Implementar um programa que informe as demais posições de um navio atingido
	pelo tiro de Joca

	Entrada:
		1. Uma linha contendo dois números inteiros positivos, N e M, que representam o tamanho do tabuleiro,
		tal que 1<=N<=20 e 1<=M<=20. N representa o número de linhas e M representa o número de
		colunas do tabuleiro;

		2. Uma linha com NxM (N vezes M) caracteres representando o tabuleiro, onde * representa água e as
		letras do alfabeto representam os navios. Letras iguais representam o mesmo navio e estão dispostas
		em posições consecutivas no tabuleiro (em uma única linha ou em uma única coluna). Diferentes
		navios não ocupam o mesmo espaço, o número de navios em um tabuleiro é aleatório e o tamanho
		dos navios variam de 1 até 20;

		3. Uma linha contendo um conjunto das posições dos tiros dados por Joca em rodadas diferentes do
		jogo no formato LxCy, onde x e y são números inteiros que representam uma linha e uma coluna
		no tabuleiro. Cada tiro sempre acerta um navio distinto do tiro anterior. A posição L-1C-1 indica o
		término da sequência de tiros.

	Saída:
		A saída consiste de um conjunto de posições, para cada navio, na forma LxCy separados por um espaço e
		ordenado pela menor linha e posteriormente menor coluna. Inclusive a última posição impressa é seguida
		de um espaço. Em casos com mais de um navio, cada linha da saída deve representar as posições de um
		único navio. Note que a posição do primeiro tiro não deve estar contida na saída.
*/

#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 100

int main(){
	//declaração de variáveis
	int linhas, colunas;
	char tabuleiro [TAM_MAX][TAM_MAX];
	int coordenadaX, coordenadaY;

	//leitura da quantidade de linhas e colunas
	scanf(" %d %d", &linhas, &colunas);
	
	//preencho o tabuleiro
	int i, j;
	for(i = 0; i < linhas; i++)
		for(j = 0; j < colunas; j++)
			scanf(" %c", &tabuleiro[i][j]);
	
	scanf(" L%dC%d", &coordenadaX, &coordenadaY);
	
	while (coordenadaX != -1 && coordenadaY != -1) {
		coordenadaX--;
		coordenadaY--;
		char navio = tabuleiro [coordenadaX][coordenadaY];
			
		for (i = 0; i < linhas; i++) {
			for (j = 0; j < colunas; j++) {
				if (tabuleiro[i][j] == navio)
					if (i != coordenadaX || j != coordenadaY)
						printf("L%dC%d ", i+1, j+1);
			}
		}
		printf("\n");
		scanf(" L%dC%d", &coordenadaX, &coordenadaY);
    }
	return 0;
}
