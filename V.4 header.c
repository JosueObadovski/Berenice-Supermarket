#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdbool.h>

//#ifndef PRODUTO_H_INCLUDED
//#define PRODUTO_H_INCLUDED

typedef struct produto { //struct principal
    int codigo;
    char nomeProduto[26];
    float valor_unitario;
    int estoque;
} item;

void menu(); // cadeia de printf do menu incial
void submenuProdutos(); // cadeia de printf do submenu
void limparTela(); //limpeza de tela systemCLS
void visualizarEstoque (item *padrao, int tamanho); //de visualização de estoque
int cadastrarProduto(item *padrao, int tamanho, int quantidade);// cadastro de produtos
void atualizarProduto (item *padrao, int tamanho);
int excluirProduto (item *padrao, int tamanho);
void reordenaEstoque (item *padrao, int tamanho); //buble sort
void salvarCupom (item *padrao, int tamanho); //Salvar cupom fiscal
void ler(item *padrao, int tamanho);
void subVendas();
void relatorio (item *padrao, int tamanho, int quant_vendas);
void realizarVenda (item *padrao, int tamanho, int quant_vendas);

#endif // HEADER_H_INCLUDED
