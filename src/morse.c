#include <stdio.h>
#include <string.h>
#include <ctype.h> // biblioteca para "mexer" nas letras
#include <stdlib.h> // biblioteca dos mallocs 
#include "../include/morse.h"

char *morse_tabela[] = { // O * é pa dizer que estamos a lidar com ponteiros
    // não foi usada matriz e sim um array de ponteiros para ocupar menos espaço na memoria
    ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",    // A-I
    ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",   // J-R
    "...",  "-",    "..-",  "...-", ".--",  "-..-", "-.--", "--..",          // S-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", // 0-9
    ".-.-.-", "--..--", "..--..", "-.-.--" // . , ? !
};

char* lerTextoMemDinamica() {
    int capacidade = 10;      // capacidade pre reservada 
    int tamanhoAtual = 0;     
    char *buffer = malloc(capacidade * sizeof(char)); // Cria o primeiro bloco
    
    int c;

    if (!buffer) return NULL; // verificaçao de segurança caso não tenha espaço no programa "fecha"

    // Loop de ler caracteres
    while (1) {
        c = getchar(); // Le as teclas

        if (c == '\n' || c == EOF) { // ao clicar enter ou termina o ficheiro End Of File
            break;
        }

        
        if (tamanhoAtual >= capacidade - 1) { // ver se chega o  -1 para sobrar espaço para o \0
            capacidade += 10; // Aumenta mais 10 lugares
            
            char *temp = realloc(buffer, capacidade * sizeof(char)); // aumentar o espaço alocado
            
            if (!temp) {
                free(buffer);
                return NULL; // Erro de memória
            }
            buffer = temp;
        }

        buffer[tamanhoAtual] = c; // basicamente a cena do i++
        tamanhoAtual++;
    }

    buffer[tamanhoAtual] = '\0'; //termina a string
    
    return buffer;
}

void traduzirParaMorse(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = toupper(texto[i]); // transformar tudo em letras grandes
        int sitio = -1; // um interger para sser variavel de controlo e depois guardar a posiçao da letra

        if (c >= 'A' && c <= 'Z') {
            sitio = c - 'A'; // calcular o sitio das letras se c = a c - A = 65-65 ou seja pos 0 e c = b 66-65 = 1 pos 1
        } 
        else if (c >= '0' && c <= '9') {
            sitio = (c - '0') + 26; // passa as letras á frente e ve os numeros
        } 
        // caracteres especiais
        else if (c == '.') sitio = 36;
        else if (c == ',') sitio = 37;
        else if (c == '?') sitio = 38;
        else if (c == '!') sitio = 39;
        else if (c == ' ') {
            printf("/ "); // Espaço entre palavras manda uma barra para ser mais facil de ler que estava impossivel de decifrar
            continue;
        }

        if (sitio != -1) {
            printf("%s ", morse_tabela[sitio]);
        }
    }
    printf("\n");
}