#include <stdio.h>
#include "interface.h"
#include "cliente.h"
#include "vendedor.h"

FILE *fpIngresso;
void abrirArquivo(){
    fpIngresso = fopen("Ingressos.txt", "ab+");
    if(fpIngresso == NULL){
        printf("Nao Abriu Ingressos.txt!\n");
        exit(1);
    }
}

void fecharArquivo(){
    fclose(fpIngresso);
}

void InserirIngressos(Ingresso i) {
    abrirArquivo();
    fwrite(&i, sizeof(Ingresso), 1, fpIngresso);
    fecharArquivo();
}

void TelaIngresso(){
    textColor(WHITE);
    Borda(4,2,60,20,0,1);
    textBackground(GREEN);
    gotoxy(20,3); printf("CADASTRO DE INGRESSOS");
    textBackground(BLACK);
    gotoxy(7,6); printf("SHOW:");
    Borda(18,5,40,2,0,0);
    gotoxy(7,9); printf("DESCRICAO:");
    Borda(18,8,40,2,0,0);
    gotoxy(7,12); printf("VALOR:");
    Borda(18,11,40,2,0,0);
    gotoxy(7,15); printf("DATA:");
    Borda(18,14,40,2,0,0);
    gotoxy(40,2);

    textColor(WHITE);
    textBackground(BLACK);
}


Ingresso digitarIngresso() {
    Ingresso i;
    char entrada[1000] = {0};
    int tecla, atual = 0;
    int y = 0;

    do {
            y = 6;
            gotoxy(19, y);
            scanf(" %[^\n]", i.show);

            y = 9;
            gotoxy(19, y);
            scanf(" %[^\n]", i.descricao);

            y = 12;
            gotoxy(19, y);
            scanf("%lf", &i.valor);

            y = 15;
            gotoxy(19, y);
            scanf(" %[^\n]", i.data);

     system("cls");

     return i;

    } while (tecla != TEC_ESC);


    return i;
}

void listarIngressos() {
    system("cls");
    char Dados[100][100];
    int Escolha = 0;
    int j = 0;
    Ingresso i;

    fseek(fpIngresso,0,SEEK_SET);

    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        sprintf(
                Dados[j], "%-20s %-25s %7.2lf %18s",
                i.show, i.descricao, i.valor, i.data
        );
        j++;
    }
    char titulo[20] = "LISTA DE INGRESSOS";
    Borda(2, 4, 77, 18, 1, 0);
    textBackground(GREEN);
    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf(titulo);
    textBackground(BLACK);

    gotoxy(5, 8); printf("%-20s %-25s %7s %12s", "Show", "Descricao", "valor", "Data");
    Selecao(Dados, j, 5, 10, 73, 15, Escolha, GREEN);
}

void pesquisarIngresso() {

    int compradores = 4000;
    Cliente c;
    int encontrado = 1;
    system("cls");
    char nomeShow[100];
    char titulo[20] = "PESQUISAR INGRESSOS";
    Borda(2, 4, 80, 18, 1, 0);
    textBackground(GREEN);
    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf(titulo);
    textBackground(BLACK);

    gotoxy(5, 8); printf("Digite o nome do Show: ");
    scanf(" %[^\n]", nomeShow);



    Ingresso i;
    fseek(fpIngresso, 0, SEEK_SET);
    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        if (strcmp(nomeShow, i.show) == 0) {
            encontrado = 2;
            textBackground(GREEN);
            textColor(BLACK);
            gotoxy(5, 10); printf("%-12s %-15s %-9s %-11s %19s", "Show", "Descricao", "valor", "Data", "Compradores");
            textBackground(BLACK);
            textColor(WHITE);
            gotoxy(5, 12); printf("%-12s %-15s %-9.2lf %-11s %19d", i.show, i.descricao, i.valor, i.data, compradores);



            /*textBackground(GREEN);
            gotoxy(57, 20); printf("Total de compradores: %d", compradores);

            */
            break;

        }

    }
    if(encontrado == 1){
            printf("Show nao encontrado.\n");

        }

    textColor(BLACK);
    tipocursor(0);
    system("pause");
    tipocursor(1);
    textColor(WHITE);
}


int CriarMenu()
{

    TelaIngresso();


    Ingresso ingressos[100];
    int QtdeIngressos = 0;
    int opcao = 0;
    abrirArquivo();
    char opcoes[][20] = {"Novo", "Pesquisa","Alterar","Excluir","Listar","Voltar"};
    int x[] = {7,14,25,35,45,54};
    int y[] = {18,18,18,18,18,18};
    int tam[] = {5,9,8,8,7,7};
    int collors[2] = {GREEN, BLACK};
    Ingresso i;


    do{
        system("cls");
        TelaIngresso();
        opcao = menu(opcoes,x,y,tam,6,opcao, collors);


        if(opcao==0){
            i = digitarIngresso();
            InserirIngressos(i);
            CriarMenu();
        }

        if(opcao == 1)
        {
            pesquisarIngresso();
        }

        if(opcao == 2)
        {

        }


        if(opcao==4){
            listarIngressos();
        }
        if(opcao == 5){
            break;
        }
    }
    while(opcao != 0);

    fecharArquivo();

    return opcao;
}






