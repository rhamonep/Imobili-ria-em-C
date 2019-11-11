#ifndef _LEITURA_VERIFICACAO_ATRIBUICAO_H_
#define _LEITURA_VERIFICACAO_ATRIBUICAO_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_BUFFER 500

int VerificaStringParaFloat(char* numero);
int VerificaStringParaInt(char* numero);
int VerificaCEP(char* cep);

char* LerEntradaString();
int LerEntradaInt();
float LerEntradaFloat();

int AtribuiInt(int entrada, int* recebe);
int AtribuiFloat(int entrada, float* recebe);



int VerificaStringParaFloat(char* numero){
    int pontoOuVirgula = 0;

    if(strlen(numero) == 0){
        return 0;
    }

    for(int i = 0; i < strlen(numero); i++){
        if(numero[i] == '.' || numero[i] == ',' && pontoOuVirgula == 0){
            if(numero[i] == ','){
                numero[i] = '.';
            }
            pontoOuVirgula = 1;
        }else if(isdigit(numero[i]) == 0){
            return 0;
        }
    }
    return 1;
}

int VerificaStringParaInt(char* numero){
    if(strlen(numero) == 0){
        return 0;
    }

    for(int i = 0; i < strlen(numero); i++){
        if(isdigit(numero[i]) == 0){
            return 0;
        }
    }
    
    return 1;
}

int VerificaCEP(char* cep){
    if(strlen(cep) != 9){
        return 0;
    }
    for(int i = 0; i < strlen(cep); i++){
        if(i==5){
            if(cep[i] != '-'){
                return 0;
            }
        }else{
            if(isdigit(cep[i]) == 0){
                return 0;
            }
        }
    }
    return 1;
}

char* LerEntradaString(){
    char buffer[TAMANHO_BUFFER];
    char* string = NULL;
    size_t tamanhoString = 0;
    size_t tamanhoBuffer = 0;

    do{
        fgets(buffer, TAMANHO_BUFFER, stdin);
        tamanhoBuffer = strlen(buffer);
        string = (char*) realloc(string, tamanhoBuffer+tamanhoString+1);
        strcpy(string+tamanhoString, buffer);
        tamanhoString += tamanhoBuffer;
    }while((tamanhoBuffer == TAMANHO_BUFFER-1) && (buffer[TAMANHO_BUFFER-2] != '\n'));

    string[strlen(string)-1] = '\0';
    return string;
}

int LerEntradaInt(){
    int temp;
    char* entrada;

    entrada = LerEntradaString();

    if(VerificaStringParaInt(entrada) == 0){
        free(entrada);
        return -1;
    }else{
        temp = strtol(entrada, NULL, 10);
        free(entrada);
        return temp;
    }
}

float LerEntradaFloat(){
    float temp;
    char* entrada;

    entrada = LerEntradaString();
    
    if(VerificaStringParaFloat(entrada) == 0){
        free(entrada);
        return -1;
    }else{
        temp = strtof(entrada, NULL);
        free(entrada);
        return temp;
    }
}

int AtribuiInt(int entrada, int* recebe){
    if(entrada == -1){
        return 0;
    }
    *recebe = entrada;
        return 1;
}

int AtribuiFloat(int entrada, float* recebe){
    if(entrada == -1){
        return 0;
    }
    *recebe = entrada;
        return 1;
}

#endif
