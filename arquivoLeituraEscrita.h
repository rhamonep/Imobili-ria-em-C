#ifndef _ARQUIVO_H_
#define _ARQUIVO_H_

#include "registroImoveis.h"
#include "listaImovel.h"
#include <string.h>
#include <stdio.h>

#define QUANTIDADE_DE_CAMPOS 6

int SarlvaArquivoImoveis(arrayImovel* imoveis, FILE* arquivo);
int LerArquivoImoveis(arrayImovel* imoveis, FILE* arquivo);



int SalvarArquivoImoveis(arrayImovel* imoveis, FILE* arquivo){

    arquivo = fopen("z_database.dat", "wb");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo (escrita)!\n");
        return 0;
    }

    fwrite(&imoveis->tamanho, sizeof(int), 1, arquivo);
    fwrite(&imoveis->indice, sizeof(int), 1, arquivo);
    
    for(int i = 0; i < imoveis->indice; i++){
        fwrite(imoveis->array[i], sizeof(imovel), 1, arquivo);
    }

    int tamanhoString;
    char* string;
    
    for(int i = 0; i < imoveis->indice; i++){
        for(int j = 0; j < QUANTIDADE_DE_CAMPOS; j++){
            switch(j){
                case 0:
                    string = imoveis->array[i]->titulo;
                    break;
                case 1:
                    string = imoveis->array[i]->endereco.bairro;
                    break;
                case 2:
                    string = imoveis->array[i]->endereco.cep;
                    break;
                case 3: 
                    string = imoveis->array[i]->endereco.cidade;
                    break;
                case 4:
                    string = imoveis->array[i]->endereco.rua;
                    break;   
                case 5: 
                    if(imoveis->array[i]->id != APARTAMENTO){
                        continue;
                    }else{
                        string = imoveis->array[i]->categoria.apartamento.posicao;            
                    }
                    break;
            }
            tamanhoString = strlen(string);
            fwrite(&tamanhoString, sizeof(int), 1, arquivo);
            fwrite(string, tamanhoString * sizeof(char), 1, arquivo);
        }
    }
    fclose(arquivo);
    return 1;
}

int LerArquivoImoveis(arrayImovel* imoveis, FILE* arquivo){
    arquivo = fopen("z_database.dat", "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo (leitura)!\n");
        return 0;
    }
    fread(&imoveis->tamanho, sizeof(int), 1, arquivo);
    fread(&imoveis->indice, sizeof(int), 1, arquivo);

    imoveis->array = (imovel**) malloc(imoveis->tamanho * sizeof(imovel*));

    for(int i = 0; i < imoveis->indice; i++){
        imoveis->array[i] = (imovel*) malloc(sizeof(imovel));
        fread(imoveis->array[i], sizeof(imovel), 1, arquivo);
    }

    int tamanhoString;
    char* string;

   for(int i = 0; i < imoveis->indice; i++){
        for(int j = 0; j < QUANTIDADE_DE_CAMPOS; j++){

            if(j == 5 && imoveis->array[i]->id != APARTAMENTO){
                continue;
            }

            fread(&tamanhoString, sizeof(int), 1, arquivo);
            string = (char*) malloc((tamanhoString+1) * sizeof(char));
            fread(string, tamanhoString* sizeof(char), 1, arquivo);
            string[tamanhoString] = '\0';

            switch(j){
                case 0:
                    imoveis->array[i]->titulo = string;
                case 1:
                    imoveis->array[i]->endereco.bairro = string;
                    break;
                case 2:
                    imoveis->array[i]->endereco.cep = string;
                    break;
                case 3: 
                    imoveis->array[i]->endereco.cidade = string;
                    break;
                case 4:
                    imoveis->array[i]->endereco.rua = string;
                    break;   
                case 5: 
                    imoveis->array[i]->categoria.apartamento.posicao = string;            
                    break;
            }
        }
    }
    fclose(arquivo);
    return 1;
}

#endif
