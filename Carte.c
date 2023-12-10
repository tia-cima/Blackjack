#include "Carte.h"
#include <stdio.h>
#include <stdlib.h>


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
    int counter = 0;
    for(int i = 0; i < 52; i++){
        printf("Carta numero %d, di tipo %c. ", array[i].valore, array[i].tipo);
        if(array[i].isJack) printf("Questa carta e' un jack");
        if(array[i].isRegina) printf("Questa carta e' una regina");
        if(array[i].isRe) printf("Questa carta e' un re");
        printf("\n");
        counter++;
    }
    printf("Counter: %d", counter);
}

Carta daicarte(Carta* array, int* dimensionedelmazzo){ 
    if (*dimensionedelmazzo <= 0) {
        printf("Non ci sono piu' carte. Rimescolo\n");
        return (Carta){0, 0, false, false, false};
    }
    int randomint = rand() % *dimensionedelmazzo;
    Carta cartaselezionata = array[randomint];
    // printf("randomint: %d, cartaselezionata: %d\n", randomint, cartaselezionata.valore);
    for (int i = randomint; i < *dimensionedelmazzo - 1; i++) {
        array[i] = array[i + 1];
    }
    (*dimensionedelmazzo)--;
    return cartaselezionata;
}