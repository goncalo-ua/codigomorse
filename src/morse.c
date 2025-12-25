#include <stdio.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h> 
#include "../include/morse.h"

// Tabela para mapear caracteres
static char *morse_tabela[] = {
    ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",    // A-I
    ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",   // J-R
    "...",  "-",    "..-",  "...-", ".--",  "-..-", "-.--", "--..",          // S-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", // 0-9
    ".-.-.-", "--..--", "..--..", "-.-.--" // . , ? !
};

// FUNÇÃO 1: LEITURA DINÂMICA
char* lerTextoMemDinamica() {
    int capacidade = 10;      
    int tamanhoAtual = 0;     
    char *buffer = malloc(capacidade * sizeof(char)); 
    int c; 

    if (!buffer) return NULL; 

    while (1) {
        c = getchar(); 

        if (c == '\n' || c == EOF) { 
            break;
        }
        
        if (tamanhoAtual >= capacidade - 1) { 
            capacidade += 10; 
            char *temp = realloc(buffer, capacidade * sizeof(char)); 
            
            if (!temp) {
                free(buffer);
                return NULL; 
            }
            buffer = temp;
        }

        buffer[tamanhoAtual] = c; 
        tamanhoAtual++;
    }

    buffer[tamanhoAtual] = '\0'; 
    return buffer;
}

// FUNÇÃO 2: TEXTO -> MORSE
char* traduzirParaMorse(char *texto) {
    char *buffer = calloc((strlen(texto) * 7) + 1, sizeof(char));
    
    if (buffer == NULL) return NULL; 

    for (int i = 0; texto[i] != '\0'; i++) {
        char c = toupper(texto[i]);
        int sitio = -1;

        if (c >= 'A' && c <= 'Z') sitio = c - 'A';
        else if (c >= '0' && c <= '9') sitio = (c - '0') + 26;
        else if (c == '.') sitio = 36;
        else if (c == ',') sitio = 37;
        else if (c == '?') sitio = 38;
        else if (c == '!') sitio = 39;
        else if (c == ' ') {
            strcat(buffer, "/ "); 
            continue;
        }

        if (sitio != -1) {
            strcat(buffer, morse_tabela[sitio]); 
            strcat(buffer, " "); 
        }
    }
    
    return buffer;
}

// FUNÇÃO 3: MORSE -> TEXTO
char* converterMorseParaTexto(char *morseOriginal) {
    char *resultado = malloc((strlen(morseOriginal) + 1) * sizeof(char));
    char *copiaSegura = malloc((strlen(morseOriginal) + 1) * sizeof(char));
    
    if (!resultado || !copiaSegura) return NULL; 

    strcpy(copiaSegura, morseOriginal);

    int posAtual = 0; 
    char *token = strtok(copiaSegura, " "); 

    while (token != NULL) {
        if (strcmp(token, "/") == 0) {
            resultado[posAtual] = ' '; 
            posAtual++;
        } 
        else {
            int indiceEncontrado = -1;
            for (int i = 0; i < 40; i++) {
                if (strcmp(morse_tabela[i], token) == 0) {
                    indiceEncontrado = i;
                    break;
                }
            }

            if (indiceEncontrado != -1) {
                char letra = '?';
                if (indiceEncontrado <= 25) letra = indiceEncontrado + 'A';
                else if (indiceEncontrado <= 35) letra = (indiceEncontrado - 26) + '0';
                else if (indiceEncontrado == 36) letra = '.';
                else if (indiceEncontrado == 37) letra = ',';
                else if (indiceEncontrado == 38) letra = '?';
                else if (indiceEncontrado == 39) letra = '!';

                resultado[posAtual] = letra;
                posAtual++;
            }
        }
        token = strtok(NULL, " ");
    }

    resultado[posAtual] = '\0'; 
    free(copiaSegura); 
    
    return resultado;
}

// FUNÇÃO 4: EXECUTAR ATALHOS (Nova Localização)
void executarAtalho(char *mensagem) {
    printf("\n>>> MENSAGEM PREDEFINIDA <<<\n");
    printf("Texto Normal: %s\n", mensagem);
    
    // Chama a função interna de tradução
    char *resultadoMorse = traduzirParaMorse(mensagem);
    
    if (resultadoMorse) {
        printf("Codigo Morse: %s\n", resultadoMorse);
        free(resultadoMorse); // Limpa a memória
    }
}