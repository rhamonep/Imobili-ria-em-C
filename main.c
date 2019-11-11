
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "registroImoveis.h"
#include "listaImovel.h"
#include "menu.h"
#include "arquivoLeituraEscrita.h"

int main(){
    arrayImovel imoveis;
    FILE* arquivo;

    setlocale(LC_ALL, "Portuguese");
 
    if(LerArquivoImoveis(&imoveis, arquivo) == 0){
        CriarListaImovel(&imoveis);
    }

    MenuPrincipal(&imoveis);

    SalvarArquivoImoveis(&imoveis, arquivo);
    DestruirListaImovel(&imoveis);

    return 0;
}