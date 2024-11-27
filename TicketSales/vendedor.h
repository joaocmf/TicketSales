#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

struct ingresso{
    char show[100];
    char descricao[300];
    double valor;
    char data[11];
};

typedef struct ingresso Ingresso;


#endif // VENDEDOR_H_INCLUDED
