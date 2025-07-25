#ifndef LIVRARIA_H
#define LIVRARIA_H

struct Livro {
    int id;
    char titulo[100];
    char autor[100];
    float preco;
    int estoque;
    struct Livro *prox;
};

extern struct Livro *inicio;
extern int totalEmails;
extern char emailsCadastrados[100][80];
extern float totalCompras;

void adicionarLivroNaLista(struct Livro *novo);
int contarLivros();
int validarEmail(char email[]);
int login();
void cadastrarLivro();
void listarLivros();
void editarLivro();
void excluirLivro();
void listarPromocoes();
void listarDisponiveis();
void comprarLivro();
void verCarrinho();
void cancelarCompra();
void buscaBinariaPorId();
void menu();

#endif
