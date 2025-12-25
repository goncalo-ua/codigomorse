#ifndef MORSE_H
#define MORSE_H

// Lê texto do teclado sem limites (usa malloc/realloc)
char* lerTextoMemDinamica();

// Traduz Texto -> Morse (devolve nova memória dinâmica)
char* traduzirParaMorse(char *texto); 

// Traduz Morse -> Texto (devolve nova memória dinâmica)
char* converterMorseParaTexto(char *morseOriginal);

// NOVA: Executa os atalhos (M1, M2, M3) e imprime o resultado
void executarAtalho(char *mensagem);

#endif