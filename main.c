//TODO algoritmo migliorato sia in fase di erogazione delle carte sia per stabilire se è meglio prendere 1 o 11 se esce l'asso
//TODO ALLA FINE pulire il codice, astrazioni, ottimizzarlo
//TODO asso non per forza devo scegliere il valore all'inizio. mettere la possibilià di scegliere cosa farci dopo essermi fermato

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

int gioca();
int scelta;
int sommacarteutente;
int sommacartecomputer;
int continua;
int counter;
int dimensionedelmazzo = 52;
int partitevinte = 0; 
int partiteperse = 0; 
Carta carte[52];
Carta cartaUtente[ARRAY_DIMENSION];
Carta cartaComputer[ARRAY_DIMENSION];
Carta* cartePtr = carte;

int main() {
    srand(time(NULL));
    popolamazzo(carte);
    continua = 0; 
    counter = 2;
    printf("\n\n#########################\nBENVENUTO AL BLACKJACK!\n-'q' rappresenta le carte quadri\n-'p' rappresenta le carte picche\n-'c' rappresenta le carte cuori\n-'f' rappresenta le carte fiori" ANSI_COLOR_GREEN "\nIl colore verde rappresenta i messaggi di vittoria" ANSI_COLOR_RESET ANSI_COLOR_RED "\nIl colore rosso rappresenta i messaggi di sconfitta" ANSI_COLOR_RESET ANSI_COLOR_YELLOW "\nIl colore giallo rappresenta i messaggi di info" ANSI_COLOR_RESET ANSI_COLOR_CYAN "\nIl colore azzurro rappresenta le tue mosse" ANSI_COLOR_RESET ANSI_COLOR_MAGENTA "\nIl colore magenta rappresenta le mosse del banco" ANSI_COLOR_RESET "\nBuon divertimento!\n#########################");
    while(1) gioca();   
    return 0;
}

int gioca(){   
    Sleep(2000);
    printf(ANSI_COLOR_YELLOW "\n\n#########################\nComincio una nuova partita\nBilancio attuale: %d partite vinte, %d partite perse\nDistribuisco le carte\n#########################\n" ANSI_COLOR_RESET, partitevinte, partiteperse);
    sommacarteutente = 0;
    sommacartecomputer = 0;
    // primo pezzo --> carte utente
    cartaUtente[0] = daicarte(carte, &dimensionedelmazzo, true); 
    cartaUtente[1] = daicarte(carte, &dimensionedelmazzo, true);
    stampacarta(cartaUtente[0], true);
    stampacarta(cartaUtente[1], true);
    if (cartaUtente[0].valore == 1) sommacarteutente += sceglivaloreasso(cartaUtente[0], true);
    else sommacarteutente += cartaUtente[0].valore;
    if (cartaUtente[1].valore == 1) sommacarteutente += sceglivaloreasso(cartaUtente[1], true);
    else sommacarteutente += cartaUtente[1].valore;    
    if(sommacarteutente == 21) printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
    printf(ANSI_COLOR_CYAN "\nIn totale hai %d" ANSI_COLOR_RESET, sommacarteutente);
    // secondo pezzo --> carte banco
    Sleep(1000);
    cartaComputer[0] = daicarte(carte, &dimensionedelmazzo, false); 
    cartaComputer[1] = daicarte(carte, &dimensionedelmazzo, false);
    stampacarta(cartaComputer[0], false);
    printf(ANSI_COLOR_MAGENTA "\nL'altra carta rimane nascosta." ANSI_COLOR_RESET);
    if (cartaComputer[0].valore == 1) sommacartecomputer += sceglivaloreasso(cartaComputer[0], false);
    else sommacartecomputer += cartaComputer[0].valore;
    if (cartaComputer[1].valore == 1) sommacartecomputer += sceglivaloreasso(cartaComputer[1], false);
    else sommacartecomputer += cartaComputer[1].valore;    
    if(sommacartecomputer == 21){
        Sleep(1000);
        stampacarta(cartaComputer[1], false);
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
        printf(ANSI_COLOR_RED "\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
        partiteperse++;
        return 1;
    } else if (sommacarteutente == 21){        
        if(sommacartecomputer == 21){
            Sleep(1000);
            stampacarta(cartaComputer[1], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
            printf(ANSI_COLOR_RED "\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
            partiteperse++;
            return 1;
        }
        else{
            Sleep(1000);
            stampacarta(cartaComputer[1], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
            printf(ANSI_COLOR_GREEN "\n\nHai fatto blackjack, hai vinto!" ANSI_COLOR_RESET);
            partitevinte++;
            return 1;   
        }
    } 
    // terzo pezzo --> chiedi carte
    do {
        Sleep(1000);
        printf(ANSI_COLOR_CYAN "\n\nCosa vuoi fare?\n1 chiedi carta\n2 fermati\n-" ANSI_COLOR_RESET);
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                continua = 1;
                cartaUtente[counter] = daicarte(carte, &dimensionedelmazzo, true);
                stampacarta(cartaUtente[counter], true);
                if (cartaUtente[counter].valore == 1) sommacarteutente += sceglivaloreasso(cartaUtente[counter], true);
                else sommacarteutente += cartaUtente[counter].valore;
                printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, sommacarteutente);
                if(sommacarteutente > 21){
                    Sleep(1000);
                    printf(ANSI_COLOR_RED "\n\nHai sballato, hai perso" ANSI_COLOR_RESET);
                    partiteperse++;
                    return 1;
                } else if(sommacarteutente == 21){
                    Sleep(1000);
                    printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
                    continua = 0;
                }
            } break;
            case 2: {
                printf(ANSI_COLOR_YELLOW "\nTi sei fermato" ANSI_COLOR_RESET);
                continua = 0;
            } break;
            default:
                break;
        }
        counter++;
    }while(continua > 0);
    counter = 2;
    // quarto pezzo --> chiedi carte banco (da migliorare)
    Sleep(1000);
    stampacarta(cartaComputer[1], false);
    printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
    while(sommacartecomputer < sommacarteutente) {
        Sleep(1000);
        cartaComputer[counter] = daicarte(carte, &dimensionedelmazzo, false);
        stampacarta(cartaComputer[counter], false);
        if (cartaComputer[counter].valore == 1) sommacartecomputer += sceglivaloreasso(cartaComputer[counter], false);
        else sommacartecomputer += cartaComputer[counter].valore;    
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
    } 
    Sleep(1000);
    printf(ANSI_COLOR_MAGENTA "\n\nIl banco si ferma" ANSI_COLOR_RESET);
    if(sommacartecomputer > 21){
        Sleep(1000);
        printf(ANSI_COLOR_GREEN"\n\nIl banco ha sballato, hai vinto!" ANSI_COLOR_RESET);
        partitevinte++;
        return 1;
    }  
    else if(sommacartecomputer == 21){
        Sleep(1000);
        printf(ANSI_COLOR_RED "\n\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
        partiteperse++;
        return 1;   
    } 
    // quinto pezzo --> tirare le somme e vedere chi ha vinto
    Sleep(1000);
    printf(ANSI_COLOR_YELLOW "\n\nSomma delle tue carte: %d\nSomma delle carte del banco: %d" ANSI_COLOR_RESET, sommacarteutente, sommacartecomputer);
    if(sommacartecomputer > sommacarteutente){
        Sleep(1000);
        printf(ANSI_COLOR_RED "\n\nIl banco ha vinto" ANSI_COLOR_RESET);
        partiteperse++;
        return 1;
    } else if (sommacarteutente > sommacartecomputer){
        Sleep(1000);
        printf(ANSI_COLOR_GREEN "\n\nHai vinto!" ANSI_COLOR_RESET);
        partitevinte++;
        return 1;
    } else if (sommacartecomputer == sommacarteutente){
        Sleep(1000);
        printf(ANSI_COLOR_RED "\n\nIl banco ha vinto, dato che vince anche in caso di pareggio" ANSI_COLOR_RESET);
        partiteperse++;
        return 1;
    }
}
