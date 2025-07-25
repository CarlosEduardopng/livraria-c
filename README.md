# Projeto de Algoritmos e Estruturas de Dados I

Este projeto é um Sistema de Gerenciamento de Livraria desenvolvido em C, utilizando listas ligadas, algoritmos de ordenação (Quicksort), busca binária, manipulação de arquivos e modularização de código.

## Funcionalidades

* **Sistema de Login:** Login com usuário e senha pré-definidos.
* **Validação de E-mail:** Garante que o e-mail contenha `@`, tenha no máximo 80 caracteres e seja único durante a sessão.
* **CRUD de Livros:**
    * Cadastrar novos livros na livraria.
    * Listar todos os livros cadastrados.
    * Editar as informações de um livro existente.
    * Excluir um livro da livraria.
* **Persistência de Dados:** Os dados dos livros são salvos em arquivo (`livros.txt`) e recarregados ao iniciar o programa.
* **Algoritmos Avançados:**
    * **Quicksort:** Para ordenar temporariamente a lista de livros por ID na busca binária.
    * **Busca Binária:** Para encontrar livros de forma eficiente após a ordenação.
* **Operações Específicas:**
    * Listar livros com preço abaixo de R$50 (promoções).
    * Listar livros disponíveis em estoque.
    * Comprar livros com atualização do estoque e cálculo do total gasto.
    * Visualizar e cancelar compras realizadas.

## Criação de arquivos

Não é necessário criar arquivos manualmente, o programa cria e atualiza o arquivo `livros.txt` automaticamente.

## Como Compilar e Executar

Compile o projeto com o GCC utilizando o seguinte comando no terminal, dentro da pasta do projeto:
````bash
gcc main.c livraria.c -o livraria.exe
````
Após compilar, execute o programa com:
```bash
./livraria
```
No Windows, o executável será livraria.exe, então execute:
```bash
livraria.exe
```
