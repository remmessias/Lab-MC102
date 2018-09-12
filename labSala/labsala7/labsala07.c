/*
	Nome: Rebecca Moreira Messias RA: 186416 Turma: W

	OBS: Fiz poucos comentários, pois acredito que as variáveis estejam com bons nomes.
	
	Boa correção e boas férias!! :D
*/

#include <stdio.h>

#define SENO 'S'
#define COSSENO 'C'
#define FIM 'F'
#define fim 'f'

/*Esta funcao calcula o fatorial de um numero inteiro.
  Recebe um inteiro e retorna o fatorial deste numero como um numero inteiro.*/
int fatorial(int numero)
{
	if (numero == 0 || numero == 1) {
		return 1;
	}
	
	return numero * fatorial(numero-1);
}

/*Esta funcao calcula a potencia inteira positiva de um numero double.
  Recebe um double e um inteiro e calcula o valor do double elevado ao inteiro.
  Retorna o valor do calculo em double.*/
double potencia(double base, int expoente) {
	if (expoente == 0)
		return 1;
	if (expoente == 1)
		return base;
	if (base == 0)
		return 0;
	if (base == 1)
		return 1;
	
	return base * potencia(base, expoente-1);
}

/*Esta funcao calcula um valor aproximado para a funcao seno em um ponto proximo de 0.
  Recebe um numero do tipo double e um limite de iteracoes para calcular o valor de
  seno no ponto do double fazendo n+1 (i=0 até i=n) iteracoes na série de Maclaurin.*/
double seno(double ponto, int indice) {
	if (indice == 0) {
		return ((potencia(-1, indice)/fatorial((2*indice)+1)) * potencia (ponto, (2*indice)+1));
	}
	
	return ((potencia(-1, indice)/fatorial((2*indice)+1)) * potencia (ponto, (2*indice)+1)) + seno (ponto, indice-1);
}

/*Esta funcao calcula um valor aproximado para a funcao cosseno em um ponto proximo de 0.
  Recebe um numero do tipo double e um limite de iteracoes para calcular o valor de
  cosseno no ponto do double fazendo n+1 (i=0 até i=n) iteracoes na serie de Maclaurin.*/
double cosseno(double ponto, int indice) {
	if (indice == 0) {
			return ((potencia(-1, indice)/fatorial(2*indice)) * potencia(ponto, 2*indice));
	}

	return ((potencia(-1, indice)/fatorial(2*indice)) * potencia(ponto, 2*indice)) + cosseno (ponto, indice-1);
}

//Essa função informa o valor do seno para o usuário
void escreveSeno (double ponto, double seno) {
	printf("O valor aproximado de seno no ponto %.4lf eh %.4lf.\n", ponto, seno);
}

//Essa função informa o valor do cosseno para o usuário
void escreveCosseno (double ponto, double cosseno) {
	printf("O valor aproximado de cosseno no ponto %.4lf eh %.4lf.\n", ponto, cosseno);
}

//Essa função informa ao usuário que ele digitou um comando inválido
void escreveMensagem () {
	printf("Comando invalido. Entre com outro comando, ou 'F' para terminar.\n");
}

//Essa função lê um caracter
void leCaracter (char *caracter) {
	scanf(" %c", &(*caracter));
}

//Essa função lê um double
void leDouble (double *numero) {
	scanf(" %lf", &(*numero));
}

//Essa função lê um inteiro
void leInteiro (int *numero) {
	scanf(" %d", &(*numero));
}

int main () {
	char opcao;
	double ponto;
	int indice;

	leCaracter(&opcao);
	do {
		if (opcao != COSSENO && opcao != SENO && opcao != FIM && opcao != fim){
			escreveMensagem();
		}
		else {
			switch (opcao) {
			case SENO:
				leDouble(&ponto);
				leInteiro(&indice);
				escreveSeno(ponto, seno(ponto, indice));
				break;
			case COSSENO:
				leDouble(&ponto);
				leInteiro(&indice);
				escreveCosseno(ponto, cosseno(ponto, indice));
				break;
			}
		}

		leCaracter(&opcao);	
	
	} while (opcao != FIM && opcao != fim);

	return 0;
}
