//Rebecca Moreira Messias RA:186416 Turma 
/*
	Descrição dos objetivos do programa:

	Esse programa tem por objetivo criar um codigo para um funcionário
	na empresa ABC

	Entrada -> inteiro : codigo
	Saída -> inteiro : codigoFinal

*/

//incluindo biliotecas para entrada/saida
#include <stdio.h>

int main(void)
{
	//declaração de variáveis que serão utilizadas
	int codigo, numero1, numero2, numero3, numero4, auxiliar, media, codigoFinal;
	
	//leitura do código digitado pelo usuário
	scanf("%d", &codigo);
	
	//para conseguir o primeiro numero divido por 1000
	numero1 = codigo/1000; 
	
	// o resto da divisão acima eu armazeno em aux
	auxiliar = codigo%1000; 
	
	//para conseguir o segundo numero divido por 100
	numero2 = auxiliar/100;

	//o resto da divisão acima eu armazeno em aux
	auxiliar = auxiliar%100;

	//para conseguir o terceiro numero divido por 10
	numero3 = auxiliar/10;

	//para conseguir o quarto numero pego o resto da divisão acima
	numero4 = auxiliar%10;

	//faço a media -> somo os 4 números obtidos e divido por 4
	media = (numero1 + numero2 + numero3 + numero4)/4;
	
	//multiplico por 10000 para mudar a ordem do número
	codigoFinal = media*10000;
	
	//e somo com o código para poder gerar o código final
	codigoFinal = codigoFinal+codigo;

	//printo para o usuário o código que foi gerado;
	printf("%d", codigoFinal);
	
	//FIM :D

	return 0;
	
}
