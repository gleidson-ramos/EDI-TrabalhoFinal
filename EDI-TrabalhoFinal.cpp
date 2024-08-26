#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nome[150];
    int idade;
} Cliente;

void cadastrar(Cliente **clientes, int *contador) {
	Cliente *novoCliente = (Cliente*) malloc(sizeof(Cliente));
	
	if (*contador > 0) {
		novoCliente->codigo = (*clientes)[(*contador) - 1].codigo + 1;
        
		printf("Digite o nome do cliente: ");
		scanf(" %[^\n]s", novoCliente->nome);
		
		printf("Digite o idade do cliente: ");
		scanf("%d", &novoCliente->idade);
		
		(*contador)++;		
		*clientes = (Cliente*) realloc(*clientes, (*contador) * sizeof(Cliente));
		(*clientes)[(*contador) - 1] = *novoCliente;
		printf("Cliente cadastrado com sucesso!\n");
	}else {
		novoCliente->codigo = 1;
		
		printf("Digite o nome do cliente: ");
		scanf(" %[^\n]s", novoCliente->nome);
		
		printf("Digite o idade do cliente: ");
		scanf("%d", &novoCliente->idade);
		
		(*contador)++;
		
		*clientes = (Cliente*) realloc(*clientes, (*contador) * sizeof(Cliente));
		(*clientes)[(*contador) - 1] = *novoCliente;
		
		printf("Cliente cadastrado com sucesso!\n");
	}
    free(novoCliente);
}

void exibir(Cliente *clientes, int contador) {
    if (contador > 0) {
        printf("Clientes cadastrados:\n");

        for (int i = 0; i < contador; i++) {
            printf("Codigo: %d\n", clientes[i].codigo);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Idade: %d\n", clientes[i].idade);
            printf("------\n");
        }
    } else {
        printf("Nenhum cliente cadastrado.\n");
    }
}

int funcaoIndex(Cliente *clientes, int contador, int codigo){
	int index = -1;
	
	for (int i = 0; i < contador; i++) {
		if (clientes[i].codigo == codigo) {
			index = i;
			break;
		}
	}
	return index;
}

void consultar(Cliente *clientes, int contador, int codigo) {
    if (contador > 0) {
        int index = funcaoIndex(clientes, contador, codigo);
        
        if (index != -1) {
            printf("\nCLIENTE %d ENCONTRADO!\n", clientes[index].codigo);
            printf("Codigo: %d\n", clientes[index].codigo);
            printf("Nome: %s\n", clientes[index].nome);
            printf("Idade: %d\n\n", clientes[index].idade);
        } else {
            printf("Cliente nao encontrado.\n");
        }
    } else {
        printf("Nenhum cliente cadastrado.\n");
    }
}


void editar(Cliente *clientes, int contador) {
	if (contador > 0) {
    	int codigo, op;
		
		printf("Digite o codigo do cliente: ");
		scanf("%d", &codigo);
		
		int index = funcaoIndex(clientes, contador, codigo);        
    	consultar(clientes, contador, codigo);
    	
    	if (index != -1) {
    		do {
    			printf("\nMenu de edicao\n");
				printf("1 - Alterar nome\n");
				printf("2 - Alterar idade\n");
				printf("3 - Alterar todos os dados\n");
				printf("4 - Voltar\n");
				printf("\nInforme a opcao: ");
				scanf("%d", &op);
				
				switch (op) {
					case 1:
						printf("Digite o nome: ");
						scanf(" %[^\n]s", clientes[index].nome);
						
						printf("Nome Alterado com sucesso!\n");
						break;
					case 2:
						printf("Digite a idade: ");
						scanf("%d", &clientes[index].idade);
						
						printf("Idade editada com sucesso!\n");
						break;
					case 3:
						printf("Digite o nome: ");
						scanf(" %[^\n]s", clientes[index].nome);
						
						printf("Digite a idade: ");
						scanf("%d", &clientes[index].idade);
						
						printf("Cliente editado com sucesso!\n");
						break;
					case 4:
						printf("Saindo do menu de edicao.\n");
						break;
					default:
						printf("Opcao invalida!\n");
				}
			}while (op != 4);
		}
	}else {
		printf("Cliente nao encontrado.\n");
	}
}
 
	

void deletar(Cliente *clientes, int *contador) {
    if (*contador > 0) {
        int codigo;

        printf("Digite o codigo do cliente que deseja deletar: ");
        scanf("%d", &codigo);

        int index = -1;

        for (int i = 0; i < *contador; i++) {
            if (clientes[i].codigo == codigo) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < (*contador) - 1; i++) {
                clientes[i] = clientes[i + 1];
            }
            (*contador)--;

            printf("Cliente deletado com sucesso!\n");
        } else {
            printf("Cliente nao encontrado.\n");
        }
        
    } else {
        printf("Nenhum cliente cadastrado.\n");
    }
}


void salvarArquivo(Cliente *clientes, int contador) {
	if (contador==0){
		remove("clientes.txt");
		printf("Lista Vazia");
	} else{
		FILE *arquivo;
		arquivo = fopen("clientes.txt", "w");
		
		if (arquivo == NULL) {
			printf("Erro ao abrir o arquivo.\n");
			return;
		}
		
		for (int i = 0; i < contador; i++) {
			fprintf(arquivo, "Codigo: %d\n", clientes[i].codigo);
			fprintf(arquivo, "Nome: %s\n", clientes[i].nome);
			fprintf(arquivo, "Idade: %d\n", clientes[i].idade);
			fprintf(arquivo, "------\n");
		}		
		fclose(arquivo);
		printf("Dados salvos no arquivo com sucesso!\n");
	}
}

void carregarArquivo(Cliente **clientes, int *contador) {
    FILE *arquivo;
    arquivo = fopen("clientes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    } else {
    	while (!feof(arquivo)) {
    		Cliente novoCliente;
			fscanf(arquivo, "Codigo: %d\n", &novoCliente.codigo);
			fscanf(arquivo, "Nome: %s\n", novoCliente.nome);
			fscanf(arquivo, "Idade: %d\n", &novoCliente.idade);
			fscanf(arquivo, "------\n");
			
			(*contador)++;
			
			*clientes = (Cliente*) realloc(*clientes, (*contador) * sizeof(Cliente));
			(*clientes)[(*contador) - 1] = novoCliente;
		}
	}    

    fclose(arquivo);
    printf("Dados carregados do arquivo com sucesso!\n");
}

int main() {
    Cliente *clientes = NULL;
    int contador = 0;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Carregar do arquivo\n");
        printf("2 - Cadastrar\n");
        printf("3 - Consultar\n");
        printf("4 - Editar\n");
        printf("5 - Deletar\n");
        printf("6 - Exibir Todos\n");
        printf("7 - Salvar em arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                carregarArquivo(&clientes, &contador);
                break;
            case 2:
                cadastrar(&clientes, &contador);
                break;
            case 3:
            	int codigo;
            	printf("Digite o codigo do cliente: ");
            	scanf("%d", &codigo);
                consultar(clientes, contador, codigo);
                break;
            case 4:
            	exibir(clientes, contador);
                editar(clientes, contador);
                break;
            case 5:
                deletar(clientes, &contador);
                break;
            case 6:
                exibir(clientes, contador);
                break;
            case 7:
                salvarArquivo(clientes, contador);
                break;
            case 0:
                printf("Programa Encerrado.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    free(clientes);

    return 0;
}

