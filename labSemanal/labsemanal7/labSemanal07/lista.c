//Nome: Rebecca Moreira Messias RA:186416 Turma: W
#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Lista *cria(ConsultaInfo info) {
	struct Lista *l = malloc(sizeof(struct Lista));
	if (l != NULL) {
		l->informacao = info;
		l->prox = l;
	}
	return l;
}

struct Lista *insere(struct Lista *l, ConsultaInfo info, String nomeDec, int mat[TAM_MAT][TAM_MAT]) {
	struct Lista *aux = l;
	struct Lista *novoElemento = NULL;

	if (l == l->prox) {
		String decodificaNome;
		decodifica(mat, l->informacao.nomePaciente, decodificaNome);
		novoElemento = malloc(sizeof(struct Lista));
		if (novoElemento != NULL) {
			novoElemento->informacao = info;
			novoElemento->prox = l;
			l->prox = novoElemento;
		}
		if (strcmp(decodificaNome, nomeDec) > 0)
			return novoElemento;
		else
			return l;
	}
	else {
		String decAtual, decProx;
		decodifica(mat, aux->informacao.nomePaciente, decAtual);
		if (strcmp(nomeDec, decAtual) < 0) { // se for inserir na primeira posição
			struct Lista *loop = aux;
			for (; loop->prox != aux; loop = loop->prox);
			novoElemento = malloc(sizeof(struct Lista));
			if (novoElemento != NULL) {
				novoElemento->informacao = info;
				novoElemento->prox = aux;
				loop->prox = novoElemento;
			}
			return novoElemento;
		}
		else { // se for inserir em alguma posição no meio da lista
			decodifica(mat, aux->prox->informacao.nomePaciente, decProx);
			do {
				if (strcmp(nomeDec, decAtual) > 0 && strcmp(nomeDec, decProx) < 0) {
					novoElemento = malloc(sizeof(struct Lista));
					if (novoElemento != NULL) {
						novoElemento->informacao = info;
						novoElemento->prox = aux->prox;
						aux->prox = novoElemento;
					}
					return l;
				}
				aux = aux->prox;
				decodifica(mat, aux->informacao.nomePaciente, decAtual);
				decodifica(mat, aux->prox->informacao.nomePaciente, decProx);
			} while (aux != l);
		}
	}
	if (aux == l) { // se for inserir na última posição
		for (aux = aux->prox; aux->prox != l; aux = aux->prox);
		novoElemento = malloc(sizeof(struct Lista));
		if (novoElemento != NULL) {
			novoElemento->informacao = info;
			novoElemento->prox = l;
			aux->prox = novoElemento;
		}
		return l;
	}

	return aux;
}

struct Lista *apagaConsulta(struct Lista *lista, String nome) {
	struct Lista *aux = lista;

	if (strcmp(nome, lista->informacao.nomePaciente) == 0 && lista->prox == lista) {
		free(lista);
		return NULL;
	}
	if (strcmp(nome, lista->informacao.nomePaciente) == 0 && lista->prox != lista) {
		for (; aux->prox != lista; aux = aux->prox);
		aux->prox = lista->prox;
		free(lista);
		return aux->prox;
	}
	do {
		if (strcmp(aux->prox->informacao.nomePaciente, nome) == 0) {
			aux->prox = aux->prox->prox;
			break;
		}
		aux = aux->prox;
	} while (aux != lista);

	return lista;
}

void atualizaDiagnostico(struct Lista *lista, String nome, CodDoenca cod) {
	if (strcmp(lista->informacao.nomePaciente, nome) == 0)
		strcpy(lista->informacao.diagnostico, cod);
	else {
		struct Lista *aux = lista->prox;
		while (aux != lista) {
			if (strcmp(aux->informacao.nomePaciente, nome) == 0) {
				strcpy(aux->informacao.diagnostico, cod);
				break;
			}
			aux = aux->prox;
		}
	}
}

void atualizaData(struct Lista *lista, String nome, Data data) {
	if (strcmp(lista->informacao.nomePaciente, nome) == 0)
		strcpy(lista->informacao.data, data);
	else {
		struct Lista *aux = lista->prox;
		while (aux != lista) {
			if (strcmp(aux->informacao.nomePaciente, nome) == 0) {
				strcpy(aux->informacao.data, data);
				break;
			}
			aux = aux->prox;
		}
	}
}

void atualizaMedico(struct Lista *lista, String nome, int crm) {
	if (strcmp(lista->informacao.nomePaciente, nome) == 0)
		lista->informacao.crm = crm;
	else {
		struct Lista *aux = lista->prox;
		while (aux != lista) {
			if (strcmp(aux->informacao.nomePaciente, nome) == 0) {
				aux->informacao.crm = crm;
				break;
			}
			aux = aux->prox;
		}
	}
}

void escreveResposta(struct Lista *l, char letra) {
	if (l->informacao.nomePaciente[0] == letra) {
		printf("%s %s %s %d\n", l->informacao.nomePaciente, l->informacao.data, l->informacao.diagnostico,
			   l->informacao.crm);
		struct Lista *aux = l->prox;
		while (aux != l) {
			printf("%s %s %s %d\n", aux->informacao.nomePaciente, aux->informacao.data, aux->informacao.diagnostico,
				   aux->informacao.crm);
			aux = aux->prox;
		}
	}
	else {
		struct Lista *aux = l;
		struct Lista *percorre;
		while (aux->informacao.nomePaciente[0] < letra) { // procura o primeiro paciente a ser escrito
			if (aux->informacao.nomePaciente[0] == 'Z' && letra != 'Z') {
				aux = l;
				break;
			}
			if (aux->prox == l) {
				aux = l;
				break;
			}
			aux = aux->prox;
		}
		printf("%s %s %s %d\n", aux->informacao.nomePaciente, aux->informacao.data, aux->informacao.diagnostico,
			   aux->informacao.crm);
		percorre = aux->prox;
		while (percorre != aux) {
			printf("%s %s %s %d\n", percorre->informacao.nomePaciente, percorre->informacao.data,
				   percorre->informacao.diagnostico, percorre->informacao.crm);
			percorre = percorre->prox;
		}
	}
}

void decodificaLista(struct Lista *l, int matriz[TAM_MAT][TAM_MAT]) {
	struct Lista *aux = l;
	String nomeDecodificado;

	decodifica(matriz, l->informacao.nomePaciente, nomeDecodificado);
	strcpy(l->informacao.nomePaciente, nomeDecodificado);

	aux = aux->prox;
	while (aux != l) {
		String nomeDecifrado;
		decodifica(matriz, aux->informacao.nomePaciente, nomeDecifrado);
		strcpy(aux->informacao.nomePaciente, nomeDecifrado);
		aux = aux->prox;
	}
}

void desalocaLista(struct Lista *lista) {

	if(lista == NULL)
		return;

	struct Lista *aux = lista->prox, *deleta;

	while(aux != lista) {
		deleta = aux;
		aux = aux->prox;
		free(deleta);
	}

	free(lista);
}
