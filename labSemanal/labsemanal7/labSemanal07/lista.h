//Nome: Rebecca Moreira Messias RA:186416 Turma: W
#ifndef LABSEMANAL07_LISTA_H
#define LABSEMANAL07_LISTA_H

#include "estrutura.h"

struct Lista {
	ConsultaInfo informacao;
	struct Lista *prox;
};

//Cria a lista
struct Lista *cria(ConsultaInfo info);

//Insere na lista
struct Lista *insere(struct Lista *l, ConsultaInfo info, String nomeDec, int mat[TAM_MAT][TAM_MAT]);

//Remove da lista
struct Lista *apagaConsulta(struct Lista *lista, String nome);

//Altera um diagnostico
void atualizaDiagnostico(struct Lista *lista, String nome, CodDoenca cod);

//Altera uma data
void atualizaData(struct Lista *lista, String nome, Data data);

//Altera um médico
void atualizaMedico(struct Lista *lista, String nome, int crm);

//Escreve a lista descriptografada
void escreveResposta(struct Lista *l, char letra);

//Decodifica a lista
void decodificaLista(struct Lista *l, int matriz[TAM_MAT][TAM_MAT]);

//Desaloca lista
void desalocaLista(struct Lista *lista);

#endif