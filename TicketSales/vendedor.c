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
    textColor(YELLOW);
    textBackground(BLUE);
    Borda(4,2,60,20,0,1);
    gotoxy(20,3); printf("CADASTRO DE INGRESSOS");
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

    do {
        if (atual == 0) {
            gotoxy(19, 6); printf("Show: ");
            scanf(" %[^\n]", i.show);
        } else if (atual == 1) {
            gotoxy(19, 9); printf("Descrição: ");
            scanf(" %[^\n]", i.descricao);
        } else if (atual == 2) {
            gotoxy(19, 12); printf("Valor: ");
            scanf("%lf", &i.valor);
        } else if (atual == 3) {
            gotoxy(19, 15); printf("Data: ");
            scanf(" %[^\n]", i.data);
        }

        tecla = EntradaDados(19, 6, 5, entrada); // Se existir a função
        if (tecla == TEC_ENTER || tecla == TEC_BAIXO) atual++;
        if (tecla == TEC_CIMA) atual--;
        if (atual < 0) atual = 0;
        if (atual > 3) atual = 3;
    } while (tecla != TEC_ESC);

    return i;
}

void listarIngressos() {
    char Dados[100][100];
    int Escolha = 0;
    int j = 0;
    Ingresso i;

    fseek(fpIngresso,0,SEEK_SET);

    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        sprintf(
                Dados[j], "%4s %-20s %7lf %10s",
                i.show, i.descricao, i.valor, i.data
        );
        j++;
    }

    Borda(4, 4, 60, 7, 1, 1);
    gotoxy(22, 5); printf("Lista de Ingressos");
    gotoxy(5, 6); printf("%-4s %-20s %7s %10s", "Show", "Descricao", "valor", "Data");
    Selecao(Dados, j, 5, 8, 58, 3, Escolha);
}

int pesquisarIngresso(char nomeDoShow[100]) {
    Ingresso i;
    fseek(fpIngresso, 0, SEEK_SET);
    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        if (strcmp(nomeDoShow, i.show) == 0) {
            printf("Show encontrado: %s, Descrição: %s, Valor: %.2lf, Data: %s\n",
                   i.show, i.descricao, i.valor, i.data);
            return 1;
        }
    }
    printf("Show não encontrado.\n");
    return 0;
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
    Ingresso i;

    do{
        TelaIngresso();
        opcao = menu(opcoes,x,y,tam,6,opcao);

        if(opcao==0){
            i = digitarIngresso();
            InserirIngressos(i);
        }

        if(opcao == 1)
        {
            TelaIngresso();
            ingressos[QtdeIngressos] = digitarIngresso();
            QtdeIngressos ++;
        }

        else if(opcao == 2)
        {
            printf("Digite o o Show que procura: ");
            char nomeShow[100];
            scanf(" %[^\n]", nomeShow);
            pesquisarIngresso(nomeShow);
        }

        if(opcao==4){
            listarIngressos();
        }


    }
    while(opcao != 0);
    fecharArquivo();

    return opcao;
}






