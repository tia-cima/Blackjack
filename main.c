//TODO split
//TODO even money
//TODO double
//TODO insurance

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "Carte.h"
#include "Conto.h"
#define ARRAY_DIMENSION 11
#define ANSI_COLOR_RED     "\x1b[31m" // sconfitta
#define ANSI_COLOR_GREEN   "\x1b[32m" // vittoria
#define ANSI_COLOR_YELLOW  "\x1b[33m" // info
#define ANSI_COLOR_MAGENTA "\x1b[35m" // banco
#define ANSI_COLOR_CYAN    "\x1b[36m" // utente
#define ANSI_COLOR_RESET   "\x1b[0m" // reset

int gioca();
int sceglipuntata();
int sceglivaloreassoutente(Carta valore, int* counterassiutente, bool isfermato);
int sceglivaloreassobanco(int sommacartecomputer);
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
int sommacarteutentesplit = 0;
int counterassiutentesplit = 0; 
bool isblackjack;
            // contogiocatore.ammontare = 1200;
bool isblackjacksplit;
bool issplit = false;
Carta carte[52];
Carta cartegiocatori[2][ARRAY_DIMENSION];
Carta* cartePtr = carte;
Conto contogiocatore;

int main() {
    srand(time(NULL));
    popolamazzo(carte);
    continua = 0; 
    counter = 2;
    printf("\n\n#########################\nBENVENUTO AL BLACKJACK!\n-'q' rappresenta le carte quadri\n-'p' rappresenta le carte picche\n-'c' rappresenta le carte cuori\n-'f' rappresenta le carte fiori" ANSI_COLOR_GREEN "\nIl colore verde rappresenta i messaggi di vittoria" ANSI_COLOR_RESET ANSI_COLOR_RED "\nIl colore rosso rappresenta i messaggi di sconfitta" ANSI_COLOR_RESET ANSI_COLOR_YELLOW "\nIl colore giallo rappresenta i messaggi di info" ANSI_COLOR_RESET ANSI_COLOR_CYAN "\nIl colore azzurro rappresenta le tue mosse" ANSI_COLOR_RESET ANSI_COLOR_MAGENTA "\nIl colore magenta rappresenta le mosse del banco" ANSI_COLOR_RESET "\nBuon divertimento!\n#########################\n");
    printf(ANSI_COLOR_YELLOW "\nPrima di cominciare, hai gia' un account o vuoi crearne uno nuovo? Ti servirà per riaccedere ai tuoi crediti anche in futuro\n1) Crea account\n2) Accedi ad account esistente (ID richiesto)\n-");
    int sceltaccount = 2;
    // scanf("%d", &sceltaccount);
    switch (sceltaccount) {
        case 1:{
            impostaconto(&contogiocatore); 
            printf(ANSI_COLOR_YELLOW "\nBenvenuto giocatore %d, hai caricato %d euro. Buona fortuna!" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
        } break;
        case 2:{
            // recuperaconto(&contogiocatore); 
            contogiocatore.id = 1;
            contogiocatore.ammontare = 1500;
            printf(ANSI_COLOR_YELLOW "\nBentornato %d! Il tuo conto e' di %d. Vuoi ricaricarlo o procedere con questo quantitativo?\n1) Ricarica\n2) Non ricaricare\n-" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
            int procedi = 2;
            // scanf("%d", &procedi);
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
    puntata = 0;
    isblackjack = false;
    isblackjacksplit = false;
    issplit = false; 
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
    // puntata = sceglipuntata();
    puntata = 50;
    if(puntata != -1){
        printf(ANSI_COLOR_YELLOW "\nHai scelto di puntare %d euro\n" ANSI_COLOR_RESET, puntata);
        aggiornaammontare(&contogiocatore, -puntata);
    } else {
        printf(ANSI_COLOR_RED "\nScelta non valida. \nHai selezionato un valore non valido oppure hai finito i crediti" ANSI_COLOR_RESET);
        return 1;
    }
    // secondo pezzo --> carte utente
    cartegiocatori[0][0] = daicarte(carte, &dimensionedelmazzo, true); 
    cartegiocatori[0][1] = daicarte(carte, &dimensionedelmazzo, true);
    stampacarta(cartegiocatori[0][0], true);
    stampacarta(cartegiocatori[0][1], true);    
    if(cartegiocatori[0][0].valore == cartegiocatori[0][1].valore && contogiocatore.ammontare >= puntata * 2){
        printf(ANSI_COLOR_CYAN "\nHai la possibilita' di splittare. Vuoi splittare le tue carte? Dovrai puntare la stessa puntata iniziale.\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
        int sceltasplit = 1;
        // scanf("%d", &sceltasplit);
        switch (sceltasplit)
        {
            case 1:{
                aggiornaammontare(&contogiocatore, -puntata);
                issplit = true;
                if (cartegiocatori[0][0].valore == 1 && cartegiocatori[0][1].valore == 1) {
                    sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][0], &counterassiutente, false);
                    cartegiocatori[0][1] = daicarte(carte, &dimensionedelmazzo, true);
                    if (cartegiocatori[0][1].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][1], &counterassiutente, false);
                    else sommacarteutente += cartegiocatori[0][1].valore;  
                    stampacarta(cartegiocatori[0][0], true);
                    stampacarta(cartegiocatori[0][1], true);    
                    printf(ANSI_COLOR_CYAN "\nSomma primo mazzo: %d" ANSI_COLOR_RESET, sommacarteutente);
                    printf(ANSI_COLOR_CYAN "\nSomma secondo mazzo: %d" ANSI_COLOR_RESET, sommacarteutentesplit);                   
                } else {
                    sommacarteutente = cartegiocatori[0][0].valore;                    
                    cartegiocatori[0][1] = daicarte(carte, &dimensionedelmazzo, true);
                    if (cartegiocatori[0][1].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][1], &counterassiutente, false);
                    else sommacarteutente += cartegiocatori[0][1].valore;    
                    stampacarta(cartegiocatori[0][0], true);
                    stampacarta(cartegiocatori[0][1], true);    
                    printf(ANSI_COLOR_CYAN "\nSomma primo mazzo: %d" ANSI_COLOR_RESET, sommacarteutente);
                    printf(ANSI_COLOR_CYAN "\nSomma secondo mazzo: %d" ANSI_COLOR_RESET, sommacarteutentesplit);                   
                }
            }
            break;
            case 2: {
                if (cartegiocatori[0][0].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][0], &counterassiutente, false);
                else sommacarteutente += cartegiocatori[0][0].valore;
                if (cartegiocatori[0][1].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][1], &counterassiutente, false);
                else sommacarteutente += cartegiocatori[0][1].valore;    
                if(sommacarteutente == 21) printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
                printf(ANSI_COLOR_CYAN "\nIn totale hai %d" ANSI_COLOR_RESET, sommacarteutente);
            }
            break;
            default:
            break;
        }
    } else {
        if (cartegiocatori[0][0].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][0], &counterassiutente, false);
        else sommacarteutente += cartegiocatori[0][0].valore;
        if (cartegiocatori[0][1].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][1], &counterassiutente, false);
        else sommacarteutente += cartegiocatori[0][1].valore;    
        if(sommacarteutente == 21) printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_MAGENTA);
        printf(ANSI_COLOR_CYAN "\nIn totale hai %d" ANSI_COLOR_RESET, sommacarteutente);
    }
    // terzo pezzo --> carte banco
    Sleep(1000);
    cartegiocatori[1][0] = daicarte(carte, &dimensionedelmazzo, false); 
    cartegiocatori[1][0] = daicarte(carte, &dimensionedelmazzo, false);
    stampacarta(cartegiocatori[1][0], false);
    printf(ANSI_COLOR_MAGENTA "\nL'altra carta rimane nascosta." ANSI_COLOR_RESET);
    if (cartegiocatori[1][0].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
    else sommacartecomputer += cartegiocatori[1][0].valore;
    if (cartegiocatori[1][0].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
    else sommacartecomputer += cartegiocatori[1][0].valore;    
    if(sommacartecomputer == 21){
        Sleep(1000);
        stampacarta(cartegiocatori[1][0], false);
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
        printf(ANSI_COLOR_RED "\n\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, -puntata);
        partiteperse++;
        return 1;
    } else if (sommacarteutente == 21){        
        if(sommacartecomputer == 21){
            Sleep(1000);
            stampacarta(cartegiocatori[1][0], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
            printf(ANSI_COLOR_RED "\n\nIl banco ha fatto blackjack, hai perso" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, -puntata);
            partiteperse++;
            return 1;
        }
        else{
            Sleep(1000);
            isblackjack = true;
            continua = 0; 
        }
    } 
    // quarto pezzo --> chiedi carte
    if(issplit){
        printf(ANSI_COLOR_YELLOW "\n\nMAZZO 1" ANSI_COLOR_RESET);
        while(continua > 0) {
            Sleep(1000);
            printf(ANSI_COLOR_CYAN "\n\nCosa vuoi fare?\n1) Chiedi carta\n2) Fermati\n-" ANSI_COLOR_RESET);
            scanf("%d", &scelta);
            switch (scelta) {
                case 1: {
                    continua = 1;
                    cartegiocatori[0][counter] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[0][counter], true);
                    if (cartegiocatori[0][counter].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][counter], &counterassiutente, false);
                    else sommacarteutente += cartegiocatori[0][counter].valore;
                    printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, sommacarteutente);
                    if(sommacarteutente > 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_RED "\n\nIl primo mazzo ha sballato, perdi la puntata" ANSI_COLOR_RESET);
                        aggiornaammontare(&contogiocatore, -puntata);
                        continua = 0;                   
                    } else if(sommacarteutente == 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_CYAN "\nHai fatto blackjack sul primo mazzo. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_RESET);
                        isblackjack = true;     
                        continua = 0;
                    }
                } break;
                case 2: {
                    printf(ANSI_COLOR_YELLOW "\nTi sei fermato" ANSI_COLOR_RESET);
                    if(counterassiutente > 0){
                        int valoretemp = 0; 
                        printf(ANSI_COLOR_YELLOW "\nHai degli assi da gestire" ANSI_COLOR_RESET);
                        for (int i = 0; i < counterassiutente; i++) {
                            valoretemp = sceglivaloreassoutente(cartegiocatori[0][0], &counterassiutente, true);
                            if (valoretemp == 11) sommacarteutente += 10;
                            printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, sommacarteutente);                        
                        }
                        if(sommacarteutente > 21){
                            Sleep(1000);
                            printf(ANSI_COLOR_RED "\n\nIl primo mazzo ha sballato, perdi la puntata" ANSI_COLOR_RESET);
                            aggiornaammontare(&contogiocatore, -puntata);
                            continua = 0;
                        } else if(sommacarteutente == 21){
                            Sleep(1000);
                            printf(ANSI_COLOR_CYAN "\nHai fatto blackjack sul primo mazzo. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_RESET);
                            isblackjack = true;     
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
        continua = 1;
        printf(ANSI_COLOR_YELLOW "\n\nMAZZO 2" ANSI_COLOR_RESET);
    } else {
        while(continua > 0) {
            Sleep(1000);
            printf(ANSI_COLOR_CYAN "\n\nCosa vuoi fare?\n1) Chiedi carta\n2) Fermati\n-" ANSI_COLOR_RESET);
            scanf("%d", &scelta);
            switch (scelta) {
                case 1: {
                    continua = 1;
                    cartegiocatori[0][counter] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[0][counter], true);
                    if (cartegiocatori[0][counter].valore == 1) sommacarteutente += sceglivaloreassoutente(cartegiocatori[0][counter], &counterassiutente, false);
                    else sommacarteutente += cartegiocatori[0][counter].valore;
                    printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, sommacarteutente);
                    if(sommacarteutente > 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_RED "\n\nHai sballato, hai perso" ANSI_COLOR_RESET);
                        aggiornaammontare(&contogiocatore, -puntata);
                        partiteperse++;
                        return 1;
                    } else if(sommacarteutente == 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_RESET);
                        isblackjack = true;
                        continua = 0;
                    }
                } break;
                case 2: {
                    printf(ANSI_COLOR_YELLOW "\nTi sei fermato" ANSI_COLOR_RESET);
                    if(counterassiutente > 0){
                        int valoretemp = 0; 
                        printf(ANSI_COLOR_YELLOW "\nHai degli assi da gestire" ANSI_COLOR_RESET);
                        for (int i = 0; i < counterassiutente; i++) {
                            valoretemp = sceglivaloreassoutente(cartegiocatori[0][0], &counterassiutente, true);
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
                            printf(ANSI_COLOR_CYAN "\nHai fatto blackjack. Attendi il risultato del banco per vedere se hai vinto" ANSI_COLOR_RESET);
                            isblackjack = true;     
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
    }
    counter = 2;
    // quinto pezzo --> chiedi carte banco
    Sleep(1000);
    stampacarta(cartegiocatori[1][0], false);
    printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
    while(sommacartecomputer < 17) {
        Sleep(1000);
        cartegiocatori[1][counter] = daicarte(carte, &dimensionedelmazzo, false);
        stampacarta(cartegiocatori[1][counter], false);
        if (cartegiocatori[1][counter].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
        else sommacartecomputer += cartegiocatori[1][counter].valore;    
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
    } 
    Sleep(1000);
    if(issplit){
        while (sommacartecomputer < sommacarteutente || sommacartecomputer < sommacarteutentesplit){
            Sleep(1000);
            cartegiocatori[1][counter] = daicarte(carte, &dimensionedelmazzo, false);
            stampacarta(cartegiocatori[1][counter], false);
            if (cartegiocatori[1][counter].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
            else sommacartecomputer += cartegiocatori[1][counter].valore;    
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
        }
    } else{
        while (sommacartecomputer < sommacarteutente){
            Sleep(1000);
            cartegiocatori[1][counter] = daicarte(carte, &dimensionedelmazzo, false);
            stampacarta(cartegiocatori[1][counter], false);
            if (cartegiocatori[1][counter].valore == 1) sommacartecomputer += sceglivaloreassobanco(sommacartecomputer);
            else sommacartecomputer += cartegiocatori[1][counter].valore;    
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, sommacartecomputer);
        }
    }
    if(sommacartecomputer > 21){
        Sleep(1000);
        printf(ANSI_COLOR_GREEN"\n\nIl banco ha sballato, hai vinto!" ANSI_COLOR_RESET);
        if(isblackjack) aggiornaammontare(&contogiocatore, (puntata * 1.5));
        else aggiornaammontare(&contogiocatore, puntata);
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
    printf(ANSI_COLOR_MAGENTA "\n\nIl banco si ferma" ANSI_COLOR_RESET);
    // sesto pezzo --> tirare le somme e vedere chi ha vinto
    Sleep(1000);
    if(issplit){
        printf(ANSI_COLOR_YELLOW "\n\nSomma delle tue carte: Mazzo 1: %d\tMazzo 2: %d\nSomma delle carte del banco: %d" ANSI_COLOR_RESET, sommacarteutente, sommacarteutentesplit, sommacartecomputer);
        if(sommacartecomputer > sommacarteutente && sommacartecomputer > sommacarteutentesplit){
            Sleep(1000);
            printf(ANSI_COLOR_RED "\n\nIl banco ha vinto" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, -(puntata * 2));
            partiteperse++;
            return 1;
        } else if (sommacartecomputer < sommacarteutente && sommacartecomputer < sommacarteutentesplit) {
            Sleep(1000);
            printf(ANSI_COLOR_GREEN "\n\nComplimenti, hai vinto con entrambi i mazzi" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, (puntata * 2));
            partitevinte++;
            return 1;
        } else if (sommacartecomputer == sommacarteutente && sommacartecomputer == sommacarteutentesplit){
            Sleep(1000);
            printf(ANSI_COLOR_GREEN "\n\nHai pareggiato con tutte e due i mazzi con il banco, le tue puntate ti verranno restituite ma non vinci niente" ANSI_COLOR_RESET);
            return 1;
        } 

        if (sommacartecomputer > sommacarteutente){
            Sleep(1000);
            printf(ANSI_COLOR_RED "\n\nIl primo mazzo ha perso" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, -puntata);
        } else if(sommacartecomputer < sommacarteutente){
            Sleep(1000);
            printf(ANSI_COLOR_GREEN "\n\nIl primo mazzo ha vinto" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, puntata);
        } else if(sommacartecomputer == sommacarteutente){
            Sleep(1000);
            printf(ANSI_COLOR_GREEN "\n\nIl primo mazzo ha pareggiato" ANSI_COLOR_RESET);
        }

        if(sommacartecomputer > sommacarteutentesplit){
            Sleep(1000);
            printf(ANSI_COLOR_RED "\n\nIl secondo mazzo ha perso" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, -puntata);
        } 
        if(sommacartecomputer < sommacarteutentesplit){
            Sleep(1000);
            printf(ANSI_COLOR_GREEN "\n\nIl secondo mazzo ha vinto" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, puntata);
        }
        if(sommacartecomputer == sommacarteutentesplit){
            Sleep(1000);
            printf(ANSI_COLOR_GREEN "\n\nIl secondo mazzo ha pareggiato" ANSI_COLOR_RESET);  
        }
        return 1;
    } else{    
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
            if(isblackjack) aggiornaammontare(&contogiocatore, (puntata * 1.5));
            else aggiornaammontare(&contogiocatore, puntata);
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

int sceglivaloreassoutente(Carta valore, int* counterassiutente, bool isfermato){
    if(isfermato){
         printf(ANSI_COLOR_CYAN "\nVuoi scegliere di usarlo come 1 o come 11?\n1) 1\n2) 11\n-" ANSI_COLOR_RESET);
        int sceltaasso = 0; 
        scanf("%d", &sceltaasso);
        switch (sceltaasso) {
            case 1:
                return 1;
            case 2:
                return 11;
            default:
                return 1;
        }      
    } else {
        printf(ANSI_COLOR_CYAN "\nE' uscito un asso. Vuoi scegliere di usarlo come 1, come 11 o decidere dopo?\n1) 1\n2) 11\n3) decidi dopo\n-" ANSI_COLOR_RESET);
        int sceltaasso = 0; 
        scanf("%d", &sceltaasso);
        switch (sceltaasso) {
            case 1:
                return 1;
            case 2:
                return 11;
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
