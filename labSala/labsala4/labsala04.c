#include <stdio.h>

#define MAX_EXPO 50
#define MAX_MONOMIO 52
#define TAM_RESULTADO 101

void lerPolinomio (int coeficiente[], int expoente[], char sinal[], int tamanho) {
	int i;
	for(i = 0; i < tamanho; i++) {
		scanf(" %c %d x^%d", &sinal[i], &coeficiente[i], &expoente[i]);
	}
}

void produtoPolinomio (int coeficiente1[MAX_MONOMIO], int coeficiente2[MAX_MONOMIO], int coeficienteR[TAM_RESULTADO],
					   int expoente1[MAX_EXPO], int expoente2[MAX_EXPO], int expoenteR[TAM_RESULTADO],
					   char sinal1[MAX_MONOMIO], char sinal2[MAX_MONOMIO], char sinalR[TAM_RESULTADO],
					   int tam1, int tam2, int qtdMonomio) {

	int h, i, j, aux1 = 0, aux2 = 0;	
	for (h = 0; h < qtdMonomio; h++) {
		for (i = aux1; i < tam1; i++) {
			for (j = aux2; j < tam2; j++) {
				if (sinal1[i] == sinal2[j])
					sinalR[h] = '+';
				else
					sinalR[h] = '-';

				coeficienteR[h] = coeficiente1[i]*coeficiente2[j];

				expoenteR[h] = expoente1[i]+expoente2[j];

				if (j == tam2 - 1) {
					i++;
					j = 0;				
				}
				else
					j++;

				aux1 = i;
				aux2 = j;
				break;
			}
			
			break;
		}
	}
}

void imprimePolinomio (int coeficienteR[TAM_RESULTADO], 
					   int expoenteR[TAM_RESULTADO], 
					   char sinalR[TAM_RESULTADO], int maiorExpR) {
	int expAtual = 0, i;
	printf("%d\n", maiorExpR);

	while (expAtual != maiorExpR) {
		for (i = 0; i < maiorExpR; i++) {
			//if (expAtual == maiorExpR && expAtual == expoenteR[i] && coeficienteR[i] != 0) {
				//printf("%c %d x^%d\n", sinalR[i], coeficienteR[i], expoenteR[i]);
			//}
			if (expAtual == expoenteR[i] && coeficienteR[i] != 0) {
				printf("%c %d x^%d ", sinalR[i], coeficienteR[i], expoenteR[i]);
			}
		}
		expAtual++;
	}
	printf("%c %d x^%d\n", sinalR[i], coeficienteR[i], expoenteR[i]);
			
}

int maiorExpoente (int expoente[], int tamanho) {
	int maior, i;
	maior = expoente[0];		
	for (i = 0; i < tamanho; i ++)
		if (expoente[i] > maior)
			maior = expoente[i];

	return maior;
}

void somaMonomios (int coeficiente[], int expoente[], char sinal[], int tamanho) {
	int i, j;
	for(i = 0; i < tamanho; i++) {
		for (j = i+1; j < tamanho; j++) {
			if (coeficiente[i] == 0)
				break;
			
			if (expoente[i] == expoente[j]) {
				if (sinal[i] == sinal[j]) {
					coeficiente[i] += coeficiente[j];
					coeficiente[j] = 0;
				}
				if (sinal[i] != sinal[j] && sinal[i] == '+') {
					if (coeficiente[i] > coeficiente[j]) {
						coeficiente[i] -= coeficiente[j];
						coeficiente[j] = 0;
					}
					if (coeficiente[i] == coeficiente[j]) {
						coeficiente[i] = 0;
						coeficiente[j] = 0;
					}
					if (coeficiente[i] < coeficiente[j]) {
						coeficiente[i] = coeficiente[j] - coeficiente[i];
						coeficiente[j] = 0;	
						sinal[i] = '-';
					}
					
				}
				if (sinal[i] != sinal[j] && sinal[i] == '-') {
					if (coeficiente[i] > coeficiente[j]) {
						coeficiente[i] -= coeficiente[j];
						coeficiente[j] = 0;
					}
					if (coeficiente[i] == coeficiente[j]) {
						coeficiente[i] = 0;
						coeficiente[j] = 0;
					}
					if (coeficiente[i] < coeficiente[j]) {
						coeficiente[i] = coeficiente[j] - coeficiente[i];
						coeficiente[j] = 0;	
						sinal[i] = '+';
					}
				}
			}
		}
	}
}

int main() {
	int tam1, tam2, maiorExp1, maiorExp2, maiorExpR;
	int coeficiente1[MAX_MONOMIO], coeficiente2[MAX_MONOMIO], coeficienteResultado[TAM_RESULTADO];
	int expoente1[MAX_EXPO], expoente2[MAX_EXPO], expoenteResultado[TAM_RESULTADO];
	char sinal1[MAX_MONOMIO], sinal2[MAX_MONOMIO], sinalResultado[TAM_RESULTADO];

	scanf(" %d", &tam1);

	lerPolinomio(coeficiente1, expoente1, sinal1, tam1);
	
	maiorExp1 = maiorExpoente(expoente1, tam1);

	scanf(" %d", &tam2);

	lerPolinomio(coeficiente2, expoente2, sinal2, tam2);

	maiorExp2 = maiorExpoente(expoente2, tam2);

	maiorExpR = maiorExp1+maiorExp2;

	produtoPolinomio(coeficiente1, coeficiente2, coeficienteResultado, 
					 expoente1, expoente2, expoenteResultado,
					 sinal1, sinal2, sinalResultado, tam1, tam2, tam1*tam2);

	somaMonomios(coeficienteResultado, expoenteResultado, sinalResultado, tam1*tam2);
	
	imprimePolinomio(coeficienteResultado, expoenteResultado, sinalResultado, maiorExpR);
	
	return 0;
		
}
