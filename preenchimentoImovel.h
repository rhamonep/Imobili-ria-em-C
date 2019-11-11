#ifndef _PREENCHIMENTO_IMOVEL_H_
#define _PREENCHIMENTO_IMOVEL_H_

#include "leituraVerificacaoAtribuicao.h"
#include "exibicao.h"
#include <stdio.h>

void PreencheTerreno(imovel *atual, int *totalPreenchido);
void PreencheApartamento(imovel *atual, int *totalPreenchido);
void PreencheCasa(imovel *atual, int *totalPreenchido);
void PreencheEndereco(imovel *atual, int *totalPreenchido);
void PreenchePrecoDisponibilidade(imovel *atual, int *totalPreenchido);



void PreencheTerreno(imovel *atual, int *totalPreenchido){

    int erro;
    int preenchidos = 0;
    terreno* ter = &atual->categoria.terreno;

    while(preenchidos <= 1){
        erro = 0;
        LimpaTela();
        ExibeCamposPreenchidos(atual, *totalPreenchido);

        switch(preenchidos){
            case 0: 
                printf("-> Digite o título do anúncio: ");
                atual->titulo = LerEntradaString();
                break;
            case 1:
                printf("-> Digite a área do terreno (m²): ");
                ter->area = LerEntradaFloat();
                if(ter->area == -1){
                    erro = 1;
                }
                break;
        }
        if(erro == 0){
            preenchidos++;
            *totalPreenchido+=1;
        }else{
            ExibeInvalido(VALOR);
            ExibePressioneEnter();
        }
    }
}

void PreencheApartamento(imovel *atual, int *totalPreenchido){

    int erro;
    int preenchidos = 0;
    apartamento *apt = &atual->categoria.apartamento;

    while(preenchidos <= 6){
        erro = 0;
        LimpaTela();
        ExibeCamposPreenchidos(atual, *totalPreenchido);

        switch(preenchidos){
            case 0: 
                printf("-> Digite o título do anúncio: ");
                atual->titulo = LerEntradaString();
                break;
            case 1: 
                printf("-> Digite a posição do apartamento (Ex.: Nascente Norte, Poente Sul): ");
                apt->posicao = LerEntradaString();
                break;
            case 2:
                printf("-> Digite a quantidade de quartos: ");
                apt->quantidadeQuartos = LerEntradaInt();
                if(apt->quantidadeQuartos == -1){
                    erro = 1;
                }
                break;
            case 3:
                printf("-> Quantidade de vagas na garagem: ");
                apt->vagasGaragem = LerEntradaInt();
                if(apt->vagasGaragem == -1){
                    erro = 1;
                }
                break;
            case 4:
                printf("-> Andar do apartamento: ");
                apt->andar = LerEntradaInt();
                if(apt->andar == -1){
                    erro = 1;
                }
                break;
            case 5:
                printf("-> Área do apartamento (m²): ");
                apt->area = LerEntradaFloat();
                if(apt->area == -1){
                    erro = 1;
                }
                break;
            case 6:
                printf("-> Valor do condomínio:  R$");
                apt->valorCondominio = LerEntradaFloat();
                if(apt->valorCondominio == -1){
                    erro = 1;
                }
                break;
        }
        if(erro == 0){
            preenchidos++;
            *totalPreenchido+=1;
        }else{
            ExibeInvalido(VALOR);
            ExibePressioneEnter();
        }
    }
}

void PreencheCasa(imovel *atual, int *totalPreenchido){

    int erro;
    int preenchidos = 0;
    casa *csa = &atual->categoria.casa;

    while(preenchidos <= 4){
        erro = 0;
        LimpaTela();
        ExibeCamposPreenchidos(atual, *totalPreenchido);

        switch(preenchidos){
            case 0: 
                printf("> Digite o título do anúncio: ");
                atual->titulo = LerEntradaString();
                break;
            case 1: 
                printf("> Digite a quantidade de pavimentos: ");
                csa->quantidadePavimentos = LerEntradaInt();
                if(csa->quantidadePavimentos == -1){
                    erro = 1;
                }
                break;
            case 2:
                printf("> Digite a quantidade de quartos: ");
                csa->quantidadeQuartos = LerEntradaInt();
                if(csa->quantidadeQuartos == -1){
                    erro = 1;
                }
                break;
            case 3:
                printf("> Digite a area do terreno (m²): ");
                csa->areaTerreno = LerEntradaFloat();
                if(csa->areaTerreno == -1){
                    erro = 1;
                }
                break;
            case 4:
                printf("> Digite a area construida (m²): ");
                csa->areaConstruida = LerEntradaFloat();
                if(csa->areaConstruida == -1){
                    erro = 1;
                }
                break;
        }

        if(erro == 0){
            preenchidos++;
            *totalPreenchido+=1;
        }
    }
}

void PreencheEndereco(imovel *atual, int *totalPreenchido){

    int erro;
    int preenchidos = 0;
    endereco* end = &atual->endereco;

    while(preenchidos <= 4){
        erro = 0;
        LimpaTela();
        ExibeCamposPreenchidos(atual, *totalPreenchido);

        switch(preenchidos){
            case 0: 
                printf("> Digite a cidade: ");
                end->cidade = LerEntradaString();
                break;
            case 1:
                printf("> Digite o bairro: ");
                end->bairro = LerEntradaString();
                break;
            case 2:
                printf("> Digite o CEP no formato \"00000-000\": ");
                end->cep = LerEntradaString();
                if(VerificaCEP(end->cep) == 0){
                    free(end->cep);
                    erro = 1;
                }
                break;
            case 3:
                printf("> Digite a rua: ");
                end->rua = LerEntradaString();
                break;
            case 4:
                printf("> Digite o numero: ");
                end->numero = LerEntradaInt();
                if(end->numero == -1){
                    erro = 1;
                }
                break;
            default:
                LimpaTela();
                return;
        }

        if(erro == 0){
            preenchidos++;
            *totalPreenchido+=1;
        }else{
            ExibeInvalido(VALOR);
            ExibePressioneEnter();
        }
    }
}

void PreenchePrecoDisponibilidade(imovel *atual, int *totalPreenchido){
    
    int erro;
    int preenchidos = 0;
    int op;

    while(preenchidos <= 1){
        erro = 0;
        LimpaTela();
        ExibeCamposPreenchidos(atual, *totalPreenchido);

        switch(preenchidos){
            case 0:
                printf("-> Venda ou Aluguel? \n");
                printf("\n");
                printf("1- Venda\n");
                printf("2- Aluguel\n");
                printf("\n");
                ExibeSelecione();

                op = LerEntradaInt();

                if(op != 1 && op != 2){
                    erro = 1;
                }

                switch(op){
                    case 1:
                        atual->disponibilidade = VENDA;
                        break;
                    case 2:
                        atual->disponibilidade = ALUGUEL;
                        break;
                }
                break;
            case 1:
                printf("->  Digite o preço:   R$");
                atual->preco = LerEntradaFloat();
                if(atual->preco == -1){
                    erro = 1;
                }
                break;
        }
        if(erro == 0){
            preenchidos++;
            *totalPreenchido+=1;
        }else{
            ExibeInvalido(VALOR);
            ExibePressioneEnter();
        }
    }
}

#endif
