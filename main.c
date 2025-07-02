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

void read_file(book **lista, int *count){
    FILE *file = fopen("C:\\Users\\JP\\EX-JOÃO\\Registro\\livros.txt", "r"); //CRIA OU ABRE O ARQUIVO LIVROS.TXT PARA LEITURA
    if (file == NULL){
        return;
    }
    fscanf(" %d", *count);
    *lista = realloc(*lista, (*count) * sizeof(book));
    for (int i = 0; i < *count; i++){
        fscanf(" %[^\n]", (*lista)[i].title);
        fscanf(" %[^\n]", (*lista)[i].autor.autNAME);
        fscanf(" %[^\n]", (*lista)[i].autor.country);
        fscanf(" %[^\n]", (*lista)[i].editora);
        fscanf(" %[^\n]", (*lista)[i].genre);
        fscanf(" %d", &(*lista)[i].pCOUNT);
        fscanf(" %d", &(*lista)[i].data.dia);
        fscanf(" %d", &(*lista)[i].data.mes);
        fscanf(" %d", &(*lista)[i].data.ano); 
    }
    fclose(file);
}

void insert_register(book **lista, int *count){
    char bufferT[30];
    printf("\nTítulo:\n"); //RECEBE DADOS DO USUÁRIO SOBRE O LIVRO
    scanf(" %[^\n]", bufferT);
    for (int i = 0; i < *count;i++){
        if (strcasecmp((*lista)[i].title, bufferT) != 0){
            prinf("\nTÍTULO JÁ REGISTRADO!\n");
            return;
        }
    }
    *lista = realloc(*lista, (*count + 1) * sizeof(book));
    if (*lista == NULL){
        printf("FALHA NA ALOCAÇÃO DE MEMÓRIA!");
        exit(1);
    }
    strcpy((*lista)[*count].title, bufferT);
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
    if (*count == 0){
        fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%d\n%d %d %d\n", ++(*count), (*lista)[*count].title, (*lista)[*count].autor.autNAME, (*lista)[*count].autor.country, (*lista)[*count].editora, (*lista)[*count].genre, (*lista)[*count].pCOUNT, (*lista)[*count].data.dia, (*lista)[*count].data.mes, (*lista)[*count].data.ano);
    //LINHA ACIMA REGISTRA AS INFORMAÇÕES NO ARQUIVO LIVROS.TXT
    } else{
         fprintf(file, "%s\n%s\n%s\n%s\n%s\n%d\n%d %d %d\n", (*lista)[*count].title, (*lista)[*count].autor.autNAME, (*lista)[*count].autor.country, (*lista)[*count].editora, (*lista)[*count].genre, (*lista)[*count].pCOUNT, (*lista)[*count].data.dia, (*lista)[*count].data.mes, (*lista)[*count].data.ano);
    //LINHA ACIMA REGISTRA AS INFORMAÇÕES NO ARQUIVO LIVROS.TXT
        (*count)++;
    }
    fclose(file);

    printf("\nRegistro realizado com sucesso!\n");
}
 
int main () {
    int option;
    int counter = 0; //NÚMERO DE LIVROS REGISTRADOS
    int menu = 1;
    book *plivraria; //PONTEIRO USADO COMO VETOR DE STRUCTS DO TIPO book
    plivraria = NULL;
    read_file(plivraria, &counter);


    printf("Olá! Digite a opção que deseja: ");

    printf("1 - Inserir novo registro /n");
    printf("2 - Remover registro existente /n");
    printf("3 - Exibir todos os livros /n");
    printf("4 - Consultar um livro específico /n");
    printf("5 - Sair\n");

    scanf("%d", &option);

    if (option > 5 || option < 1) {
        while (option > 5 || option < 1){ //MANTÉM O LOOP ENQUANTO O USUÁRIO NÃO ESCOLHE OPÇÃO VÁLIDA
            printf("Ops! Escolha uma opção válida do menu:\n");
            scanf("%d", &option);
        }
    }

    while (menu){
        switch (option) {
            case 1: 
                insert_register(plivraria, &counter);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                menu = 0; //INVALIDA A CHECAGEM DO LOOP
                break;
        }
    }
    
    return 0;
}