/*
 * Nome: Rebecca Moreira Messias RA:186416 Turma: W
 *
 * Objetivo: Encontrar a pessoa com mais afinidade para uma outra pessoa (~tirar alguém da friendzone)
 *
 * Entrada:
 *  -> Data atual,
 *  -> Quantidade de pessoas que vão fazer o teste
 *  -> Para cada pessoa
 *      - Nome
 *      - Data de nascimento, gênero e preferência sexual
 *      - Nível da afinidade entre as outras pessoas (0-10)
 *
 *  Saída:
 *  -> Uma frase dizendo: "X combina com Y com k de sintonia s2", onde X é a pessoa mais popular do
 *  grupo, Y é a pessoa com quem a popular tem maior sintonia e k é aintonia entre elas.
 *
 *  OBSERVAÇÕES:
 *
 *  1- Meu código não passou nos testes 7 e 11 e após analisa-lo n vezes, suponho
 *  que o teste 7 esteja falhando por problemas no algoritmo Soundex. Tentei refazê-lo
 *  de 3 maneiras diferentes, mas nenhuma dessas resolveu meu problema. Sobre isso
 *  gostaria de deixar uma observação: A explicação do algoritmo Soundex ficou um
 *  tanto ambígua, já que em conversas com outras pessoas da turma houveram diversas
 *  interpretações.
 *
 *  2- Tentei fazer comentários, nas partes mais 'confusas' do meu código, não sei se deveria comentar
 *  em mais alguma. Tentei ser o mais clara possível, mas pode ser que eu tenha falhado nisso.
 *
 *  3- Somente, boa correção! :D
 *
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_ALUNO 40
#define MAX_ARESTAS 780

typedef char string[200];
typedef char codNome[4];
typedef int codIdade[3];

/*
 * Definindo structs que serão usadas na resolução do problema
 */
typedef struct Data {
    unsigned int dia, mes, ano;
} Data;

typedef struct Pessoa {
    string nome;
    Data nascimento;
    char genero;
    char interesse;
    double afinidades[MAX_ALUNO];
} Pessoa;

typedef struct Aresta {
    Pessoa *alone;
    Pessoa *crush;
    double afinidade;
} Aresta;

typedef struct Grafo {
    Pessoa pessoas[MAX_ALUNO];
    Aresta arestas[MAX_ARESTAS];
} Grafo;


/*
 * Função para ler a data;
 */
void lerData(Data *data) {
    scanf(" %u/%u/%u", &data->dia, &data->mes, &data->ano);
}

/*
 * Função para descobrir a pessoa mais popular: Percorre o vetor arestas do grafo passado por
 * parâmetro e verifica qual pessoa possui mais ligações (aparece mais vezes).
 */
struct Pessoa pessoaMaisPopular(Grafo *grafo, unsigned int qtdAlunos, unsigned int qtdArestas) {
    unsigned int qtasLigacoesPopular = 0, qtasLigacoes = 0, i, j;
    Pessoa popular, atual;

    for (i = 0; i < qtdAlunos; i++) {
        atual = grafo->pessoas[i];

        for (j = 0; j < qtdArestas; j++) {
            if ((strcmp(atual.nome, (*grafo->arestas[j].alone).nome) == 0) ||
                (strcmp(atual.nome, (*grafo->arestas[j].crush).nome) == 0)) {
                qtasLigacoes++;
            }
        }
        if (qtasLigacoes > qtasLigacoesPopular) {
            qtasLigacoesPopular = qtasLigacoes;
            popular = atual;
        }
        if (qtasLigacoes == qtasLigacoesPopular) {
            for (j = 0; j < qtdAlunos; j++) {
                if (strcmp((*grafo).pessoas[j].nome, popular.nome) == 0) {
                    break;
                }
                if (strcmp((*grafo).pessoas[j].nome, atual.nome) == 0) {
                    popular = atual;
                    break;
                }
            }
        }
        qtasLigacoes = 0;
    }

    return popular;
}

/*
 * Função que imprime a resposta para o usuário.
 */
void escreveResposta(struct Pessoa *popular, struct Pessoa *par, double sintonia) {
    printf("%s combina com %s com %.2lf de sintonia s2\n", popular->nome, par->nome, sintonia);
}

/*
 * Compara a código gerado na etapa 3-b para saber a taxa de igualdade entre os códigos gerados a partir
 * das idades e datas de nascimento.
 */
double comparaNumerologia(codIdade pess, codIdade pop) {
    double compara = 0;
    int i;
    for (i = 0; i < 3; i++) {
        if (pess[i] == pop[i])
            compara += 1.0 / 3.0;
    }

    return compara;
}

/*
 * Compara a código gerado na etapa 3-a para saber a taxa de igualdade entre os códigos gerados a partir
 * do nome pelo algoritmo Soundex
 */
double comparaNomes(codNome pess, codNome pop) {
    double compara = 0;
    int i;
    for (i = 0; i < 4; i++) {
        if (pess[i] == pop[i]) {
            compara += 0.25;
        }
    }
    return compara;
}

/*
 * Calcula a sintonia através da fórmula informada no enunciado.
 */
double calculaSintonia(codIdade codIdadePess, codIdade codIdadePop, codNome codNomePess,
                       codNome codNomePop, double afinidade) {
    double simetriaNome = comparaNomes(codNomePess, codNomePop);
    double simetriaNumerologia = comparaNumerologia(codIdadePess, codIdadePop);

    double sintonia = ((3 * simetriaNome) + (5 * simetriaNumerologia) + (2 * (afinidade / 10))) / 10;
    return sintonia;
}

/*
 * Função auxiliar que auxilia no cálculo da soma dos algarismos de um número.
 */
unsigned int calculaSomaAlgarismos(unsigned int *numero) {
    unsigned int aux = (*numero) % 10;
    (*numero) = (*numero) / 10;
    return aux;
}

/*
 * Função que calcula uma idade a partir da data de nascimento e da data atual
 */
unsigned int calculaIdade(Data *nascimento, Data *entrevista) {
    unsigned int idade = entrevista->ano - nascimento->ano;

    if ((nascimento->mes > entrevista->mes) ||
        ((nascimento->mes == entrevista->mes) && (nascimento->dia >= entrevista->dia)))
        idade--;

    return idade;
}

/*
 * Função para descobrir o código numerológico de uma pessoa a partir da idade e da data de nascimento
 */
void numerologia(Data *nascimento, codIdade resp, Data *entrevista) {
    unsigned int numero;
    unsigned int ano = nascimento->ano, somatoriaAno = 0, somatoriaDataNascimento, soma = 15, idade;

    idade = calculaIdade(&(*nascimento), &(*entrevista));
    numero = idade;

    // While que calcula a soma dos algarismos dos anos de nascimento
    while (ano > 0) {
        somatoriaAno += calculaSomaAlgarismos(&ano);
    }

    somatoriaDataNascimento = somatoriaAno + nascimento->dia + nascimento->mes;

    // while que vai fazer a soma dos algarismos da somatoria da
    // data de nascimento até que ele seja apenas um algarismo.
    while (soma >= 10) {
        while (somatoriaDataNascimento > 0) {
            soma += calculaSomaAlgarismos(&somatoriaDataNascimento);
        }
        if (soma - 15 >= 10) {
            somatoriaDataNascimento = soma - 15;
            soma = 15;
        }
        else {
            soma -= 15;
            break;
        }
    }

    //coloco na primeira posicao do vet esse número gerado
    resp[0] = soma;

    // aproprio a idade nas posições restantes
    if (idade < 10) { // se a idade tiver um dígito eu coloco um 0 na última posição
        resp[1] = idade;
        resp[2] = 0;
    }
    if (idade >= 10 && idade < 100) { // se a idade tiver dois algarismos
        resp[1] = idade / 10;
        resp[2] = idade % 10;
    }

    if (idade >= 100) { // se a idade for > 100 so coloco os dois primeiros números
        while (numero >= 100) {
            numero /= 10;
        }

        resp[1] = numero / 10;
        resp[2] = numero % 10;
    }
}

/*
 * Função que cácula o código Soundex de uma palavra (no nosso caso, o nome das pessoas)
 */
void codificaNome(string nome, codNome resp) {
    // Resolvi usar uma matriz, pois achei mais simples que fazer um switch,
    // mas não sei dizer qual é a melhor maneira em relação a performance
    char consoantes[3][18] = {{'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'x', 'z'},
                              {'B', 'C', 'D', 'F', 'G', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'X', 'Z'},
                              {'4', '3', '6', '7', '1', '1', '3', '8', '5', '5', '4', '3', '9', '2', '6', '7', '2', '2'}};
    char codPrimeiraLetra = 0;
    unsigned int posicao = 1, i, j, k;
    string auxNome;
    resp[0] = nome[0]; // Coloco a primeira letra do nome no vetor código
    for (i = 0; i < 2; i++) {

        for (j = 0; j < 18; j++) { // Descubro qual é o código da primeira letra
            if (consoantes[i][j] == resp[0])
                codPrimeiraLetra = consoantes[2][j];
        }

    }

    strcpy(auxNome, nome);

    auxNome[0] = codPrimeiraLetra;
    for (i = 1; !((nome[i] < 96) || (nome[i] > 122)); i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 18; k++) {

                if (auxNome[i] == consoantes[j][k]) {
                    auxNome[i] = consoantes[2][k];
                }
            }
        }
        if ((auxNome[i] < 48) || (auxNome[i] > 57))
            auxNome[i] = '0';
    }
    int tam = i;
    for (i = 1; i < tam; i++) {
        if (auxNome[i] == auxNome[i + 1] && auxNome[i] != '0') {
            for (j = i + 1; j < tam; j++) {
                auxNome[j] = auxNome[j + 1];
            }
            tam--;
            resp[posicao] = auxNome[i];
            posicao++;

        }
        else if (auxNome[i] != '0') {
            resp[posicao] = auxNome[i];
            posicao++;
        }
    }

    // se o vetor respostas não esta completo é colocado 0 nas posições restantes
    if (posicao < 4) {

        for (i = posicao; i < 4; i++) {
            resp[i] = '0';
        }
    }
}

/*
 * Função que calcula a media geometrica a partir da afinidade entre duas pessoas
 */
double calculaMedia(Pessoa *pessoa1, Pessoa *pessoa2, unsigned int i, unsigned int j) {
    double notaP1P2 = pessoa1->afinidades[j];
    double notaP2P1 = pessoa2->afinidades[i];

    double media = sqrt(notaP1P2 * notaP2P1);

    return media;
}

/*
 * Função que lê o nome da pessoa
 */
void lerNome(Pessoa *pessoa) {
    scanf(" %[^\n]s", pessoa->nome);
}

/*
 * Função que lê o restante dos dados
 */
void lerDados(Pessoa *pessoa, int qtdAlunos, int posicaoEntrevistado) {
    int i;

    scanf(" %u/%u/%u %c %c", &pessoa->nascimento.dia, &pessoa->nascimento.mes, &pessoa->nascimento.ano,
          &pessoa->genero, &pessoa->interesse);

    for (i = 0; i < qtdAlunos; i++) {
        if (posicaoEntrevistado == i)
            pessoa->afinidades[i] = 10;
        else
            scanf(" %lf", &pessoa->afinidades[i]);
    }
}

/*
 * Função que calculo o peso e se ele for >= 5 é criado uma nova aresta
 */
double calculaPeso(unsigned int localA, unsigned int localP1, unsigned int localP2, Pessoa *pessoa1,
                   Pessoa *pessoa2, Aresta vetAresta[MAX_ARESTAS]) {
    double media;
    media = calculaMedia(&(*pessoa1), &(*pessoa2), localP1, localP2);

    if (media >= 5) {
        vetAresta[localA].alone = &(*pessoa1);
        vetAresta[localA].crush = &(*pessoa2);
        vetAresta[localA].afinidade = media;
    }

    return media;
}

int main(void) {
    Grafo grafo;
    Data dataEntrevista;
    unsigned int qtdAlunos, qtdArestas, posicaoAresta = 0, i, j;
    Pessoa maisPopular, pessoaCerta, pessoaAuxiliar;
    codNome codNomePop, codNomePess;
    codIdade codIdadePop, codIdadePess;
    double sintonia, maiorSintonia = 0, media;

    //MANIPULANDO DADOS NO GRAFO
    lerData(&dataEntrevista);

    scanf(" %u", &qtdAlunos);

    qtdArestas = (qtdAlunos * (qtdAlunos - 1)) / 2;

    for (i = 0; i < qtdAlunos; i++) {
        lerNome(&grafo.pessoas[i]);
        lerDados(&grafo.pessoas[i], qtdAlunos, i);
    }

    for (i = 0; i < qtdAlunos; i++) {
        for (j = i + 1; j < qtdAlunos; j++) {
            media = calculaPeso(posicaoAresta, i, j, &grafo.pessoas[i], &grafo.pessoas[j],
                                grafo.arestas);
            if (media >= 5)
                posicaoAresta++;
            else
                qtdArestas--;
        }
    }

    //DESCOBRINDO PESSOA MAIS POPULAR
    maisPopular = pessoaMaisPopular(&grafo, qtdAlunos, qtdArestas);

    //DESCOBRIR SINTONIAS

    codificaNome(maisPopular.nome, codNomePop);
    numerologia(&maisPopular.nascimento, codIdadePop, &dataEntrevista);

    for (i = 0; i < qtdArestas; i++) {
        if (strcmp((*grafo.arestas[i].alone).nome, maisPopular.nome) == 0) {
            if (maisPopular.interesse == (*grafo.arestas[i].crush).genero) {
                if (grafo.arestas[i].afinidade >= 5) {
                    codificaNome((*grafo.arestas[i].crush).nome, codNomePess);
                    numerologia(&(*grafo.arestas[i].crush).nascimento, codIdadePess, &dataEntrevista);
                    sintonia = calculaSintonia(codIdadePess, codIdadePop, codNomePess, codNomePop,
                                               grafo.arestas[i].afinidade);
                    pessoaAuxiliar = (*grafo.arestas[i].crush);

                }
            }
        }

        else if (strcmp((*grafo.arestas[i].crush).nome, maisPopular.nome) == 0 &&
                 strcmp(maisPopular.nome, (*grafo.arestas[i].alone).nome) != 0) {
            if (maisPopular.interesse == (*grafo.arestas[i].alone).genero) {
                if (grafo.arestas[i].afinidade >= 5) {
                    codificaNome((*grafo.arestas[i].alone).nome, codNomePess);
                    numerologia(&(*grafo.arestas[i].alone).nascimento, codIdadePess, &dataEntrevista);
                    sintonia = calculaSintonia(codIdadePess, codIdadePop, codNomePess, codNomePop,
                                               grafo.arestas[i].afinidade);
                    pessoaAuxiliar = (*grafo.arestas[i].alone);
                }
            }
        }

        if (sintonia > maiorSintonia) {
            maiorSintonia = sintonia;
            pessoaCerta = pessoaAuxiliar;
        }
        if (sintonia == maiorSintonia) {
            for (j = 0; j < qtdAlunos; j++) {
                if (strcmp(grafo.pessoas[j].nome, pessoaCerta.nome) == 0) {
                    break;
                }
                if (strcmp(grafo.pessoas[j].nome, pessoaAuxiliar.nome) == 0) {
                    pessoaCerta = pessoaAuxiliar;
                    break;
                }
            }

        }
    }

    escreveResposta(&maisPopular, &pessoaCerta, maiorSintonia);

    return 0;
}
