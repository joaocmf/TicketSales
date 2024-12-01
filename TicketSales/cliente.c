#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "cliente.h"

FILE *fpCliente;
Cliente clientes[100];

int MenuCliente(opcaoMain) {
    char descricao[][60] = { "Seja bem vindo cliente ao nosso sistema.", "Selecione uma opcao abaixo:"};
    char opcoes[][20] = { "Cadastrar", "Pesquisar Cliente", "Shows", "Voltar" };

    int opcao;

    AbrirCliente();

    do {
        system("cls");
        opcao = criarMenuCliente(3, 2, 80, descricao, opcoes, 4);

        switch(opcao) {
            case 0:
                system("cls");
                registrarCliente();
                break;
            case 1:
                ListarClientes();
                break;
            case 2:
                system("cls");
                system("pause");
                break;
        }
    } while(opcao != 3);

    FecharCliente();

    return opcaoMain;
}

void registrarCliente() {
    telaCadastro(4, 2, 70);
    Cliente c;

    gotoxy(19, 6); scanf(" %[^\n]", c.nome);
    gotoxy(19, 9); scanf("%d", &c.idade);
    gotoxy(19, 12); scanf(" %[^\n]", &c.cpf);

    char sexos[][20] = { "Masculino", "Feminino" };
    int posicoesY[2] = {14, 14};

    int posicoes[2] = { 18, 18+strlen(sexos[0])+27 };
    int tamanhos[2] = { strlen(sexos[0]), strlen(sexos[1]) };

    int colors[] = {BLACK, BLACK};
    int sexo = menu(sexos, posicoes, posicoesY, tamanhos, 2, 0, colors);

    if (sexo == 0) strcpy(c.sexo, "Masculino");;
    if (sexo == 1) strcpy(c.sexo, "Feminino");

    textBackground(RED);
    Borda(18, 14, 44, 2, 0, 0);

    textBackground(BLACK);
    gotoxy(19, 15); printf("%s", c.sexo);

    gotoxy(7, 18);
    system("pause");

    InsirirCliente(c);
}

void telaCadastro(int x, int y, int tamanho) {
    textColor(WHITE);
    textBackground(RED);

    Borda(x, y, tamanho, 20, 0, 1);
    char titulo[50] = "Cadastro de Cliente";

    gotoxy(calcularTamanhoString(titulo, tamanho, x), 3);
    printf(titulo);

    gotoxy(7, 6); printf("Nome:");
    Borda(18, 5, 44, 2, 0, 0);

    gotoxy(7, 9); printf("Idade:");
    Borda(18, 8, 44, 2, 0, 0);

    gotoxy(7, 12); printf("CPF:");
    Borda(18, 11, 44, 2, 0, 0);

    gotoxy(7, 15); printf("Sexo:");

    textColor(WHITE);
    textBackground(BLACK);
}

int criarMenuCliente(int initX, int initY, int tamanho, char desc[][60], char opcoes[][20], int qntd) {
    Borda(initX, initY, tamanho, 25, 1, 0);

    textBackground(RED);
    int titlePositionX = calcularTamanhoString("Cliente", tamanho, initX);
    gotoxy(titlePositionX, 4); printf("%s", "Cliente");
    textBackground(BLACK);

    for (int i = 0; i < 2; i++) {
        int sizeDescription = calcularTamanhoString(desc[i], tamanho, initX);

        gotoxy(sizeDescription, 6+i);
        printf("%s", desc[i]);
    }

    int initialOptionsY = 10;
    int posicoes[qntd];

    int posicoesY[qntd];
    int tamanhos[qntd];

    calcularTamanhoPosicao(posicoes, opcoes, tamanho, initX, qntd);

    for (int j = 0; j < qntd; j++) {
        posicoesY[j] = initialOptionsY+(3*j);
        tamanhos[j] = strlen(opcoes[j]);
    }

    int colors[2] = {RED, BLACK};
    int opcao = menu(opcoes, posicoes, posicoesY, tamanhos, qntd, 0, colors);

    return opcao;
}

void ListarClientes() {
    char Dados[100][100];
    char title[30] = "Lista de Clientes";

    int Escolha = 0;
    int i = 0;

    Cliente c;
    fseek(fpCliente, 0, SEEK_SET);

    while (fread(&c, sizeof(Cliente), 1, fpCliente)) {
        sprintf(
                Dados[i], "%-20s %5d %16s %20s",
                c.nome, c.idade, c.cpf, c.sexo
        );
        i++;
    }

    Borda(6, 4, 73, 20, 1, 1);
    gotoxy(calcularTamanhoString(title, 73, 6), 5); printf(title);

    gotoxy(8, 7); printf("%-20s %5s %16s %20s", "Nome", "Idade", "CPF", "Sexo");
    Selecao(Dados, i, 8, 8, 58, 10, Escolha, RED);
    textBackground(BLACK);
}

void AbrirCliente() {
    fpCliente = fopen("clientes.txt", "ab+");

    if (fpCliente == NULL) {
        printf("Nao foi possivel abrir o arquivo cliente.txt\n");
        exit(1);
    }
}

void FecharCliente() {
    fclose(fpCliente);
}

void InsirirCliente(Cliente c) {
    fseek(fpCliente, 0, SEEK_END);
    fwrite(&c, sizeof(Cliente), 1, fpCliente);
}


