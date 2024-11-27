#include <stdio.h>
#include <stdlib.h>

int main() {
    char descricao[][60] = { "Seja bem vindo ao nosso sistema de compra de ingressos.", "Selecione uma opcao abaixo:"};
    char opcoes[][20] = { "1- Cliente (Compra)", "2- Vendedor" };

    criarMenuPrincipal(3, 2, 80, descricao, opcoes);
}

void criarMenuPrincipal(int initX, int initY, int tamanho, char desc[][60], char opcoes[][20]) {
    Borda(initX, initY, tamanho, 25, 1, 0);
    char projetoName[50] = "TicketSales";

    int titlePositionX = calcularTamanhoString(projetoName, tamanho, initX);
    printf("%d", titlePositionX);

    gotoxy(titlePositionX, 4); printf("%s", projetoName);

    for (int i = 0; i < 2; i++) {
        int sizeDescription = calcularTamanhoString(desc[i], tamanho, initX);

        gotoxy(sizeDescription, 6+i);
        printf("%s", desc[i]);
    }

    int posicoes[2];

    calcularTamanhoPosicao(posicoes, opcoes, tamanho, initX, 2);

    int posicoesY[2] = {15, 19};
    int tamanhos[2] = {strlen(opcoes[0]), strlen(opcoes[1])};

    int opcao = menu(opcoes, posicoes, posicoesY, tamanhos, 2, 0);
}

void calcularTamanhoPosicao(int posicoes[2], char strings[][20], int tamanhoBorda, int x, int qntd) {
    for (int i = 0; i > qntd; i++) {
        int stringSize = calcularTamanhoString(strings[i]);

    }
}

int calcularTamanhoString(char string[], int tamanhoBorda, int x) {
    int tamanhoNome = strlen(string);

    return (tamanhoBorda/2)-2+x-(tamanhoNome/2);
}
