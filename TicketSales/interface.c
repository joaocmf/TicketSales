#include "interface.h"
#include <windows.h>
#include "vendedor.h"
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

int menu(char opcoes[][20], int x[], int y[], int tam[], int qntd, int opcao, int colors[2]) {
    int tecla;

    textBackground(colors[1]);
    for (int i = 0; i < qntd; i++) {
        Borda(x[i], y[i], tam[i], 2, 0, 0);
        gotoxy(x[i]+1, y[i]+1);
        printf("%s", opcoes[i]);
    }

    do {
        textBackground(colors[0]);
        Borda(x[opcao], y[opcao], tam[opcao], 2, 1, 0);
        gotoxy(x[opcao]+1, y[opcao]+1);
        printf("%s", opcoes[opcao]);
        textBackground(colors[1]);

        tecla = getTecla();

        if (tecla == TEC_ESC) opcao = qntd-1;
        if (tecla == TEC_ENTER) break;

        Borda(x[opcao], y[opcao], tam[opcao], 2, 0, 0);
        gotoxy(x[opcao]+1, y[opcao]+1);
        printf("%s", opcoes[opcao]);

        if (tecla == TEC_DIR || tecla == TEC_BAIXO) opcao++;
        if (tecla == TEC_ESQ || tecla == TEC_CIMA) opcao--;
        if (opcao < 0) opcao = qntd-1;
        if (opcao >= qntd) opcao = 0;

    } while(tecla != TEC_ESC);

    return opcao;
}


int Lista(char Dados[][100], int Qte, int x, int y, int Largura, int Altura, int Escolha, int color) {
    int primeira = 0;
    int tecla;

    do {
        for (int i = primeira; i < Qte && i-primeira < Altura; i++) {
            gotoxy(x, y+i-primeira);
            if (i == Escolha) textBackground(color);
            else textBackground(BLACK);
            printf("%*s", -Largura, Dados[i]);
        }

        tecla = getTecla();

        if (tecla == TEC_ESC) break;
        if (tecla == TEC_BAIXO) Escolha++;
        if (tecla == TEC_CIMA) Escolha--;

        if (Escolha < 0) Escolha=0;
        if (Escolha > Qte-1) Escolha=Qte-1;

        if (Escolha > Altura-primeira-1) primeira++;
        if (Escolha < primeira) primeira = Escolha;

        if (primeira > Qte-Altura) primeira = Qte-Altura;
        if (primeira < 0) primeira=0;
    } while(tecla != TEC_ESC);
    textBackground(BLACK);
    return -1;
}


int Selecao(char Dados[][100], int Qte, int x, int y, int Largura, int Altura, int Escolha, int color) {
    int primeira = 0;
    int tecla;

    do {
        for (int i = primeira; i < Qte && i-primeira < Altura; i++) {
            gotoxy(x, y+i-primeira);
            if (i == Escolha) textBackground(color);
            else textBackground(BLACK);
            printf("%*s", -Largura, Dados[i]);
        }

        tecla = getTecla();

        if (tecla == TEC_BAIXO) Escolha++;
        if (tecla == TEC_CIMA) Escolha--;

        if (Escolha < 0) Escolha=0;
        if (Escolha > Qte-1) Escolha=Qte-1;

        if (Escolha > Altura-primeira-1) primeira++;
        if (Escolha < primeira) primeira = Escolha;

        if (primeira > Qte-Altura) primeira = Qte-Altura;
        if (primeira < 0) primeira=0;

        if (tecla == TEC_ENTER) break;
        if (tecla == TEC_ESC) Escolha = -1;
    } while(tecla != TEC_ESC);
    textBackground(BLACK);
    return Escolha;
}

int EntradaInserindo = 1;

void tipocursor(int cursor){
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    BOOL result;
    CURSOR.dwSize = 1;
    if(cursor == 0)
    CURSOR.bVisible = FALSE;
    else
    CURSOR.bVisible = TRUE;
    result=SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

void textcoloreback (int letras, int fundo){/*para mudar a cor de fundo mude o background*/
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letras + (fundo << 4));
}

int EntradaDados(int x, int y, int Tamanho, char Texto[], int cor[2]) {
    int Tecla, Pos;
    char aux[10000];

    gotoxy(x, y);
    textcoloreback(cor[0], cor[1]);

    printf("%*s", Tamanho, " ");
    gotoxy(x, y);

    printf("%s", Texto);
    Pos = strlen(Texto);

    gotoxy(67, 0);

    do {
        gotoxy(Pos + x, y);
        Tecla = getTecla();

        if(Tecla == TEC_ENTER) break;
        if(Tecla == TEC_ESQ) Pos--;
        if(Tecla == TEC_DIR) Pos++;
        if(Tecla == TEC_CIMA) break;
        if(Tecla == TEC_BAIXO) break;
        if(Tecla == TEC_ESC) break;

        if(Tecla == TEC_BACKSPACE && Pos > 0){
            Pos--;
            strcpy(&Texto[Pos], &Texto[Pos+1]);
            printf("\x08%s ", &Texto[Pos]);
        }

        if(Tecla == TEC_DEL && Pos >= 0 && Texto[Pos] != 0){
            //Pos--;
            strcpy(&Texto[Pos], &Texto[Pos+1]);
            printf("%s ", &Texto[Pos]);
        }

        if(Tecla >= ' ' && Tecla < 127) {
            if(Pos < Tamanho){
                if(EntradaInserindo){
                    // Inserir
                    if (strlen(Texto) < Tamanho){
                        if(Texto[Pos] == 0) Texto[Pos+1] = 0;

                        strcpy(aux, Texto);
                        strcpy(&Texto[Pos+1], &aux[Pos]);
                        Texto[Pos++] = Tecla;

                        printf("%s", &Texto[Pos-1]);
                    }
                }

                // Sobrescreve
                else{
                    if (Texto[Pos] == 0) Texto[Pos+1] = 0;

                    Texto[Pos++] = Tecla;
                    printf("%c", Tecla);
                }
            }
        }

        if(Pos < 0) Pos = 0;
        if(Pos > Tamanho) Pos = Tamanho;
        if(Pos > 0 && Texto[Pos-1] == 0) Pos--;
    } while(1);

    textcoloreback(WHITE, BLACK);
    gotoxy(67, 0);

    return Tecla;
}
