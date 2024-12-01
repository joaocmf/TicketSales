#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendedor.h"
#include "cliente.h"

int main() {
    char descricao[][60] = { "Seja bem vindo ao nosso sistema de compra de ingressos.", "Selecione uma opcao abaixo:"};
    char opcoes[][20] = { "Cliente (Compra)", "Vendedor", "Sair" };

    int opcao;

    do {
        system("cls");
        opcao = criarMenuPrincipal(3, 2, 80, descricao, opcoes, 3);

        switch(opcao) {
            case 0:
                system("cls");

                system("pause");
                break;
            case 1:
                system("cls");
                CriarMenu();
                system("pause");
                break;
            case 2:
                system("cls");
                printf("FIM DO PROGRAMA\n\n");
                break;
        }
    } while(opcao != 2);
}

int criarMenuPrincipal(int initX, int initY, int tamanho, char desc[][60], char opcoes[][20], int qntd) {
    Borda(initX, initY, tamanho, 25, 1, 0);
    char projetoName[50] = "TicketSales";

    int titlePositionX = calcularTamanhoString(projetoName, tamanho, initX);
    gotoxy(titlePositionX, 4); printf("%s", projetoName);

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

    int opcao = menu(opcoes, posicoes, posicoesY, tamanhos, qntd, 0);

    return opcao;
}

void calcularTamanhoPosicao(int posicoes[20], char strings[][20], int tamanhoBorda, int x, int qntd) {
    for (int i = 0; i < qntd; i++) {
        int stringSize = calcularTamanhoString(strings[i], tamanhoBorda, x);

        posicoes[i] = stringSize;
    }
}

int calcularTamanhoString(char string[], int tamanhoBorda, int x) {
    int tamanhoNome = strlen(string);

    return (tamanhoBorda/2)-2+x-(tamanhoNome/2);
}
