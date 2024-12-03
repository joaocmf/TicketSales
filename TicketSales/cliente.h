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

void AbrirCliente();
void FecharCliente();
Cliente capturarDadosCliente();
void registrarCliente();
void editarCliente(int posicao);
void ListarClientes(int escolha);
void ExcluirCliente(int posicao);
void InserirCliente(Cliente c);
void telaCadastro(int x, int y, int tamanho);
int criarMenuCliente(int initX, int initY, int tamanho, char desc[][60], char opcoes[][20], int qntd);
void ListarShows();
void FecharIngresso();
void AbrirIngresso();

#endif // CLIENTE_H_INCLUDED
