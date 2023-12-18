#include "Carte.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m" // info
#define ANSI_COLOR_CYAN    "\x1b[36m" // utente
#define ANSI_COLOR_RESET   "\x1b[0m" // reset

void popolamazzo(Carta* array) {
    const char tipi[] = {'c', 'q', 'f', 'p'};
    int index = 0;
    for (int i = 0; i < 4; i++) { // For each suit
        for (int j = 1; j <= 13; j++) { // For each card value
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
    printf(ANSI_COLOR_YELLOW "\n\nNumero di carte rimaste: %d" ANSI_COLOR_RESET, counter);
}

Carta daicarte(Carta* array, int* dimensionedelmazzo, bool isutente){ 
    if (*dimensionedelmazzo <= 0) {
        printf(ANSI_COLOR_YELLOW "\n\nNon ci sono piu' carte. Rimescolo" ANSI_COLOR_RESET);
        return (Carta){0, 0, false, false, false};
    }
    int randomint = rand() % *dimensionedelmazzo;
    Carta cartaselezionata = array[randomint];
    // printf("randomint: %d, cartaselezionata: %d", randomint, cartaselezionata.valore);
    for (int i = randomint; i < *dimensionedelmazzo - 1; i++) {
        array[i] = array[i + 1];
    }
    (*dimensionedelmazzo)--;
    if (cartaselezionata.valore == 1 && isutente){
        printf(ANSI_COLOR_CYAN "\n\nE' uscito un asso. Vuoi scegliere di usarlo come 1 o come 11?\n1) 1\n2) 11\n-" ANSI_COLOR_RESET);
        int sceltaAsso = 0; 
        scanf("%d", &sceltaAsso);
        switch (sceltaAsso)
        {
        case 1:
            cartaselezionata.valore = 1;
            break;
        case 2:
            cartaselezionata.valore = 11;
            break;
        default:
            break;
        }
    }
    else if (cartaselezionata.valore == 1 && !isutente){ // migliorare
        int randomintcpu = rand() % 2;
        if(randomintcpu > 1) cartaselezionata.valore = 1;
        else cartaselezionata.valore = 11;
    }
    return cartaselezionata;
}