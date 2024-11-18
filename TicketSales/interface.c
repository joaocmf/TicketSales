#include "interface.h"
#include <windows.h>
#include <conio.h>

int getTecla(){
    int ch;
    ch = getch();
    if(ch == 224){
        ch = getch() + 1000;
    }
    return ch;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x-1;
    coord.Y = y-1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textColor(int iColor) {
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

void textBackground(int iColor) {
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x000F;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
}

void Borda(int x, int y, int largura, int altura, int tipo, int sombra){    // EsqSup DirSup EsqInf DirInf LHoriz LVertical
    char C[][6] = {"\xda\xbf\xc0\xd9\xc4\xb3" ,
                    "\xc9\xbb\xc8\xbc\xcd\xba"};
    int i, j;
    gotoxy(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][1]);
    for(j = 0; j < altura; j++){
        gotoxy(x, y+j+1); printf("%c", C[tipo][5]);
        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][5]);
        if(sombra) printf("\xb2");
    }
    gotoxy(x, y+altura); printf("%c", C[tipo][2]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][3]);
    if(sombra){
        gotoxy(x+1, y+altura+1);
        for(i = 0; i < largura+2; i++) printf("\xb2");
    }
}

int menu(char opcoes[][20], int x[], int y[], int tam[], int qntd, int opcao) {
    int tecla;

    for (int i = 0; i < qntd; i++) {
        Borda(x[i], y[i], tam[i], 2, 0, 0);
        gotoxy(x[i]+1, y[i]+1);
        printf("%s", opcoes[i]);
    }

    do {
        Borda(x[opcao], y[opcao], tam[opcao], 2, 1, 0);
        gotoxy(x[opcao]+1, y[opcao]+1);
        printf("%s", opcoes[opcao]);

        tecla = getTecla();

        if (tecla == TEC_ENTER) break;

        Borda(x[opcao], y[opcao], tam[opcao], 2, 0, 0);
        gotoxy(x[opcao]+1, y[opcao]+1);
        printf("%s", opcoes[opcao]);

        if (tecla == TEC_DIR) opcao++;
        if (tecla == TEC_ESQ) opcao--;
        if (opcao < 0) opcao = qntd-1;
        if (opcao >= qntd) opcao = 0;

    } while(tecla != TEC_ESC);

    return opcao;
}

int Selecao(char Dados[][100], int Qte, int x, int y, int Largura, int Altura, int Escolha) {
    int primeira = 0;
    int tecla;

    do {
        for (int i = primeira; i < Qte && i-primeira < Altura; i++) {
            gotoxy(x, y+i-primeira);
            if (i == Escolha) textBackground(BLUE);
            else textBackground(BLACK);
            printf("%*s", -Largura, Dados[i]);
        }

        tecla = getTecla();

        if (tecla == TEC_ESC) break;
        if (tecla == TEC_BAIXO) Escolha++;
        if (tecla == TEC_CIMA) Escolha--;

        if (Escolha < 0) Escolha=0;
        if (Escolha > Qte-1) Escolha=Qte-1;

        if (primeira > Qte-Altura) primeira = Qte-Altura;
        if (primeira < 0) primeira=0;
    } while(tecla != TEC_ESC);
    textBackground(BLACK);
}
