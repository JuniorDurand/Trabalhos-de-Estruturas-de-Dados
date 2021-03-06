#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	printf("1 - Criar Colecao\n");
	printf("2 - Inserir elemento\n");
	printf("3 - Consultar elemento\n");
	printf("4 - Remover elemento\n");
	printf("5 - Listar todos os elementos\n");
	printf("6 - Destruir estrutura\n");
	printf("0 - Sair\n");
	printf("Digite uma opcao: \n");
}


void printPessoa(Pessoa *p){
	if(p != NULL){
		printf("Nome: %s",p->nome );
		printf("Idade: %d\n",p->idade);
		printf("Quantidade de filhos: %d\n",p->numFilhos);
		printf("Salario: %f\n",p->salario);
		printf("CPF: %s\n",p->CPF);
	}
}


void criaPessoa(Col *c){
	if(c != NULL){
		Pessoa *p = (Pessoa*)malloc(sizeof(Pessoa));
		printf("Digite o nome:");
		setbuf(stdin, NULL);
		fgets(p->nome,50,stdin);
		printf("Digite a idade:");
		setbuf(stdin, NULL);
		scanf("%d", &(p->idade));
		printf("Digite a quantidade de filhos:");
		setbuf(stdin, NULL);
		scanf("%d", &(p->numFilhos));
		printf("Digite o salario:");
		setbuf(stdin, NULL);
		scanf("%f", &(p->salario));
		printf("Digite o CPF:");
		setbuf(stdin, NULL);
		fgets(p->CPF,15,stdin);
		int flag = colInsert(c, (void*)p);
		if(flag){
			printf("Elemento inserido com sucesso\n");
		}else{
			printf("Elemento não inserido na colecao\n");
		}
	}else{
		printf("ERRO: colecao inexistente\n");
	}

}




void printMenuProcura(){
	printf("1 - Procurar por nome\n");
	printf("2 - Procurar por CPF\n");
}

int compCPF(void *x, char *b){
	Pessoa *a = (Pessoa*)x;
	if(strcmp(a->CPF, b)==0){
		return true;
	}else{
		return false;
	}
}






int compNome(void *x, char *b){
	Pessoa *a = (Pessoa*)x;
	if(strcmp(a->nome, b)==0){
		return true;
	}else{
		return false;
	}
}



int procuraPorNome(Col *c){
	Pessoa *p;
	char nomeProc[50];
	int flag = true;
	printf("Digite o nome:");
	setbuf(stdin, NULL);
	fgets(nomeProc,50,stdin);
	p = (Pessoa*)colQueryFirst(c);
	while(p != NULL){
		if(compNome( p, nomeProc)){
			printPessoa(p);
			//flag = false;
			return true;
		}else{
			p = (Pessoa*)colQueryNext(c);
		}
	}
	if(flag){
		//printf("\nPessoa não encontrada\n");
		return false;
	}
}

int procuraPorCPF(Col *c){
	Pessoa *p;
	char CPFProc[15];
	int flag = true;
	printf("Digite o CPF:");
	setbuf(stdin, NULL);
	fgets(CPFProc,15,stdin);
	p = (Pessoa*)colQueryFirst(c);
	while(p != NULL){
		if(compCPF( p, CPFProc)){
			printPessoa(p);
			//flag = false;
			return true;
		}else{
			p = (Pessoa*)colQueryNext(c);
		}
	}
	if(flag){
		//printf("\nPessoa não encontrada\n");
		return false;
	}
}


Pessoa* retornaPorNome(Col *c){
	Pessoa *p;
	char nomeProc[50];
	int flag = true;
	printf("Digite o nome:");
	setbuf(stdin, NULL);
	fgets(nomeProc,50,stdin);
	p = (Pessoa*)colQueryFirst(c);
	while(p != NULL){
		if(compNome( p, nomeProc)){
			flag = false;
			return p;
		}else{
			p = (Pessoa*)colQueryNext(c);
		}
	}
	if(flag){
		//printf("\nPessoa não encontrada\n");
		return NULL;
	}
}

Pessoa* retornaPorCPF(Col *c){
	Pessoa *p;
	char CPFProc[15];
	int flag = true;
	printf("Digite o CPF:");
	setbuf(stdin, NULL);
	fgets(CPFProc,15,stdin);
	p = (Pessoa*)colQueryFirst(c);
	while(p != NULL){
		if(compCPF( p, CPFProc)){
			flag = false;
			return p;
		}else{
			p = (Pessoa*)colQueryNext(c);
		}
	}
	if(flag){
		//printf("\nPessoa não encontrada\n");
		return NULL;
	}
}

void ProcuraPessoa(Col *c){
	if(c != NULL){
		int opcao;
		
		do{
			printMenuProcura();
			setbuf(stdin, NULL);
			scanf("%d", &opcao);
			if(opcao == 1){
				int teste;
				teste = procuraPorNome(c);
				if(!teste){
					printf("\nPessoa nao encontrada\n");
				}				

			}else if(opcao == 2){
				int teste;
				teste = procuraPorCPF(c);
				if(!teste){
					printf("\nPessoa nao encontrada\n");
				}
			}
		}while(opcao < 1 || opcao > 2);
	}
}


void removePessoa(Col *c){
	if(c != NULL){
		int opcao;
		
		do{
			printMenuProcura();
			setbuf(stdin, NULL);
			scanf("%d", &opcao);
			if(opcao == 1){
				Pessoa *pesRemov;
				pesRemov = retornaPorNome(c);
				if(pesRemov!=NULL){
					Pessoa *aux = (Pessoa*)colRemoveVoid(c, (void*)pesRemov);
					printPessoa(pesRemov);
					free(pesRemov);
					printf("Pessoa removida com sucesso\n");
				}else{
					printf("Pessoa nao encontrada\n");
				}				

			}else if(opcao == 2){
				Pessoa *pesRemov;
				pesRemov = retornaPorCPF(c);
				if(pesRemov!=NULL){
					Pessoa *aux = (Pessoa*)colRemoveVoid(c, (void*)pesRemov);
					printPessoa(pesRemov);
					free(pesRemov);
					printf("Pessoa removida com sucesso\n");
				}else{
					printf("Pessoa nao encontrada\n");
				}
			}
		}while(opcao < 1 || opcao > 2);
	}
}

void printTodasPessoas(Col *c){
	if(c != NULL){
		printf("\n---------------\n");		
		Pessoa *p = (Pessoa*)malloc(sizeof(Pessoa));
		p = (Pessoa*)colQueryFirst(c);
		while(p != NULL){
			colStatus(c);
			printPessoa(p);
			printf("\n---------------\n");
			p = (Pessoa*)colQueryNext(c);
		}
	}
}




void destruirColecao(Col *pessoas){
	int teste = colDestroy(pessoas);
	if(teste == true){
		pessoas = NULL;
		printf("Colecao destruida com sucesso\n");
	}else{
		printf("Erro ao destruir colecao\n");
		printf("Elementos dentro da colecao.\n");
		printf("Remover todos os elementos e destruir(1 - Sim/ 2 -Nao).\n");
		int remov;
		setbuf(stdin,NULL);
		scanf("%d",&remov);
		if(remov == 1){
			Pessoa *p = (Pessoa*)colRemoveLast(pessoas);
			while(p!=NULL){
				printPessoa(p);
				p = (Pessoa*)colRemoveLast(pessoas);
			}
			teste = colDestroy(pessoas);
			if (teste == true){
				pessoas = NULL;
				printf("Colecao destruida com sucesso\n");

			}else{
				printf("ERRO ao destruir colecao\n");
			}
		}

	}
}