#include <stdio.h>
#include <string.h>
#include <ctype.h> // biblioteca para "mexer" nas letras
#include <stdlib.h> // biblioteca dos mallocs 
#include "../include/morse.h"


int main() {
    printf("Mega tradutor de codigo morse\n"); // Adicionei um \n aqui para ficar bonito
    printf("Escreva a sua mensagem:\n");
    
    char *mensagem = lerTextoMemDinamica(); //chamar a funçao

    if (mensagem != NULL) { //se não for nulll
        printf("Leu %lu caracteres.\n", strlen(mensagem));
        printf("Em Morse: ");
        traduzirParaMorse(mensagem);

        free(mensagem); //se não limpar a memoria o pc fica com a mem ocupada ate reniciar o programa
    } else {
        printf("Erro ao ler a mensagem.\n");
    }

    return 0;
}