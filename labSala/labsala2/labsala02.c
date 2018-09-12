/*
	Rebecca Moreira Messias 186416 Turma W

	Objetivo: Este programa simula um jogo de dominó a pontos

	A entrada é:
		Um inteiro N (1 a 28) indicando o número de peças na partida;
		N peças no formato X:Y separadas por espaço, ordenadas de acordo com as jogadas

	A saída é:
		Um número inteiro indicando a quantidaDE total de pontos foi obtido na partida
*/

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	//declaração de variáveis
	int n, aux, pontos=0, soma;
	int extremidade1, extremidade2;
	int x1, y1;

	//leitura da quantidade de peças
	scanf("%d", &n);
	
	//verifico intervalo de n
	if ((n>=1) && (n<=28))
	{
		//leitura da primeira peça
		scanf("%d:%d", &x1, &y1);
	
		extremidade1 = x1;
		extremidade2 = y1;
		/*
			Este 'for' executará os seguintes passos
				1 - Ler uma peça
				2 - verificar se as extremidade da peça equivale a extremidade do tabuleiro
					- se equivaler vai para o bloco correspondente
					- se não executa normalmente				
		*/

		if(n == 1)
			printf("%d", pontos);
		else
		{
			for(aux = 2; aux <= n; aux++)
			{
				soma = 0;
				scanf("%d:%d", &x1, &y1);
		
				if((x1 == extremidade1 && y1==extremidade2) && (x1 < y1))
				{
					extremidade1 = y1;
					soma = extremidade1+extremidade2;
					if (soma%4 == 0)
						pontos -= soma;
					else if (soma%5 == 0)
						pontos += soma;
				}

				else if((x1 == extremidade1 && y1==extremidade2) && (x1 >= y1))
				{
					extremidade2 = x1;
					soma = extremidade1+extremidade2;
					if (soma%4 == 0)
						pontos -= soma;
					else if (soma%5 == 0)
						pontos += soma;
				}

			 	else if((y1 == extremidade1 && x1==extremidade2) && (x1 < y1))
				{
					extremidade2 = y1;
					soma = extremidade1+extremidade2;
					if (soma%4 == 0)
						pontos -= soma;
					else if (soma%5 == 0)
						pontos += soma;
				}

			 	else if((y1 == extremidade1 && x1==extremidade2) && (x1 >= y1))
				{
					extremidade1 = x1;
					soma = extremidade1+extremidade2;
					if (soma%4 == 0)
						pontos -= soma;
					else if (soma%5 == 0)
						pontos += soma;
				}

				else 
				{
					if (extremidade1 == x1)
					{
						extremidade1 = y1;
						soma = extremidade1+extremidade2;
						if (soma%4 == 0)
							pontos -= soma;
						else if (soma%5 == 0)
							pontos += soma;
					}
					else if (extremidade1 == y1)
					{
						extremidade1 = x1;
						soma = extremidade1+extremidade2;
						if (soma%4 == 0)
							pontos -= soma;
						else if (soma%5 == 0)
							pontos += soma;
					}
					else if (extremidade2 == x1)
					{
						extremidade2 = y1;
						soma = extremidade1+extremidade2;
						if (soma%4 == 0)
							pontos -= soma;
						else if (soma%5 == 0)
							pontos += soma;
					}
					else if (extremidade2 == y1)
					{
							extremidade2 =x1;
							soma = extremidade1+extremidade2;
							if (soma%4 == 0)
								pontos -= soma;
							else if (soma%5 == 0)
								pontos += soma;
					}
				}
			}
		}
	}

	//printa a pontuação final
	printf("%d",pontos);

	return 0;	
}



































