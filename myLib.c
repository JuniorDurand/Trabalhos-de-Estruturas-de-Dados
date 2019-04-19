#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "colecao.h"


typedef struct _pessoa_{
	char nome[50];
	int idade;
	int numFilhos;
	float salario;
	char CPF[15];
}Pessoa;


void printMenu(){
	printf("1 - Inserir elemento\n");
	printf("2 - Consultar elemento\n");
	printf("3 - Remover elemento\n");
	printf("4 - Listar todos os elementos\n");
	printf("5 - Destruir estrutura e sair\n");
	printf("Digite uma opcao: \n");
}

