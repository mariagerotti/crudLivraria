//podemos começar o trabalho!
//GRUPO: JOÃO PEDRO DA SILVA, MARIA EDUARDA GEROTTI, MARIAH GARCIA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
        struct author{
            char autNAME[25];
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

// Valida a a data de publicação do livro, para serem apenas valores válidos para o formato [dd-mm-yyyy]
int read_valid_number(const char *msg, int min, int max) {
    int value;
    int success;

    do {
        printf("\n%s", msg);
        success = scanf("%d", &value);
        printf("\n");

        if (success != 1 || value < min || value > max) {
            printf("Entrada inválida! Digite um número entre %d e %d.\n", min, max);
            while (getchar() != '\n');
        }

    } while (success != 1 || value < min || value > max);

    return value;
}

char correct_case(char c){ //TEORICAMENTE, DEVERIA CONVERTER CARACTÉRES ESPECIAIS EM CARACTÉRES SIMPLES E MINÚSCULOS, MAS NÃO FUNCIONA DIREITO. ESTOU DEIXANDO SIMPLESMENTE PARA MOSTRAR QUE TENTAMOS.
    unsigned char ac = (unsigned char)c;

    if (ac == 225 || ac == 224 || ac == 227 || ac == 226 || ac == 228) {return 'a';} // á à ã â ä
    if (ac == 193 || ac == 192 || ac == 195 || ac == 194 || ac == 196) {return 'a';} // Á À Ã Â Ä

    if (ac == 233 || ac == 232 || ac == 234 || ac == 235) {return 'e';} // é è ê ë
    if (ac == 201 || ac == 200 || ac == 202 || ac == 203) {return 'e';} // É È Ê Ë

    if (ac == 237 || ac == 236 || ac == 238 || ac == 239) {return 'i';} // í ì î ï
    if (ac == 205 || ac == 204 || ac == 206 || ac == 207) {return 'i';} // Í Ì Î Ï

    if (ac == 243 || ac == 242 || ac == 244 || ac == 245 || ac == 246) {return 'o';} // ó ò ô õ ö
    if (ac == 211 || ac == 210 || ac == 212 || ac == 213 || ac == 214) {return 'o';} // Ó Ò Ô Õ Ö

    if (ac == 250 || ac == 249 || ac == 251 || ac == 252) {return 'u';} // ú ù û ü
    if (ac == 218 || ac == 217 || ac == 219 || ac == 220) {return 'u';} // Ú Ù Û Ü

    if (ac == 231 || ac == 199) {return 'c';} // ç Ç

    return tolower(ac);
}

void read_file(book **lista, int *count){ //lÊ E CARREGA OS REGISTROS DO ARQUIVOS LIVROS.TXT NO VETOR PLIVRARIA
    int i;
    FILE *file = fopen("livros.txt", "r"); //ABRE O ARQUIVO LIVROS.TXT PARA LEITURA
    if (file == NULL){
        return;
    }
    fscanf(file, "%d", count);//LÊ O NÚMERO DE REGISTROS NO ARQUIVO
    *lista = realloc(*lista, (*count) * sizeof(book));
    for (i = 0; i < *count; i++){
        fscanf(file, " %[^\n]", (*lista)[i].title);
        fscanf(file, " %[^\n]", (*lista)[i].autor.autNAME);
        fscanf(file, " %[^\n]", (*lista)[i].autor.country);
        fscanf(file, " %[^\n]", (*lista)[i].editora);
        fscanf(file, " %[^\n]", (*lista)[i].genre);
        fscanf(file, "%d", &(*lista)[i].pCOUNT);
        fscanf(file, "%d", &(*lista)[i].data.dia);
        fscanf(file, "%d", &(*lista)[i].data.mes);
        fscanf(file, "%d", &(*lista)[i].data.ano); 
    }
    fclose(file);
}

void insert_register(book **lista, int *count){
    int i; int j; int k; int MOVE;
    char bufferC1[30] = {0};//MUDEI //char bufferC2[30];
    char bufferT[30] = {0}; //VARIÁVEL TEMPORÁRIA PARA O TÍTULO
    printf("\nTítulo:\n"); //RECEBE DADOS DO USUÁRIO SOBRE O LIVRO
    scanf(" %[^\n]", bufferT);

    for (j = 0; bufferT[j] != 0; j++){
        bufferC1[j] = correct_case(bufferT[j]);
    }
    bufferC1[j] = 0;
    for (i = 0; i < *count;i++){ //VERIFICA SE O TÍTULO JÁ NÃO EXISTE NO REGISTRO
        char bufferC2[30] = {0};
        for (k = 0; ((*lista)[i].title)[k] != 0; k++){
            bufferC2[k] = correct_case(((*lista)[i].title)[k]);
        }
        bufferC2[k] = 0;
        if (strcmp(bufferC1, bufferC2) == 0){
            printf("\nTÍTULO JÁ REGISTRADO!\n");
            return;
        }
    }
    *lista = realloc(*lista, (*count + 1) * sizeof(book));
    if (*lista == NULL){
        printf("FALHA NA ALOCAÇÃO DE MEMÓRIA!");
        exit(1);
    }
    strcpy((*lista)[*count].title, bufferT); //TRANSFERE O TÍTULO DA VARIÁVEL TEMPORÁRIA PARA SEU LUGAR NA STRUCT
    printf("\nAutor:\n");
    scanf(" %[^\n]", (*lista)[*count].autor.autNAME);
    printf("\nPaís:\n");
    scanf(" %[^\n]", (*lista)[*count].autor.country);
    printf("\nEditora:\n");
    scanf(" %[^\n]", (*lista)[*count].editora);
    printf("\nGênero:\n");
    scanf(" %[^\n]", (*lista)[*count].genre);
    (*lista)[*count].pCOUNT = read_valid_number("Número de páginas:\n", 1, 100000);
    (*lista)[*count].data.dia = read_valid_number("Dia da Publicação:\n", 1, 31);
    (*lista)[*count].data.mes = read_valid_number("Mês da Publicação:\n", 1, 12);
    (*lista)[*count].data.ano = read_valid_number("Ano da Publicação:\n", 500, 2025); 
    // printf("\nNúmero de Páginas:\n");
    // scanf("%d", &(*lista)[*count].pCOUNT);
    // printf("\nDia da Publicação:\n");
    // scanf("%d", &(*lista)[*count].data.dia);
    // printf("\nMês da Publicação:\n");
    // scanf("%d", &(*lista)[*count].data.mes);
    // printf("\nAno da Publicação:\n");
    // scanf("%d", &(*lista)[*count].data.ano);

    FILE *file = fopen("livros.txt", "w"); //CRIA OU ABRE O ARQUIVO LIVROS.TXT EM MODO DE ESCRITA
    if (file == NULL){
        printf("\n ERRO AO ABRIR O ARQUIVO DE REGISTRO\n");
        return;
    }
    for (MOVE = 0; MOVE < (*count+1); MOVE++){
        if (MOVE == 0){
            fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n",
                ((*count)+1),
                (*lista)[MOVE].title,
                (*lista)[MOVE].autor.autNAME,
                (*lista)[MOVE].autor.country,
                (*lista)[MOVE].editora,
                (*lista)[MOVE].genre,
                (*lista)[MOVE].pCOUNT,
                (*lista)[MOVE].data.dia,
                (*lista)[MOVE].data.mes,
                (*lista)[MOVE].data.ano); 
                //LINHA ACIMA ADICIONA O CONTADOR AO TOPO DA LISTA DE REGISTROS E REGISTRA AS INFORMAÇÕES NO ARQUIVO LIVROS.TXT
        } else{
            fprintf(file, "%s\n%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n",
                (*lista)[MOVE].title,
                (*lista)[MOVE].autor.autNAME,
                (*lista)[MOVE].autor.country,
                (*lista)[MOVE].editora,
                (*lista)[MOVE].genre,
                (*lista)[MOVE].pCOUNT,
                (*lista)[MOVE].data.dia,
                (*lista)[MOVE].data.mes,
                (*lista)[MOVE].data.ano);    //LINHA ACIMA REGISTRA AS INFORMAÇÕES NO ARQUIVO LIVROS.TXT
        }
    }
    (*count)++;
    fclose(file);

    printf("\nRegistro realizado com sucesso!\n");
}

void delete_register(book **lista, int *count){ //REMOVE UM REGISTRO DA LISTA
    char removed[30];
    int i; int k;
    //MUDEI
    //int i; int j; int k;
    int check = 1;
    printf("\nInsira o título a ser removido do registro:\n");
    scanf(" %[^\n]", removed);
    for (i = 0; i < *count; i++){ //COMPARA O TÍTULO COM OS TÍTULOS REGISTRADOS
        if (strcasecmp((*lista)[i].title, removed) == 0){
            check = 0;
            break;
        }
    }
    if (check){ //CHECA SE O TÍTULO EXISTE NO REGISTRO
        printf("\nTÍTULO NÃO ENCONTRADO!\n");
        return;
    }
    for (int j = i; j < (*count)-1; j++){//REORGANIZA OS REGISTROS NO VETOR
        (*lista)[j] = (*lista)[j+1];
    }
    (*count)--;
    book *temp = realloc(*lista, (*count) * sizeof(book));//DIMINUI O ESPAÇO ALOCADO PARA O VETOR
    if (temp == NULL && *count > 0) {
        printf("\nERRO AO REALOCAR MEMÓRIA!\n");
        return;
    }
    *lista = temp;
    FILE *file = fopen("livros.txt", "w"); //ABRE O ARQUIVO EM MODO DE ESCRITA, OU SEJA, REINICIA O ARQUIVO
    if(file == NULL){
        printf("\nERRO AO ABRIR O ARQUIVO!\n");
        return;
    }
    for (k = 0; k < *count; k++){
        if (k == 0){
            fprintf(file, "%d\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n",
            (*count),
            (*lista)[k].title,
            (*lista)[k].autor.autNAME,
            (*lista)[k].autor.country,
            (*lista)[k].editora,
            (*lista)[k].genre,
            (*lista)[k].pCOUNT,
            (*lista)[k].data.dia,
            (*lista)[k].data.mes,
            (*lista)[k].data.ano);     //LINHA ACIMA REGISTRA A NOVA LISTA DE TÍTULOS NO ARQUIVO LIVROS.TXT
        } else{
            fprintf(file, "%s\n%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n",
            (*lista)[k].title,
            (*lista)[k].autor.autNAME,
            (*lista)[k].autor.country,
            (*lista)[k].editora,
            (*lista)[k].genre,
            (*lista)[k].pCOUNT,
            (*lista)[k].data.dia,
            (*lista)[k].data.mes,
            (*lista)[k].data.ano);     //LINHA ACIMA REGISTRA A NOVA LISTA DE TÍTULOS NO ARQUIVO LIVROS.TXT
        }
    }
    fclose(file);

    printf("TÍTULO REMOVIDO COM SUCESSO!");
}


void show_single(book **lista, int *count){ //MOSTRA APENAS UM LIVRO REGISTRADO
    char keyT[30];
    int i; int check = 1;

    printf("\nInsira o título do livro a ser consultado:\n");
    scanf(" %[^\n]", keyT);

    for (i = 0; i < *count; i++){ //COMPARA O TÍTULO COM OS TÍTULOS REGISTRADOS
        if (strcasecmp((*lista)[i].title, keyT) == 0){
            check = 0;
            break;
        }
    }

    if (check){ //CHECA SE O TÍTULO EXISTE NO REGISTRO
        printf("\nTÍTULO NÃO ENCONTRADO!\n");
        return;
    }
    //A LINHA ABAIXO IMPRIME AS INFORMAÇÕES DO LIVRO CONSULTADO EM UM BLOCO DE TEXTO ESTRUTURADO
    printf("\n ------------------------------\n Título: %s\n Autor: %s\n Gênero: %s\n Número de Páginas: %d\n Editora: %s\n País: %s\n Data de Lançamento: %02d/%02d/%d\n ------------------------------\n", (*lista)[i].title, (*lista)[i].autor.autNAME, (*lista)[i].genre, (*lista)[i].pCOUNT, (*lista)[i].editora, (*lista)[i].autor.country, (*lista)[i].data.dia, (*lista)[i].data.mes, (*lista)[i].data.ano);
}

void print_list (book **lista, int *count){ //IMPRIME LISTA DE LIVROS COM AS INFORMAÇÕES MARCADAS COM *
    int i;
    printf(" <Número de Livros Cadastrados: %d>\n\n", *count);
    printf(" %-25s %-25s %-20s %-15s\n", "Livro", "Autor", "Nacionalidade", "Data");
    printf(" -----------------------------------------------------------------------------------------\n");
    for (i = 0; i < *count; i++){
        printf(" %-25s %-25s %-20s %02d/%02d/%04d\n", 
            (*lista)[i].title, 
            (*lista)[i].autor.autNAME, 
            (*lista)[i].autor.country,
            (*lista)[i].data.dia,
            (*lista)[i].data.mes,
            (*lista)[i].data.ano);
    }
    printf(" -----------------------------------------------------------------------------------------\n");
}

void load_list(book **lista, int *count){ //CARREGA A LISTA DE TÍTULOS NO ARQUIVO listagem.txt
    int i;
    FILE *listagem = fopen("listagem.txt", "w");
    if (listagem == NULL){
        printf("\n ERRO AO ABRIR O ARQUIVO DE REGISTRO\n");
        return;
    }
    fprintf(listagem, " <Número de Livros Cadastrados: %d>\n\n", *count);
    fprintf(listagem, " %-25s %-25s %-20s %-15s\n", "Livro", "Autor", "Nacionalidade", "Data");
    fprintf(listagem, " -----------------------------------------------------------------------------------------\n");
    for (i = 0; i < *count; i++){
        fprintf(listagem, " %-25s %-25s %-20s %02d/%02d/%04d\n", 
            (*lista)[i].title, 
            (*lista)[i].autor.autNAME, 
            (*lista)[i].autor.country,
            (*lista)[i].data.dia,
            (*lista)[i].data.mes,
            (*lista)[i].data.ano);
    }
    fprintf(listagem, " -----------------------------------------------------------------------------------------\n");
    fclose(listagem);
    printf("\nAo encerrar o programa, a listagem estará disponível no arquivo 'listagem.txt'.\n");
}

void list_books(book **lista, int *count){
    int list;
    if(*count == 0){
        printf("\nNÃO HÁ LIVROS REGISTRADOS!\n");
        //break;
        return;
    }
    printf("\n  ---------------------------------\n");
    printf("  |Olá! Digite a opção que deseja|\n\n");
    printf("  -> 1 - Imprimir listagem em tela.\n");
    printf("  -> 2 - Carregar listagem em documento de texto.\n");
    printf("  ---------------------------------\n");
    scanf(" %d", &list);
     switch (list){
        case 1:
            print_list(lista, count);
            break;
        case 2:
            load_list(lista, count);
            break;
    }
    //MUDEI
    //switch (list){
    //    case 1:
    //        print_list(&plivraria, &counter);
    //        break;
    //    case 2:
    //        load_list(&plivraria, &counter);
    //        break;
    //}
}

int main () {
    int option;
    int counter = 0; //NÚMERO DE LIVROS REGISTRADOS
    int menu = 1;
    book *plivraria; //PONTEIRO USADO COMO VETOR DE STRUCTS DO TIPO book
    plivraria = NULL;
    read_file(&plivraria, &counter);

    while (menu){
        printf("\n  ---------------------------------\n");
        printf("  |Olá! Digite a opção que deseja|\n\n");
        printf("  -> 1 - Inserir novo registro\n");
        printf("  -> 2 - Remover registro existente\n");
        printf("  -> 3 - Exibir todos os livros\n");
        printf("  -> 4 - Consultar um livro específico\n");
        printf("  -> 5 - Sair\n");
        printf("  ---------------------------------\n");

        scanf("%d", &option);

        if (option > 5 || option < 1) {
            while (option > 5 || option < 1){ //MANTÉM O LOOP ENQUANTO O USUÁRIO NÃO ESCOLHE OPÇÃO VÁLIDA
                printf("Ops! Escolha uma opção válida do menu:\n");
                scanf("%d", &option);
            }
        }
        switch (option) {
            case 1: //INSERIR
                insert_register(&plivraria, &counter);
                break;
            case 2: //DELETAR
                delete_register(&plivraria, &counter);
                break;
            case 3: //LISTAR
                list_books(&plivraria, &counter);
                //MUDEI
                //list_book(&plivraria, &counter);
                break;
            case 4: //CONSULTAR
                show_single(&plivraria, &counter);
                break;
            case 5: //SAIR
                free(plivraria);
                printf("PROGRAMA ENCERRADO!");
                menu = 0; //INVALIDA A CHECAGEM DO LOOP
                break;
        }
    }
    
    return 0;
}
