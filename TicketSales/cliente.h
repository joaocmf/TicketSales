#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

struct cliente {
    char nome[100];
    int idade;
    char cpf[16];
    char sexo[30];
    int shows[100];
};

typedef struct cliente Cliente;

#endif // CLIENTE_H_INCLUDED
