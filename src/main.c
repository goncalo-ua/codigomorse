#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/morse.h"

#define FICHEIRO_MENSAGENS "mensagens_morse.txt"

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void mostrarMenu() {
    printf("\n╔════════════════════════════════════╗\n");
    printf("║   MEGA TRADUTOR MORSE              ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf("  1  - Texto Normal -> Codigo Morse\n");
    printf("  2  - Codigo Morse -> Texto Normal\n");
    printf("  ────────────────────────────────\n");
    printf("  3  - Guardar mensagem em ficheiro\n");
    printf("  4  - Ler mensagens do ficheiro\n");
    printf("  ────────────────────────────────\n");
    printf("  M1 - S.O.S\n");
    printf("  M2 - Ola\n");
    printf("  M3 - Estas a escuta?\n");
    printf("  ────────────────────────────────\n");
    printf("  0  - Sair\n");
    printf("  ════════════════════════════════\n");
    printf("  Escolha uma opcao: ");
}

void guardarMensagem() {
    printf("\n╔════════════════════════════════════╗\n");
    printf("║  GUARDAR MENSAGEM                  ║\n");
    printf("╚════════════════════════════════════╝\n");
    
    printf("\nEscreva a mensagem para guardar:\n> ");
    
    char *textoOriginal = lerTextoMemDinamica();
    
    if (textoOriginal == NULL) {
        printf("[ERRO] Falha na alocacao de memoria.\n");
        return;
    }
    
    if (strlen(textoOriginal) == 0) {
        printf("[ERRO] Mensagem vazia!\n");
        free(textoOriginal);
        return;
    }
    
    // Traduzir para Morse
    char *codigoMorse = traduzirParaMorse(textoOriginal);
    
    if (codigoMorse == NULL) {
        printf("[ERRO] Falha na traducao para Morse.\n");
        free(textoOriginal);
        return;
    }
    
    // Abrir ficheiro em modo append
    FILE *ficheiro = fopen(FICHEIRO_MENSAGENS, "a");
    
    if (ficheiro == NULL) {
        printf("[ERRO] Nao foi possivel abrir o ficheiro para escrita.\n");
        free(textoOriginal);
        free(codigoMorse);
        return;
    }
    
    // Guardar no formato: TEXTO | MORSE
    fprintf(ficheiro, "TEXTO: %s\n", textoOriginal);
    fprintf(ficheiro, "MORSE: %s\n", codigoMorse);
    fprintf(ficheiro, "─────────────────────────────────────\n");
    
    fclose(ficheiro);
    
    printf("\n[SUCESSO] Mensagem guardada em '%s'!\n", FICHEIRO_MENSAGENS);
    printf("\nTexto: %s\n", textoOriginal);
    printf("Morse: %s\n", codigoMorse);
    
    free(textoOriginal);
    free(codigoMorse);
}

void lerMensagens() {
    printf("\n╔════════════════════════════════════╗\n");
    printf("║  MENSAGENS GUARDADAS               ║\n");
    printf("╚════════════════════════════════════╝\n\n");
    
    FILE *ficheiro = fopen(FICHEIRO_MENSAGENS, "r");
    
    if (ficheiro == NULL) {
        printf("[ERRO] Ficheiro '%s' nao encontrado.\n", FICHEIRO_MENSAGENS);
        printf("        Ainda nao guardou nenhuma mensagem.\n");
        return;
    }
    
    // Verificar se o ficheiro está vazio
    fseek(ficheiro, 0, SEEK_END);
    long tamanho = ftell(ficheiro);
    fseek(ficheiro, 0, SEEK_SET);
    
    if (tamanho == 0) {
        printf("[AVISO] O ficheiro esta vazio.\n");
        fclose(ficheiro);
        return;
    }
    
    // Ler e mostrar todo o conteúdo
    char linha[500];
    int contador = 0;
    
    while (fgets(linha, sizeof(linha), ficheiro) != NULL) {
        // Contar mensagens (cada bloco começa com "TEXTO:")
        if (strncmp(linha, "TEXTO:", 6) == 0) {
            contador++;
            printf("Mensagem #%d\n", contador);
        }
        printf("%s", linha);
    }
    
    fclose(ficheiro);
    
    if (contador == 0) {
        printf("[AVISO] Nenhuma mensagem encontrada no ficheiro.\n");
    } else {
        printf("\nTotal de mensagens: %d\n", contador);
    }
}

int main() {
    char inputMenu[10];
    int continuar = 1;

    while (continuar) {
        mostrarMenu();
        
        scanf("%s", inputMenu);
        
        // Limpeza de buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // Converter para maiúsculas
        for(int i = 0; inputMenu[i]; i++){
            inputMenu[i] = toupper(inputMenu[i]);
        }

        printf("\n");

        // ═══ LOGICA DE DECISÃO ═══

        if (strcmp(inputMenu, "0") == 0) {
            printf("╔════════════════════════════════════╗\n");
            printf("║  Encerrando o programa...          ║\n");
            printf("║  Ate breve! 73 (Best regards)      ║\n");
            printf("╚════════════════════════════════════╝\n");
            continuar = 0;
        }
        else if (strcmp(inputMenu, "3") == 0) {
            guardarMensagem();
            pausar();
        }
        else if (strcmp(inputMenu, "4") == 0) {
            lerMensagens();
            pausar();
        }
        else if (strcmp(inputMenu, "M1") == 0) {
            executarAtalho("S.O.S");
            pausar();
        }
        else if (strcmp(inputMenu, "M2") == 0) {
            executarAtalho("OLA");
            pausar();
        }
        else if (strcmp(inputMenu, "M3") == 0) {
            executarAtalho("ESTAS A ESCUTA?");
            pausar();
        }
        else if (strcmp(inputMenu, "1") == 0 || strcmp(inputMenu, "2") == 0) {
            
            printf("╔════════════════════════════════════╗\n");
            if (strcmp(inputMenu, "1") == 0) {
                printf("║  TEXTO -> MORSE                    ║\n");
            } else {
                printf("║  MORSE -> TEXTO                    ║\n");
            }
            printf("╚════════════════════════════════════╝\n");
            
            printf("\nEscreva a mensagem:\n");
            if (strcmp(inputMenu, "2") == 0) {
                printf("(Use espacos entre letras e / entre palavras)\n");
            }
            printf("> ");

            char *inputUtilizador = lerTextoMemDinamica();

            if (inputUtilizador != NULL) {
                if (strlen(inputUtilizador) == 0) {
                    printf("\n[ERRO] Mensagem vazia!\n");
                } else {
                    char *resultadoFinal = NULL;

                    if (strcmp(inputMenu, "1") == 0) {
                        resultadoFinal = traduzirParaMorse(inputUtilizador);
                        printf("\n─── RESULTADO (Morse) ───\n");
                    }
                    else {
                        resultadoFinal = converterMorseParaTexto(inputUtilizador);
                        printf("\n─── RESULTADO (Texto) ───\n");
                    }

                    if (resultadoFinal != NULL) {
                        printf("%s\n", resultadoFinal);
                        printf("─────────────────────────\n");
                        free(resultadoFinal);
                    } else {
                        printf("[ERRO] Falha na conversao.\n");
                    }
                }

                free(inputUtilizador);
            } else {
                printf("[ERRO] Falha na alocacao de memoria.\n");
            }
            
            pausar();
        }
        else {
            printf("╔════════════════════════════════════╗\n");
            printf("║  [ERRO] Opcao invalida!            ║\n");
            printf("╚════════════════════════════════════╝\n");
            pausar();
        }
    }

    return 0;
}