#ifndef _OPERACOES_IMOVEL_H_
#define _OPERACOES_IMOVEL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "registroImoveis.h"
#include "exibicao.h"
#include "preenchimentoImovel.h"
#include "leituraVerificacaoAtribuicao.h"

void ContarImovel(arrayImovel *imoveis, int* totalApt, int* totalCasas, int* totalTerrenos);
void CadastrarImovel(arrayImovel* imoveis, imovelID ID);
void EditarImovel(imovel *atual, int op);
void BuscarImovel(arrayImovel* imoveis, buscaID id, char* titulo, int op);



void ContarImovel(arrayImovel *imoveis, int* totalApt, int* totalCasas, int* totalTerrenos){

    for(int i = 0; i < imoveis->indice; i++){

        switch(imoveis->array[i]->id){
            case CASA:
                *totalCasas+=1;
                break;
            case APARTAMENTO:
                *totalApt+=1;
                break;
            case TERRENO:
                *totalTerrenos+=1;
                break;
        }       
    }
}

void CadastrarImovel(arrayImovel* imoveis, imovelID ID){
    
    int preenchidos = 0;
    imovel atual;

    atual.id = ID;

    switch(ID){
        case CASA:
            PreencheCasa(&atual, &preenchidos);
            break;
        case APARTAMENTO:
            PreencheApartamento(&atual, &preenchidos);
            break;
        case TERRENO:
            PreencheTerreno(&atual, &preenchidos);
            break;
        default:
            printf("Erro ao tentar ler imóvel: ID inválido!\n");
            return;
    }
    PreencheEndereco(&atual, &preenchidos);
    PreenchePrecoDisponibilidade(&atual, &preenchidos); 

    ExibeCamposPreenchidos(&atual, preenchidos+1);
    ExibeSucesso(CADASTRO);
    ExibePressioneEnter();

    AdicionarListaImovel(imoveis, &atual);
}

void EditarImovel(imovel *atual, int op){

    int erro = 0;
    int opEndereco = 0;

    int entradaInt;
    float entradaFloat;
    char* entradaString;

    casa *casaAtual = &atual->categoria.casa;
    apartamento *apartamentoAtual = &atual->categoria.apartamento;
    terreno *terrenoAtual = &atual->categoria.terreno;

    switch(op){
        case 1:
            ExibeEditaNovo("anúncio", M);
            free(atual->titulo);
            atual->titulo = LerEntradaString();
            break;
        case 0:
            erro = 2;
            break;
        default:
            switch(atual->id){
                case CASA:
                    switch(op){
                        case 2:
                            ExibeEditaNovo("quantidade de quartos", F);
                            entradaInt = LerEntradaInt();
                            erro = !AtribuiInt(entradaInt, &casaAtual->quantidadeQuartos);
                            break;
                        case 3:
                            ExibeEditaNovo("quantidade de pavimentos", F);
                            entradaInt = LerEntradaInt();
                            erro = !AtribuiInt(entradaInt, &casaAtual->quantidadePavimentos);
                            break;
                        case 4:
                            ExibeEditaNovo("área construida (m²)", F);
                            entradaFloat = LerEntradaFloat();
                            erro = !AtribuiFloat(entradaFloat, &casaAtual->areaConstruida);
                            break;
                        case 5:
                            ExibeEditaNovo("área do terreno (m²)", F);
                            entradaFloat = LerEntradaFloat();
                            erro = !AtribuiFloat(entradaFloat, &casaAtual->areaTerreno);
                            break;
                    }   
                    opEndereco = op - 5;
                    break;
                case APARTAMENTO:
                    switch(op){
                        case 2:
                            ExibeEditaNovo("posição do apartamento", F);
                            free(apartamentoAtual->posicao);
                            apartamentoAtual->posicao = LerEntradaString();
                            break;
                        case 3:
                            ExibeEditaNovo("quantidade de quartos", F);
                            entradaInt = LerEntradaInt();
                            erro = !AtribuiInt(entradaInt, &apartamentoAtual->quantidadeQuartos);
                            break;
                        case 4:
                            ExibeEditaNovo("vagas na garagem", F);
                            entradaInt = LerEntradaInt();
                            erro = !AtribuiInt(entradaInt, &apartamentoAtual->vagasGaragem);
                            break;
                        case 5:
                            ExibeEditaNovo("andar do apartamento", M);
                            entradaInt = LerEntradaInt();
                            erro = !AtribuiInt(entradaInt, &apartamentoAtual->andar);
                            break;
                        case 6:
                            ExibeEditaNovo("área do apartamento (m²)", F);
                            entradaFloat = LerEntradaFloat();
                            erro = !AtribuiFloat(entradaFloat, &apartamentoAtual->area);
                            break;
                        case 7:
                            ExibeEditaNovo("valor do condomínio", M);
                            entradaFloat = LerEntradaFloat();
                            erro = !AtribuiFloat(entradaFloat, &apartamentoAtual->valorCondominio);
                            break;
                    }
                    opEndereco = op - 7;
                    break;
                case TERRENO:
                    switch(op){
                        case 2:
                            ExibeEditaNovo("área do terreno (m²)", F);
                            entradaFloat = LerEntradaFloat();
                            erro = !AtribuiFloat(entradaFloat, &terrenoAtual->area);
                            break;
                    }
                    opEndereco = op - 2 ;
                    break;
            }
    }

    switch(opEndereco){
        case 1:
            ExibeEditaNovo("cidade", F);
            free(atual->endereco.cidade);
            atual->endereco.cidade = LerEntradaString();
            break;
        case 2: 
            ExibeEditaNovo("bairro", M);
            free(atual->endereco.bairro);
            atual->endereco.bairro = LerEntradaString();
            break;
        case 3:
            ExibeEditaNovo("CEP", M);
            entradaString = LerEntradaString();
            if(VerificaCEP(entradaString) == 0){
                ExibeInvalido(CEP);
                ExibePressioneEnter();
                erro = 2;
            }else{
                free(atual->endereco.cep);
                atual->endereco.cep = entradaString;
            }
            break;
        case 4:
            ExibeEditaNovo("rua", F);
            free(atual->endereco.rua);
            atual->endereco.rua = LerEntradaString();
            break;
        case 5: 
            ExibeEditaNovo("número", M);
            entradaInt = LerEntradaInt();
            erro = !AtribuiInt(entradaInt, &atual->endereco.numero);
            break;
        case 6:
            printf("\n");
            printf("Seleciona venda ou aluga: \n");
            printf("\n");
            printf("1- VENDA\n");
            printf("2- ALUGA\n");
            printf("\n");
            ExibeSelecione();
            entradaInt = LerEntradaInt();
            if(entradaInt == -1){
                erro = 1;
            }else{
                switch(entradaInt){
                    case 1:
                        atual->disponibilidade = VENDA;
                        break;
                    case 2:
                        atual->disponibilidade = ALUGUEL;
                        break;
                    default:
                    erro = 2;
                    ExibeInvalido(OPCAO);
                    ExibePressioneEnter();
                }
            }
            break;
        case 7:
            ExibeEditaNovo("preço", M);
            entradaFloat = LerEntradaFloat();
            erro = !AtribuiFloat(entradaFloat, &atual->preco);
            break;
    }

    free(entradaString);
    if(erro == 0){
        ExibeSucesso(EDICAO);
        ExibePressioneEnter();
    }else if(erro == 1){
        ExibeInvalido(VALOR);
        ExibePressioneEnter();
    }
}

int BuscarStringImovel(arrayImovel* arrayEntrada, buscaID id, char* stringProcura, arrayImovel* arraySaida){
    int resultados = 0;
    char* stringAtributo;
    for(int i = 0; i < arrayEntrada->indice; i++){
        imovel atual = *arrayEntrada->array[i];
        switch(id){
            case TITULO:
                stringAtributo = atual.titulo;
                break;
            case BAIRRO:
                stringAtributo = atual.endereco.bairro;
                break;
        }

        if(strstr(stringAtributo, stringProcura) != NULL){
            AdicionarListaImovel(arraySaida, &atual);
            resultados++;
        }
    }
    return resultados;
}

int BuscarValorImovel(arrayImovel* arrayEntrada, buscaID id, double valorProcura, comparacaoID comparador, imovelID tipo, arrayImovel* arraySaida){
    int resultados = 0;
    double valorDoAtributo;

    for(int i = 0; i < arrayEntrada->indice; i++){
        imovel *atual = arrayEntrada->array[i];

        switch(id){
            case PRECO:
                valorDoAtributo = atual->preco;
                break;
            case DISPONIBILIDADE:
                valorDoAtributo = atual->disponibilidade;
        }

        if(atual->id == tipo || tipo == QUALQUER){       
            switch(comparador){
                case MENOR:
                    if(valorDoAtributo < valorProcura){
                        AdicionarListaImovel(arraySaida, atual);
                        resultados++;
                    }
                    break;
                case MAIOR:
                    if(valorDoAtributo > valorProcura){
                        AdicionarListaImovel(arraySaida, atual);
                        resultados++;
                    }
                    break;
                case IGUAL:
                    if(valorDoAtributo == valorProcura){
                        AdicionarListaImovel(arraySaida, atual);
                        resultados++;
                    }
                    break;
                case MENOR_IGUAL:
                    if(valorDoAtributo <= valorProcura){
                        AdicionarListaImovel(arraySaida, atual);
                        resultados++;
                    }
                    break;
                case MAIOR_IGUAL:
                    if(valorDoAtributo >= valorProcura){
                        AdicionarListaImovel(arraySaida, atual);
                        resultados++;
                    }
                    break;
            }
        }
    }
    return resultados;
}

void BuscarImovel(arrayImovel* imoveis, buscaID id, char* titulo, int op){
    char* stringBusca;
    float valorBusca;

    int resultadosEncontrados = 0;
    int erro = 0;

    arrayImovel encontrados;
    CriarListaImovel(&encontrados);

    switch(id){
        case TITULO:

            stringBusca = LerEntradaString();
            resultadosEncontrados = BuscarStringImovel(imoveis, TITULO, stringBusca, &encontrados);
            free(stringBusca);
            break;

        case BAIRRO:

            stringBusca = LerEntradaString();

            resultadosEncontrados = BuscarStringImovel(imoveis, BAIRRO, stringBusca, &encontrados);
            free(stringBusca);
            break;

        case PRECO:

            valorBusca = LerEntradaFloat();

            if(valorBusca == -1){
                erro = 1;
            } 

            switch(op){
                case 1:
                    resultadosEncontrados = BuscarValorImovel(imoveis, PRECO, valorBusca, MAIOR_IGUAL, QUALQUER, &encontrados);
                    break;
                case 2:
                    resultadosEncontrados = BuscarValorImovel(imoveis, PRECO, valorBusca, MENOR_IGUAL, QUALQUER, &encontrados);
                    break;
                case 3:
                    resultadosEncontrados = BuscarValorImovel(imoveis, PRECO, valorBusca, IGUAL, QUALQUER, &encontrados);
                    break;
                case 0:
                    break;
                default:
                    erro = 1;
            }
            break;

        case VENDENDO:

            switch(op){
                case 1:
                    resultadosEncontrados = BuscarValorImovel(imoveis, DISPONIBILIDADE, VENDA, IGUAL, APARTAMENTO, &encontrados);
                    break;
                case 2:
                    resultadosEncontrados = BuscarValorImovel(imoveis, DISPONIBILIDADE, VENDA, IGUAL, CASA, &encontrados);
                    break;
                case 3:
                    resultadosEncontrados = BuscarValorImovel(imoveis, DISPONIBILIDADE, VENDA, IGUAL, TERRENO, &encontrados);
                    break;
                case 0:
                    break;
                default:
                    erro = 1;
            }
            break;

        case ALUGANDO:

            switch(op){
                case 1:
                    resultadosEncontrados = BuscarValorImovel(imoveis, DISPONIBILIDADE, ALUGUEL, IGUAL, APARTAMENTO, &encontrados);
                    break;
                case 2:
                    resultadosEncontrados = BuscarValorImovel(imoveis, DISPONIBILIDADE, ALUGUEL, IGUAL, CASA, &encontrados);
                    break;
                case 3:
                    resultadosEncontrados = BuscarValorImovel(imoveis, DISPONIBILIDADE, ALUGUEL, IGUAL, TERRENO, &encontrados);
                    break;
                case 0:
                    break;
                default:
                    erro = 1;
            }
            break;
        default:
            erro = 1;
    }
    if(erro == 0){
        LimpaTela();
        ExibeTituloCentro(titulo);
        printf("\n");     
        printf("\n");
        ExibeResultadosEncontrados(resultadosEncontrados);
        printf("\n");
        printf("\n");
        ExibeImoveis(&encontrados);
        ExibeTituloCentro("-------");
        printf("\n");
        ExibePressioneEnter();
        printf("\n");
        printf("\n");
    }
    for(int i = 0; i < encontrados.indice; i++){
        free(encontrados.array[i]);
    }
    free(encontrados.array);
}

#endif
