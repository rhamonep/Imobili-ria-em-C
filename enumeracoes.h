#ifndef _ENUMERACOES_H_
#define _ENUMERACOES_H_

typedef enum imovelID{
    CASA,
    APARTAMENTO,
    TERRENO,
    QUALQUER
}imovelID;

typedef enum disponibilidade{
    ALUGUEL,
    VENDA
}disponibilidade;

typedef enum generoID{
    M,
    F
}generoID;

typedef enum buscaID{
    VENDENDO,
    ALUGANDO,
    TITULO,
    BAIRRO,
    PRECO,
    ANDAR,
    QUARTOS,
    DISPONIBILIDADE
}buscaID;

typedef enum comparacaoID{
    MAIOR = 1,
    MENOR = 2,
    IGUAL = 4,

    MAIOR_IGUAL = MAIOR+IGUAL,
    MENOR_IGUAL = MENOR+IGUAL
}comparacaoID;

typedef enum sucessoID{
    CADASTRO,
    REMOCAO,
    EDICAO
}sucessoID;

typedef enum operacaoID{
    REMOVER,
    EDITAR
}operacaoID;

typedef enum invalidoID{
    OPCAO,
    IMOVEL,
    CEP,
    VALOR
}invalidoID;

#endif