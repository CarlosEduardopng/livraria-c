#include <stdio.h>
#include <locale.h>
#include "livraria.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    if (login()) {
        printf("\nBem-vindo a Livraria Virtual!\n");
        menu();
    } else {
        printf("Erro no login. Encerrando.\n");
    }
    return 0;
}
