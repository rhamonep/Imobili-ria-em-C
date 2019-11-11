#ifndef _EXIBICAO_H_
#define _EXIBICAO_H_

#include <stdlib.h>
#include <stdio.h>    
#include "registroImoveis.h"

void LimpaTela();

void ExibeCamposPreenchidos(imovel *atual, int preenchidos);
void ExibeTituloCentro(char* titulo);
void ExibeSelecione();
void ExibeInvalido(invalidoID tipo);
void ExibePressioneEnter();
void ExibeResultadosEncontrados(int resultadosEncontrados);
void ExibeImovel(imovel *atual);
int ExibeImoveis(arrayImovel *imoveis);
void ExibeSucesso(sucessoID tipo);
void ExibeEditaNovo(char* nome, generoID genero);



void LimpaTela(){
    system("clear");
}

void ExibeTituloCentro(char* titulo){
    printf("  ----------  %s  ----------  \n", titulo);
}

void ExibeSelecione(){
    printf("-> Digite a opção desejada: ");
}

void ExibeInvalido(invalidoID tipo){
    printf("\n");
    printf("\n");
    switch(tipo){
        case IMOVEL:
            printf("    -> NÃO HÁ IMÓVEL COM ESTE NÚMERO ! <-\n");
            break;
        case OPCAO:
            printf("    -> OPÇÃO INVÁLIDA ! <-\n");
            break;
        case CEP:
            printf("    -> CEP INVÁLIDO ! <-\n");
            break;
        case VALOR:
            printf("    -> VALOR INVÁLIDO ! <-\n");
            break;
    }
    printf("\n");
    printf("\n");
}

void ExibePressioneEnter(){
    printf("Pressione enter para continuar...");
    scanf("%*c");
}

void ExibeResultadosEncontrados(int resultadosEncontrados){
    if(resultadosEncontrados == 0){
        printf("Nenhum resultado encontado.");
    }else if(resultadosEncontrados == 1){
        printf("Foi encontrado %d resultado: ", resultadosEncontrados);
    }else{
        printf("Foram encontrados %d resultados: ", resultadosEncontrados);
    }
}

void ExibeSucesso(sucessoID tipo){
    printf("\n");
    printf("\n");
    switch(tipo){
        case CADASTRO:
            printf("    -> CADASTRO REALIZADO COM SUCESSO! <-   \n");
            break;
        case REMOCAO:
            printf("    -> IMÓVEL REMOVIDO COM SUCESSO! <-   \n");
            break;
        case EDICAO:
            printf("    -> IMÓVEL EDITADO COM SUCESSO! <-   \n");
            break;
    }
    printf("\n");
    printf("\n");
}

void ExibeEditaNovo(char* nome, generoID genero){
    switch(genero){
        case M:
            printf("-> Digite o novo %s: ", nome);
            break;            
        case F:
            printf("-> Digite a nova %s: ", nome); 
            break;
        default:
            printf("ERRO!");          
    }
}

int ExibeImoveis(arrayImovel *imoveis){
    
    int totalImoveis = 0;
    imovel* atual;

    for(int i = 0; i < imoveis->indice; i++){
        atual = imoveis->array[i];
        printf("%d-)", i+1);
        ExibeImovel(atual);
        printf("\n");
        if(i == imoveis->indice-1){
            printf("    ---------------------------   \n");
            printf("\n");
        }
        totalImoveis++;
    }
    return totalImoveis;
}

void ExibeImovel(imovel *atual){
    switch(atual->id){
            case CASA:
                ExibeTituloCentro("CASA");
                printf("\n");
                printf("    Anúncio :   \"%s\"\n", atual->titulo);  
                printf("    Quantidade de quartos :   %d\n", atual->categoria.casa.quantidadeQuartos);
                printf("    Quantidade pavimentos :   %d\n", atual->categoria.casa.quantidadePavimentos);
                printf("    Área Construida (m²):   %.2f\n", atual->categoria.casa.areaConstruida);
                printf("    Área do terreno (m²):   %.2f\n", atual->categoria.casa.areaTerreno);
                break;
            case APARTAMENTO:
                ExibeTituloCentro("APARTAMENTO");
                printf("\n");
                printf("    Anúncio :   \"%s\"\n", atual->titulo);  
                printf("    Posição do apartamento :   %s\n", atual->categoria.apartamento.posicao);
                printf("    Quantidade de quartos :   %d\n", atual->categoria.apartamento.quantidadeQuartos);
                printf("    Vagas na garagem :   %d\n", atual->categoria.apartamento.vagasGaragem);
                printf("    Andar do apartamento :   %d\n", atual->categoria.apartamento.andar);
                printf("    Área do apartamento (m²):   %.2f\n", atual->categoria.apartamento.area);
                printf("    Valor do condomínio:   R$%.2f\n", atual->categoria.apartamento.valorCondominio);
                break;
            case TERRENO:
                ExibeTituloCentro("TERRENO");
                printf("\n");
                printf("    Anúncio :   \"%s\"\n", atual->titulo);
                printf("    Área do terreno (m²):   %.2f\n", atual->categoria.terreno.area);
                break;
        }
            printf("\n");
            printf("    Cidade :   %s\n", atual->endereco.cidade);
            printf("    Bairro :   %s\n", atual->endereco.bairro);
            printf("    CEP:    %s\n", atual->endereco.cep);
            printf("    Rua :   %s\n", atual->endereco.rua);
            printf("    Nº :   %d\n", atual->endereco.numero);
            printf("\n");
            if(atual->disponibilidade == VENDA)
                printf("    Venda ou Aluga :   VENDA\n");
            else if(atual->disponibilidade == ALUGUEL)
                printf("    Venda ou Aluga :   ALUGA\n");
            printf("    Preço:   R$%.2f\n", atual->preco);
            printf("\n");
}

void ExibeCamposPreenchidos(imovel *atual, int preenchidos){

    char* VendaOuAluga;
    int exibidos = 0;

    endereco *enderecoAtual = &atual->endereco;
    casa *casaAtual = &atual->categoria.casa;
    terreno *terrenoAtual = &atual->categoria.terreno;

    LimpaTela();

    switch(atual->id){
        case CASA:     
            ExibeTituloCentro("CADASTRO DE CASA");
            printf("\n");
            printf("-- INFORMAÇÕES DA CASA --\n");
            printf("\n");
            switch(preenchidos){
                default:
                    exibidos = preenchidos - 5;
                case 5:
                    printf("    Área construida (m²):   %.2f\n", casaAtual->areaConstruida);
                case 4:
                    printf("    Área do terreno (m²):    %.2f\n", casaAtual->areaTerreno);
                case 3:
                    printf("    Quantidade de quartos:    %d\n", casaAtual->quantidadeQuartos);
                case 2:
                    printf("    Quantidade de Pavimentos:    %d\n", casaAtual->quantidadePavimentos);
                case 1:
                    printf("    Anúncio:    \"%s\"\n", atual->titulo);
                case 0:
                    printf("\n");
            }
            break;
        case APARTAMENTO:
            ExibeTituloCentro("CADASTRO DE APARTAMENTO");
            printf("\n");
            printf("-- INFORMAÇÕES DO APARTAMENTO --\n");
            printf("\n");
            switch(preenchidos){
                default:
                    exibidos = preenchidos - 7;
                case 7:
                    printf("    Valor do condomínio:   R$%.2f\n", atual->categoria.apartamento.valorCondominio); 
                case 6:               
                    printf("    Área do apartamento (m²):   %.2f\n", atual->categoria.apartamento.area);
                case 5:
                    printf("    Andar do apartamento :   %d\n", atual->categoria.apartamento.andar);
                case 4:
                    printf("    Vagas na garagem :   %d\n", atual->categoria.apartamento.vagasGaragem);
                case 3:
                    printf("    Quantidade de quartos :   %d\n", atual->categoria.apartamento.quantidadeQuartos);
                case 2:
                    printf("    Posição do apartamento :   %s\n", atual->categoria.apartamento.posicao);
                case 1:
                    printf("    Anúncio :   \"%s\"\n", atual->titulo);  
                case 0:
                    printf("\n");
            }
            break;
        case TERRENO:
            ExibeTituloCentro("CADASTRO DE TERRENO");
            printf("\n");
            printf("-- INFORMAÇÕES DO TERRENO: --\n");
            printf("\n");
            switch(preenchidos){
                default:
                    exibidos = preenchidos - 2;
                case 2:
                    printf("    Área do terreno (m²):   %.2f\n", terrenoAtual->area);
                case 1:
                    printf("    Anúncio :   \"%s\"\n", atual->titulo);
                case 0: 
                    printf("\n"); 
            }
            break;

    }

    if(exibidos > 0){
        printf("\n");
        printf("-- INFORMAÇÕES DO ENDEREÇO: --\n");
        printf("\n");
    }
    switch(exibidos){
        default:
        case 5:
            printf("    Nº:   %d\n", enderecoAtual->numero);
        case 4:
            printf("    Rua:   %s\n", enderecoAtual->rua);
        case 3:
            printf("    CEP:   %s\n", enderecoAtual->cep);
        case 2:
            printf("    Bairro:   %s\n", enderecoAtual->bairro);
        case 1:
            printf("    Cidade:   %s\n", enderecoAtual->cidade);
        case 0:
            printf("\n");
    }
    
    if(exibidos > 5){
        printf("\n");
        printf("-- INFORMAÇÕES DE VENDA: --\n");
        printf("\n");
    }
    switch(exibidos){
        case 8:
        case 7:
            printf("    Preço:  R$%.2f\n", atual->preco);
        case 6:
            if(atual->disponibilidade == VENDA)
                VendaOuAluga = "VENDA";
            else if(atual->disponibilidade == ALUGUEL)
                VendaOuAluga = "ALUGUEL";
            printf("    Venda ou Alguel:    %s\n", VendaOuAluga);
            printf("\n");
    }
    if(exibidos == 8)
        ExibeTituloCentro("-------------------"); 
}

#endif
