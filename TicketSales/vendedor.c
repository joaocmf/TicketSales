#include <stdio.h>
#include <conio.h>
#include "interface.h"
#include "cliente.h"
#include "vendedor.h"

FILE *fpIngresso;
int quantidade = 0;

void abrirArquivo(){
    fpIngresso = fopen("ingressos.txt", "ab+");
    if(fpIngresso == NULL){
        printf("Nao Abriu ingressos.txt!\n");
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

void TelaIngresso(char titulo[]){
    textColor(WHITE);
    Borda(4,2,60,20,0,1);
    textBackground(GREEN);
    gotoxy(20,3); printf(titulo);
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

    memset(&i, 0, sizeof(Ingresso));

    int tecla, atual = 0;
    int y = 0;

    i.id = quantidade*10;

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
    abrirArquivo();
    system("cls");
    char Dados[100][100];
    int Escolha = 0;
    int j = 0;
    Ingresso i;

    fseek(fpIngresso,0,SEEK_SET);

    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        sprintf(
                Dados[j], "%-5d %-16.16s %-20.20s %7.2lf %18s",
                i.id, i.show, i.descricao, i.valor, i.data
        );
        j++;
    }
    char titulo[20] = "LISTA DE INGRESSOS";
    Borda(2, 4, 77, 18, 1, 0);
    textBackground(GREEN);
    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf(titulo);
    textBackground(BLACK);

    gotoxy(5, 8); printf("%-5s %-16s %-20s %6s %13s", "ID", "Show", "Descricao", "Valor", "Data");
    Lista(Dados, j, 5, 10, 73, 15, Escolha, GREEN);
}

void quantidadeDeIngressos() {
    Ingresso i;
    int j;

    fseek(fpIngresso, 0, SEEK_SET);

    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        j++;
    }

    quantidade = j;
}

void pesquisarIngresso() {
    char Dados[100][100];
    int encontrado = 1;

    system("cls");

    char nomeShow[100];
    char titulo[20] = "PESQUISAR INGRESSOS";

    Borda(2, 4, 87, 18, 1, 0);
    textBackground(GREEN);

    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf(titulo);
    textBackground(BLACK);

    gotoxy(5, 7); printf("Digite o nome do Show: ");
    Borda(27, 6, 19, 2, 0, 0);

    gotoxy(28, 7);
    scanf(" %[^\n]", nomeShow);

    Ingresso i;
    fseek(fpIngresso, 0, SEEK_SET);

    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        if (strstr(i.show, nomeShow) != NULL) {
            int compradores = QuantidadeCompradores(i.id);

            encontrado = 2;
            textBackground(GREEN);
            textColor(BLACK);
            AbrirCliente();

            gotoxy(5, 11); printf("%-5s %-18s %-20s %-9s %-14s %-9s", "ID", "Show", "Descricao", "Valor", "Data", "Compradores");
            textBackground(BLACK);
            textColor(WHITE);
            gotoxy(5, 12); printf("%-5d %-18s %-20s %-9.2lf %-14s %9d", i.id, i.show, i.descricao, i.valor, i.data, compradores);



            textBackground(GREEN);
            gotoxy(57, 20); printf("Lucro Bruto: R$%.2lf", i.vendidos);
            textBackground(BLACK);


            break;
        }

    }
    if(encontrado == 1){
            printf("Show nao encontrado.\n");

        }

    int colors[2] = {WHITE, BLACK};
    PausarInvisivel(5, 21, colors);
}

void alterarIngresso() {
    system("cls");
    int i = 0;
    int idIngresso = 0, encontrado = 0;
    int tecla, campo = 0;
    Ingresso ingressos[100];
    int numIngressos = 0;
    char entrada[100];
    char titulo[20] = "ALTERAR INGRESSO";
    int cores[2] = {WHITE, BLACK};

    char opcoes[][20] = {"SIM", "NAO"};
    int opcao = 3;
    int x[] = {7, 14};
    int y[] = {17, 17};
    int tam[] = {3, 3};
    int colors[2] = {GREEN, BLACK};

    Borda(2, 4, 80, 18, 1, 0);
    textBackground(GREEN);
    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf(titulo);
    textBackground(BLACK);


    gotoxy(5, 8); printf("Digite o ID do ingresso: ");

    double valor = 0;
    int finalizado = 0;

    do{
        if(campo == 0){
            sprintf(entrada, "%d", idIngresso);

            if(idIngresso == 0) entrada[0] = 0;
            tecla = EntradaDados(30, 8, 3, entrada, cores);
            idIngresso = atoi(entrada);

            if(tecla == TEC_ESC){
                break;
            }
        }


        if (idIngresso != 0) {
            if (opcao == 3) {
                fseek(fpIngresso, 0, SEEK_SET);

                while (fread(&ingressos[numIngressos], sizeof(Ingresso), 1, fpIngresso)) {
                    numIngressos++;
                }

                for (i = 0; i < numIngressos; i++) {
                    if (ingressos[i].id == idIngresso) {
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    gotoxy(5, 20); printf("Ingresso com ID %d nao encontrado.\n", idIngresso);

                    PausarInvisivel(5, 25, cores);
                    break;
                }

                LimparArea(4, 19, 70, 2, cores);
                gotoxy(5, 10); printf("Show: %s", ingressos[i].show);
                gotoxy(5, 11); printf("Descricao: %s", ingressos[i].descricao);
                gotoxy(5, 12); printf("Valor: %.2lf", ingressos[i].valor);
                gotoxy(5, 13); printf("Data: %s", ingressos[i].data);
                gotoxy(5, 15); printf("Deseja Editar este ingresso?");

                opcao = 0;
                opcao = menu(opcoes, x, y, tam, 2, opcao, colors);
            }

            valor = ingressos[i].valor;

            if(opcao == 0){
                if(campo == 1){
                    system("cls");
                    TelaIngresso("EDICAO DE INGRESSO");

                    tecla = EntradaDados(19, 6, 40, ingressos[i].show, cores);
                }

                if(campo == 2){
                    tecla = EntradaDados(19, 9, 40, ingressos[i].descricao, cores);
                }

                if (campo == 3) {
                    gotoxy(19, 12); scanf("%lf", &ingressos[i].valor);
                    tecla = TEC_ENTER;
                }

                if(campo == 4){
                    tecla = EntradaDados(19, 15, 11, ingressos[i].data, cores);
                    finalizado = 1;
                }

                if (finalizado == 1){
                    fpIngresso = fopen("ingressos.txt", "wb");
                    fseek(fpIngresso, 0, SEEK_CUR);
                    for (int i = 0; i < numIngressos; i++) {
                        fwrite(&ingressos[i], sizeof(Ingresso), 1, fpIngresso);
                    }
                    fecharArquivo();
                    gotoxy(5, 20); printf("Ingresso editado com sucesso!\n");
                    PausarInvisivel(5, 25, cores);
                    break;
                }
            }

            else if(opcao == 1){
                gotoxy(5, 21); printf("Operacao cancelada!\n");
                PausarInvisivel(5, 25, cores);
                break;
            }
        } else break;

        if (tecla == TEC_BAIXO || tecla == TEC_ENTER) campo++;
        if (tecla == TEC_CIMA) campo--;
        if(campo <= 0 && campo > 1) campo = 0;

        if(opcao == 0){
            if (campo < 1) campo = 1;
            if (campo > 4) campo = 4;
        }
    }while(tecla != TEC_ESC);
}


void excluirIngresso() {
    system("cls");
    int idIngresso, encontrado = 0, opcao = 0;
    Ingresso ingressos[100];
    int numIngressos = 0;
    char titulo[20] = "EXCLUIR INGRESSO";

    Borda(2, 4, 80, 18, 1, 0);
    textBackground(GREEN);
    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf("%s", titulo);
    textBackground(BLACK);

    gotoxy(5, 8); printf("Digite o ID do ingresso: ");
    Borda(30, 7, 5, 2, 0, 0);
    gotoxy(31, 8);
    scanf("%d", &idIngresso);

    fseek(fpIngresso, 0, SEEK_SET);
    while (fread(&ingressos[numIngressos], sizeof(Ingresso), 1, fpIngresso)) {
        numIngressos++;
    }

    for (int z = 0; z < numIngressos; z++) {
        if (ingressos[z].id == idIngresso) {
            encontrado = 1;

            gotoxy(5, 10); printf("Show: %s", ingressos[z].show);
            gotoxy(5, 11); printf("Descricao: %s", ingressos[z].descricao);
            gotoxy(5, 12); printf("Valor: %.2lf", ingressos[z].valor);
            gotoxy(5, 13); printf("Data: %s", ingressos[z].data);

            gotoxy(5, 15); printf("Deseja excluir este ingresso?");
            char opcoes[][20] = {"SIM", "NAO"};
            int x[] = {7, 14};
            int y[] = {17, 17};
            int tam[] = {3, 3};
            int colors[2] = {GREEN, BLACK};

            opcao = menu(opcoes, x, y, tam, 2, opcao, colors);

            if (opcao == 0) {
                for (int j = z; j < numIngressos - 1; j++) {
                    ingressos[j] = ingressos[j + 1];
                }
                numIngressos--;

                FILE *tempFile = fopen("ingressos.txt", "wb");
                if (tempFile == NULL) {
                    gotoxy(5, 17); printf("Erro ao abrir o arquivo para escrita.\n");
                    return;
                }

                fwrite(ingressos, sizeof(Ingresso), numIngressos, tempFile);
                fclose(tempFile);

                textColor(WHITE);
                gotoxy(5, 21); printf("Ingresso excluido com sucesso!");



                int colors[2] = {WHITE, BLACK};
                PausarInvisivel(5, 26, colors);

                return;
            } else if (opcao == 1) {
                gotoxy(5, 22); printf("Operacao cancelada!\n");
                textColor(BLACK);
                int colors[2] = {WHITE, BLACK};
                PausarInvisivel(5, 21, colors);
            }
        }
    }

    if (!encontrado) {
        gotoxy(5, 20); printf("Ingresso com ID %d nao encontrado.\n", idIngresso);
    }

    system("pause");
}





int CriarMenu()
{

    TelaIngresso("CADASTRO DE INGRESSOS");


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
        TelaIngresso("CADASTRO DE INGRESSOS");
        opcao = menu(opcoes,x,y,tam,6,opcao, collors);


        if(opcao==0){
            quantidadeDeIngressos();
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
            alterarIngresso();
        }
        if(opcao == 3){
            excluirIngresso();
        }
        if(opcao == 4){
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






