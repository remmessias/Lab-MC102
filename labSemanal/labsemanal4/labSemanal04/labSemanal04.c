/* Nome: Rebecca Moreira Messias RA: 186416 Turma: W
 *
 * Objetivo: Desenvolver um programa que ajude a senhora Marta
 * a gerenciar a sua agenda telefônica para no máximo 10 contatos
 * de cada tipo.
 *
 * Entrada: A entrada pode variar dependendo da opção escolhida no menu.
 *  -> Para inserir:
 *      +Tipo do contato
 *      +Nome
 *      +CPF
 *      +Endereco
 *      +Telefone
 *      +Celular
 *  -> Para excluir:
 *      +Tipo do contato
 *      +Nome
 *  -> Para alterar:
 *      +Tipo do contato
 *      +Nome
 *      +CPF
 *      +Endereco
 *      +Telefone
 *      +Celular
 *  -> Para buscar:
 *      +Tipo do contato
 *      +Nome
 *  -> Para listar contatos pessoais, profisionais ou os dois tipos não é necessário
 *     digitar uma entrada
 *
 *
 * Saída: A saída pode variar dependendo da opção escolhida o menu.
 *
 * Observações:
 *
 * 1- Por esse lab não ter muitas instruções complexas, resolvi comentar em cima de cada função
 * o que elas fazem. Nos trechos que eu julguei mais complexos comentarei passo a passo com
 * comentário de linha
 *
 * 2- Para facilitar, resolvi estipular por -1 uma posição vazia. Esse valor ficará no CPF
 *
 * 3- Na main não tem quase nada comentado porque tem muitas coisas com nomes  apropriados o que facilita a leitura.
 * Por esse motivo dispensei comentários. Se por algum motivo achar que fosse necessário mais comentários me avise no
 * feedback!
 *
 * 4- Sobre o enunciado: Achei que tinha muitas coisas que não foram explicadas muito bem (tipo onde deveria ser
 * printado as mensagens de sucesso ou insucesso), que depois de testes percebi os lugares em que as mensagens
 * deveriam ficar, por mais que eu achasse que as mensagens deveriam ser outras nesses lugares :P
 *
 * 5- Boa correção!! :D
 *
 */

#include <stdio.h>
#include <string.h>

// valor estipulado por mim para indicar uma posição vazia
#define LUGAR_VAGO -1
#define CAPACIDADE_AGENDA 10

typedef char string[60];

/*
 * Percorre o vetor cpf até achar um lugar que esteja vago e
 * quando achar coloca as informações do contato nessa posição
 */
int inserir(string nome, long long int CPF, string endereco, long long int telefone, long long int celular,
            char vetNome[CAPACIDADE_AGENDA][60], long long int vetCPF[CAPACIDADE_AGENDA],
            char vetEndereco[CAPACIDADE_AGENDA][60], long long int vetTelefone[CAPACIDADE_AGENDA],
            long long int vetCelular[CAPACIDADE_AGENDA]) {
    unsigned int sucesso = 0;

    int i;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if (vetCPF[i] == LUGAR_VAGO) {
            strcpy(vetNome[i], nome);
            vetCPF[i] = CPF;
            strcpy(vetEndereco[i], endereco);
            vetTelefone[i] = telefone;
            vetCelular[i] = celular;
            sucesso = 1;
            break;
        }
    }
    return sucesso;
}

/*
 * Percorre o vetor até achar a posição com o nome a ser excluído
 * Quando achar, vai pegar todas as posições seguintes e trazer uma
 * posição abaixo.
 */
int excluir(string nome, char vetNome[CAPACIDADE_AGENDA][60], long long int vetCPF[CAPACIDADE_AGENDA],
            char vetEndereco[CAPACIDADE_AGENDA][60], long long int vetTelefone[CAPACIDADE_AGENDA],
            long long int vetCelular[CAPACIDADE_AGENDA]) {
    unsigned int sucesso = 0;

    int i;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if (strcmp(vetNome[i], nome) == 0) {
            int k;
            for (k = i + 1; k < CAPACIDADE_AGENDA; k++) {
                strcpy(vetNome[i], vetNome[k]);
                vetCPF[i] = vetCPF[k];
                strcpy(vetEndereco[i], vetEndereco[k]);
                vetTelefone[i] = vetTelefone[k];
                vetCelular[i] = vetCelular[k];
                i++;
            }
            vetCPF[i] = LUGAR_VAGO;
            sucesso = 1;
            break;
        }
    }
    return sucesso;
}

/*
 * Percorre o vetor até achar a posição com o nome a ser alterado
 * Se o CPF da posição não estiver com -1, irá setar os valores dassa posição
 * para os novos que foram informados.
 */
int alterar(string nome, long long int CPF, string endereco, long long int telefone, long long int celular,
            char vetNome[CAPACIDADE_AGENDA][60], long long int vetCPF[CAPACIDADE_AGENDA],
            char vetEndereco[CAPACIDADE_AGENDA][60], long long int vetTelefone[CAPACIDADE_AGENDA],
            long long int vetCelular[CAPACIDADE_AGENDA]) {
    unsigned int sucesso = 0;

    int i;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if ((strcmp(vetNome[i], nome) == 0) && (vetCPF[i] != LUGAR_VAGO)) {
            vetCPF[i] = CPF;
            strcpy(vetEndereco[i], endereco);
            vetTelefone[i] = telefone;
            vetCelular[i] = celular;
            sucesso = 1;
            break;
        }
    }

    return sucesso;
}

/*
 * Percorre a agenda e se a posição não estiver vaga eu escrevo as informações do contato na tela
 */
int listar(char vetNome[CAPACIDADE_AGENDA][60], long long int vetCPF[CAPACIDADE_AGENDA],
           char vetEndereco[CAPACIDADE_AGENDA][60], long long int vetTelefone[CAPACIDADE_AGENDA],
           long long int vetCelular[CAPACIDADE_AGENDA]) {
    unsigned int sucesso = 0;
    int i;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if (vetCPF[i] != LUGAR_VAGO) {
            printf("%s\n", vetNome[i]);
            printf("%lli\n", vetCPF[i]);
            printf("%s\n", vetEndereco[i]);
            printf("%lli\n", vetTelefone[i]);
            printf("%lli\n", vetCelular[i]);
            sucesso = 1;
        }
    }

    return sucesso;
}

/*
 * Percorre o vetor até achar a posição com o nome procurado
 * Se o CPF da posição não estiver com -1, irá escrever o contato na tela
 */
int buscar(string nome, char vetNome[CAPACIDADE_AGENDA][60], long long int vetCPF[CAPACIDADE_AGENDA],
           char vetEndereco[CAPACIDADE_AGENDA][60], long long int vetTelefone[CAPACIDADE_AGENDA],
           long long int vetCelular[CAPACIDADE_AGENDA]) {
    unsigned int sucesso = 0;
    int i;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if ((strcmp(vetNome[i], nome) == 0) && (vetCPF[i] != LUGAR_VAGO)) {
            printf("%s\n", vetNome[i]);
            printf("%lli\n", vetCPF[i]);
            printf("%s\n", vetEndereco[i]);
            printf("%lli\n", vetTelefone[i]);
            printf("%lli\n", vetCelular[i]);
            sucesso = 1;
            break;
        }
    }
    return sucesso;
}

/*
 * Percorre a agenda e verifica se ela esta cheia
 */
int estaCheia(long long int vetCPF[CAPACIDADE_AGENDA]) {
    unsigned int cheia = 1;
    int i;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if (vetCPF[i] == LUGAR_VAGO) {
            cheia = 0;
            break;
        }
    }

    return cheia;
}

/*
 * Percorre a agenda e verifica se ela esta vazia
 */
int estaVazia(long long int vetCPF[CAPACIDADE_AGENDA]) {
    unsigned int vazia = 1;
    int i;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if (vetCPF[i] != LUGAR_VAGO) {
            vazia = 0;
            break;
        }
    }
    return vazia;
}

/*
 * Percorre a agenda e verifica se existe um contato na agenda
 */
int temContato(char vetNome[CAPACIDADE_AGENDA][60], string nome) {
    int i, tem = 0;
    for (i = 0; i < CAPACIDADE_AGENDA; i++) {
        if (strcmp(nome, vetNome[i]) == 0) {
            tem = 1;
            break;
        }
    }

    return tem;
}

int main() {
    string nome, endereco;
    long long int cpf, telefone, celular;
    unsigned int opcaoMenu, tipoContato;
    string nomePessoal[CAPACIDADE_AGENDA], nomeProfissional[CAPACIDADE_AGENDA],
            enderecoPessoal[CAPACIDADE_AGENDA], enderecoProfissional[CAPACIDADE_AGENDA];
    long long int cpfPessoal[CAPACIDADE_AGENDA] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            cpfProfissional[CAPACIDADE_AGENDA] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            telefonePessoal[CAPACIDADE_AGENDA] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            telefoneProfissional[CAPACIDADE_AGENDA] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            celularPessoal[CAPACIDADE_AGENDA] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            celularProfissional[CAPACIDADE_AGENDA] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    do {
        scanf(" %u", &opcaoMenu);

        switch (opcaoMenu) {
            case 1: //inserir
                scanf(" %u", &tipoContato);
                scanf(" %[^\n]s", nome);
                scanf(" %lli", &cpf);
                scanf(" %[^\n]s", endereco);
                scanf(" %lli", &telefone);
                scanf(" %lli", &celular);

                if (tipoContato == 1) {
                    if (estaCheia(cpfPessoal)) {
                        printf("Desculpe, agenda lotada!\n");
                    }
                    else {
                        if (inserir(nome, cpf, endereco, telefone, celular, nomePessoal, cpfPessoal,
                                    enderecoPessoal, telefonePessoal, celularPessoal)) {
                            printf("Inserido com sucesso!\n");
                        }
                        else
                            printf("Desculpe, agenda lotada!\n");
                    }
                }
                else {
                    if (estaCheia(cpfProfissional)) {
                        printf("Desculpe, agenda lotada!\n");
                    }
                    else {
                        if (inserir(nome, cpf, endereco, telefone, celular, nomeProfissional, cpfProfissional,
                                    enderecoProfissional, telefoneProfissional, celularProfissional)) {
                            printf("Inserido com sucesso!\n");
                        }
                        else
                            printf("Desculpe, agenda lotada!\n");
                    }
                }

                break;
            case 2: //excluir
                scanf(" %u", &tipoContato);
                scanf(" %[^\n]s", nome);

                if (tipoContato == 1) {
                    if (!(estaVazia(cpfPessoal))) {
                        if (excluir(nome, nomePessoal, cpfPessoal, enderecoPessoal, telefonePessoal,
                                    celularPessoal)) {
                            printf("Excluido com sucesso!\n");
                        }
                        else {
                            printf("Desculpe, contato %s nao existe!\n", nome);
                        }
                    }
                    else
                        printf("Desculpe, contato %s nao existe!\n", nome);
                }
                else {
                    if (!(estaVazia(cpfProfissional))) {
                        if (excluir(nome, nomeProfissional, cpfProfissional, enderecoProfissional,
                                    telefoneProfissional, celularProfissional)) {
                            printf("Excluido com sucesso!\n");
                        }
                        else {
                            printf("Desculpe, contato %s nao existe!\n", nome);
                        }
                    }
                    else
                        printf("Desculpe, contato %s nao existe!\n", nome);
                }

                break;
            case 3: //alterar
                scanf(" %u", &tipoContato);
                scanf(" %[^\n]s", nome);

                if (tipoContato == 1) {
                    if (!(estaVazia(cpfPessoal))) {
                        if (temContato(nomePessoal, nome)) {
                            scanf(" %lli", &cpf);
                            scanf(" %[^\n]s", endereco);
                            scanf(" %lli", &telefone);
                            scanf(" %lli", &celular);

                            if (alterar(nome, cpf, endereco, telefone, celular, nomePessoal, cpfPessoal,
                                        enderecoPessoal, telefonePessoal, celularPessoal))
                                printf("Alterado com sucesso!\n");
                            else
                                printf("Desculpe, contato %s nao existe!\n", nome);
                        }
                        else
                            printf("Desculpe, contato %s nao existe!\n", nome);
                    }
                    else
                        printf("Desculpe, contato %s nao existe!\n", nome);
                }
                else {
                    if (!(estaVazia(cpfProfissional))) {
                        if (temContato(nomeProfissional, nome)) {
                            scanf(" %lli", &cpf);
                            scanf(" %[^\n]s", endereco);
                            scanf(" %lli", &telefone);
                            scanf(" %lli", &celular);

                            if (alterar(nome, cpf, endereco, telefone, celular, nomeProfissional, cpfProfissional,
                                        enderecoProfissional, telefoneProfissional, celularProfissional))
                                printf("Alterado com sucesso!\n");
                            else
                                printf("Desculpe, contato %s nao existe!\n", nome);
                        }
                        else
                            printf("Desculpe, contato %s nao existe!\n", nome);
                    }
                    else
                        printf("Desculpe, contato %s nao existe!\n", nome);
                }

                break;
            case 4: //buscar
                scanf("%u", &tipoContato);
                scanf(" %[^\n]s", nome);

                if (tipoContato == 1) {
                    if (!(estaVazia(cpfPessoal))) {
                        if (buscar(nome, nomePessoal, cpfPessoal, enderecoPessoal, telefonePessoal, celularPessoal))
                            printf("Buscado com sucesso!\n");
                        else
                            printf("Desculpe, contato %s nao existe!\n", nome);
                    }
                    else
                        printf("Desculpe, contato %s nao existe!\n", nome);
                }
                else {
                    if (!(estaVazia(cpfProfissional))) {
                        if (buscar(nome, nomeProfissional, cpfProfissional, enderecoProfissional,
                                   telefoneProfissional, celularProfissional))
                            printf("Buscado com sucesso!\n");
                        else
                            printf("Desculpe, contato %s nao existe!\n", nome);
                    }
                    else
                        printf("Desculpe, contato %s nao existe!\n", nome);
                }

                break;
            case 5: //listar pessoais
                if (!(estaVazia(cpfPessoal))) {
                    if (listar(nomePessoal, cpfPessoal, enderecoPessoal, telefonePessoal, celularPessoal))
                        printf("Listado com sucesso!\n");
                    else
                        printf("Desculpe, agenda vazia!\n");
                }
                else {
                    printf("Desculpe, agenda vazia!\n");
                }

                break;
            case 6: //listar profissionais
                if (!(estaVazia(cpfProfissional))) {
                    if (listar(nomeProfissional, cpfProfissional, enderecoProfissional, telefoneProfissional,
                               celularProfissional))
                        printf("Listado com sucesso!\n");
                    else
                        printf("Desculpe, agenda vazia!\n");
                }
                else {
                    printf("Desculpe, agenda vazia!\n");
                }

                break;
            case 7: //listar todos
                if (!(estaVazia(cpfPessoal))) {
                    if (listar(nomePessoal, cpfPessoal, enderecoPessoal, telefonePessoal, celularPessoal))
                        printf("Listado com sucesso!\n");
                    else
                        printf("Desculpe, agenda vazia!\n");
                }
                else {
                    printf("Desculpe, agenda vazia!\n");
                }

                if (!(estaVazia(cpfProfissional))) {
                    if (listar(nomeProfissional, cpfProfissional, enderecoProfissional, telefoneProfissional,
                               celularProfissional))
                        printf("Listado com sucesso!\n");
                    else
                        printf("Desculpe, agenda vazia!\n");
                }
                else {
                    printf("Desculpe, agenda vazia!\n");
                }
                break;
        }

    } while (opcaoMenu != 0);

    printf("Obrigado!\n");
    return 0;
}