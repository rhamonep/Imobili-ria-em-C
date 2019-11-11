#ifndef _LISTA_IMOVEL_
#define _LISTA_IMOVEL_

#include <stdlib.h>
#include "registroImoveis.h"

#define TAMANHO_ARRAY_IMOVEL_INICIAL 10

void CriarListaImovel(arrayImovel* imoveis);
void AumentarListaImovel(arrayImovel* imoveis);
void DiminuirListaImovel(arrayImovel* imoveis);
void AdicionarListaImovel(arrayImovel* imoveis, imovel* adicionar);
void RemoverListaImovel(arrayImovel* imoveis, int posicao);
imovel* AcessarPosicaoListaImovel(arrayImovel* imoveis, int posicao);
void DestruirListaImovel(arrayImovel *imoveis);
int VerificarPosicaoListaImovel(arrayImovel *imoveis, int posicao);



void CriarListaImovel(arrayImovel* imoveis){
    imoveis->array = (imovel**) malloc(TAMANHO_ARRAY_IMOVEL_INICIAL * sizeof(imovel*));
    imoveis->indice = 0;
    imoveis->tamanho = TAMANHO_ARRAY_IMOVEL_INICIAL;
}

void AumentarListaImovel(arrayImovel* imoveis){
    imoveis->array = (imovel**) realloc(imoveis->array, (imoveis->tamanho + TAMANHO_ARRAY_IMOVEL_INICIAL) * sizeof(imovel));
    imoveis->tamanho += TAMANHO_ARRAY_IMOVEL_INICIAL;
}

void DiminuirListaImovel(arrayImovel* imoveis){
    imoveis->array = (imovel**) realloc(imoveis->array, (imoveis->tamanho - TAMANHO_ARRAY_IMOVEL_INICIAL) * sizeof(imovel));
    imoveis->tamanho += TAMANHO_ARRAY_IMOVEL_INICIAL;
}

void AdicionarListaImovel(arrayImovel* imoveis, imovel* adicionar){
    
    imovel* novo;

    novo = (imovel*) malloc(sizeof(imovel));
    *novo = *adicionar;

    if(imoveis->indice == imoveis->tamanho){
        AumentarListaImovel(imoveis);
    }
    imoveis->array[imoveis->indice] = novo;
    imoveis->indice += 1;
}

int VerificarPosicaoListaImovel(arrayImovel *imoveis, int posicao){
    if(posicao-1 < imoveis->indice && posicao > 0)
        return 1;
    return 0;
}

void RemoverListaImovel(arrayImovel* imoveis, int posicao){

    free(imoveis->array[posicao]);

    for(int i = posicao; i < imoveis->indice; i++){
        imoveis->array[i] = imoveis->array[i+1];
    }
    imoveis->indice -= 1;

    if(imoveis->tamanho - imoveis->indice > TAMANHO_ARRAY_IMOVEL_INICIAL){
        DiminuirListaImovel(imoveis);
    }
}

imovel* AcessarPosicaoListaImovel(arrayImovel *imoveis, int posicao){
    return imoveis->array[posicao];
}

void DestruirListaImovel(arrayImovel *imoveis){
    for(int i = 0; i < imoveis->indice; i++){

        free(imoveis->array[i]->titulo);
        endereco* endAtual = &imoveis->array[i]->endereco;
        free(endAtual->rua);
        free(endAtual->cidade);
        free(endAtual->cep);
        free(endAtual->bairro);

        if(imoveis->array[i]->id == APARTAMENTO){
            free(imoveis->array[i]->categoria.apartamento.posicao);
        }
        free(imoveis->array[i]);
    }
    free(imoveis->array);
}

#endif
