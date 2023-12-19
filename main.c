//TODO algoritmo migliorato sia in fase di erogazione delle carte sia per stabilire se è meglio prendere 1 o 11 se esce l'asso
//TODO ALLA FINE pulire il codice, astrazioni, ottimizzarlo
//TODO risolvere asso che viene chiesto subito
//TODO dopo aver scelto 11, non posso chiedere piu carta
//TODO counter partite vinte e perse

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "Carte.h"
#define ARRAY_DIMENSION 10
#define ANSI_COLOR_RED     "\x1b[31m" // sconfitta
#define ANSI_COLOR_GREEN   "\x1b[32m" // vittoria
#define ANSI_COLOR_YELLOW  "\x1b[33m" // info
#define ANSI_COLOR_MAGENTA "\x1b[35m" // banco
#define ANSI_COLOR_CYAN    "\x1b[36m" // utente
#define ANSI_COLOR_RESET   "\x1b[0m" // reset

Carta carte[52];
Carta* cartePtr = carte;
int gioca();
int scelta;
int sommacarteutente;
int sommacartecomputer;
int continua;
int counter;
int dimensionedelmazzo = 52;
int partitevinte = 0; 
int partiteperse = 0; 

Carta cartaUtente[ARRAY_DIMENSION];
Carta cartaComputer[ARRAY_DIMENSION];

int main() {
    srand(time(NULL));
    popolamazzo(carte);
    continua = 0; 
    counter = 2;
    printf("\n\n#########################\nBENVENUTO AL BLACKJACK!\n-'q' rappresenta le carte quadri\n-'p' rappresenta le carte picche\n-'c' rappresenta le carte cuori\n-'f' rappresenta le carte fiori");
    printf(ANSI_COLOR_GREEN "\nIl colore verde rappresenta i messaggi di vittoria" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED "\nIl colore rosso rappresenta i messaggi di sconfitta" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\nIl colore giallo rappresenta i messaggi di info" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\nIl colore azzurro rappresenta le tue mosse" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "\nIl colore magenta rappresenta le mosse del banco" ANSI_COLOR_RESET);
    printf("\nBuon divertimento!\n#########################");
    while(1){
        gioca();
        Sleep(1500);
    }
    return 0;
}

int gioca(){   
    printf(ANSI_COLOR_YELLOW "\n\n#########################\nComincio una nuova partita\nBilancio attuale: %d partite vinte, %d partite perse\nDistribuisco le carte\n#########################" ANSI_COLOR_RESET, partitevinte, partiteperse);
    sommacarteutente = 0;
    sommacartecomputer = 0;
    Sleep(1000);
    cartaUtente[0] = daicarte(carte, &dimensionedelmazzo, true); 
    sommacarteutente += cartaUtente[0].valore;
    cartaUtente[1] = daicarte(carte, &dimensionedelmazzo, true);
    sommacarteutente += cartaUtente[1].valore;
    cartaComputer[0] = daicarte(carte, &dimensionedelmazzo, false); 
    sommacartecomputer += cartaComputer[0].valore;
    cartaComputer[1] = daicarte(carte, &dimensionedelmazzo, false);
    sommacartecomputer += cartaComputer[1].valore;
    printf(ANSI_COLOR_CYAN "\n\nTu hai il %d di %c e il %d di %c.\nIn totale hai %d" ANSI_COLOR_RESET, cartaUtente[0].valore, cartaUtente[0].tipo, cartaUtente[1].valore, cartaUtente[1].tipo, cartaUtente[0].valore + cartaUtente[1].valore );
    printf(ANSI_COLOR_MAGENTA "\n\nIl banco ha pescato %d e l'altra carta nascosta" ANSI_COLOR_RESET, cartaComputer[0]);
    if((cartaComputer[0].valore + cartaComputer[1].valore) == 21){
        Sleep(1000);
        printf(ANSI_COLOR_MAGENTA "\n\nIl banco scopre la sua carta nascosta: %d" ANSI_COLOR_RESET, cartaComputer[1]);
        printf(ANSI_COLOR_RED "\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
        partiteperse++;
        return 1 ;
    } else if ((cartaUtente[0].valore + cartaUtente[1].valore) == 21){        
        Sleep(1000);
        if((cartaComputer[0].valore + cartaComputer[1].valore) == 21){
            printf(ANSI_COLOR_MAGENTA "\n\nIl banco scopre la sua carta nascosta: %d" ANSI_COLOR_RESET, cartaComputer[1]);
            printf(ANSI_COLOR_RED "\nIl banco ha vinto, dato che vince anche in caso di pareggio" ANSI_COLOR_RESET);
            partiteperse++;
            return 1;
        }
        else{
            printf(ANSI_COLOR_MAGENTA "\n\nIl banco scopre la sua carta nascosta: %d" ANSI_COLOR_RESET, cartaComputer[1]);
            printf(ANSI_COLOR_GREEN "\nHai fatto blackjack, hai vinto!" ANSI_COLOR_RESET);
            partitevinte++;
            return 1;   
        }
    }
    do {
        printf(ANSI_COLOR_CYAN "\n\nCosa vuoi fare?\n1 chiedi carta\n2 fermati\n-" ANSI_COLOR_RESET);
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                continua = 1;
                cartaUtente[counter] = daicarte(carte, &dimensionedelmazzo, true);
                sommacarteutente += cartaUtente[counter].valore;
                printf(ANSI_COLOR_CYAN "\nCarta %d.\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, cartaUtente[counter].valore, sommacarteutente);
                if(sommacarteutente > 21){
                    printf(ANSI_COLOR_RED "\n\nHai sballato, hai perso" ANSI_COLOR_RESET);
                    partiteperse++;
                    return 1;
                } else if(sommacarteutente == 21){
                    printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
                    continua = 0;
                }
            } break;
            case 2: {
                printf(ANSI_COLOR_YELLOW "\nTi sei fermato" ANSI_COLOR_RESET);
                Sleep(1500);
                continua = 0;
            } break;
            default:
                break;
        }
        counter++;
    }while(continua > 0);
    counter = 2;

    // algoritmo cpu migliorare
    printf(ANSI_COLOR_MAGENTA "\n\nIl banco scopre la sua carta nascosta: %d" ANSI_COLOR_RESET, cartaComputer[1]);
    while(sommacartecomputer < 16) {
        cartaComputer[counter] = daicarte(carte, &dimensionedelmazzo, false);
        sommacartecomputer += cartaComputer[counter].valore;
        printf(ANSI_COLOR_MAGENTA "\n\nIl banco ha pescato %d.\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, cartaComputer[counter].valore, sommacartecomputer);
        Sleep(500);
    }

    printf(ANSI_COLOR_MAGENTA "\n\nIl banco si ferma" ANSI_COLOR_RESET);
    if(sommacartecomputer > 21){
        printf(ANSI_COLOR_GREEN"\n\nIl banco ha sballato, hai vinto!" ANSI_COLOR_RESET);
        partitevinte++;
        return 1;
    }  
    else if(sommacartecomputer == 21){
        printf(ANSI_COLOR_RED "\n\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
        partiteperse++;
        return 1;   
    } 
    printf(ANSI_COLOR_YELLOW "\n\nSomma delle tue carte: %d\nSomma delle carte del banco: %d" ANSI_COLOR_RESET, sommacarteutente, sommacartecomputer);

    if(sommacartecomputer > sommacarteutente){
        printf(ANSI_COLOR_RED "\n\nIl banco ha vinto" ANSI_COLOR_RESET);
        partiteperse++;
        return 1;
    } else if (sommacarteutente > sommacartecomputer){
        printf(ANSI_COLOR_GREEN "\n\nHai vinto!" ANSI_COLOR_RESET);
        partitevinte++;
        return 1;
    } else if (sommacartecomputer == sommacarteutente){
        printf(ANSI_COLOR_RED "\n\nIl banco ha vinto, dato che vince anche in caso di pareggio" ANSI_COLOR_RESET);
        partiteperse++;
        return 1;
    }
}
