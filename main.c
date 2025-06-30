#include <stdio.h>

//podemos começar o trabalho!

int main () {
    int option;
    int main = 0;

    printf("Olá! Digite a opção que deseja: ");

    printf("1 - Inserir novo registro /n");
    printf("2 - Remover registro existente /n");
    printf("3 - Exibir todos os livros /n");
    printf("4 - Consultar um livro específico /n");
    printf("5 - Sair\n");

    scanf("%d", &option);

    if (option > 5 || option < 1) {
        printf("Ops! Escolha uma opção válida do menu");
        return;
    }

    while (main){
        switch (option) {
            case 1: 

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                main = 0;
                break;
        }
    }
    
    return 0;
}
