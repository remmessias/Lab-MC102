/*
 * Nome: Rebecca Moreira Messias RA:186416 Turma: W
 *
 * Observações:
 * 1 - Tentei deixar nomes intuitivos para evitar muitos comentários.
 *     Espero que realmente estejam intuitivos XD
 * 2 - Boa correção.
*/

#include <stdio.h>
#include <stdlib.h>
#include "estrutura.h"

int main() {
	int qtdDoenca, qtdMedicos;
	Doenca *doenca = NULL;
	Medico *medico = NULL;
	int matChave[TAM_MAT][TAM_MAT];
	char letraInicial;

	leInteiro(&qtdDoenca);
	// Aloca um espaço para o vetor de doenças com a quantidade indicada de doenças
	doenca = malloc(qtdDoenca * sizeof(Doenca));
	if (doenca != NULL) {
		leVetorDoenca(doenca, qtdDoenca);
	}
	else {
		exit(1);
	}

	leInteiro(&qtdMedicos);

	// Aloca um espaço para o detor de médicos com a quantidade indicada de médicos
	medico = malloc(qtdMedicos * sizeof(Medico));
	if (medico != NULL) {
		leVetorMedico(medico, qtdMedicos);
	}
	else {
		exit(1);
	}
	leMaztrizChave(matChave);
	leCaracter(&letraInicial);

	//Lê a sequência de inserções, remoções e alterações nas consultas
	leConsultas(letraInicial, matChave, qtdDoenca, doenca, qtdMedicos, medico);

	free(medico);
	free(doenca);

	return 0;
}