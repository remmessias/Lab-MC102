//Nome: Rebecca Moreira Messias RA:186416 Turma: W
#include "estrutura.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leVetorDoenca(Doenca *doenca, int qtd) {
	int i;
	for (i = 0; i < qtd; i++) {
		scanf(" %s %[^\n]s", doenca[i].codigo, doenca[i].nome);
	}
}

int procuraCRM(String nome, int qtd, Medico *medico) {
	int i, crm;
	for (i = 0; i < qtd; i++) {
		if (strcmp(nome, medico[i].nome) == 0) {
			crm = medico[i].crm;
		}
	}
	return crm;
}

Doenca *procuraDoenca(String nome, int qtd, Doenca *doenca) {
	int i;
	for (i = 0; i < qtd; i++) {
		if (strcmp(nome, doenca[i].nome) == 0) {
			return &doenca[i];
		}
	}
	return NULL;
}

void leVetorMedico(Medico *medico, int qtd) {
	int i;
	for (i = 0; i < qtd; i++) {
		scanf(" %d %[^\n]s", &medico[i].crm, medico[i].nome);
	}
}

void leInteiro(int *variavel) {
	scanf(" %d", &(*variavel));
}

void leMaztrizChave(int matriz[TAM_MAT][TAM_MAT]) {
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			scanf(" %d", &matriz[i][j]);
		}
	}
}

void leCaracter(char *letra) {
	scanf(" %c", &(*letra));
}

int letraCod(char letra) {
	return letra-65;
}

char codLetra(int cod) {
	return cod+65;
}

void criptografia(int matriz[TAM_MAT][TAM_MAT], String nome, String criptografia) {
	int i, j = 1, codLetra1, codLetra2, codLetraCrip1, codLetraCrip2;
	for (i = 0; nome[i] != '\0';) {
		// Pego o código das letras do par atual
		codLetra1 = letraCod(nome[i]);
		codLetra2 = letraCod(nome[j]);
		// Faço o produto entre a matriz chave a matriz com os códigos obtidos
		codLetraCrip1 = ((matriz[0][0] * codLetra1) + (matriz[0][1] * codLetra2)) % 26;
		codLetraCrip2 = ((matriz[1][0] * codLetra1) + (matriz[1][1] * codLetra2)) % 26;
		// Pego a letra obtida com o código encriptografado da letra
		criptografia[i] = codLetra(codLetraCrip1);
		criptografia[j] = codLetra(codLetraCrip2);
		// Incremento para pegar o próximo par de letras
		j += 2;
		i += 2;
	}
	criptografia[i] = '\0';
}

void decodifica(int matriz[TAM_MAT][TAM_MAT], String nome, String desencripta) {
	int dMenos, i, j, determinante = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
	int inversa[TAM_MAT][TAM_MAT];
	int codLetra1, codLetra2, codLetraCrip1, codLetraCrip2;
	// Inversa da matriz
	inversa[0][0] = matriz[1][1];
	inversa[0][1] = -matriz[0][1];
	inversa[1][0] = -matriz[1][0];
	inversa[1][1] = matriz[0][0];
	// Procura o d^(-1)
	for (dMenos = 1; dMenos < 26; dMenos++) {
		if ((determinante * dMenos) % 26 == 1)
			break;
	}
	// Faço o produto da inversa por d^(-1)
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			inversa[i][j] = inversa[i][j] * dMenos;
			inversa[i][j] = inversa[i][j] % 26;
			if (inversa[i][j] < 0) {
				inversa[i][j] = 26 + inversa[i][j];
			}
		}
	}
	for (i = 0, j = 1; nome[i] != '\0';) {
		// Pego o código das letras do par atual
		codLetra1 = letraCod(nome[i]);
		codLetra2 = letraCod(nome[j]);
		// Faço o produto da matriz para desemcripta e o código das letras encriptografadas
		codLetraCrip1 = ((inversa[0][0] * codLetra1) + (inversa[0][1] * codLetra2)) % 26;
		codLetraCrip2 = ((inversa[1][0] * codLetra1) + (inversa[1][1] * codLetra2)) % 26;
		// Pego a letra obtida com o código desencriptamento da letra
		desencripta[i] = codLetra(codLetraCrip1);
		desencripta[j] = codLetra(codLetraCrip2);
		// Incremento para ir para o próximo par de letras
		j += 2;
		i += 2;
	}
	desencripta[i] = '\0';
}

void leConsultas(char letra, int matriz[TAM_MAT][TAM_MAT], int qtdDoenca, Doenca *vetD, int qtdMedico, Medico *vetM) {
	String comando;
	struct Lista *lista = NULL;
	int qtdElemento = 0;

	scanf(" %s", comando);

	while (strcmp(comando, "0") != 0) {
		if (strcmp(comando, "add") == 0) { // para adicionar
			ConsultaInfo info;
			String nomeDecodificado;
			scanf(" %s %s %s %d", info.nomePaciente, info.data, info.diagnostico, &info.crm);

			decodifica(matriz, info.nomePaciente, nomeDecodificado);

			if (qtdElemento == 0) {
				lista = cria(info);
				qtdElemento++;
			}
			else {
				lista = insere(lista, info, nomeDecodificado, matriz);
				qtdElemento++;
			}
		}
		else if (strcmp(comando, "altdiag") == 0) { // para alterar diagnóstico
			String doenca, nome, nomeCrip;
			scanf(" %s %[^\n]s", nome, doenca);

			criptografia(matriz, nome, nomeCrip);

			Doenca *d = procuraDoenca(doenca, qtdDoenca, vetD);
			atualizaDiagnostico(lista, nomeCrip, d->codigo);
		}
		else if (strcmp(comando, "rm") == 0) { // para remover o diagnóstico
			String nome, nomeCrip;
			scanf(" %s", nome);

			criptografia(matriz, nome, nomeCrip);

			lista = apagaConsulta(lista, nomeCrip);
			qtdElemento--;
		}
		else if (strcmp(comando, "altdata") == 0) { // para alterar data
			String nome, nomeCrip;
			Data data;
			scanf(" %s %s", nome, data);

			criptografia(matriz, nome, nomeCrip);

			atualizaData(lista, nomeCrip, data);
		}
		else if (strcmp(comando, "altmed") == 0) { // para alterar médico
			String med, nome, nomeCrip;
			scanf(" %s %[^\n]s", nome, med);

			criptografia(matriz, nome, nomeCrip);

			int crm = procuraCRM(med, qtdMedico, vetM);
			atualizaMedico(lista, nomeCrip, crm);
		}
		scanf(" %s", comando);
	}

	decodificaLista(lista, matriz); //decodifico a lista

	if (qtdElemento > 0) {
		escreveResposta(lista, letra);
	}

	desalocaLista(lista);
}