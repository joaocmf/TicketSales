#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#define TEC_ENTER 13
#define TEC_TAB 9
#define TEC_BACKSPACE 8
#define TEC_ESC 27
#define TEC_DIR 1077
#define TEC_ESQ 1075
#define TEC_BAIXO 1080
#define TEC_CIMA 1072
#define TEC_DEL 1083
#define TEC_END 1079
#define TEC_INSERT 1082
#define TEC_HOME 1071
#define TEC_PAGE_UP 1073
#define TEC_PAGE_DOWN 1081

void gotoxy(int x, int y);
void textColor(int icolor);
void textBackground(int icolor);
void Borda(int x, int y, int largura, int altura, int tipo, int sombra);
int Selecao(char Dados[][100], int Qte, int x, int y, int Largura, int Altura, int Escolha);

enum DOS_COLORS {
       BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
       LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
       LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE };

#endif // INTERFACE_H_INCLUDED
