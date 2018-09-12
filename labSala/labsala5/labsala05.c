/*
	Nome: Rebecca Moreira Messias RA: 186416 Turma: W
*/

#include <stdio.h>
#include <string.h>

#define maxH 100 //max de horas na agenda do projeto
#define maxF 20 //max funcionários

typedef struct {
	char mat[7]; //matricula 
	float custo;
} func; //funcionario

/*
	Função que calcula a qtd de horas livres que o projeto possui para alocação
*/
int qtdHorasLivres(int projeto[maxH], int qtdHoras) {
	int i;
	int qtdHorasLivres = 0;
	for (i = 0; i < qtdHoras; i++) {
		if (projeto[i] == -1)
			qtdHorasLivres++;
	}

	return qtdHorasLivres;	
}

/*
	Função que calcula a qtd de horas que um funcionário tem trabalhando no projeto
*/
int qtdHorasTrabalhadas(int projeto[maxH], int qtdHoras, int posicao) {
	int i;
	int qtdHorasTrabalhadas = 0;
	for (i = 0; i < qtdHoras; i++) {
		if (projeto[i] == posicao)
			qtdHorasTrabalhadas++;
	}

	return qtdHorasTrabalhadas;	
}


/*
	Função que aloca uma determinada quantidade de horas para um funionário
*/
void alocaHoras(int posicao, int horas, int projeto[maxH], int qtdHoras) {
	int i, auxHoras = horas, qtdHorasVagas = 0;
	
	qtdHorasVagas = qtdHorasLivres(projeto, qtdHoras);

	if (qtdHorasVagas >= horas) {
		for (i = 0; i < qtdHoras; i++) {
			if (projeto[i] == -1 && auxHoras > 0) {
				projeto[i] = posicao;
				auxHoras--;
			}
		} 
	}
	
}

/*
	Função que desaloca uma determinada quantidade de horas para um funionário
*/
void desalocaHoras(int posicao, int horas, int projeto[maxH], int qtdHoras) {
	int i, auxHoras = horas, qtdHorasTrabalho = 0;
	
	qtdHorasTrabalho = qtdHorasTrabalhadas(projeto, qtdHoras, posicao);

	if (horas <= qtdHorasTrabalho) {
		for (i = 0; i < qtdHoras; i++) {
			if (projeto[i] == posicao && auxHoras > 0) {
				projeto[i] = -1;
				auxHoras--;
			}
		} 
	}
}

/*
	Função que calcula o valor de bonificação para o funionário que tem mais quantidade
	de horas consecutivas
*/
double calculaValor(int projeto[maxH], func vetFunc[maxF], int qtdHoras, int qtdFunc) {
	int posFunc = -1, posFuncAux = -1, qtdVezes = 0, qtdVezesAux = 0, i, j, proximaPosicao = 0;

	for ( i = 0; i < qtdHoras; i++) {
		posFuncAux = projeto[proximaPosicao];
		
		for (j = 0; j < qtdHoras; j++) {
			if (projeto[j] == posFuncAux)
				qtdVezesAux++;
			else
				break;
		}
		
		proximaPosicao = j;

		if (qtdVezesAux > qtdVezes) {
			qtdVezes = qtdVezesAux;
			posFunc = posFuncAux;
			qtdVezesAux = 0;
		}

	}
	
	//printf("pos %d\n", posFunc);

	double custo = vetFunc[posFunc].custo * qtdVezes;

	return custo;
	
}

//Funções para tratar o vetor de funcionários
void lerFunc (int n, func vet[]);
void imprimeFunc(int n, func vet[]);

//funções para tratar agenda do projeto
void imprimeProjeto(int n, int projeto[], func vetFunc[]);
void inicializaVetor(int n, int vet[]);


int main (){
	int nFunc, nHoras;
	func vetFunc[maxF];
	int projeto[maxH]; //vetor deverá armazenar o índice (posição) do funcionário no vetor vetFunc
	int i, nReg, horas;
	char tipo; //tipo do registro: Alocar ou desalocar horas em projeto
	char mat[7]; //matricula
	int posicaoFuncionario, j;
	scanf("%d", &nHoras);
	inicializaVetor(nHoras, projeto);

	//leitura dos funcionarios (maticula e custo por hora)
	scanf("%d", &nFunc);
	lerFunc(nFunc, vetFunc);
	
	//leitura dos registos de agendamento e cancelamento
	scanf("%d", &nReg);
	for (i=0; i<nReg; i++){
		scanf("\n%c ", &tipo);
		char matri[7];
		switch (tipo){
			case 'A':
				scanf("%s", matri);
				scanf("%d", &horas);
				//ALOCAR HORAS PARA FUNCIONARIO AQUI
				for (j = 0; j < nFunc; j++) {
					if (strcmp(matri, vetFunc[j].mat) == 0) {
						posicaoFuncionario = j;
						break;
					}
				}
				alocaHoras(posicaoFuncionario, horas, projeto, nHoras);
				break;
			case 'D':
				scanf("%s", mat);
				scanf("%d", &horas);
				//DESALOCAR HORAS PARA FUNCIONARIO AQUI
				for (j = 0; j < nFunc; j++) {
					if (strcmp(mat, vetFunc[j].mat) == 0) {
						posicaoFuncionario = j;
						break;
					}
				}
				desalocaHoras(posicaoFuncionario, horas, projeto, nHoras);
				break;
			default:
				printf("ERRO");
				break;
		}
	}


	//-----CALCULE O CUSTO DA MAIOR SEQUENCIA AQUI

	double valor = calculaValor(projeto, vetFunc, nHoras, nFunc); 

	printf("O valor pago para a maior sequencia consecutiva realizada por um unico funcionario eh %.2f\n", valor);

	return 0;

}


/**
 * Ler os funcionários da entrada. 
 * Função ler N funcionários e armazenas num vetor de estrutura do tipo func. 
 * O vetor é recebido como referência, portanto a função modifica seus valores.
 * Função retorna nada.
 * @param n Número de funcionários a serem lidos na entrada
 * @param vet Vetor de estrutura func, onde serão armazenados os funcionários lido da entrada.
 */
void lerFunc(int n, func vet[]){
	int i;
	
	for (i=0; i<n; i++)
		scanf("\n%s %f", vet[i].mat, &vet[i].custo);		
}


/**
 * Função que imprime o vetor de funcionários. 
 * Função feita apenas com o propósito de teste.
 * Função imprime a matrícula do funcionário e o custo por hora do funcionário
 * @param n Número de funcionários, tamanho do vetor
 * @param vet Vetor de estrutura que armazena os funcionários.
 */
void imprimeFunc(int n, func vet[]){
	int i;
	
	for (i=0; i<n; i++)
		printf("%s %.2f", vet[i].mat, vet[i].custo);
printf("\n");

}

/**
 * Função que imprime a agenda do projeto. 
 * Função feita apenas com o propósito de testar.
 * Função imprime * para horas livres e a matrícula do funcionário para horas alocada para alguém
 * @param n Número de horas na agenda
 * @param projeto Vetor de inteiros/índice para o funcionário alocado. Vetor mostra a configuração da agenda do projeto (os funcionários alocados). 
 * @param vetFunc Vetor que armazena as informações dos funcionários
 */
void imprimeProjeto(int n, int projeto[], func vetFunc[]){
	int i;
	
	for (i=0; i<n; i++)
		if (projeto[i]==-1)
			printf("* "); //uso * para mostrar hora vazia (disponível)
		else
			printf("%s ", vetFunc[projeto[i]].mat);

	printf("\n");
}


/**
 * Função que inicializa um vetor de inteiros com valor -1.
 * Função usada para inicializar o vetor que representa a agenda do projeto.
 * @param n Números de horas do projeto
 * @param vet Vetor de inteiros que armazena o índice para o funcionário alocado. Vetor guarda a configuração da agenda do projeto.
 */
void inicializaVetor(int n, int vet[]){
	int i;
	for (i=0; i<n; i++)
		vet[i]=-1;
}


