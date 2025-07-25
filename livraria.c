#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livraria.h"

struct Livro *inicio = NULL;
int totalEmails = 0;
char emailsCadastrados[100][80];
float totalCompras = 0;

void adicionarLivroNaLista(struct Livro *novo) {
    novo->prox = NULL;
    if (inicio == NULL) {
        inicio = novo;
    } else {
        struct Livro *atual = inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

int contarLivros() {
    int count = 0;
    struct Livro *atual = inicio;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

int validarEmail(char email[]) {
    if (strlen(email) >= 80 || strchr(email, '@') == NULL) {
        return 0;
    }
    for (int i = 0; i < totalEmails; i++) {
        if (strcmp(emailsCadastrados[i], email) == 0) {
            return 0;
        }
    }
    strcpy(emailsCadastrados[totalEmails], email);
    totalEmails++;
    return 1;
}

int login() {
    char email[100];
    char usuario[50];
    char senha[50];

    while (1) {
        printf("Digite seu e-mail (max 80 caracteres e deve conter '@'): ");
        scanf("%s", email);

        if (!validarEmail(email)) {
            printf("E-mail invalido ou ja cadastrado. Tente novamente.\n");
            continue;
        }

        printf("Usuario: ");
        scanf("%s", usuario);
        printf("Senha: ");
        scanf("%s", senha);

        if (strcmp(usuario, "admin") == 0 && strcmp(senha, "1234") == 0) {
            return 1;
        } else {
            printf("Usuario ou senha incorretos. Tente novamente.\n");
        }
    }
}

void cadastrarLivro() {
    struct Livro *novo = (struct Livro *) malloc(sizeof(struct Livro));
    if (!novo) {
        printf("Erro de memoria!\n");
        return;
    }

    novo->id = contarLivros() + 1;
    getchar();
    printf("Titulo: ");
    fgets(novo->titulo, 100, stdin);
    strtok(novo->titulo, "\n");

    printf("Autor: ");
    fgets(novo->autor, 100, stdin);
    strtok(novo->autor, "\n");

    printf("Preco: R$ ");
    scanf("%f", &novo->preco);

    printf("Estoque: ");
    scanf("%d", &novo->estoque);

    adicionarLivroNaLista(novo);
    printf("Livro cadastrado com sucesso!\n");
}

void listarLivros() {
    if (!inicio) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    struct Livro *atual = inicio;
    while (atual != NULL) {
        printf("\nID: %d\nTitulo: %s\nAutor: %s\nPreco: R$%.2f\nEstoque: %d\n",
               atual->id, atual->titulo, atual->autor, atual->preco, atual->estoque);
        atual = atual->prox;
    }
}

void editarLivro() {
    int id;
    printf("Digite o ID do livro a editar: ");
    scanf("%d", &id);

    struct Livro *atual = inicio;
    while (atual != NULL) {
        if (atual->id == id) {
            getchar();
            printf("Novo titulo: ");
            fgets(atual->titulo, 100, stdin);
            strtok(atual->titulo, "\n");

            printf("Novo autor: ");
            fgets(atual->autor, 100, stdin);
            strtok(atual->autor, "\n");

            printf("Novo preco: R$ ");
            scanf("%f", &atual->preco);

            printf("Novo estoque: ");
            scanf("%d", &atual->estoque);

            printf("Livro atualizado com sucesso!\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Livro nao encontrado.\n");
}

void excluirLivro() {
    int id;
    printf("Digite o ID do livro a excluir: ");
    scanf("%d", &id);

    struct Livro *atual = inicio, *anterior = NULL;
    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) {
                inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Livro excluido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Livro nao encontrado.\n");
}

void listarPromocoes() {
    struct Livro *atual = inicio;
    printf("\nLivros com preco abaixo de R$50:\n");
    while (atual != NULL) {
        if (atual->preco < 50) {
            printf("- %s (R$%.2f)\n", atual->titulo, atual->preco);
        }
        atual = atual->prox;
    }
}

void listarDisponiveis() {
    struct Livro *atual = inicio;
    printf("\nLivros com estoque disponivel:\n");
    while (atual != NULL) {
        if (atual->estoque > 0) {
            printf("ID: %d - %s (%d unidades)\n", atual->id, atual->titulo, atual->estoque);
        }
        atual = atual->prox;
    }
}

void comprarLivro() {
    int id, qtd;
    listarDisponiveis();

    printf("\nDigite o ID do livro que deseja comprar: ");
    scanf("%d", &id);

    struct Livro *atual = inicio;
    while (atual != NULL) {
        if (atual->id == id) {
            printf("Quantidade: ");
            scanf("%d", &qtd);
            if (qtd > atual->estoque) {
                printf("Quantidade indisponivel.\n");
                return;
            }
            atual->estoque -= qtd;
            totalCompras += atual->preco * qtd;
            printf("Compra realizada: %d unidade(s) de \"%s\" por R$%.2f\n",
                   qtd, atual->titulo, atual->preco * qtd);
            return;
        }
        atual = atual->prox;
    }
    printf("Livro nao encontrado.\n");
}

void verCarrinho() {
    printf("\nTotal de compras: R$%.2f\n", totalCompras);
}

void cancelarCompra() {
    if (totalCompras == 0) {
        printf("Nenhuma compra para cancelar.\n");
        return;
    }
    totalCompras = 0;
    printf("Compras canceladas com sucesso.\n");
}

int compararId(const void *a, const void *b) {
    struct Livro *l1 = *(struct Livro **)a;
    struct Livro *l2 = *(struct Livro **)b;
    return l1->id - l2->id;
}

void buscaBinariaPorId() {
    int n = contarLivros();
    if (n == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    struct Livro **vetor = malloc(n * sizeof(struct Livro *));
    struct Livro *atual = inicio;
    for (int i = 0; i < n; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }
    qsort(vetor, n, sizeof(struct Livro *), compararId);

    int id;
    printf("Digite o ID para buscar: ");
    scanf("%d", &id);

    int ini = 0, fim = n - 1, meio;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        if (vetor[meio]->id == id) {
            printf("\nLivro encontrado:\nTitulo: %s\nAutor: %s\nPreco: R$%.2f\nEstoque: %d\n",
                   vetor[meio]->titulo, vetor[meio]->autor,
                   vetor[meio]->preco, vetor[meio]->estoque);
            free(vetor);
            return;
        } else if (vetor[meio]->id < id) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Livro nao encontrado.\n");
    free(vetor);
}

void menu() {
    int opcao;
    do {
        printf("\n====== MENU ======\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Editar livro\n");
        printf("4. Excluir livro\n");
        printf("5. Listar livros em promocao\n");
        printf("6. Comprar livro\n");
        printf("7. Ver total de compras\n");
        printf("8. Cancelar compras\n");
        printf("9. Listar livros disponiveis\n");
        printf("10. Buscar livro por ID\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarLivro(); break;
            case 2: listarLivros(); break;
            case 3: editarLivro(); break;
            case 4: excluirLivro(); break;
            case 5: listarPromocoes(); break;
            case 6: comprarLivro(); break;
            case 7: verCarrinho(); break;
            case 8: cancelarCompra(); break;
            case 9: listarDisponiveis(); break;
            case 10: buscaBinariaPorId(); break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
