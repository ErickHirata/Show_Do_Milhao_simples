/*
[ Erick Yuji Hirata                       ]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição Estruturas de dados copiado do enunciado
typedef struct {
    int cd_cliente;
    char nm_cliente[50];
    char ds_endereco[50];
    int nr_numero;
    char nr_documento[20];
    char ds_cidade[50];
    char cd_uf[5];
    char dt_cadastro[19];
    char nr_telefone[15];
} reg_cliente;

// Definição 
typedef struct Node {
    reg_cliente cliente;
    struct Node* next;
} Node;

Node* initializeList() {
    return NULL;
}

Node* insertEnd(Node* head, reg_cliente newCliente) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro: Falha na alocação de memória para o novo cliente.\n");
        return head;
    }

    newNode->cliente = newCliente;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

Node* insertBeginning(Node* head, reg_cliente newCliente) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro: Falha na alocação de memória para o novo cliente. \n");
        return head;
    }
    newNode->cliente = newCliente;
    newNode->next = head;
    return newNode;
}

Node* insertAtPosition(Node* head, reg_cliente newCliente, int position) {
    if (position < 1) {
        printf("Erro 404: Insira uma posição maior ou igual a 1. \n");
        return head;
    }

    if (position == 1) {
        return insertBeginning(head, newCliente);
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro 404: Deu ruim... )-: \n");
        return head;
    }
    newNode->cliente = newCliente;

    Node* current = head;
    int currentPosition = 1;
    while (current != NULL && currentPosition < position - 1) {
        current = current->next;
        currentPosition++;
    }

    if (current == NULL) {
        printf("Erro 404: Não é possível inserir nessa posição \n");
        free(newNode);
        return head;
    }

    newNode->next = current->next; //q nem na aula
    current->next = newNode;
    return head;
}

void listAllClients(Node* head) {
    Node* current = head;
    if (current == NULL) {
        printf("A lista de clientes está vazia né... \n");
    } 
    
    else {
        while (current != NULL) {
            reg_cliente cliente = current->cliente;
            printf("Código: %d\n", cliente.cd_cliente);
            printf("Nome: %s\n", cliente.nm_cliente);
            printf("Endereço: %s %d\n", cliente.ds_endereco, cliente.nr_numero);
            printf("Documento: %s\n", cliente.nr_documento);
            printf("Cidade: %s, UF: %s\n", cliente.ds_cidade, cliente.cd_uf);
            printf("Data de Cadastro: %s\n", cliente.dt_cadastro);
            printf("Telefone: %s\n\n", cliente.nr_telefone);

            current = current->next;
        }
    }
}

Node* removeEnd(Node* head) {
    if (head == NULL) {
        printf("A lista de clientes está vazia, POR ISSO NÃO É POSSIVEL REMOVER. \n");
        return NULL;
    } 
    
    else if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Node* current = head;
    Node* previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    free(current);
    previous->next = NULL;
    return head;
}

Node* removeFromPosition(Node* head, int position) {
    if (position < 1) {
        printf("Erro 404: Insira uma posição maior ou igual a 1 por favor... \n");
        return head;
    }

    if (position == 1) {
        Node* newHead = head->next;
        free(head);
        return newHead;
    }

    Node* current = head;
    int currentPosition = 1;
    while (current != NULL && currentPosition < position - 1) {
        current = current->next;
        currentPosition++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Erro 404 berg: Posição fora dos limites. \n");
        return head;
    }

    Node* nodeToRemove = current->next;
    current->next = nodeToRemove->next;
    free(nodeToRemove);
    return head;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* clientList = initializeList();
    int option;

    do {
        printf("Opções:\n");
        printf("1 - Cadastrar Cliente no Final da Lista \n");
        printf("2 - Consultar Todos Clientes \n");
        printf("3 - Cadastrar Cliente no Início da Lista \n");
        printf("4 - Cadastrar Cliente em uma Posição da Lista \n");
        printf("5 - Remover Cliente no Final da Lista \n");
        printf("6 - Remover Cliente na Posição da Lista \n");
        printf("7 - Remover Cliente no Início da Lista \n");
        printf("8 - Finalizar Programa \n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                reg_cliente newClient;
                printf("Código do Cliente:  ");
                scanf("%d", &newClient.cd_cliente);

                printf("Nome do Cliente:  ");
                scanf(" %49[^\n]", newClient.nm_cliente);  //%49 ->  Especifica que a entrada deve ser lida como uma string de até tal numero LEMBRAR PRA PROVA

                printf("Endereço:  ");
                scanf(" %49[^\n]", newClient.ds_endereco);

                printf("Número da Casa/Apto:  ");
                scanf("%d", &newClient.nr_numero);

                printf("Documento:  ");
                scanf(" %19[^\n]", newClient.nr_documento);

                printf("Cidade:  ");
                scanf(" %49[^\n]", newClient.ds_cidade);

                printf("UF:  ");
                scanf(" %5[^\n]", newClient.cd_uf);

                printf("Data de Cadastro: ");
                scanf(" %19[^\n]", newClient.dt_cadastro);

                printf("Telefone: ");
                scanf(" %14[^\n]", newClient.nr_telefone);

                clientList = insertEnd(clientList, newClient);
                break;
            }
            case 2: {
                listAllClients(clientList);
                break;
            }
            case 3: {
                reg_cliente newClient;
                printf("Código do Cliente: ");
                scanf("%d", &newClient.cd_cliente);

                printf("Nome do Cliente: ");
                scanf(" %49[^\n]", newClient.nm_cliente);

                printf("Endereço: ");
                scanf(" %49[^\n]", newClient.ds_endereco);

                printf("Número Da Casa Ou Apartamento/ algum numero da sua residencia por favor: ");
                scanf("%d", &newClient.nr_numero);

                printf("Documento: ");
                scanf(" %19[^\n]", newClient.nr_documento);

                printf("Cidade: ");
                scanf(" %49[^\n]", newClient.ds_cidade);

                printf("UF: ");
                scanf(" %5[^\n]", newClient.cd_uf);

                printf("Data de Cadastro: ");
                scanf(" %19[^\n]", newClient.dt_cadastro);

                printf("Telefone: ");
                scanf(" %14[^\n]", newClient.nr_telefone);

                clientList = insertBeginning(clientList, newClient);
                break;
            }
            case 4: {
                int position;
                printf("Digite a posição para inserir o cliente: ");
                scanf("%d", &position);

                reg_cliente newClient;
                printf("Código do Cliente: ");
                scanf("%d", &newClient.cd_cliente);

                printf("Nome do Cliente: ");
                scanf(" %49[^\n]", newClient.nm_cliente);

                printf("Endereço: ");
                scanf(" %49[^\n]", newClient.ds_endereco);

                printf("Número: ");
                scanf("%d", &newClient.nr_numero);

                printf("Documento: ");
                scanf(" %19[^\n]", newClient.nr_documento);

                printf("Cidade: ");
                scanf(" %49[^\n]", newClient.ds_cidade);

                printf("UF: ");
                scanf(" %5[^\n]", newClient.cd_uf);

                printf("Data de Cadastro: ");
                scanf(" %19[^\n]", newClient.dt_cadastro);

                printf("Telefone: ");
                scanf(" %14[^\n]", newClient.nr_telefone);

                clientList = insertAtPosition(clientList, newClient, position);
                break;
            }
            case 5: {
                clientList = removeEnd(clientList);
                break;
            }
            case 6: {
                int position;
                printf("Digite a posição para remover o cliente: ");
                scanf("%d", &position);

                clientList = removeFromPosition(clientList, position);
                break;
            }
            case 7: {
                if (clientList == NULL) {
                    printf("A lista de clientes tá vazia...  )-:  \n");
                } 
                
                else {
                    Node* temp = clientList;
                    clientList = clientList->next;
                    free(temp);
                }
                break;
            }
            case 8: {
                freeList(clientList);
                exit(0);
            }
            default:
                printf("Opção inválida right now hehehe. \n");
                break;
        }
    } 
    
    while (option != 8);

    return 0;
}
