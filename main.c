//TODO algoritmo migliorato
//TODO erogazione carte con nuovo metodo per avversario
//TODO gestione spazi, br e in generale formattazione del testo, ad oggi è inguardabile
//TODO ALLA FINE pulire il codice, astrazioni, ottimizzarlo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h> // sleep
#include "Carte.h"
#define ARRAY_DIMENSION 10

Carta carte[52];
Carta* cartePtr = carte;
int gioca();
int scelta;
int sommacarteutente;
int sommacartecomputer;
int continua;
int counter;
int dimensionedelmazzo = 52;

Carta cartaUtente[ARRAY_DIMENSION];
Carta cartaComputer[ARRAY_DIMENSION];

int main() {
    srand(time(NULL));
    popolamazzo(carte);
    sommacarteutente = 0;
    sommacartecomputer = 0;
    continua = 0; 
    counter = 2;
    printf("\n\nBENVENUTO AL BLACKJACK!\nI CARATTERI 'q', 'p', 'c' e 'f' RAPPRESENTANO RISPETTIVAMENTE LE CARTE QUADRI, PICCHE, CUORI E FIORI\n");
    while(1){
        gioca();
        Sleep(1500);
    }
    // do {

    //     printf("\nPer giocare premi 1, se vuoi uscire premi 2\n-");
    //     scanf("%d", &scelta);
    //     switch (scelta) {
    //     case 1:
    //         restart = gioca();
    //         break;
    //     case 2:
    //         printf("Grazie per aver giocato!\n");
    //         restart = 0;
    //         break;
    //     default:
    //         printf("Scelta non valida.\n");
    //     }
    //     Sleep(1500);
    // } while (scelta != 2 || restart > 0); per me è stupido chiedere ogni volta se voglio uscire o giocare. se voglio smettere, ch
    return 0;
}

int gioca(){   
    printf("\nDistribuisco le carte.\n\n");
    Sleep(1000);
    cartaUtente[0] = daicarte(carte, &dimensionedelmazzo, true); 
    sommacarteutente += cartaUtente[0].valore;
    cartaUtente[1] = daicarte(carte, &dimensionedelmazzo, true);
    sommacarteutente += cartaUtente[1].valore;
    cartaComputer[0] = daicarte(carte, &dimensionedelmazzo, false); 
    sommacartecomputer += cartaComputer[0].valore;
    cartaComputer[1] = daicarte(carte, &dimensionedelmazzo, false);
    sommacartecomputer += cartaComputer[1].valore;
    printf("Tu hai il %d di %c e il %d di %c. In totale hai %d\n", cartaUtente[0].valore, cartaUtente[0].tipo, cartaUtente[1].valore, cartaUtente[1].tipo, cartaUtente[0].valore + cartaUtente[1].valore);
    printf("L'avversario ha pescato %d e l'altra carta nascosta.\n\n", cartaComputer[0]);
    if((cartaComputer[0].valore + cartaComputer[1].valore) == 21){
        Sleep(1000);
        printf("\nIl banco scopre la sua carta nascosta: %d\n", cartaComputer[1]);
        printf("Il banco ha fatto blackjack, hai perso\n\n");
        return 1 ;
    } else if ((cartaUtente[0].valore + cartaUtente[1].valore) == 21){        
        Sleep(1000);
        if((cartaComputer[0].valore + cartaComputer[1].valore) == 21){
            printf("\nIl banco scopre la sua carta nascosta: %d\n", cartaComputer[1]);
            printf("Cpu ha vinto, il banco vince in caso di pareggio\n");
            return 1;
        }
        else{
            printf("\nIl banco scopre la sua carta nascosta: %d\n", cartaComputer[1]);
            printf("Hai fatto blackjack! Hai vinto\n\n");
            return 1;   
        }
    }
    do {
        printf("Cosa vuoi fare?\n1 carta \n2 stai\n-");
        scanf("%d", &scelta);
        switch (scelta)
        {
            case 1:
            {
                cartaUtente[counter] = daicarte(carte, &dimensionedelmazzo, true);
                sommacarteutente += cartaUtente[counter].valore;
                printf("\nCarta %d. La somma delle tue carte e' %d\n", cartaUtente[counter].valore, sommacarteutente);
                if(sommacarteutente > 21){
                    printf("Hai sballato\n\n");
                    return 1;
                }  
            } break;
            case 2: {
                printf("\nTi sei fermato. \n\n");
                continua = 0;
            } break;
            default:
                break;
        }
        counter++;
    }while(continua > 0);
    counter = 2;

    // algoritmo cpu migliorare
    printf("\nIl banco scopre la sua carta nascosta: %d\n", cartaComputer[1]);
    while(sommacartecomputer < 16) {
        cartaComputer[counter] = daicarte(carte, &dimensionedelmazzo, false);
        sommacartecomputer += cartaComputer[counter].valore;
        printf("Cpu ha pescato %d. La somma delle sue carte e' %d\n", cartaComputer[counter].valore, sommacartecomputer);
        Sleep(500);
    }

    printf("Cpu si ferma\n\n");
    if(sommacartecomputer > 21){
        printf("Cpu ha sballato\n");
        return 1;
    }  
    else if(sommacartecomputer == 21){
        printf("Cpu ha vinto\n");
        return 1;   
    } 
    printf("Somma carte user: %d\nSomma carte cpu: %d\n\n", sommacarteutente, sommacartecomputer);

    if(sommacartecomputer > sommacarteutente){
        printf("Cpu ha vinto\n");
        return 1;
    } else if (sommacarteutente > sommacartecomputer){
        printf("Hai vinto!\n");
        return 1;
    } else if (sommacartecomputer == sommacarteutente){
        printf("Cpu ha vinto, il banco vince in caso di pareggio\n");
        return 1;
    }
}
