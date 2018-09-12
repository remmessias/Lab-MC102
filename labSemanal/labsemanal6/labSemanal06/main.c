/*
 * Nome: Rebecca Moreira Messias RA: 186416 Turma: W
 *
 * Objetivo: Desenvolver um programa que encontre o melhor funcionário do ano em uma empresa com base no seu salário,
 *           produtividade relativa e nível na hierarquia da empresa
 *
 * Entrada:
 *      -> Um número real positivo T, indicando o total gasto mensalmente com salários na Unicamp (T <= 10^12)
 *      -> Um número inteiro positivo F, indicando o fator de regularização do cálculo de qualidade (F <= 10^5)
 *      -> Um inteiro N, indicando o número de funcionários da empresa (0 < N <= 100)
 *      -> N linhas, cada uma contendo o primeiro nome de um funcionário, com até 30 caracteres e um inteiro p
 *         indicando a produtividade absoluta desse funcionário (0 < p <= 100)
 *      -> N-1 linhas, cada uma contendo dois nomes com até 30 caracteres cada, sendo o primeiro o nome do
 *         funcionário e o segundo o nome de seu chefe
 *
 * Saída:
 *      -> O nome do funcionário escolhido para ganhar o prêmio, seguido de seu Índice de Qualidade, com 2 casa
 *         decimais
 *
 * OBSERVAÇÕES:
 *
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_FUNC 100
#define MAX_RELACAO 99
#define MAX_NOME 31

// definição de tipos e structs que serão utilizadas na solução
typedef char string[MAX_NOME];

typedef struct Funcionario {
    string nome;
    int prodAbsoluta, nivel;
    double prodRelativa, salario, taxa, indiceQualidade;
} Funcionario;

typedef struct Relacao {
    int chefe, subordinado;
} Relacao;

/*
 * Função que verifica se um funcionario é subordinado máximo, ou seja,
 * ele não é chefe de ninguém
 */
int ehSubordinado(int subordinado, Relacao vetRelacao[MAX_RELACAO], int relacao) {
    int ehSubordinadoMaximo = 1, i;

    for (i = 0; i < relacao; i++) {
        if (vetRelacao[i].chefe == subordinado) {
            ehSubordinadoMaximo = 0;
            break;
        }
    }

    return ehSubordinadoMaximo;
}

/*
 * Função que soma a quantidade de funcionários de um chefe
 */
int somatoriaQtdSubordinados(int func, Relacao vetRelacao[MAX_RELACAO], int relacao) {
    int somatoria = 0, i;

    for (i = 0; i < relacao; i++) {
        if (vetRelacao[i].chefe == func) {
            somatoria++;
        }
    }

    return somatoria;
}

/*
 * Função que procura a posição do presidente
 */
int procuraPosPresidente(Relacao vetRelacao[MAX_RELACAO], unsigned int relacao) {
    int posPresidente = -1, i, j;

    for (i = 0; i < relacao; i++) {
        posPresidente = vetRelacao[i].chefe;
        for (j = 0; j < relacao; j++) {
            if (vetRelacao[j].subordinado == vetRelacao[i].chefe) {
                posPresidente = -1;
                break;
            }
        }
        if (posPresidente != -1)
            break;
    }

    return posPresidente;
}

/*
 * Função que lê os funcionários
 */
void lerFuncionarios(Funcionario vetFunc[MAX_FUNC], unsigned int qtd) {
    int i;
    for (i = 0; i < qtd; i++) {
        scanf(" %s %d\n", vetFunc[i].nome, &vetFunc[i].prodAbsoluta);
    }
}

/*
 * função que procura a posição de um funcionário no vetor de funcionários a partir do nome
 */
int procuraPosicao(string nome, unsigned int qtd, Funcionario vetFunc[MAX_FUNC]) {
    int posicao = -1, i;
    for (i = 0; i < qtd; i++) {
        if (strcmp(nome, vetFunc[i].nome) == 0) {
            posicao = i;
            break;
        }
    }
    return posicao;
}

/*
 * Função que lê as relações de de subordinado-chefe
 */
void lerRelacao(Relacao vetRelacao[MAX_RELACAO], unsigned int qtd, Funcionario vetFunc[MAX_FUNC], unsigned int qtdFunc) {
    int i;
    string chefe, subordinado;
    for (i = 0; i < qtd; i++) {
        scanf(" %s %s", subordinado, chefe);
        vetRelacao[i].subordinado = procuraPosicao(subordinado, qtdFunc, vetFunc);
        vetRelacao[i].chefe = procuraPosicao(chefe, qtdFunc, vetFunc);
    }
}

/*
 * Função que procura o chefe de um subordinado
 */
int procuraChefe(Relacao vetRelacao[MAX_RELACAO], unsigned int relacao, int subordinado) {
    int j, chefe = 0;
    for (j = 0; j < relacao; j++) {
        if (vetRelacao[j].subordinado == subordinado) {
            chefe = vetRelacao[j].chefe;
            break;
        }
    }

    return chefe;
}

/*
 * Função que escreve o funcionário com melhor desempenho na tela
 */
void escreveResposta(Funcionario vetFuncionario[], unsigned int funcionario) {
    int i;
    Funcionario vencedor;

    vencedor.indiceQualidade = 0;

    for (i = 0; i < funcionario; i++) {
        if (vetFuncionario[i].indiceQualidade > vencedor.indiceQualidade) {
            vencedor = vetFuncionario[i];
        }
    }

    printf("%s %.2lf\n", vencedor.nome, vencedor.indiceQualidade);
}

/*
* Calcula a produtividade relativa dos funcionários recursivamente
*/
double calculaProdRealtivaRecur(int func, Funcionario vetFuncionario[MAX_FUNC], Relacao vetRelacao[MAX_RELACAO],
                                int funcionario, int relacao) {

    double produtividadeRelativa = 0;

    if (ehSubordinado(func, vetRelacao, relacao)) {
        vetFuncionario[func].prodRelativa = vetFuncionario[func].prodAbsoluta;
        produtividadeRelativa = vetFuncionario[func].prodRelativa;
    }
    else {
        double somaProdRelativaSub = 0;
        int j;

        for(j = 0; j < relacao; j++) {
            if (vetRelacao[j].chefe == func) {
                somaProdRelativaSub += calculaProdRealtivaRecur(vetRelacao[j].subordinado, vetFuncionario, vetRelacao, funcionario, relacao);
            }
        }
        double somaQtdSubordinados = somatoriaQtdSubordinados(func, vetRelacao, relacao);
        double resultProdRelativa =
                0.5 * (vetFuncionario[func].prodAbsoluta + (1/somaQtdSubordinados * somaProdRelativaSub));

        vetFuncionario[func].prodRelativa = resultProdRelativa;
        produtividadeRelativa = resultProdRelativa;
    }

    return produtividadeRelativa;
}

/*
 * Função que calcula a produtividade relativa
 */
void calculaProdRelativa(Funcionario vetFuncionario[MAX_FUNC], unsigned int funcionario, Relacao vetRelacao[MAX_RELACAO],
                         unsigned int relacao) {

    int posPresidente = procuraPosPresidente(vetRelacao, relacao);

    vetFuncionario[posPresidente].prodRelativa = calculaProdRealtivaRecur(posPresidente, vetFuncionario, vetRelacao, funcionario, relacao);

}

/*
 * Função recursiva que calcula o nível hierarquico do funcionário
 */
void procuraNivel(int posChefe, Relacao vetRelacao[MAX_RELACAO], Funcionario vetFunc[MAX_FUNC], unsigned int relacao, unsigned int nivel) {
    unsigned int i;

    for (i = 0; i < relacao; i++) {
        if (vetRelacao[i].chefe == posChefe) {
            vetFunc[vetRelacao[i].subordinado].nivel = nivel;
            if (ehSubordinado(vetRelacao[i].subordinado, vetRelacao, relacao) == 0) {
                procuraNivel(vetRelacao[i].subordinado, vetRelacao, vetFunc, relacao, nivel+1);
            }
        }
    }
}

/*
 * Função que calcula o nível hierarquico de um funcionário
 */
void calculaNivelHierarquico(Funcionario vetFunc[MAX_FUNC], Relacao vetRelacao[MAX_RELACAO],
                             unsigned int relacao) {

    int posPresidente = procuraPosPresidente(vetRelacao, relacao);
    vetFunc[posPresidente].nivel = 1;

    procuraNivel(posPresidente, vetRelacao, vetFunc, relacao, 2);
}

/*
 * Função que calcula a taxa de comparação do salário de um subordinado em relação
 * ao salário do presidente
 */
void calculaTaxa(Funcionario vetFuncionario[MAX_FUNC], unsigned int funcionario, Relacao vetRelacao[MAX_RELACAO], unsigned int relacao,
                 int nivel) {
    int i;
    for(i = 0; i < funcionario; i++) {
        if (vetFuncionario[i].nivel == nivel) {
            int chefe = procuraChefe(vetRelacao, relacao, i);

            double somaSub = somatoriaQtdSubordinados(chefe, vetRelacao,relacao);

            vetFuncionario[i].taxa = (somaSub/(somaSub+1))*vetFuncionario[chefe].taxa;

            if (ehSubordinado(i, vetRelacao, relacao) == 0) {
                calculaTaxa(vetFuncionario, funcionario, vetRelacao, relacao, nivel+1);
            }
        }
    }
}

/*
 * Função que calcula o salário dos funcionarios
 */
void calculaSalario(Funcionario vetFuncionario[MAX_FUNC], unsigned int funcionario, Relacao vetRelacao[MAX_RELACAO],
                    unsigned int relacao, double total) {
    int i;

    int posPresidente = procuraPosPresidente(vetRelacao, relacao);
    vetFuncionario[posPresidente].taxa = 1;

    calculaTaxa(vetFuncionario, funcionario, vetRelacao, relacao, 2);

    double somaTaxas = 0;

    for (i = 0; i < funcionario; i++) {
        somaTaxas += vetFuncionario[i].taxa;
    }

    double salarioPresidente = total/somaTaxas;

    for (i = 0; i < funcionario; i++) {
        vetFuncionario[i].salario = vetFuncionario[i].taxa*salarioPresidente;
    }
}

/*
 * Função que calcula o log*(x)
 */
double logEstrela(double nivel) {

    if (nivel <= 1) {
        return 0;
    }

    return 1 + logEstrela(log2(nivel));
}

/*
 * Função que calcula o indice de qualidade dos funcionarios
 */
void calculaIndiceQualidade(Funcionario vetFuncionario[MAX_FUNC], unsigned int funcionario, unsigned int fator) {
    int i;

    for (i = 0; i < funcionario; i++) {
        double calcLogEstrela = logEstrela(vetFuncionario[i].nivel) + 1;
        double divisao = vetFuncionario[i].prodRelativa / log2(vetFuncionario[i].salario);
        vetFuncionario[i].indiceQualidade = fator *  calcLogEstrela * divisao;
    }
}

int main () {

    double totalSalario;
    unsigned int fatorRegularizacao, qtdFuncionario, qtdRelacao;
    Funcionario vetFuncionarios[MAX_FUNC];
    Relacao vetRelacao[MAX_RELACAO];

    scanf(" %lf\n", &totalSalario);
    scanf(" %u\n", &fatorRegularizacao);
    scanf(" %u\n", &qtdFuncionario);

    if (qtdFuncionario == 1) {
        lerFuncionarios(vetFuncionarios, qtdFuncionario);
        vetFuncionarios[qtdFuncionario-1].taxa = 1;
        vetFuncionarios[qtdFuncionario-1].salario = totalSalario;
        vetFuncionarios[qtdFuncionario-1].prodRelativa = vetFuncionarios[qtdFuncionario-1].prodAbsoluta;
        vetFuncionarios[qtdFuncionario-1].nivel = 1;
        calculaIndiceQualidade(vetFuncionarios, qtdFuncionario, fatorRegularizacao);
        escreveResposta(vetFuncionarios, qtdFuncionario);
    }
    else {
        qtdRelacao = qtdFuncionario - 1;

        lerFuncionarios(vetFuncionarios, qtdFuncionario);

        lerRelacao(vetRelacao, qtdRelacao, vetFuncionarios, qtdFuncionario);

        calculaNivelHierarquico(vetFuncionarios, vetRelacao, qtdRelacao);

        calculaProdRelativa(vetFuncionarios, qtdFuncionario, vetRelacao, qtdRelacao);

        calculaSalario(vetFuncionarios, qtdFuncionario, vetRelacao, qtdRelacao, totalSalario);

        calculaIndiceQualidade(vetFuncionarios, qtdFuncionario, fatorRegularizacao);

        escreveResposta(vetFuncionarios, qtdFuncionario);

    }

    return 0;
}