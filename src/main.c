#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/morse.h"

int main() {
    char inputMenu[10]; 

    printf("\n=== MEGA TRADUTOR MORSE ===\n");
    printf("1  - Texto Normal -> Codigo Morse\n");
    printf("2  - Codigo Morse -> Texto Normal\n");
    printf("M1 - S.O.S\n");
    printf("M2 - Ola\n");
    printf("M3 - Estas a escuta?\n");
    printf("Escolha uma opcao: ");
    
    scanf("%s", inputMenu);
    
    // Limpeza de buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    // Converter para maiúsculas
    for(int i = 0; inputMenu[i]; i++){
        inputMenu[i] = toupper(inputMenu[i]);
    }

    //  LOGICA DE DECISÃO 

    if (strcmp(inputMenu, "M1") == 0) {
        executarAtalho("S.O.S");
    }
    else if (strcmp(inputMenu, "M2") == 0) {
        executarAtalho("OLA");
    }
    else if (strcmp(inputMenu, "M3") == 0) {
        executarAtalho("ESTAS A ESCUTA?");
    }
    else if (strcmp(inputMenu, "1") == 0 || strcmp(inputMenu, "2") == 0) {
        
        printf("\nEscreva a mensagem:\n");
        if (strcmp(inputMenu, "2") == 0) printf("(Use espacos entre letras e / entre palavras)\n");

        char *inputUtilizador = lerTextoMemDinamica();

        if (inputUtilizador != NULL) {
            char *resultadoFinal = NULL;

            if (strcmp(inputMenu, "1") == 0) {
                printf("\n RESULTADO (Morse) \n");
                resultadoFinal = traduzirParaMorse(inputUtilizador);
            }
            else {
                printf("\n RESULTADO (Texto) \n");
                resultadoFinal = converterMorseParaTexto(inputUtilizador);
            }

            if (resultadoFinal != NULL) {
                printf("%s\n", resultadoFinal);
                free(resultadoFinal);
            }

            free(inputUtilizador);
        } else {
            printf("Erro: Falha na alocacao de memoria.\n");
        }
    } 
    else {
        printf("Opcao invalida!\n");
    }

    return 0;
}