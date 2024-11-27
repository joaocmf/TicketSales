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

void InserirIngressos(){
    Ingresso i;
    abrirArquivo();
    fwrite(&i, sizeof(ingresso), 1, fpIngresso);
    fecharArquivo();
}

void cadastrarIngreso(){

}


void TelaIngresso(){
    textcolor(YELLOW);
    textbackground(BLUE);
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

    textcolor(WHITE);
    textbackground(BLACK);
}


Ingresso digitarIngresso(){
    Ingresso i;
    char entrada[1000];
    i.show[200];
    i.descricao[200];
    i.valor = 0;
    i.data[11];

    int tecla, atual = 0;

    do{

    }

}




int CriarMenu()
{
    TelaIngresso();

    Ingresso ingressos[100];
    int QtdeIngressos = 0;
    int opcao = 0;
    AbrirIngresso();
    char opcoes[][20] = {"Novo", "Pesquisa","Alterar","Excluir","Listar","Voltar"};
    int x[] = {7,14,25,35,45,54};
    int y[] = {18,18,18,18,18,18};
    int tam[] = {5,9,8,8,7,7};
    Ingresso i;

    do{
        TelaIngresso();
        opcao = Menu(opcoes,x,y,tam,6,opcao);

        if(opcao==0){
            i = ();
            InserirProduto(p);
        }

        if(opcao == 1)
        {
            TelaProduto();
            produtos[QtdeProdutos] = DigitarProduto();
            QtdeProdutos ++;
        }

        else if(opcao == 2)
        {
            printf("Digite o o Show que Deseja procurar: ");
            int Codigo;
            scanf("%d", Codigo);
            PesquisarProduto(Codigo,&p);
        }

        if(opcao==4){
            ListarProdutos();
        }


    }
    while(opcao != 0);
    FecharProduto();

    return opcao;
}






