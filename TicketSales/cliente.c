#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "cliente.h"
#include "vendedor.h"

FILE *fpCliente;
FILE *fpIngresso;

Cliente clientes[100];

int MenuCliente(opcaoMain) {
    char descricao[][60] = { "Seja bem vindo cliente ao nosso sistema.", "Selecione uma opcao abaixo:"};
    char opcoes[][20] = { "Cadastrar", "Pesquisar Cliente", "Listar Shows", "Voltar" };

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
                ListarClientes(0);
                break;
            case 2:
                AbrirIngresso();
                ListarShows();
                FecharIngresso();
                break;
        }
    } while(opcao != 3);

    FecharCliente();

    return opcaoMain;
}

void registrarCliente() {
    char entrada[100];

    int tecla;
    int campo = 0;

    telaCadastro(4, 2, 70);
    Cliente c;

    char sexos[][20] = { "Masculino", "Feminino" };
    int posicoesY[2] = {14, 14};

    int posicoes[2] = { 18, 18+strlen(sexos[0])+27 };
    int tamanhos[2] = { strlen(sexos[0]), strlen(sexos[1]) };

    int colors[] = {RED, RED};
    int corEspaco[] = { WHITE, LIGHT_RED };

    char questions[][20] = {"Nao", "Sim"};
    int posQuestion[2] = {18, 26};

    int posYQuestion[2] = {17, 17};
    int tamanhosQuestion[2] = {strlen(questions[0]), strlen(questions[1])};
    int sexo, continuar;

    c.nome[0] = 0;
    c.idade = 0;
    c.cpf[0] = 0;

    do {
        switch(campo) {
            case 0:
                tecla = EntradaDados(19, 6, 44, c.nome, corEspaco);
                break;
            case 1:
                sprintf(entrada, "%d", c.idade);
                if (c.idade == 0) entrada[0] = 0;

                tecla = EntradaDados(19, 9, 3, entrada, corEspaco);
                c.idade = atoi(entrada);
                break;
            case 2:
                tecla = EntradaDados(19, 12, 14, c.cpf, corEspaco);
                break;
            case 3:
                sexo = menu(sexos, posicoes, posicoesY, tamanhos, 2, 0, colors);

                if (sexo == 0) strcpy(c.sexo, "Masculino");;
                if (sexo == 1) strcpy(c.sexo, "Feminino");

                textBackground(RED);
                Borda(18, 14, 44, 2, 0, 0);

                textBackground(LIGHT_RED);
                gotoxy(19, 15); printf("%s", c.sexo);

                tecla = TEC_BAIXO;
                break;
            case 4:
                gotoxy(7, 18); printf("Editar?");

                continuar = menu(questions, posQuestion, posYQuestion, tamanhosQuestion, 2, 0, colors);

                if (continuar == 0) {
                    InserirCliente(c);
                    tecla = TEC_ESC;
                } else if (continuar == 1) {
                    tecla = TEC_CIMA;
                    campo = 3;
                }
                break;
        }

        if (tecla == TEC_BAIXO || tecla == TEC_ENTER) campo++;
        if (tecla == TEC_CIMA) campo--;

        if (campo < 0) campo = 0;
        if (campo > 4) campo = 4;
        } while(tecla != TEC_ESC);

        textBackground(BLACK);
}

void telaCadastro(int x, int y, int tamanho) {
    textColor(WHITE);
    textBackground(RED);

    Borda(x, y, tamanho, 20, 0, 1);
    char titulo[50] = "Cadastro de Cliente";

    gotoxy(calcularTamanhoString(titulo, tamanho, x), 3);
    printf(titulo);

    gotoxy(x+3, y+4); printf("Nome:");
    Borda(x+14, y+3, 44, 2, 0, 0);

    gotoxy(x+3, y+7); printf("Idade:");
    Borda(x+14, y+6, 44, 2, 0, 0);

    gotoxy(x+3, y+10); printf("CPF:");
    Borda(x+14, y+9, 44, 2, 0, 0);

    gotoxy(x+3, y+13); printf("Sexo:");

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

void ListarClientes(int escolha) {
    char Dados[100][100];
    char title[30] = "Lista de Clientes";

    int Escolha = escolha;
    int i = 0;

    Cliente c;
    fseek(fpCliente, 0, SEEK_SET);

    while (fread(&c, sizeof(Cliente), 1, fpCliente)) {
        int quantidadeDeShows = 0;

        for (int s = 0; c.shows[s] == 0; s++) {
            quantidadeDeShows++;
        }

        sprintf(
                Dados[i], "%-25.25s %5d %16s %12s %7d",
                c.nome, c.idade, c.cpf, c.sexo, quantidadeDeShows
        );
        i++;
    }

    Borda(6, 4, 73, 20, 1, 1);
    gotoxy(calcularTamanhoString(title, 73, 6), 5); printf(title);

    gotoxy(8, 7); printf("%-25s %5s %16s %12s %7s", "Nome", "Idade", "CPF", "Sexo", "Shows");

    int selecionado = Selecao(Dados, i, 8, 8, 58, 10, Escolha, RED);

    if (selecionado >= 0) {
        int cores[] = { RED, BLACK };

        char opcoes[][20] = { "Editar", "Apagar", "Voltar" };
        int qtdOpcao = 3;

        int posicaoX[qtdOpcao];
        int posicaoY[qtdOpcao];

        int tamanhos[qtdOpcao];
        int initialY = 10;

        for (int j = 0; j < qtdOpcao; j++) {
            tamanhos[j] = strlen(opcoes[j]);
            posicaoX[j] = initialY;
            posicaoY[j] = 20;

            initialY+= tamanhos[j]+5;
        }

        int opcao = menu(opcoes, posicaoX, posicaoY, tamanhos, qtdOpcao, 0, cores);

        switch(opcao) {
            case 0:
                EditarCliente(selecionado);
            break;
            case 1:
                ExcluirCliente(selecionado);
            break;
            case 2:
                ListarClientes(selecionado);
            break;
        }
    }

    textBackground(BLACK);
}

void EditarCliente(int posicao) {
    Cliente clientes[100];

    int numClientes = 0;
    char entrada[100];

    int tecla;
    int campo = 0;

    telaCadastro(6, 4, 73);
    fseek(fpCliente, 0, SEEK_SET);

    while (fread(&clientes[numClientes], sizeof(Cliente), 1, fpCliente)) {
        numClientes++;
    }

    char sexos[][20] = { "Masculino", "Feminino" };
    int posicoesY[2] = {16, 16};

    int posicoes[2] = { 20, 20+strlen(sexos[0])+27 };
    int tamanhos[2] = { strlen(sexos[0]), strlen(sexos[1]) };

    int colors[] = {RED, RED};
    int corEspaco[] = { WHITE, LIGHT_RED };

    char questions[][20] = {"Nao", "Sim"};
    int posQuestion[2] = {20, 28};

    int posYQuestion[2] = {19, 19};
    int tamanhosQuestion[2] = {strlen(questions[0]), strlen(questions[1])};

    int sexo, continuar;

    do {
        switch(campo) {
            case 0:
                tecla = EntradaDados(21, 8, 44, clientes[posicao].nome, corEspaco);
                break;
            case 1:
                sprintf(entrada, "%d", clientes[posicao].idade);
                if (clientes[posicao].idade == 0) entrada[0] = 0;

                tecla = EntradaDados(21, 11, 3, entrada, corEspaco);
                clientes[posicao].idade = atoi(entrada);
                break;
            case 2:
                tecla = EntradaDados(21, 14, 14, clientes[posicao].cpf, corEspaco);
                break;
            case 3:
                sexo = menu(sexos, posicoes, posicoesY, tamanhos, 2, 0, colors);

                if (sexo == 0) strcpy(clientes[posicao].sexo, "Masculino");;
                if (sexo == 1) strcpy(clientes[posicao].sexo, "Feminino");

                textBackground(RED);
                Borda(20, 16, 44, 2, 0, 0);

                textBackground(LIGHT_RED);
                gotoxy(21, 17); printf("%s", clientes[posicao].sexo);

                tecla = TEC_BAIXO;
                break;
            case 4:
                gotoxy(9, 20); printf("Editar?");

                continuar = menu(questions, posQuestion, posYQuestion, tamanhosQuestion, 2, 0, colors);

                if (continuar == 0) {
                    freopen("clientes.txt", "wb", fpCliente);

                    for (int i = 0; i < numClientes; i++) {
                        fwrite(&clientes[i], sizeof(Cliente), 1, fpCliente);
                    }

                    tecla = TEC_ESC;

                    FecharCliente();
                    AbrirCliente();

                    textBackground(BLACK);
                    //system("cls");
                    ListarClientes(posicao);
                } else if (continuar == 1) {
                    tecla = TEC_CIMA;
                    campo = 3;
                }
                break;
        }

        if (tecla == TEC_BAIXO || tecla == TEC_ENTER) campo++;
        if (tecla == TEC_CIMA) campo--;

        if (campo < 0) campo = 0;
        if (campo > 4) campo = 4;
    } while(tecla != TEC_ESC);

    textBackground(BLACK);
}

void ExcluirCliente(int posicao) {
    Cliente clientes[100];
    int numClientes = 0;

    fseek(fpCliente, 0, SEEK_SET);

    while (fread(&clientes[numClientes], sizeof(Cliente), 1, fpCliente)) {
        numClientes++;
    }

    for (int i = posicao; i < numClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }

    numClientes--;
    freopen("clientes.txt", "wb", fpCliente);

    for (int i = 0; i < numClientes; i++) {
        fwrite(&clientes[i], sizeof(Cliente), 1, fpCliente);
    }

    FecharCliente();
    AbrirCliente();
    ListarClientes(0);
}

void ListarShows() {
    char Dados[100][100];
    char title[30] = "Shows Disponiveis";

    int Escolha = 0;
    int j = 0;

    Ingresso i;
    Cliente c;

    fseek(fpIngresso, 0, SEEK_SET);

    while (fread(&i, sizeof(Ingresso), 1, fpIngresso)) {
        sprintf(
                Dados[j], "%-5d %-16.16s %-20.20s %7.2lf %18s",
                i.id, i.show, i.descricao, i.valor, i.data
        );
        j++;
    }

    Borda(6, 4, 73, 20, 1, 1);
    gotoxy(calcularTamanhoString(title, 73, 6), 5); printf(title);

    gotoxy(8, 7); printf("%-5s %-16s %-20s %6s %13s", "ID", "Show", "Descricao", "Valor", "Data");
    Selecao(Dados, j, 8, 8, 58, 10, Escolha, RED);
    textBackground(BLACK);
}

void AbrirCliente() {
    fpCliente = fopen("clientes.txt", "ab+");

    if (fpCliente == NULL) {
        printf("Nao foi possivel abrir o arquivo cliente.txt\n");
        exit(1);
    }
}

void AbrirIngresso(){
    fpIngresso = fopen("ingressos.txt", "rb+");
    if (fpIngresso == NULL){
        printf("Nao Abriu ingressos.txt!\n");
        exit(1);
    }
}

void FecharIngresso() {
    fclose(fpIngresso);
}

void FecharCliente() {
    fclose(fpCliente);
}

void InserirCliente(Cliente c) {
    fseek(fpCliente, 0, SEEK_END);
    fwrite(&c, sizeof(Cliente), 1, fpCliente);
}
