#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node* esquerda;
    struct Node* direita;
} Node;

Node* criarNo(int valor) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    if (!novoNo) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

Node* minimo(Node* raiz) {
    while (raiz && raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

Node* remover(Node* raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }
    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            Node* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Node* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Node* temp = minimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    return raiz;
}

void buscarPreOrdem(Node* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        buscarPreOrdem(raiz->esquerda);
        buscarPreOrdem(raiz->direita);
    }
}

void buscarEmOrdem(Node* raiz) {
    if (raiz != NULL) {
        buscarEmOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        buscarEmOrdem(raiz->direita);
    }
}

void buscarPosOrdem(Node* raiz) {
    if (raiz != NULL) {
        buscarPosOrdem(raiz->esquerda);
        buscarPosOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

void liberarArvore(Node* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int existe(Node* raiz, int valor) {
    if (raiz == NULL) {
        return 0;
    }
    if (valor < raiz->valor) {
        return existe(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        return existe(raiz->direita, valor);
    }
    return 1; 
}

int main() {
    Node* raiz = NULL;
    int opcao, valor;
    int validInput;

    do {
        printf("\n* * * MENU DE OPÇÕES * * *\n");
        printf("1. Incluir nó.\n");
        printf("2. Remover nó.\n");
        printf("3. Buscar pré-ordem.\n");
        printf("4. Buscar em ordem.\n");
        printf("5. Buscar pós-ordem.\n");
        printf("0. Encerrar.\n");
        printf("Escolha uma opção: ");

        validInput = scanf("%d", &opcao);
        
    
        while (getchar() != '\n');

        if (validInput != 1) {
            printf("Entrada inválida! Por favor, insira um número inteiro.\n");
            continue; 
        }
        printf("----------------------------------------\n");
        switch (opcao) {
            case 1:
                printf("Digite o valor do nó a ser incluído: ");
                validInput = scanf("%d", &valor);
                while (getchar() != '\n');

                if (validInput != 1) {
                    printf("Entrada inválida! Por favor, insira um número inteiro.\n");
                    continue;
                }
                raiz = inserir(raiz, valor);
                printf("Valor %d incluído na árvore!\n", valor);
                break;

            case 2:
                printf("Digite o valor do nó a ser removido: ");
                validInput = scanf("%d", &valor);
                while (getchar() != '\n');

                if (validInput != 1) {
                    printf("Entrada inválida! Por favor, insira um número inteiro.\n");
                    continue;
                }
                if (existe(raiz, valor)) {
                    raiz = remover(raiz, valor);
                    printf("Valor %d removido da árvore!\n", valor);
                } else {
                    printf("Valor %d não encontrado na árvore. Não foi possível remover.\n", valor);
                }
                break;

            case 3:
                printf("\nBusca em pré-ordem: ");
                buscarPreOrdem(raiz);
                printf("\n");
                break;

            case 4:
                printf("\nBusca em ordem: ");
                buscarEmOrdem(raiz);
                printf("\n");
                break;

            case 5:
                printf("\nBusca em pós-ordem: ");
                buscarPosOrdem(raiz);
                printf("\n");
                break;

            case 0:
                liberarArvore(raiz);
                printf("Encerrando o programa...\n");
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
        printf("----------------------------------------\n");
    } while (1);

    return 0;
}
