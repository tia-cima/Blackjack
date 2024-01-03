#include "Carte.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_COLOR_RED     "\x1b[31m" // sconfitta
#define ANSI_COLOR_GREEN   "\x1b[32m" // vittoria
#define ANSI_COLOR_YELLOW  "\x1b[33m" // info
#define ANSI_COLOR_MAGENTA "\x1b[35m" // banco
#define ANSI_COLOR_CYAN    "\x1b[36m" // utente
#define ANSI_COLOR_RESET   "\x1b[0m" // reset

void popolamazzo(Carta* array) {
    const char tipi[] = {'c', 'q', 'f', 'p'};
    int index = 0;
    for (int i = 0; i < 4; i++) { 
        for (int j = 1; j <= 13; j++) { 
            array[index].valore = (j > 10) ? 10 : j; // if c > 0 assegna 10, senno 10
            array[index].tipo = tipi[i];
            array[index].isJack = (j == 11);
            array[index].isRegina = (j == 12);
            array[index].isRe = (j == 13); // vero se j = 13
            index++;
        }
    }
}

void stampamazzo(Carta* array){
    printf("\n\n");
    int counter = 0;
    for(int i = 0; i < 52; i++){
        printf(ANSI_COLOR_YELLOW "\nCarta numero %d, di tipo %c. " ANSI_COLOR_RESET, array[i].valore, array[i].tipo);
        if(array[i].isJack) printf(ANSI_COLOR_YELLOW "Questa carta e' un jack" ANSI_COLOR_RESET);
        if(array[i].isRegina) printf(ANSI_COLOR_YELLOW "Questa carta e' una regina" ANSI_COLOR_RESET);
        if(array[i].isRe) printf(ANSI_COLOR_YELLOW "Questa carta e' un re" ANSI_COLOR_RESET);
        counter++;
    }
}

void stampacarta(Carta valore, bool isutente){
    char tipo[7]; 
    char figura[30]; 
    switch (valore.tipo)
    {
    case 'c':
        strcpy(tipo, "cuori");
        break;
    case 'q':
        strcpy(tipo, "quadri");
        break;
    case 'f':
        strcpy(tipo, "fiori");
        break;
    case 'p':
        strcpy(tipo, "picche");
        break;
    default:
        break;
    }
    if(valore.isJack) {strcpy(figura, "Questa carta e' un jack. ");}
    else if(valore.isRegina) {strcpy(figura, "Questa carta e' una regina. ");}
    else if(valore.isRe) {strcpy(figura, "Questa carta e' un re. ");}
    else {strcpy(figura, "");}
    if(isutente){
        printf(ANSI_COLOR_CYAN "\n%d di %s. %s" ANSI_COLOR_RESET, valore.valore, tipo, figura);
    } else {
        printf(ANSI_COLOR_MAGENTA "\n\nIl banco ha pescato %d di %s. %s" ANSI_COLOR_RESET, valore.valore, tipo, figura);
    }
}

Carta daicarte(Carta* array, int* dimensionedelmazzo, bool isutente){
    if (*dimensionedelmazzo <= 0) {
        printf(ANSI_COLOR_YELLOW "\n\nNon ci sono piu' carte. Rimescolo" ANSI_COLOR_RESET);
        popolamazzo(array);
        *dimensionedelmazzo = 52;
    }
    int randomint = rand() % *dimensionedelmazzo;
    Carta cartaselezionata = array[randomint];
    for (int i = randomint; i < *dimensionedelmazzo - 1; i++) {
        array[i] = array[i + 1];
    }
    (*dimensionedelmazzo)--;
    return cartaselezionata;
}
