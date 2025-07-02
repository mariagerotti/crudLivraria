#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
        struct author{
            char autNAME[15];
            char country[15];
        } autor; //DEFINE A STRUCT author COMO autor (DEVE-SE USAR autor AO LONGO DO PROGRAMA)
        struct date{
            int dia;
            int mes;
            int ano;
        } data; //DEFINE A STRUCT date COMO data (DEVE-SE USAR data AO LONGO DO PROGRAMA)
        char title[30];
        int pCOUNT;
        char genre[10];
        char editora[20];
    } book; //DEFINE A STRUCT DE DADOS COMO O TIPO book

void insert_register(book **lista, int *count){
    *lista = realloc(*lista, (*count + 1) * sizeof(book));
    if (*lista == NULL){
        printf("FALHA NA ALOCAÇÃO DE MEMÓRIA!");
        exit(1);
    }
    printf("\nTítulo:\n"); //RECEBE DADOS DO USUÁRIO SOBRE O LIVRO
    scanf(" %[^\n]", (*lista)[*count].title);
    for (int i = 0; i < *count;i++){
        if (strcasecmp((*lista)[i].title, (*lista)[*count].title) != 0){
            prinf("\nTÍTULO JÁ REGISTRADO!\n");
            return;
        }
    }
    printf("\nAutor:\n");
    scanf(" %[^\n]", (*lista)[*count].autor.autNAME);
    printf("\nPaís:\n");
    scanf(" %[^\n]", (*lista)[*count].autor.country);
    printf("\nEditora:\n");
    scanf(" %[^\n]", (*lista)[*count].editora);
    printf("\nGênero:\n");
    scanf(" %[^\n]", (*lista)[*count].genre);
    printf("\nNúmero de Páginas:\n");
    scanf(" %d", &(*lista)[*count].pCOUNT);
    printf("\nDia da Publicação:\n");
    scanf(" %d", &(*lista)[*count].data.dia);
    printf("\nMês da Publicação:\n");
    scanf(" %d", &(*lista)[*count].data.mes);
    printf("\nAno da Publicação:\n");
    scanf(" %d", &(*lista)[*count].data.ano);

    FILE *file = fopen("C:\\Users\\JP\\EX-JOÃO\\Registro\\livros.txt", "a"); //CRIA OU ABRE O ARQUIVO LIVROS.TXT
    if (file == NULL){
        printf("\n ERRO AO ABRIR O ARQUIVO DE REGISTRO\n");
        return;
    }
    fprintf(file, "%s;%s;%s;%s;%s;%d;%d/%d/%d\n", (*lista)[*count].title, (*lista)[*count].autor.autNAME, (*lista)[*count].autor.country, (*lista)[*count].editora, (*lista)[*count].genre, (*lista)[*count].pCOUNT, (*lista)[*count].data.dia, (*lista)[*count].data.mes, (*lista)[*count].data.ano);
    //lINHA ACIMA REGISTRA AS INFORMAÇÕES NO ARQUIVO LIVROS.TXT
    fclose(file);

    (*count)++;

    printf("\nRegistro realizado com sucesso!\n");
}

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
