#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 100
#define TAM_TELEFONE 20

typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];
} Contato;

typedef struct No {
    Contato contato;
    struct No* prox;
} No;

// Função para criar um novo nó
No* criarNo(Contato contato) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo != NULL) {
        novo->contato = contato;
        novo->prox = NULL;
    }
    return novo;
}

// Adiciona o contato em ordem alfabética
void adicionarContato(No** lista, Contato contato) {
    No* novo = criarNo(contato);
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    if (*lista == NULL || strcmp(contato.nome, (*lista)->contato.nome) < 0) {
        novo->prox = *lista;
        *lista = novo;
    } else {
        No* atual = *lista;
        while (atual->prox != NULL && strcmp(contato.nome, atual->prox->contato.nome) > 0) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }

    printf("Contato adicionado com sucesso!\n");
}

// Remove um contato pelo nome
void removerContato(No** lista, const char* nome) {
    No* atual = *lista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->contato.nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Contato não encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Contato removido com sucesso!\n");
}

// Busca contato pelo nome
void buscarContato(No* lista, const char* nome) {
    while (lista != NULL) {
        if (strcmp(lista->contato.nome, nome) == 0) {
            printf("Nome: %s\n", lista->contato.nome);
            printf("Telefone: %s\n", lista->contato.telefone);
            return;
        }
        lista = lista->prox;
    }
    printf("Contato não encontrado.\n");
}

// Lista todos os contatos
void listarContatos(No* lista) {
    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("\n--- Lista de Contatos ---\n");
    while (lista != NULL) {
        printf("Nome: %s\n", lista->contato.nome);
        printf("Telefone: %s\n", lista->contato.telefone);
        printf("------------------------\n");
        lista = lista->prox;
    }
}

// Libera memória da lista
void liberarLista(No* lista) {
    No* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// Menu interativo
int main() {
    No* lista = NULL;
    int opcao;
    Contato contato;
    char nomeBusca[TAM_NOME];

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar contato\n");
        printf("2. Remover contato\n");
        printf("3. Buscar contato\n");
        printf("4. Listar contatos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(contato.nome, TAM_NOME, stdin);
                contato.nome[strcspn(contato.nome, "\n")] = '\0'; // remove '\n'

                printf("Telefone: ");
                fgets(contato.telefone, TAM_TELEFONE, stdin);
                contato.telefone[strcspn(contato.telefone, "\n")] = '\0';

                adicionarContato(&lista, contato);
                break;

            case 2:
                printf("Nome do contato a remover: ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                removerContato(&lista, nomeBusca);
                break;

            case 3:
                printf("Nome do contato a buscar: ");
                fgets(nomeBusca, TAM_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                buscarContato(lista, nomeBusca);
                break;

            case 4:
                listarContatos(lista);
                break;

            case 0:
                liberarLista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
