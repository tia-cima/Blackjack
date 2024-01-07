
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Carte.h"
#include "Conto.h"
#include "Blackjack.h"
#define ARRAY_DIMENSION 11
#define ANSI_COLOR_RED     "\x1b[31m" // sconfitta
#define ANSI_COLOR_GREEN   "\x1b[32m" // vittoria
#define ANSI_COLOR_YELLOW  "\x1b[33m" // info
#define ANSI_COLOR_MAGENTA "\x1b[35m" // banco
#define ANSI_COLOR_CYAN    "\x1b[36m" // utente
#define ANSI_COLOR_RESET   "\x1b[0m" // reset

int puntate[] = {10, 20, 50, 100, 200, 500};

int sceglipuntata(Conto* contopersona){
    printf(ANSI_COLOR_YELLOW "\nQuanto vuoi puntare?" ANSI_COLOR_RESET);
    for (int i = 0; i < sizeof(puntate) / sizeof(puntate[0]); i++){
        printf(ANSI_COLOR_YELLOW "\n%d) %d" ANSI_COLOR_RESET, i, puntate[i]);
    }
    printf("\n-");
    int puntatagiocatore;
    int puntatatemp;
    scanf("%d", &puntatagiocatore);
    for (int i = 0; i < sizeof(puntate) / sizeof(puntate[0]); i++) {
        if (puntatagiocatore == i) {
            puntatatemp = puntate[i];
        }
    }
    if (puntatatemp < 0) return -1;
    else if(puntatatemp > contopersona->ammontare) return -1;
    else return puntatatemp;
}

int sceglivaloreassoutente(Carta valore, int* counterassiutente, bool isfermato){
    if(isfermato){
         printf(ANSI_COLOR_CYAN "\n\nVuoi scegliere di usarlo come 1 o come 11?\n1) 1\n2) 11\n-" ANSI_COLOR_RESET);
        int sceltaasso = 0; 
        scanf("%d", &sceltaasso);
        switch (sceltaasso) {
            case 1:
                return 1;
            case 2:{
                valore.valore = 11;
                return 11;
            }
            default:
                return 1;
        }      
    } else {
        printf(ANSI_COLOR_CYAN "\n\nE' uscito un asso. Vuoi scegliere di usarlo come 1, come 11 o decidere dopo?\n1) 1\n2) 11\n3) Decidi dopo (il valore 1 è aggiunto a prescindere)\n-" ANSI_COLOR_RESET);
        int sceltaasso = 0; 
        scanf("%d", &sceltaasso);
        switch (sceltaasso) {
            case 1:
                return 1;
            case 2:{
                valore.valore = 11;
                return 11;
            }      
            case 3: {
                (*counterassiutente)++;
                return 1;
            }
            default:
                return 1;
        }         
    }
}

int sceglivaloreassobanco(int sommacartecomputer){
    if (sommacartecomputer + 11 <= 21) {
        return 11;
    }
    return 1;
}
