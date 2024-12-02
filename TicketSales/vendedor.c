#include <stdio.h>
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

    i.id = quantidade*100;

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
    int compradores = 4000;
    Cliente c;
    int encontrado = 1;
    system("cls");
    char nomeShow[100];
    char titulo[20] = "PESQUISAR INGRESSOS";
    Borda(2, 4, 93, 18, 1, 0);

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
            AbrirCliente();

            gotoxy(5, 11); printf("%-5s %-18s %-20s %-13s %-17s %-9s", "ID", "Show", "Descricao", "Valor", "Data", "Compradores");
            textBackground(BLACK);
            textColor(WHITE);
            gotoxy(5, 12); printf("%-5d %-18s %-20s %-13.2lf %-17s %-9d", i.id, i.show, i.descricao, i.valor, i.data, c.shows);



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

void alterarIngresso() {
    system("cls");
    int idIngresso, encontrado = 0;
    Ingresso ingressos[100];
    int numIngressos = 0;
    char titulo[20] = "ALTERAR INGRESSO";

    Borda(2, 4, 80, 18, 1, 0);
    textBackground(GREEN);
    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf(titulo);
    textBackground(BLACK);


    gotoxy(5, 8); printf("Digite o ID do ingresso: ");
    scanf("%d", &idIngresso);


    fseek(fpIngresso, 0, SEEK_SET);
    while (fread(&ingressos[numIngressos], sizeof(Ingresso), 1, fpIngresso)) {
        numIngressos++;
    }


    for (int i = 0; i < numIngressos; i++) {
        if (ingressos[i].id == idIngresso) {
            encontrado = 1;


            gotoxy(5, 10); printf("Show: %s", ingressos[i].show);
            gotoxy(5, 11); printf("Descricao: %s", ingressos[i].descricao);
            gotoxy(5, 12); printf("Valor: %.2lf", ingressos[i].valor);
            gotoxy(5, 13); printf("Data: %s", ingressos[i].data);


            gotoxy(5, 15); printf("Digite o novo nome do show: ");
            scanf(" %[^\n]", ingressos[i].show);
            gotoxy(5, 16); printf("Digite a nova descricao: ");
            scanf(" %[^\n]", ingressos[i].descricao);
            gotoxy(5, 17); printf("Digite o novo valor: ");
            scanf("%lf", &ingressos[i].valor);
            gotoxy(5, 18); printf("Digite a nova data: ");
            scanf(" %[^\n]", ingressos[i].data);

            break;
        }
    }

    if (!encontrado) {
        gotoxy(5, 20); printf("Ingresso com ID %d nao encontrado.\n", idIngresso);
    } else {


        fpIngresso = fopen("ingressos.txt", "wb");
        fseek(fpIngresso, 0, SEEK_CUR);
        for (int i = 0; i < numIngressos; i++) {
            fwrite(&ingressos[i], sizeof(Ingresso), 1, fpIngresso);
        }
        fecharArquivo();
        gotoxy(5, 20); printf("Ingresso editado com sucesso!\n");
    }


}


void excluirIngresso(){
    system("cls");
    int idIngresso, encontrado = 0;
    Ingresso ingressos[100];
    int numIngressos = 0;
    char titulo[20] = "EXCLUIR INGRESSO";

    Borda(2, 4, 80, 18, 1, 0);
    textBackground(GREEN);
    gotoxy(calcularTamanhoString(titulo, 77, 2), 5); printf(titulo);
    textBackground(BLACK);


    gotoxy(5, 8); printf("Digite o ID do ingresso: ");
    scanf("%d", &idIngresso);


    fseek(fpIngresso, 0, SEEK_SET);
    while (fread(&ingressos[numIngressos], sizeof(Ingresso), 1, fpIngresso)) {
        numIngressos++;
    }


    for (int i = 0; i < numIngressos; i++) {
        if (ingressos[i].id == idIngresso) {
            encontrado = 1;


            gotoxy(5, 10); printf("Show: %s", ingressos[i].show);
            gotoxy(5, 11); printf("Descricao: %s", ingressos[i].descricao);
            gotoxy(5, 12); printf("Valor: %.2lf", ingressos[i].valor);
            gotoxy(5, 13); printf("Data: %s", ingressos[i].data);


            gotoxy(5, 15); printf("Deseja Excluir esse ingresso? (1 - Sim / 0 - Nao): ");
            int opcao;
            scanf("%d", &opcao);

            if (opcao == 1) {
                // Deslocar todos os ingressos após o excluído para preencher o espaço
                for (int j = i; j < numIngressos - 1; j++) {
                    ingressos[j] = ingressos[j + 1];  // Copiar os ingressos para "remover" o escolhido
                }

                numIngressos--;


                abrirArquivo();
                fseek(fpIngresso, 0, SEEK_SET);
                for (int j = 0; j < numIngressos; j++) {
                    fwrite(&ingressos[j], sizeof(Ingresso), 1, fpIngresso);  // Regravar todos os ingressos restantes
                }
                fecharArquivo();  // Fechar o arquivo

                gotoxy(5, 17); printf("Ingresso excluido com sucesso!\n");
            } else {
                gotoxy(5, 17); printf("Operacao cancelada.\n");
            }

            break;
        }
    }

    if (!encontrado) {
        gotoxy(5, 20); printf("Ingresso com ID %d nao encontrado.\n", idIngresso);
    }

    system("pause");
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






