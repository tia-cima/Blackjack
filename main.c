//TODO ALLA FINE pulire il codice, astrazioni, ottimizzarlo
//TODO regola blackjack, la casa deve puntare minimo fino a quando non arriva a 17
//TODO controllo puntata

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "Carte.h"
#include "Conto.h"
#define ARRAY_DIMENSION 10
#define ANSI_COLOR_RED     "\x1b[31m" // sconfitta
#define ANSI_COLOR_GREEN   "\x1b[32m" // vittoria
#define ANSI_COLOR_YELLOW  "\x1b[33m" // info
#define ANSI_COLOR_MAGENTA "\x1b[35m" // banco
#define ANSI_COLOR_CYAN    "\x1b[36m" // utente
#define ANSI_COLOR_RESET   "\x1b[0m" // reset

int gioca();
int sceglipuntata();
int scelta;
int sommacarteutente;
int sommacartecomputer;
int continua;
int counter;
int dimensionedelmazzo = 52;
int partitevinte = 0; 
int partiteperse = 0; 
int counterassiutente = 0; 
int puntate[] = {10, 20, 50, 100, 200, 500};
int puntata = 0;
Carta carte[52];
Carta cartaUtente[ARRAY_DIMENSION];
Carta cartaComputer[ARRAY_DIMENSION];
Carta* cartePtr = carte;
Conto contogiocatore;

int main() {
    srand(time(NULL));
    popolamazzo(carte);
    continua = 0; 
    counter = 2;
    printf("\n\n#########################\nBENVENUTO AL BLACKJACK!\n-'q' rappresenta le carte quadri\n-'p' rappresenta le carte picche\n-'c' rappresenta le carte cuori\n-'f' rappresenta le carte fiori" ANSI_COLOR_GREEN "\nIl colore verde rappresenta i messaggi di vittoria" ANSI_COLOR_RESET ANSI_COLOR_RED "\nIl colore rosso rappresenta i messaggi di sconfitta" ANSI_COLOR_RESET ANSI_COLOR_YELLOW "\nIl colore giallo rappresenta i messaggi di info" ANSI_COLOR_RESET ANSI_COLOR_CYAN "\nIl colore azzurro rappresenta le tue mosse" ANSI_COLOR_RESET ANSI_COLOR_MAGENTA "\nIl colore magenta rappresenta le mosse del banco" ANSI_COLOR_RESET "\nBuon divertimento!\n#########################\n");
    printf(ANSI_COLOR_YELLOW "\nPrima di cominciare, hai gia' un account o vuoi crearne uno nuovo? Ti servirà per riaccedere ai tuoi crediti anche in futuro\n1) Crea account\n2) Accedi ad account esistente (ID richiesto)\n-");
    int sceltaccount;
    scanf("%d", &sceltaccount);
    switch (sceltaccount) {
        case 1:{
            impostaconto(&contogiocatore); 
            printf(ANSI_COLOR_YELLOW "\nBenvenuto giocatore %d, hai caricato %d euro. Buona fortuna!" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
        } break;
        case 2:{
            recuperaconto(&contogiocatore); 
            printf(ANSI_COLOR_YELLOW "\nBentornato %d! Il tuo conto e' di %d. Vuoi ricaricarlo o procedere con questo quantitativo?\n1) Ricarica\n2) Non ricaricare\n-" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
            int procedi;
            scanf("%d", &procedi);
            switch (procedi)
            {
            case 1:{
                printf(ANSI_COLOR_YELLOW "\nQuanto vuoi caricare sul tuo conto? Solo cifre intere\n-" ANSI_COLOR_RESET);
                int valore;
                scanf("%d", &valore);
                aggiornaammontare(&contogiocatore, valore);
                printf(ANSI_COLOR_YELLOW "\nRicarica effettuata con successo, nuovo ammontare pari a %d euro. Buona fortuna!" ANSI_COLOR_RESET, contogiocatore.ammontare);
            }            
                break;
            case 2:{
                printf(ANSI_COLOR_YELLOW "\nBuona fortuna!" ANSI_COLOR_RESET);
            }
            default:
                break;
            }
        } break;
        default:
            break;
    }
    while(1) gioca();   
    return 0;
}

int gioca(){       
    sommacarteutente = 0;
    sommacartecomputer = 0;
    counterassiutente = 0; 
    continua = 1;
    Sleep(2000);
    printf(ANSI_COLOR_YELLOW "\n\n#########################\nComincio una nuova partita\nBilancio attuale: %d partite vinte, %d partite perse\nCrediti rimasti: %d\n#########################\n" ANSI_COLOR_RESET, partitevinte, partiteperse, contogiocatore.ammontare);
    if(contogiocatore.ammontare <= 0) {
        printf(ANSI_COLOR_YELLOW "\nHai terminato i crediti. Aggiorna il tuo conto.\nQuanto vuoi caricare?\n-" ANSI_COLOR_RESET);
        int valorefinito;
        scanf("%d", &valorefinito);
        aggiornaammontare(&contogiocatore, valorefinito);
        printf(ANSI_COLOR_YELLOW "\nHai con successo aggiornato il conto" ANSI_COLOR_RESET);
    }
    // primo pezzo --> scelta puntata
    puntata = sceglipuntata();
    if(puntata != -1){
        printf(ANSI_COLOR_CYAN "\nHai scelto di puntare %d euro\n" ANSI_COLOR_RESET, puntata);
    } else {
        printf(ANSI_COLOR_RED "\nScelta non valida. \nHai selezionato un valore non valido oppure hai finito i crediti" ANSI_COLOR_RESET);
        return 1;
    }
    // secondo pezzo --> carte utente
    cartaUtente[0] = daicarte(carte, &dimensionedelmazzo, true); 
    cartaUtente[1] = daicarte(carte, &dimensionedelmazzo, true);
    stampacarta(cartaUtente[0], true);
    stampacarta(cartaUtente[1], true);
    if (cartaUtente[0].valore == 1) sommacarteutente += sceglivaloreassoutente(cartaUtente[0], &counterassiutente);
    else sommacarteutente += cartaUtente[0].valore;
    if (cartaUtente[1].valore == 1) sommacarteutente += sceglivaloreassoutente(cartaUtente[1], &counterassiutente);
    else sommacarteutente += cartaUtente[1].valore;    
    if(sommacarteutente == 21) printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
    printf(ANSI_COLOR_CYAN "\nIn totale hai %d" ANSI_COLOR_RESET, sommacarteutente);
    // terzo pezzo --> carte banco
    Sleep(1000);
    cartaComputer[0] = daicarte(carte, &dimensionedelmazzo, false); 
    cartaComputer[1] = daicarte(carte, &dimensionedelmazzo, false);
    stampacarta(cartaComputer[0], false);
    printf(ANSI_COLOR_MAGENTA "\nL'altra carta rimane nascosta." ANSI_COLOR_RESET);
    if (cartaComputer[0].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
    else sommacartecomputer += cartaComputer[0].valore;
    if (cartaComputer[1].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
    else sommacartecomputer += cartaComputer[1].valore;    
    if(sommacartecomputer == 21){
        Sleep(1000);
        stampacarta(cartaComputer[1], false);
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
        printf(ANSI_COLOR_RED "\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, -puntata);
        partiteperse++;
        return 1;
    } else if (sommacarteutente == 21){        
        if(sommacartecomputer == 21){
            Sleep(1000);
            stampacarta(cartaComputer[1], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
            printf(ANSI_COLOR_RED "\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, -puntata);
            partiteperse++;
            return 1;
        }
        else{
            Sleep(1000);
            stampacarta(cartaComputer[1], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
            continua = 0; 
        }
    } 
    // quarto pezzo --> chiedi carte
    while(continua > 0) {
        Sleep(1000);
        printf(ANSI_COLOR_CYAN "\n\nCosa vuoi fare?\n1 chiedi carta\n2 fermati\n-" ANSI_COLOR_RESET);
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                continua = 1;
                cartaUtente[counter] = daicarte(carte, &dimensionedelmazzo, true);
                stampacarta(cartaUtente[counter], true);
                if (cartaUtente[counter].valore == 1) sommacarteutente += sceglivaloreassoutente(cartaUtente[counter], &counterassiutente);
                else sommacarteutente += cartaUtente[counter].valore;
                printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, sommacarteutente);
                if(sommacarteutente > 21){
                    Sleep(1000);
                    printf(ANSI_COLOR_RED "\n\nHai sballato, hai perso" ANSI_COLOR_RESET);
                    aggiornaammontare(&contogiocatore, -puntata);
                    partiteperse++;
                    return 1;
                } else if(sommacarteutente == 21){
                    Sleep(1000);
                    printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
                    puntata = puntata + (puntata * 1,5);
                    continua = 0;
                }
            } break;
            case 2: {
                printf(ANSI_COLOR_YELLOW "\nTi sei fermato" ANSI_COLOR_RESET);
                if(counterassiutente > 0){
                    int valoretemp = 0; 
                    printf(ANSI_COLOR_YELLOW "\nHai degli assi da gestire" ANSI_COLOR_RESET);
                    for (int i = 0; i < counterassiutente; i++) {
                        valoretemp = sceglivaloreassoutente(cartaUtente[0], &counterassiutente);
                        if (valoretemp == 11) sommacarteutente += 10;
                        printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, sommacarteutente);                        
                    }
                    if(sommacarteutente > 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_RED "\n\nHai sballato, hai perso" ANSI_COLOR_RESET);
                        aggiornaammontare(&contogiocatore, -puntata);
                        partiteperse++;
                        return 1;
                    } else if(sommacarteutente == 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
                        puntata = puntata + (puntata * 1,5);
                        continua = 0;
                    }
                }
                continua = 0;
            } break;
            default: continua = 1;
                break;
        }
        counter++;
    }
    counter = 2;
    // quinto pezzo --> chiedi carte banco (da migliorare)
    Sleep(1000);
    stampacarta(cartaComputer[1], false);
    printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
    while(sommacartecomputer < sommacarteutente) {
        Sleep(1000);
        cartaComputer[counter] = daicarte(carte, &dimensionedelmazzo, false);
        stampacarta(cartaComputer[counter], false);
        if (cartaComputer[counter].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
        else sommacartecomputer += cartaComputer[counter].valore;    
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
    } 
    Sleep(1000);
    printf(ANSI_COLOR_MAGENTA "\n\nIl banco si ferma" ANSI_COLOR_RESET);
    if(sommacartecomputer > 21){
        Sleep(1000);
        printf(ANSI_COLOR_GREEN"\n\nIl banco ha sballato, hai vinto!" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, puntata);
        partitevinte++;
        return 1;
    }  
    else if(sommacartecomputer == 21){
        Sleep(1000);
        printf(ANSI_COLOR_RED "\n\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, -puntata);
        partiteperse++;
        return 1;   
    } 
    // sesto pezzo --> tirare le somme e vedere chi ha vinto
    Sleep(1000);
    printf(ANSI_COLOR_YELLOW "\n\nSomma delle tue carte: %d\nSomma delle carte del banco: %d" ANSI_COLOR_RESET, sommacarteutente, sommacartecomputer);
    if(sommacartecomputer > sommacarteutente){
        Sleep(1000);
        printf(ANSI_COLOR_RED "\n\nIl banco ha vinto" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, -puntata);
        partiteperse++;
        return 1;
    } else if (sommacarteutente > sommacartecomputer){
        Sleep(1000);
        printf(ANSI_COLOR_GREEN "\n\nHai vinto!" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, puntata);
        partitevinte++;
        return 1;
    } else if (sommacartecomputer == sommacarteutente){
        Sleep(1000);
        printf(ANSI_COLOR_RED "\n\nIl banco ha vinto, dato che vince anche in caso di pareggio" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, -puntata);
        partiteperse++;
        return 1;
    }
}

int sceglipuntata(){
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
    else if(puntatatemp > contogiocatore.ammontare) return -1;
    else return puntatatemp;
}