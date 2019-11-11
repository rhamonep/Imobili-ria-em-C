#ifndef _MENU_H_
#define _MENU_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "registroImoveis.h"
#include "exibicao.h"
#include "operacoesImovel.h"
#include "leituraVerificacaoAtribuicao.h"
#include "enumeracoes.h"
#include "listaImovel.h"

void MenuPrincipal(arrayImovel* imoveis);
int MenuBuscar3(arrayImovel *imoveis);
void SubMenuBuscar2(arrayImovel* imoveis, buscaID buscaID, char* titulo, int tipo);
void MenuBuscar2(arrayImovel* imoveis, buscaID buscaID);
void MenuBuscar1(arrayImovel* imoveis);
void MenuExibeImoveis(arrayImovel* imoveis, bool subMenu);
void MenuCadastroImovel(arrayImovel* imoveis);
void MenuEdicao(arrayImovel* imoveis, int posicao);
void MenuEditarOuRemover(arrayImovel* imoveis, operacaoID op);



void MenuPrincipal(arrayImovel* imoveis){

    int op;

    do{
        LimpaTela();
        ExibeTituloCentro("MENU PRINCIPAL");
        printf("\n");
        printf("1- Cadastrar imóvel.\n");
        printf("2- Exibir imóveis.\n");
        printf("3- Buscar imóvel.\n");
        printf("4- Imóveis para vender.\n");
        printf("5- Imóveis para alugar.\n");
        printf("6- Remover imóvel.\n");
        printf("7- Editar imóvel\n");
        printf("\n");
        printf("0- Sair.\n");
        printf("\n");
        ExibeSelecione();

        op = LerEntradaInt();

        switch (op){
            case 1:
                MenuCadastroImovel(imoveis);
                break;
            case 2:
                MenuExibeImoveis(imoveis, true);
                break;
            case 3:
                MenuBuscar1(imoveis);
                break;
            case 4:
                MenuBuscar2(imoveis, VENDENDO);
                break;
            case 5:
                MenuBuscar2(imoveis, ALUGANDO);
                break;
            case 6:
                MenuEditarOuRemover(imoveis, REMOVER);
                break;
            case 7:
                MenuEditarOuRemover(imoveis, EDITAR);
                break;
            case 0:
                break;
            default:
                ExibeInvalido(OPCAO);
                ExibePressioneEnter();
        }
    }while(op!=0);
}

int MenuBuscar3(arrayImovel *imoveis){
    int op;
    printf("OPÇÕES: \n");
    printf("\n");
    printf("1- Nova busca.\n");
    printf("2- Remover imóvel.\n");
    printf("3- Editar imóvel.\n");
    printf("\n");
    printf("0- Voltar\n");
    printf("\n");
    ExibeSelecione();

    op = LerEntradaInt();

    switch(op){
        case 1:
            MenuBuscar1(imoveis);
            return 1;
        case 2:
            MenuEditarOuRemover(imoveis, REMOVER);
            return 1;
        case 3:
            MenuEditarOuRemover(imoveis, EDITAR);
            return 1;
        case 0:     
            return 1;
            break;
        default:
            ExibeInvalido(OPCAO);
            ExibePressioneEnter();
    }
    return 0;
}

void SubMenuBuscar2(arrayImovel* imoveis, buscaID buscaID, char* titulo, int tipo){
    int op;
    int erro;
    do{
        LimpaTela();
        erro = 0;
        switch(tipo){
            case VENDENDO:
                ExibeTituloCentro(titulo);
                printf("\n");     
                printf("1- Apartamentos à venda.\n");
                printf("2- Casas à venda.\n");
                printf("3- Terrenos à venda.\n"); 
                printf("\n");
                break;
            case ALUGANDO:
                ExibeTituloCentro(titulo);
                printf("\n");     
                printf("1- Apartamentos para alugar.\n");
                printf("2- Casas para alugar.\n");
                printf("3- Terrenos para alugar.\n"); 
                printf("\n");  
                break;
            case PRECO:
                ExibeTituloCentro(titulo);
                printf("\n");     
                printf("1- Buscar preço MAIOR ou IGUAL a um valor.\n");
                printf("2- Buscar preço MENOR ou IGUAL a um valor.\n");
                printf("3- Buscar preço IGUAL a um valor.\n");
                printf("\n");
                break;
        }
        printf("0- Voltar"); 
        printf("\n");
        printf("\n");
        ExibeSelecione();
        op = LerEntradaInt(); 

        if(op != 0 && op != 1 && op != 2 && op != 3){
            erro = 1;      
        }
        
        if(op != 0){
            if(erro == 0){
                LimpaTela();
                ExibeTituloCentro(titulo);
                printf("\n");
                printf("\n");
                if(tipo == PRECO){
                    printf("Digite o preço a ser buscado:   R$");
                }
                BuscarImovel(imoveis, buscaID, titulo, op);
                return;
            }else{
                ExibeInvalido(VALOR);
                ExibePressioneEnter();
            }  
        }
    }while(op!=0);
}

void MenuBuscar2(arrayImovel* imoveis, buscaID buscaID){

    int erro = 0;
    char* titulo;

    LimpaTela();

    switch(buscaID){
        case TITULO:

            titulo = "BUSCAR IMÓVEIS POR ANÚNCIO";
            ExibeTituloCentro(titulo);
            printf("\n");
            printf("Digite o anúncio a ser buscado:   ");
            BuscarImovel(imoveis, buscaID, titulo, 0);
            break;

        case BAIRRO:
        
            titulo = "BUSCAR IMÓVEIS POR BAIRRO";
            ExibeTituloCentro(titulo);
            printf("\n");
            printf("Digite o bairro a ser buscado:   ");
            BuscarImovel(imoveis, buscaID, titulo, 0);
            break;

        case PRECO:

            titulo = "BUSCAR IMÓVEIS POR PREÇO";
            SubMenuBuscar2(imoveis, buscaID, titulo, PRECO);       
            break;

        case VENDENDO:

            titulo = "IMÓVEIS À VENDA";
            SubMenuBuscar2(imoveis, buscaID, titulo, VENDENDO);
            break;

        case ALUGANDO:

            titulo = "IMÓVEIS PARA ALUGAR";
            SubMenuBuscar2(imoveis, buscaID, titulo, ALUGANDO);
            break;
    }
    return;
}

void MenuBuscar1(arrayImovel* imoveis){
    int op;
        do{
        LimpaTela();
        ExibeTituloCentro("BUSCAR IMÓVEIS");
        printf("\n");
        printf("1- Buscar por anúncio.\n");
        printf("2- Buscar por bairro.\n");
        printf("3- Buscar por preço.\n");
        printf("\n");
        printf("0- Voltar\n");
        printf("\n");
        ExibeSelecione();

        op = LerEntradaInt();

        switch(op){
            case 1:
                MenuBuscar2(imoveis, TITULO);
                return;
            case 2:
                MenuBuscar2(imoveis, BAIRRO);
                return;
            case 3:
                MenuBuscar2(imoveis, PRECO);
                return;
            case 0:     
                break;
            default:
                ExibeInvalido(VALOR);
                ExibePressioneEnter();
        }
    }while(op!=0);
}

void MenuExibeImoveis(arrayImovel* imoveis, bool subMenu){
    int sair;
    int totalApt;
    int totalCasas;
    int totalTerrenos;
    do{
        totalApt = 0;
        totalCasas = 0;
        totalTerrenos = 0;
        ContarImovel(imoveis, &totalApt, &totalCasas, &totalTerrenos);

        int total = totalApt + totalCasas + totalTerrenos;
        LimpaTela();
        ExibeTituloCentro("IMÓVEIS");
        printf("\n");
        printf("Total de imóveis cadastrados : %d\n", total);
        printf("\n");
        printf(" -> %d Casas\n", totalCasas);
        printf(" -> %d Apartamentos\n", totalApt);
        printf(" -> %d Terrenos\n", totalTerrenos);
        printf("\n");
        ExibeTituloCentro("--------");
        printf("\n");
        printf("\n");
        ExibeImoveis(imoveis);
        if(subMenu == true){
            sair = MenuBuscar3(imoveis);
        }
    }while(sair==0);
}

void MenuCadastroImovel(arrayImovel* imoveis){

    int op;
    
    do{
        LimpaTela();
        ExibeTituloCentro("CADASTRO DE IMÓVEIS");
        printf("\n");
        printf("Escolha o tipo de imóvel: \n");
        printf("\n");
        printf("1- Casa\n");
        printf("2- Apartamento\n");
        printf("3- Terreno\n");
        printf("\n");
        printf("0- Voltar\n");
        printf("\n");
        ExibeSelecione();

        op = LerEntradaInt();

        switch(op){           
            case 1:
                CadastrarImovel(imoveis, CASA);
                return;
            case 2:
                CadastrarImovel(imoveis, APARTAMENTO);
                return;
            case 3:
                CadastrarImovel(imoveis, TERRENO);
                return;
            case 0:
                break;   
            default:
                ExibeInvalido(VALOR);
                ExibePressioneEnter();        
        }
    }while(op!=0);
}

void MenuEdicao(arrayImovel* imoveis, int posicao){

    int indice;
    int op;
    do{
        indice = 0;
        LimpaTela();
        ExibeTituloCentro("MENU DE EDIÇÃO DE IMÓVEIS");
        printf("\n");
        printf("\n");
        ExibeImovel(imoveis->array[posicao-1]);
        printf("\n");
        printf("Escolha qual campo deseja editar: ");
        printf("\n");
        printf("\n");
        printf("%d- Anúncio\n", ++indice);
        switch(imoveis->array[posicao-1]->id){
                case CASA:
                    printf("%d- Quantidade de quartos\n", ++indice);
                    printf("%d- Quantidade pavimentos\n", ++indice);
                    printf("%d- Área Construida (m²)\n", ++indice);
                    printf("%d- Área do terreno (m²)\n", ++indice);
                    break;
                case APARTAMENTO:
                    printf("%d- Posição do apartamento\n", ++indice);
                    printf("%d- Quantidade de quartos\n", ++indice); 
                    printf("%d- Vagas na garagem\n", ++indice); 
                    printf("%d- Andar do apartamento\n", ++indice);
                    printf("%d- Área do apartamento (m²)\n", ++indice); 
                    printf("%d- Valor do condomínio\n", ++indice); 
                    break;
                case TERRENO:
                    printf("%d- Área do terreno (m²)\n", ++indice);
        }

                    printf("%d- Cidade\n", ++indice);
                    printf("%d- Bairro\n", ++indice);
                    printf("%d- CEP\n", ++indice);
                    printf("%d- Rua\n", ++indice);
                    printf("%d- Nº\n", ++indice);
                    printf("%d- Venda ou Aluga\n", ++indice);
                    printf("%d- Preço\n", ++indice);
                    printf("\n");
                    printf("0- Voltar");
                    printf("\n");
                    printf("\n");
                    ExibeSelecione();

                    op = LerEntradaInt();

                    if(op == -1 || op > indice){
                        ExibeInvalido(VALOR);
                        ExibePressioneEnter();
                    }else{
                        EditarImovel(imoveis->array[posicao-1], op);
                    }
                    
    }while(op!=0);
}

void MenuEditarOuRemover(arrayImovel* imoveis, operacaoID op){

    int entrada;
    int erro;

    do{
        LimpaTela();
        MenuExibeImoveis(imoveis, false);
        erro = 0;
        switch(op){
            case REMOVER:
                printf("-> Digite o número do imóvel a ser removido (0 para cancelar): ");
                entrada = LerEntradaInt();

                if(entrada == -1){
                    erro = 2;
                }else if(VerificarPosicaoListaImovel(imoveis, entrada) == 1){
                    RemoverListaImovel(imoveis, entrada-1);
                }else{
                    erro = 1;
                }
                    
                if(erro == 0){
                    ExibeSucesso(REMOCAO);
                    ExibePressioneEnter();
                    return;
                }else if(erro == 1 && entrada != 0){
                    ExibeInvalido(IMOVEL);    
                    ExibePressioneEnter();
                }
                break;
            case EDITAR:
                printf("-> Digite o número do imóvel a ser editado: (0 para cancelar): ");
                entrada = LerEntradaInt();

                if(entrada == -1){
                    erro = 2;
                }else if(VerificarPosicaoListaImovel(imoveis, entrada) == 1){
                    MenuEdicao(imoveis, entrada);
                    return;
                }else{
                    erro = 1;
                
                }if(erro == 1 && entrada != 0){
                    ExibeInvalido(IMOVEL);    
                    ExibePressioneEnter();
                }
                break;
        }

        if(erro == 2){
            ExibeInvalido(OPCAO);    
            ExibePressioneEnter();
        }
    }while(entrada != 0);
}

#endif
