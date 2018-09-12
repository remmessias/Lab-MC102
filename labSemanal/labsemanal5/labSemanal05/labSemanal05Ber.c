/*
 * Nome : Bernardo do Amaral Teodosio
 * RA   : 167494
 * Turma: W
 */
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_TAMANHO_NOME 200
#define MAX_TAMANHO_NOME_CODIFICADO 4
#define MAX_TAMANHO_CODIGO_NUMEROLOGIA 3
#define MAX_QTD_PESSOAS 40
#define MAX_QTD_ARESTAS (40 * 39) / 2
#define MIN_VALOR_ARESTA 5
#define ARESTA_NAO_DEVE_EXISTIR 0.0
#define VALOR_CONVERTIDO_NAO_EH_VALIDO -1

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    char nome[MAX_TAMANHO_NOME];
    Data dataNasc;
    char sexo, preferencia;
    int afinidades[MAX_QTD_PESSOAS];
} Pessoa;

typedef struct {
    Pessoa* origem;
    Pessoa* destino;
    double peso;
} Aresta;

typedef struct {
    Pessoa pessoas[MAX_QTD_PESSOAS];
    Aresta arestas[MAX_QTD_ARESTAS];
} Grafo;

void leiaData(Data* ptData) {
    scanf("%d/%d/%d", &ptData->dia, &ptData->mes, &ptData->ano);
}

void leiaInt(int* ptInt) {
    scanf("%d", ptInt);
}

void leiaChar(char* ptChar) {
    scanf("%c", ptChar);
}

// usado para evitar bugs na leitura
void leiaEspaco() {
    scanf(" ");
}

// usado para evitar bugs na leitura
void leiaCharEspaco(char* ptChar) {
    leiaChar(ptChar);
    leiaEspaco();
}

void leiaAfinidades(int afinidades[], int posicao, int qtdPessoas) {
    for (int i = 0; i < qtdPessoas; i++) {
        // afinidade da pessoa consigo mesma
        if (i == posicao) {
            afinidades[i] = 10;
            continue;
        }

        int afinidade;
        leiaInt(&afinidade);

        // se nao e a ultima posiçao de leitura
        if (i < qtdPessoas - 2) {
            leiaEspaco();
        }

        afinidades[i] = afinidade;
    }
}

void leiaPessoa(Pessoa* ptPessoa, int posicao, int qtdPessoas) {
    scanf(" %[^\n]s", ptPessoa->nome);
    leiaData(&ptPessoa->dataNasc);
    leiaEspaco();
    leiaCharEspaco(&ptPessoa->sexo);
    leiaCharEspaco(&ptPessoa->preferencia);
    leiaAfinidades(ptPessoa->afinidades, posicao, qtdPessoas);
}

void leiaTodasAsPessoas(Grafo* ptGrafo, int qtdPessoas) {
    for (int i = 0; i < qtdPessoas; i++) {
        leiaPessoa(&ptGrafo->pessoas[i], i, qtdPessoas);
    }
}

/*
 * retorna 0.0 se não deve existir aresta entre as duas pessoas;
 * caso deva existir, retorna o peso da aresta
*/
double deveExistirAresta(Pessoa* ptPessoa1, int posP1, Pessoa* ptPessoa2, int posP2) {
    double afinidadeP1P2 = ptPessoa1->afinidades[posP2];
    double afinidadeP2P1 = ptPessoa2->afinidades[posP1];

    double peso = sqrt(afinidadeP1P2 * afinidadeP2P1);
    if (peso >= MIN_VALOR_ARESTA) {
        return peso;
    }

    return ARESTA_NAO_DEVE_EXISTIR;
}

void criarAresta(Aresta* ptAresta, Pessoa* ptOrigem, Pessoa* ptDestino, double peso) {
    ptAresta->origem = ptOrigem;
    ptAresta->destino = ptDestino;
    ptAresta->peso = peso;
}

void colocarArestasDaPessoa(Grafo* ptGrafo, int posPessoa, int qtdPessoas, int* ptPosAresta) {
    Pessoa* ptPessoa = &ptGrafo->pessoas[posPessoa];
    for (int i = posPessoa + 1; i < qtdPessoas; i++) {
        // verifica se existe aresta entre as pessoas
        Pessoa* ptPossivelDestino = &ptGrafo->pessoas[i];
        double pesoAresta = deveExistirAresta(ptPessoa, posPessoa, ptPossivelDestino, i);

        if (pesoAresta != ARESTA_NAO_DEVE_EXISTIR) {
            // cria a aresta e adiciona no grafo
            Aresta aresta;
            criarAresta(&aresta, ptPessoa, ptPossivelDestino, pesoAresta);
            ptGrafo->arestas[*ptPosAresta] = aresta;
            (*ptPosAresta)++;
        }
    }
}

/*
 * retorna a quantidade de arestas que o grafo possui
*/
int colocarArestasNoGrafo(Grafo* ptGrafo, int qtdPessoas) {
    int qtdArestas = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        colocarArestasDaPessoa(ptGrafo, i, qtdPessoas, &qtdArestas);
    }

    return qtdArestas;
}

/*
 * retorna 0 se a pessoa não está na aresta e um valor diferente de zero
 * se a pessoa lá se encontra
*/
int pessoaEstaNaAresta(Pessoa* ptPessoa, Aresta* ptAresta) {
    if (strcmp(ptAresta->origem->nome, ptPessoa->nome) == 0) {
        return 1;
    } else if (strcmp(ptAresta->destino->nome, ptPessoa->nome) == 0) {
        return 2;
    }

    return 0;
}

int calcularPopularidade(Pessoa* ptPessoa, Grafo* ptGrafo, int qtdArestas) {
    int popularidade = 0;

    for (int i = 0; i < qtdArestas; i++) {
        if (pessoaEstaNaAresta(ptPessoa, &ptGrafo->arestas[i])) {
            popularidade++;
        }
    }

    return popularidade;
}

Pessoa* buscarPessoaMaisPopular(Grafo* ptGrafo, int popularidadeDasPessoas[], int qtdPessoas) {
    int indicePessoaMaisPopular = 0;

    // encontra o índice da pessoa mais popular
    for (int i = 0; i < qtdPessoas; i++) {
        if (popularidadeDasPessoas[i] > popularidadeDasPessoas[indicePessoaMaisPopular]) {
            indicePessoaMaisPopular = i;
        }
    }

    return &ptGrafo->pessoas[indicePessoaMaisPopular];
}

Pessoa* encontrarPessoaMaisPopular(Grafo* ptGrafo, int qtdPessoas, int qtdArestas) {
    int popularidadeDasPessoas[MAX_QTD_PESSOAS];

    for (int i = 0; i < qtdPessoas; i++) {
        Pessoa* ptPessoaAtual = &ptGrafo->pessoas[i];
        popularidadeDasPessoas[i] = calcularPopularidade(ptPessoaAtual, ptGrafo, qtdArestas);
    }

    return buscarPessoaMaisPopular(ptGrafo, popularidadeDasPessoas, qtdPessoas);
}

/*
 * retorna a outra ponta da aresta
 */
Pessoa* obterOutroVerticeDaAresta(Pessoa* ptPessoa, Aresta* ptAresta) {
    if (strcmp(ptAresta->origem->nome, ptPessoa->nome) == 0) {
        return ptAresta->destino;
    }

    return ptAresta->origem;
}

/*
 * retorna 1 se c nao deve ser condierado
 * retorna 0 caso c deva ser condierado.
 */
int caracterNaoDeveSerConsiderado(const char c) {
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'y':
        case 'h':
        case 'w':
        case 'Y':
        case 'H':
        case 'W':
            return 1;
    }

    return 0;
}

/*
 * retorna o valor da consoante convertido em numero pelo algoritmo Soundex
 */
char obterValorConvertido(const char c) {
    switch (c) {
        case 'g':
        case 'j':
        case 'G':
        case 'J':
            return '1';
        case 's':
        case 'z':
        case 'x':
        case 'S':
        case 'Z':
        case 'X':
            return '2';
        case 'c':
        case 'k':
        case 'q':
        case 'C':
        case 'K':
        case 'Q':
            return '3';
        case 'b':
        case 'p':
        case 'B':
        case 'P':
            return '4';
        case 'm':
        case 'n':
        case 'M':
        case 'N':
            return '5';
        case 'd':
        case 't':
        case 'D':
        case 'T':
            return '6';
        case 'f':
        case 'v':
        case 'F':
        case 'V':
            return '7';
        case 'l':
        case 'L':
            return '8';
        case 'r':
        case 'R':
            return '9';
        case ' ':
            return -2;
        case '\0':
            return -3;
    }

    return VALOR_CONVERTIDO_NAO_EH_VALIDO;
}

void converterConsoantesEmNumeros(char consoantesEmNumeros[], const char nome[], const char primeiraLetraNome) {
    int qtdConsoantesAdicionadas = 0;

    // evita codificacao identica com a da primeira letra
    for (;;) {
        if (obterValorConvertido(primeiraLetraNome) != obterValorConvertido(nome[0])) {
            break;
        }

        nome++;
    }

    // procura consoantes e as converte
    for (int i = 0; nome[i] != '\0' && nome[i] != ' ' && qtdConsoantesAdicionadas < 3; i++) {
        if (!caracterNaoDeveSerConsiderado(nome[i])) {
            char valorConvertido = obterValorConvertido(nome[i]);
            char proximoValorConvetido = obterValorConvertido(nome[i + 1]);

            // nao sao consoantes de mesmo codigo adjacentes
            if (valorConvertido != proximoValorConvetido) {
                consoantesEmNumeros[qtdConsoantesAdicionadas] = valorConvertido;
                qtdConsoantesAdicionadas++;
            }
        }
    }

    // se nao foram convertidas 3 consoantes
    if (qtdConsoantesAdicionadas < 3) {
        for (; qtdConsoantesAdicionadas < 3; qtdConsoantesAdicionadas++) {
            consoantesEmNumeros[qtdConsoantesAdicionadas] = '0';
        }
    }

    consoantesEmNumeros[3] = '\0';
}

void codificarNome(char nome[], Pessoa* pessoa) {
    nome[0] = pessoa->nome[0];
    converterConsoantesEmNumeros(nome + 1, pessoa->nome + 1, nome[0]);
}

/*
 * retorna a idade da pessoa
 */
int calcularIdade(const Pessoa* ptPessoa, const Data* ptDataFormulario) {
    int idade = ptDataFormulario->ano - ptPessoa->dataNasc.ano;

    // pessoa nao fez aniversario este ano ainda
    if (ptPessoa->dataNasc.mes > ptDataFormulario->mes) {
        idade--;
    } else if (ptPessoa->dataNasc.mes == ptDataFormulario->mes) {
        if (ptPessoa->dataNasc.dia > ptDataFormulario->dia) {
            idade--;
        }
    }

    return idade;
}

void codificarDataNasc(char codigo[], Pessoa* ptPessoa, Data* ptDataFormulario) {
    int codigoNasc = ptPessoa->dataNasc.dia + ptPessoa->dataNasc.mes;

    int ano = ptPessoa->dataNasc.ano;

    // acrescenta todos os digitos do ano
    const int divisor = 10;
    do {
        codigoNasc += ano % divisor;
        ano /= divisor;
    } while (ano != 0);

    while (codigoNasc > 9) {
        int codigoNascAux = 0;

        do {
            codigoNascAux += codigoNasc % divisor;
            codigoNasc /= divisor;
        } while (codigoNasc != 0);

        codigoNasc = codigoNascAux;
    }

    // conversao para char
    codigo[0] = (char) (codigoNasc + '0');

    int idade = calcularIdade(ptPessoa, ptDataFormulario);

    // coloca a idade da pessoa no codigo
    sprintf(codigo + 1, "%d", idade);

    codigo[3] = '\0';

    if (codigo[2] == '\0') {
        codigo[2] = '0';
    }
}

double calcularSintoniaEntreCaracteres(char cadeia1[], char cadeia2[], int tamanhoCadeia) {
    double sintonia = 0.0;

    for (int i = 0; i < tamanhoCadeia; i++) {
        if (cadeia1[i] == cadeia2[i]) {
            sintonia++;
        }
    }

    sintonia /= tamanhoCadeia;
    return sintonia;
}

double calcularSintoniaNasc(char cod1[], char cod2[]) {
    return calcularSintoniaEntreCaracteres(cod1, cod2, MAX_TAMANHO_CODIGO_NUMEROLOGIA);
}

double calcularSintoniaNomes(char nome1[], char nome2[]) {
    return calcularSintoniaEntreCaracteres(nome1, nome2, MAX_TAMANHO_NOME_CODIFICADO);
}

/*
 * calcula a sintonia entre duas pessoas
 */
double calcularSintonia(Pessoa* p1, Pessoa* p2, Data* ptDataFormulario, Aresta* ptAresta) {
    char nomeCodificadoP1[MAX_TAMANHO_NOME_CODIFICADO + 1],
            nomeCodificadoP2[MAX_TAMANHO_NOME_CODIFICADO + 1];

    codificarNome(nomeCodificadoP1, p1);
    codificarNome(nomeCodificadoP2, p2);

    char codNascP1[MAX_TAMANHO_CODIGO_NUMEROLOGIA + 1], codNascP2[MAX_TAMANHO_CODIGO_NUMEROLOGIA + 1];

    codificarDataNasc(codNascP1, p1, ptDataFormulario);
    codificarDataNasc(codNascP2, p2, ptDataFormulario);

    double sintoniaNomes = calcularSintoniaNomes(nomeCodificadoP1, nomeCodificadoP2);
    double sintoniaNasc = calcularSintoniaNasc(codNascP1, codNascP2);

    return (3.0 * sintoniaNomes + 5.0 * sintoniaNasc + (2 * ptAresta->peso) / 10.0) / 10.0;
}

/*
 * retorna 0 se as preferencias nao sao compativeis (preferencia de p1 nao eh o sexo de p2);
 * retorna 1 caso as preferencias sejam compativeis
 */
int preferenciasCompativeis(Pessoa* p1, Pessoa* p2) {
    if (p1->preferencia == p2->sexo) {
        return 1;
    }

    return 0;
}

/*
 * retorna o par perfeito da pessoa
 */
Pessoa* encontrarParPerfeito(Pessoa* ptPessoa, Grafo* grafo, int qtdPessoas,
                             int qtdArestas, double* sintonia, Data* ptDataFormulario) {
    *sintonia = -1.0;
    Pessoa* ptPossivelParPerfeito = ptPessoa;

    for (int i = 0; i < qtdArestas; i++) {
        Aresta* ptAresta = &grafo->arestas[i];

        if (pessoaEstaNaAresta(ptPessoa, ptAresta)) {
            Pessoa* ptOutroVertice = obterOutroVerticeDaAresta(ptPessoa, ptAresta);

            if (preferenciasCompativeis(ptPessoa, ptOutroVertice)) {
                double sintoniaAtual = calcularSintonia(ptPessoa, ptOutroVertice, ptDataFormulario, ptAresta);

                if (sintoniaAtual > *sintonia) {
                    *sintonia = sintoniaAtual;
                    ptPossivelParPerfeito = ptOutroVertice;
                }
            }
        }
    }

    return ptPossivelParPerfeito;
}

void printSaida(const Pessoa* ptPessoaMaisPopular, const Pessoa* ptParPerfeito, const double sintonia) {
    printf("%s combina com %s com %.2lf de sintonia s2\n", ptPessoaMaisPopular->nome, ptParPerfeito->nome, sintonia);
}

int main() {
    Data dataFormulario;
    leiaData(&dataFormulario);

    int qtdPessoas;
    leiaInt(&qtdPessoas);

    Grafo grafo;

    leiaTodasAsPessoas(&grafo, qtdPessoas);
    int qtdArestas = colocarArestasNoGrafo(&grafo, qtdPessoas);

    Pessoa* ptPessoaMaisPopular = encontrarPessoaMaisPopular(&grafo, qtdPessoas, qtdArestas);

    double sintoniaPessoaMaisPopular;
    Pessoa* ptParPerfeito = encontrarParPerfeito(ptPessoaMaisPopular, &grafo, qtdPessoas,
                                                 qtdArestas, &sintoniaPessoaMaisPopular, &dataFormulario);

    if (sintoniaPessoaMaisPopular > 0.0) {
        printSaida(ptPessoaMaisPopular, ptParPerfeito, sintoniaPessoaMaisPopular);
    }

    return 0;
}