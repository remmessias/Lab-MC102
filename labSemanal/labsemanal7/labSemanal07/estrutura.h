//Nome: Rebecca Moreira Messias RA:186416 Turma: W
#ifndef LABSEMANAL07_ESTRUTURA_H
#define LABSEMANAL07_ESTRUTURA_H

#define MAX_COD_DOENCA 4
#define MAX_STRING 100
#define TAM_MAT 2
#define MAX_DATA 11

typedef char CodDoenca[MAX_COD_DOENCA];
typedef char String[MAX_STRING];
typedef char Data[MAX_DATA];

typedef struct {
	CodDoenca codigo;
	String nome;
} Doenca;

typedef struct {
	int crm;
	String nome;
} Medico;

typedef struct {
	String nomePaciente;
	String data;
	CodDoenca diagnostico;
	int crm;
} ConsultaInfo;

//Lê coloca as informações de doenças no vetor de doenças
void leVetorDoenca(Doenca *doenca, int qtd);

//Procura o CRM de um médico dado o seu nome
int procuraCRM(String nome, int qtd, Medico *medico);

//Procura uma doença dado seu nome
Doenca *procuraDoenca(String nome, int qtd, Doenca *doenca);

//Lê e coloca as informações de médicos no vetor de médicos
void leVetorMedico(Medico *medico, int qtd);

//Lê um valor inteiro
void leInteiro(int *variavel);

//Lê uma matriz de ordem 2
void leMaztrizChave(int matriz[TAM_MAT][TAM_MAT]);

//Lê um caracter
void leCaracter(char *letra);

//Lê as rotinas que serão feitas na agenda: add, rm, altdiag, altdata, altmed
void leConsultas(char letra, int matriz[TAM_MAT][TAM_MAT], int qtdDoenca, Doenca *vetD, int qtdMedico, Medico *vetM);

//Faz a criptografia de um nome
void criptografia(int matriz[TAM_MAT][TAM_MAT], String nome, String criptografia);

//Retorna uma letra dado o seu código
char codLetra(int cod);

//Retorna um código dado sua letra
int letraCod(char letra);

//Decodifica um nome
void decodifica(int matriz[TAM_MAT][TAM_MAT], String nome, String d);

#endif