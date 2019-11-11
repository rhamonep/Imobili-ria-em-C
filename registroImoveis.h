#ifndef _REGISTRO_IMOVEIS_H_
#define _REGISTRO_IMOVEIS_H_

#include "enumeracoes.h"

typedef struct endereco{
    char *rua;
    char *bairro;
    char *cidade;
    char *cep;

    int numero;
}endereco;

typedef struct casa{
    int quantidadePavimentos;
    int quantidadeQuartos;

    float areaTerreno;
    float areaConstruida;
}casa;

typedef struct apartamento{
    char *posicao;
    
    int quantidadeQuartos;
    int vagasGaragem;
    int andar;

    float area;
    float valorCondominio;
}apartamento;

typedef struct terreno{
    float area;
}terreno;

typedef union categoriaImovel{
    apartamento apartamento;
    casa casa;
    terreno terreno;
}categoriaImovel;

typedef struct imovel{
    char *titulo;
    imovelID id;
    categoriaImovel categoria;
    endereco endereco;
    disponibilidade disponibilidade;
    float preco;
}imovel;

typedef struct arrayImovel{
    imovel** array;
    unsigned int tamanho;
    unsigned int indice;
}arrayImovel;

#endif