#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

struct ingresso {
    int id;
    char show[100];
    char descricao[300];
    double valor;
    char data[11];
};

typedef struct ingresso Ingresso;

int CriarMenu();
void pesquisarIngresso();
void listarIngressos();
Ingresso digitarIngresso();
void TelaIngresso();
void cadastrarIngreso();
void InserirIngressos();
void fecharArquivo();
void abrirArquivo();

#endif
