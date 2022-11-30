#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "header.h"

//funções para o menu principal

void menu() { //cadeia de printf
    printf("\n\t\t\t\t--------Bem vindo ao Mercadinho da Berenice!--------");
    printf("\n\t\t\t\tOpcao(1) - Produtos");
    printf("\n\t\t\t\tOpcao(2) - Vendas");
    printf("\n\t\t\t\tOpcao(3) - Sair");
    printf("\n");
}

void submenuProdutos() {
    printf("\n\t\t\t\t--------Produtos--------\n");
    printf("\n\t\t\t\tOpcao(1) - Exibir");
    printf("\n\t\t\t\tOpcao(2) - Cadastrar");
    printf("\n\t\t\t\tOpcao(3) - Atualizar");
    printf("\n\t\t\t\tOpcao(4) - Excluir");
    printf("\n\t\t\t\tOpcao(5) - Salvar");
    printf("\n\t\t\t\tOpcao(6) - Ler");
    printf("\n\t\t\t\tOpcao(0) - Voltar");
    printf("\n");
}

void subVendas() {
    printf("\n\t\t\t\t--------SubMenu de Vendas--------\n");
    printf("\n\t\t\t\tOpcao(1) - Realizar Venda");
    printf("\n\t\t\t\tOpcao(2) - Relatorio de Vendas");
    printf("\n\t\t\t\tOpcao(0) - Voltar");
    printf("\n");
}

void limparTela() {
    system("cls");
}

void visualizarEstoque (item *padrao, int tamanho) {
    printf("|  \tCodigo\t  |  \tValor\t  |  \tEstoque\t  |  \tNome\t  |\n--------------------------------------------------------------------\n");
    for(int i=0; i<tamanho; i++) { //loop para exibir todos os produtos disponiveis no estoque
        printf("|  \t%d\t  |  \t%.2f\t  |  \t%d\t  |  \t%s\t\n", padrao[i].codigo, padrao[i].valor_unitario, padrao[i].estoque,padrao[i].nomeProduto);
    }
    printf("\n\Linha: %i", tamanho);
}

int cadastrarProduto(item *padrao, int tamanho, int quantidade) {
    int pn=0, i=0, j=0;
    int codigo_aux=0;

    for(j=0; j<quantidade; j++) {
        if(tamanho==0) {
            padrao[tamanho].codigo = 1; //validação do inicio
        } else {
            padrao[tamanho].codigo = padrao[tamanho-1].codigo + 1; //reordena se ha um salto entre duas posições, se houver, insere uma posição entre elas
            for(int i=0; i<tamanho; i++) {
                if(padrao[i+1].codigo==padrao[i].codigo+1) {
                    continue;
                }
                padrao[tamanho].codigo = i+2;
                break;
            }
        }

        printf("Digite o codigo do produto desejado: \n");
        do {
            scanf("%i", &padrao[tamanho].codigo);
            codigo_aux = padrao[tamanho].codigo;
            for(i=0; i<tamanho; i++) {
                if(padrao[i].codigo==codigo_aux) {
                    printf("\nEste código já existe!\n");
                    padrao[tamanho].codigo=0;
                }
            }
            if(padrao[tamanho].codigo<=0) {
                printf("Tente novamente com um codigo inexistente!");
            }
        } while(padrao[tamanho].codigo<=0);

        printf("\tInsira o nome do produto: \n");
        setbuf(stdin, NULL); //limpa leitura de entrada padrão do teclado
        gets(padrao[tamanho].nomeProduto);

        printf("\tInsira o preco: \n");
        do {
            scanf("%f", &padrao[tamanho].valor_unitario);
            if(padrao[tamanho].valor_unitario<=0) {
                printf("Valor invalido!\n");
            }
        } while(padrao[tamanho].valor_unitario<=0);
        getchar();

        printf("\tInsira a quantidade para o estoque: \n");
        do {
            scanf("%d", &padrao[tamanho].estoque);
            getchar();
            if(padrao[tamanho].estoque<=0) {
                printf("Valor invalido!\n");
            }
        } while(padrao[tamanho].estoque<=0);
        tamanho++; //aumento no tamanho do estoque
    }
    reordena_estoque(padrao, tamanho); //bubble sort
    return tamanho;
}

void atualizarProduto (item *padrao, int tamanho) {
    int i, j, erro=0;
    int produto, opcao, etq_antes;
    float pri_antes;
    char nm_antes[26];
    visualizarEstoque(padrao, tamanho);
    printf("\nDigite o codigo desejado para atualizar\n== ");
    scanf("%i", &produto);
    getchar();
    system("cls");
    printf("|  \tCodigo\t  |  \tValor\t  |  \tEstoque\t  |  \tNome\t  |\n--------------------------------------------------------------------\n");

    for(i=0; i<tamanho; i++) {
        printf("|  \t%d\t  |  \t%.2f\t  |  \t%d\t  |  \t%s\t\n", padrao[i].codigo, padrao[i].valor_unitario, padrao[i].estoque,padrao[i].nomeProduto);
    }

    for(i=0; i<tamanho; i++) {
        if(padrao[i].codigo==produto) { //compara todas as posicoes com as do usuario
            limparTela();
            printf("|  \tCodigo\t  |  \tValor\t  |  \tEstoque\t  |  \tNome\t  |\n--------------------------------------------------------------------\n");
            printf("|  \t%d\t  |  \t%.2f\t  |  \t%d\t  |  \t%s\t\n", padrao[i].codigo, padrao[i].valor_unitario, padrao[i].estoque,padrao[i].nomeProduto); //printf com o i do usuario
            printf("\n\nO que deseja alterar?\n----> "
                   "\n\t1 - Nome do Produto"
                   "\n\t2 - Preco"
                   "\n\t3 - Estoque"
                   "\n\t0 - Voltar"
                   "\n\t--->: ");
            scanf("%i", &opcao);
            getchar();
            system("cls");
            strcpy(nm_antes,padrao[i].nomeProduto);
            pri_antes = padrao[i].valor_unitario;
            etq_antes = padrao[i].estoque;
            switch(opcao) {
            case 1:
                printf("Insira o novo nome do produto: ");
                setbuf(stdin, NULL); //limpa leitura de entrada padrão do teclado
                gets(padrao[i].nomeProduto);
                break;
            case 2:
                printf("Insira o novo preco do produto: ");
                scanf("%f", &padrao[i].valor_unitario);
                getchar();
                if(padrao[i].valor_unitario<=0) {
                    printf("'\nDigite um valor valido!");
                    padrao[i].valor_unitario=pri_antes;
                    erro++;
                }
                break;
            case 3:
                printf("Insira o novo estoque do produto: ");
                scanf("%d", &padrao[i].estoque);
                getchar();
                if(padrao[i].estoque<=0) {
                    printf("'\nDigite um valor valido!");
                    padrao[i].estoque=pri_antes;
                    erro++;
                }
                break;
            default:
                break;
            }
            if(erro<=0) {
                printf("\nAntes:\n");
                printf("|  \tCodigo\t  |  \tValor\t  |  \tEstoque\t  |  \tNome\t  |\n--------------------------------------------------------------------\n");
                printf("|  \t%d\t  |  \t%.2f\t  |  \t%d\t  |  \t%s\t\n", padrao[i].codigo, pri_antes, etq_antes,nm_antes); //printf com o i do usuario
                printf("\nDepois:\n");
                printf("|  \tCodigo\t  |  \tValor\t  |  \tEstoque\t  |  \tNome\t  |\n--------------------------------------------------------------------\n");
                printf("|  \t%d\t  |  \t%.2f\t  |  \t%d\t  |  \t%s\t\n", padrao[i].codigo, padrao[i].valor_unitario, padrao[i].estoque,padrao[i].nomeProduto); //printf com o i do usuario
                printf("\n\nDeseja alterar?\n( 0 ) - Nao\n( 1 ) - Sim\n--->");
                scanf("%i",&opcao);
            }
            if(opcao == 0) {
                strcpy(padrao[i].nomeProduto,nm_antes);
                padrao[i].valor_unitario=pri_antes;
                padrao[i].estoque = etq_antes;
                printf("\nAlteracoes desfeitas...");
            }
        } else {
            printf("Produto nao encontrado");
        }
    }
}

int excluir_produto(item *padrao, int tamanho) {
    int i,tam_aux,opcao=0;
    int produto;
    visualizarEstoque(padrao, tamanho);
    printf("\nDigite o código do item que deseja excluir: ");
    scanf("%d", &produto);
    getchar();
    limparTela();
    tam_aux = tamanho;

    printf("|  \tCodigo\t  |  \tValor\t  |  \tEstoque\t  |  \tNome\t  |\n--------------------------------------------------------------------\n");
    for(i=0; i<tamanho; i++) {
        if(padrao[i].codigo == produto) {
            printf("|  \t%d\t  |  \t%.2f\t  |  \t%d\t  |  \t%s\t\n", padrao[i].codigo, padrao[i].valor_unitario, padrao[i].estoque,padrao[i].nomeProduto); //printf com o i do usuario
            printf("\nDeseja excluir?\n( 0 ) - Nao\n( 1 ) - Sim");
            scanf("%i",&opcao);
        }
    }

    if(opcao == 1) {
        for(i=0; i<tamanho; i++) {
            if(padrao[i].codigo==produto) {
                for(; i<tamanho-1; i++) {
                    padrao[i] =padrao[i+1];
                }
                tamanho--;
            }
        }
    }

    if(tam_aux == tamanho && opcao == 100) {
        printf("\n\t\tProduto nao encontrado");
    }

    return tamanho;
}

void reordena_estoque(item *padrao, int tamanho) { //bubble sort
    for(int i=0; i<tamanho-1; i++) {
        for(int j=i+1; j<tamanho; j++) {
            if(padrao[i].codigo>padrao[j].codigo) {
                item aux = padrao[i];
                padrao[i] = padrao[j];
                padrao[j] = aux;
            }
        }
    }
}

void realizar_venda(item *padrao, int tamanho,int quant_vendas) {
    int produto, i,quantidade,opc,parcelas;
    float total,total_vet[tamanho],total_parc,rcbd,troco; //total_vet usado para somar todos as posicoes e ter valor final
    char opcao1='c';
    do {
        visualizarEstoque(padrao, tamanho);
        printf("\nDigite o Codigo desejado\n---->");
        do {
            scanf("%d", &produto);
            getchar();
            for(i=0; i<tamanho; i++) {
                padrao[i].codigo;
                if(padrao[i].codigo == produto) {
                    break;
                } else {
                    printf("Digite um Codigo valido!\n----> ");
                }
            }

        } while(padrao[i].codigo != produto);
        limparTela();
        printf("Qual a quantidade? \n");
        scanf("%d",&quantidade);
        do {
            if(quantidade <= 0 || quantidade >padrao[i].estoque) {
                limparTela();
                printf("Quantidade invalida ou Estoque insuficiente!\nDigite 999 para sair da venda\n---->");
                scanf("%d",&quantidade);
            }
            if(quantidade==999) {
                break;
            }
        } while(quantidade <= 0 || quantidade >padrao[i].estoque);

        if(quantidade!=999) {
            padrao[i].estoque = padrao[i].estoque - quantidade; //subtrair estoque pela quantiddade desejada
            total_vet[i] = quantidade*padrao[i].valor_unitario; //multiplicar totais/quant por posicoes
        }
        printf("%i", padrao[i].estoque);

        printf("Deseja continuar vendendo?\n");
        printf("( 0 ) - Nao\n( 1 ) - Sim");
        scanf("%d",&opcao1);

    } while(opcao1 != 0); //fim loop


    for(i=0; i<tamanho; i++) {
        total += total_vet[i]; //somar totais
    }
    printf("\n\tO valor total foi de R$%.2f (Sem desconto) \n\n",total);

    printf("Forma de Pagamento\n");
    printf("( 1 ) - A vista\n( 2 ) - Parcelado");

    scanf("%d",&opcao1);//forma de pagamento desejada pelo cliente
    switch(opcao1) {

    case 1:// Opcao de pagamento a vista
        if(total<=50) { //5% Desconto
            total*=0.95;
        } else if(total>50 && total<100) { //10% Desconto
            total*=0.90;
        } else if(total>=100) { //18% Desconto
            total*=0.82;
        }
        do {
            printf("\t\tTotal com Desconto: %.2f\n\n",total);
            printf("\nDigite o dinheiro recebido:\n");
            scanf("%f", &rcbd);
            getchar();

            if(rcbd<total) {
                printf("Valor do troco Invalido,Falta R$ %.2f\n", -rcbd+total);
            }
        } while(rcbd<total);
        troco=-total+rcbd;
        printf("\t\tTotal com desconto: %.2f\n", total);
        printf("\t\tTroco comm desconto: %.2f\n\n", troco);
        printf("\n\tClique Enter para continuar...");
        getchar();
        break;

    case 2://opcao parcelada
        do {
            printf("\tQual a quantidade de parcelas? ");
            scanf("%d",&parcelas);

            if(parcelas<1) {
                system("cls");
                printf("\n\tNúmero de parcelas inválido, digite um valor acima de 1.\n");
            }
        } while(parcelas <1);
        if(parcelas<=3) { //5% Juros aplicado ao valor da compra
            total*=1.05;
            total_parc = total/parcelas;
        } else if (parcelas>3) { //8% Juros aplicado ao valor da compra
            total*=1.08;
            total_parc = total/parcelas;
        }
        printf("\n\t|------------------NOTA-------------------|\n\n");

        printf("\t|O valor a prazo (%d meses) ficou: R$%.2f\n",parcelas,total);
        printf("\t|O valor total das parcelas ficou: R$%.2f\n\n",total_parc);
        printf("\t|-----------------------------------------|\n\n\n");
        printf("\n\tDigite ( 0 ) para voltar...");
        scanf("%d",&opc);
    }
}

void salvar_base(item *padrao, int tamanho) { //CUPOM FISCAL
    char filename[40];

    struct tm *timenow; //usado para pegar tempo atual

    time_t now = time(NULL);
    timenow = gmtime(&now);

    strftime(filename, sizeof(filename), "%Y-%m-%d_%H-%M-%S.txt", timenow); //adicionando nomenclatura e tamanho

    FILE *fp = fopen(filename, "w"); //abrindo arquito para escrita

    if(fp == NULL) {
        printf("Erro ao abrir o arquivo %s", filename);
        exit(1);
    }

    fprintf(fp, "Quantidade de Vendas\n");
    fprintf(fp, "%d\n", tamanho);
    for(int i = 0; i < tamanho; i++) { //usado para printar
        fprintf(fp, "\nItem: %d", padrao[i]);
    }

    fclose(fp);
    printf("\t\tSalvamento com sucesso! Clique Enter para Continuar");
    getchar();
    limparTela();
}

void ler(item *base, int tam) {
    char filename[40];
    char str[50];

    FILE *fp;

    fp = fopen("base.txt", "r"); //ler arquivo

    if(fp == NULL) {
        printf("Erro ao abrir o arquivo %s", filename);
        exit(1);
    }
    while(fgets(str, 50, fp) != NULL) {
        printf("\t\t%s", str);
    }
    fclose(fp );
    printf("\n\t\t\tLeitura da base com sucesso! \n\t\t\tClique Enter para continuar...");
    getchar();
}
void salvar(item *padrao, int tamanho) {
    char filename[40];
    int qt_venda=0;

    FILE *fp = fopen("base.txt", "w");//String
    FILE *fp_bi = fopen("base.bin", "wb");//BINARIO

    if(fp == NULL || fp_bi == NULL) {
        printf("Erro ao abrir o arquivo %s", filename);
        exit(1);
    }

    fprintf(fp, "\n%d",tamanho);
    fprintf(fp_bi, "\n%d",tamanho);
    for(int i = 0; i < tamanho; i++) {
        //String
        fprintf(fp, "\n%d", padrao[i].codigo);
        fprintf(fp, "\n%s", padrao[i].nomeProduto);
        fprintf(fp, "\n%.2f", padrao[i].valor_unitario);
        fprintf(fp, "\n%d", padrao[i].estoque);
        //BINARIO
        fwrite(padrao,sizeof(padrao),tamanho,fp_bi);
    }

    fclose(fp);//fechar arquivo de string
    fclose(fp_bi);//fechar arquivo binario
    printf("\t\tSalvamento com sucesso! Clique Enter para Continuar");
    getchar();
    limparTela();
}

void relatorio(item *padrao, int tamanho, int quant_vendas) {
    printf("\n\t\t\t------------------------------\n");
    for(int i=0; i<tamanho; i++) {
        printf("\t\t\t%d\n",quant_vendas);
        printf("\t\t\t%d\n",padrao[i].codigo);
        printf("\t\t\t%s\n",padrao[i].nomeProduto);
        printf("\t\t\t%.2f\n",padrao[i].valor_unitario);
        printf("\t\t\t%d\n",padrao[i].estoque);
    }
}
