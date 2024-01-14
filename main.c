#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "Carte.h"
#include "Conto.h"
#include "Blackjack.h"
#define ARRAY_DIMENSION 11
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int gioca();
int* somme;
int* assi;
int scelta;
int sceltasplit = 1;
int dimensionedelmazzo = 52;
int puntata;
int righecartegiocatore = 1;
int assisplit = 0;
int soldiiniziali = 0; 
bool continua = true;
bool* raddoppia; 
bool issplit = false;
Carta carte[52];
Carta** cartegiocatori;
Conto contogiocatore;

int main() {
    srand(time(NULL));
    popolamazzo(carte);
    printf("\n\n#########################\nBENVENUTO AL BLACKJACK!\n-'q' rappresenta le carte quadri\n-'p' rappresenta le carte picche\n-'c' rappresenta le carte cuori\n-'f' rappresenta le carte fiori" ANSI_COLOR_GREEN "\nIl colore verde rappresenta i messaggi di vittoria" ANSI_COLOR_RESET ANSI_COLOR_RED "\nIl colore rosso rappresenta i messaggi di sconfitta" ANSI_COLOR_RESET ANSI_COLOR_YELLOW "\nIl colore giallo rappresenta i messaggi di info" ANSI_COLOR_RESET ANSI_COLOR_CYAN "\nIl colore azzurro rappresenta le tue mosse" ANSI_COLOR_RESET ANSI_COLOR_MAGENTA "\nIl colore magenta rappresenta le mosse del banco" ANSI_COLOR_RESET "\nBuon divertimento!\n#########################\n");
    printf(ANSI_COLOR_YELLOW "\nPrima di cominciare, hai gia' un account o vuoi crearne uno nuovo? Ti servirà per riaccedere ai tuoi crediti anche in futuro\n1) Crea account\n2) Accedi ad account esistente (ID richiesto)\n-" ANSI_COLOR_RESET);
    int sceltaccount = 0;
    scanf("%d", &sceltaccount);
    switch (sceltaccount) {
        case 1:{
            impostaconto(&contogiocatore); 
            printf(ANSI_COLOR_YELLOW "\nBenvenuto giocatore %d, hai caricato %d euro. Buona fortuna!" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
        } break;
        case 2:{
            recuperaconto(&contogiocatore); 
            printf(ANSI_COLOR_YELLOW "\nBentornato %d! Il tuo conto e' di %d. Vuoi ricaricarlo o procedere con questo quantitativo?\n1) Ricarica\n2) Non ricaricare\n-" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
            int procedi = 0;
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
                    break;
                default:{
                    printf(ANSI_COLOR_YELLOW "\nBuona fortuna!" ANSI_COLOR_RESET);
                }
                    break;
            }
        } break;
        default:{
            impostaconto(&contogiocatore); 
            printf(ANSI_COLOR_YELLOW "\nBenvenuto giocatore %d, hai caricato %d euro. Buona fortuna!" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
        } break;
    }            
    while(1) gioca();   
    return 0;
}

int gioca(){     
    free(cartegiocatori);
    free(somme);
    free(assi);
    free(raddoppia);
    issplit = false;
    righecartegiocatore = 1;    
    puntata = 0;
    assisplit = 0;
    continua = true;
    somme = (int *)malloc((righecartegiocatore + 1) * sizeof(int));  
    for(int i = 0; i < (righecartegiocatore + 1); i++)    somme[i] = 0;
    raddoppia = (bool *)malloc((righecartegiocatore + 1) * sizeof(bool));  
    for(int i = 0; i < (righecartegiocatore + 1); i++)    raddoppia[i] = false;
    assi = (int *)malloc((righecartegiocatore + 1) * sizeof(int));  
    for(int i = 0; i < (righecartegiocatore + 1); i++)    assi[i] = 0;
    cartegiocatori = (Carta **)malloc((righecartegiocatore + 1) * sizeof(Carta *));
    for (int i = 0; i < (righecartegiocatore + 1); i++) cartegiocatori[i] = (Carta *)malloc(ARRAY_DIMENSION * sizeof(Carta));    
    Sleep(2000);
    printf(ANSI_COLOR_YELLOW "\n\n#########################\nComincio una nuova partita\nSaldo attuale: %d euro\n#########################\n" ANSI_COLOR_RESET, contogiocatore.ammontare);
    if(contogiocatore.ammontare <= 0) {
        printf(ANSI_COLOR_YELLOW "\nHai terminato i crediti. Aggiorna il tuo conto.\nQuanto vuoi caricare?\n-" ANSI_COLOR_RESET);
        int valorefinito;
        scanf("%d", &valorefinito);
        aggiornaammontare(&contogiocatore, valorefinito);
        printf(ANSI_COLOR_YELLOW "\nHai con successo aggiornato il conto" ANSI_COLOR_RESET);
    }
    soldiiniziali = contogiocatore.ammontare;
    // primo pezzo --> scelta puntata
    puntata = sceglipuntata(&contogiocatore);
    if(puntata != -1){
        printf(ANSI_COLOR_YELLOW "\nHai scelto di puntare %d euro\n" ANSI_COLOR_RESET, puntata);
        aggiornaammontare(&contogiocatore, -puntata);
    } else {
        printf(ANSI_COLOR_RED "\nScelta non valida. \nHai selezionato un valore non valido oppure hai finito i crediti" ANSI_COLOR_RESET);
        return 1;
    }
    printf(ANSI_COLOR_YELLOW "\n#########################\nSaldo aggiornato: %d euro" ANSI_COLOR_RESET, contogiocatore.ammontare);
    printf(ANSI_COLOR_GREEN "\nPotenziali vincite:\nNormale: %d euro\nRaddoppio: %d euro\nDoppio split: %d euro\nDoppio split con due raddoppi: %d euro\nTriplo split: %d euro\nTriplo split con tre raddoppi: %d euro\nQuadruplo split: %d euro\nVINCITA MASSIMA: Quadruplo split con 4 raddoppi: %d euro" ANSI_COLOR_RESET, puntata, puntata * 2, puntata * 2, puntata * 4, puntata * 3, puntata * 6, puntata * 4, puntata * 8);
    printf(ANSI_COLOR_YELLOW "\n#########################\n" ANSI_COLOR_RESET);
    // secondo pezzo --> distribuzione delle carte
    cartegiocatori[1][0] = daicarte(carte, &dimensionedelmazzo, true); 
    cartegiocatori[1][1] = daicarte(carte, &dimensionedelmazzo, true);
    stampacarta(cartegiocatori[1][0], true);
    stampacarta(cartegiocatori[1][1], true);    
    Sleep(1000);
    cartegiocatori[0][0] = daicarte(carte, &dimensionedelmazzo, false); 
    cartegiocatori[0][1] = daicarte(carte, &dimensionedelmazzo, false);
    stampacarta(cartegiocatori[0][0], false);
    if(cartegiocatori[0][0].valore == 1 && ((cartegiocatori[1][0].valore == 1 && cartegiocatori[1][1].valore == 10) || (cartegiocatori[1][0].valore == 10 && cartegiocatori[1][1].valore == 1)))    {
        printf(ANSI_COLOR_YELLOW "\n\nHai fatto blackjack, mentre il banco ha un asso. Il banco ti offre di interrompere ora la partita vincendo l'importo della tua puntata. Vuoi farlo?\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
        int sceltaeven;
        scanf("%d", &sceltaeven);
        if(sceltaeven == 1){
            stampacarta(cartegiocatori[0][1], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            int puntatatemp = puntata * 2;
            aggiornaammontare(&contogiocatore, puntatatemp);
            if(cartegiocatori[0][1].valore == 10) printf(ANSI_COLOR_GREEN "\nIl banco ha fatto blackjack, ma fortunatamente hai accettato la sua proposta. Hai vinto %d euro" ANSI_COLOR_RESET, puntatatemp);
            else printf(ANSI_COLOR_GREEN "\nIl banco non ha fatto blackjack, ma accettando la sua proposta hai vinto %d euro" ANSI_COLOR_RESET, puntatatemp);
            return 1;
        }
    } else if(cartegiocatori[0][0].valore == 1){
        printf(ANSI_COLOR_YELLOW "\n\nAttenzione! Il banco ha un asso come prima carta. Vuoi procedere con l'assicurazione?\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
        int sceltassicurazione;
        scanf("%d", &sceltassicurazione);
        if(sceltassicurazione == 1){
            int puntatatemp = puntata / 2;
            aggiornaammontare(&contogiocatore, -puntatatemp);
            printf(ANSI_COLOR_YELLOW "\nSaldo aggiornato: %d euro \n" ANSI_COLOR_RESET, contogiocatore.ammontare);
            if(cartegiocatori[0][1].valore == 10){
                stampacarta(cartegiocatori[0][1], false);
                printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_MAGENTA "\nIl banco ha fatto blackjack. Complimenti per aver acquistato l'assicurazione, ti vengono restituiti %d euro" ANSI_COLOR_RESET, (puntatatemp + puntata));
                Sleep(2000);
                aggiornaammontare(&contogiocatore, (puntatatemp + puntata));
                return 1;
            } else {
                printf(ANSI_COLOR_YELLOW "\nIl banco non ha un 10, percio' non potra' fare blackjack. Perdi %d euro" ANSI_COLOR_RESET, puntatatemp);
            }
        }
    }
    if (((cartegiocatori[1][0].valore == 1 && cartegiocatori[1][1].valore == 10) || (cartegiocatori[1][0].valore == 10 && cartegiocatori[1][1].valore == 1)) && ((cartegiocatori[0][0].valore == 1 && cartegiocatori[0][1].valore == 10) || (cartegiocatori[0][0].valore == 10 && cartegiocatori[0][1].valore == 1))) {
        Sleep(1000);
        stampacarta(cartegiocatori[0][1], false);
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_YELLOW "\n\nAvete entrambi fatto blackjack, ti vengono restituiti %d euro" ANSI_COLOR_RESET, puntata);
        aggiornaammontare(&contogiocatore, puntata);
        return 1;
    }
    if ((cartegiocatori[0][0].valore == 1 && cartegiocatori[0][1].valore == 10) || (cartegiocatori[0][0].valore == 10 && cartegiocatori[0][1].valore == 1)) {
        Sleep(1000);
        stampacarta(cartegiocatori[0][1], false);
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_RED "\n\nIl banco ha fatto blackjack, hai perso %d euro" ANSI_COLOR_RESET, puntata);
        return 1;
    } 
    if ((cartegiocatori[1][0].valore == 1 && cartegiocatori[1][1].valore == 10) || (cartegiocatori[1][0].valore == 10 && cartegiocatori[1][1].valore == 1)) {
        Sleep(1000);
        stampacarta(cartegiocatori[0][1], false);
        int puntatatemp = (puntata + (puntata * 1.5));
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "\n\nHai fatto blackjack, hai vinto %d euro" ANSI_COLOR_RESET, puntatatemp);
        aggiornaammontare(&contogiocatore, puntatatemp);   
        return 1;    
    } 
    printf(ANSI_COLOR_MAGENTA "\nL'altra carta rimane nascosta." ANSI_COLOR_RESET);
    if (cartegiocatori[0][0].valore == 1) somme[0] += sceglivaloreassobanco(somme[0]);
    else somme[0] += cartegiocatori[0][0].valore;
    if (cartegiocatori[0][1].valore == 1) somme[0] += sceglivaloreassobanco(somme[0]);
    else somme[0] += cartegiocatori[0][1].valore;    
    //terzo step --> split
    sceltasplit = 2;
    if(cartegiocatori[1][0].valore == cartegiocatori[1][1].valore && (contogiocatore.ammontare >= puntata)){
        printf(ANSI_COLOR_YELLOW "\n\nHai la possibilita' di splittare. Vuoi splittare le tue carte? Dovrai puntare la stessa puntata iniziale.\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
        scanf("%d", &sceltasplit);
        if(sceltasplit == 1){
            issplit = true;
            aggiornaammontare(&contogiocatore, -puntata);
            printf(ANSI_COLOR_YELLOW "\nSaldo aggiornato: %d euro\n" ANSI_COLOR_RESET, contogiocatore.ammontare);
            righecartegiocatore++;               
            somme = realloc(somme, (3) * sizeof(int));
            somme[2] = 0;
            assi = realloc(assi, (3) * sizeof(int));
            assi[2] = 0;
            cartegiocatori = realloc(cartegiocatori, (3) * sizeof(Carta *));
            cartegiocatori[2] = malloc(ARRAY_DIMENSION * sizeof(Carta));
            cartegiocatori[2][0] = cartegiocatori[1][1]; 
            printf(ANSI_COLOR_YELLOW "\nMazzo numero 1" ANSI_COLOR_RESET);
            cartegiocatori[1][1] = daicarte(carte, &dimensionedelmazzo, true);    
            stampacarta(cartegiocatori[1][0], true);
            stampacarta(cartegiocatori[1][1], true);
            somme[1] = cartegiocatori[1][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[1][0], &assi[1], false, somme[1]) : cartegiocatori[1][0].valore;
            somme[1] += cartegiocatori[1][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[1][1], &assi[1], false, somme[1]) : cartegiocatori[1][1].valore;
            printf(ANSI_COLOR_YELLOW "\nSomma mazzo 1: %d\n" ANSI_COLOR_RESET, somme[1]);
            printf(ANSI_COLOR_YELLOW "\nMazzo numero 2" ANSI_COLOR_RESET);
            cartegiocatori[2][1] = daicarte(carte, &dimensionedelmazzo, true);
            stampacarta(cartegiocatori[2][0], true);
            stampacarta(cartegiocatori[2][1], true);
            somme[2] = cartegiocatori[2][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[2][0], &assi[2], false, somme[2]) : cartegiocatori[2][0].valore;
            somme[2] += cartegiocatori[2][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[2][1], &assi[2], false, somme[2]) : cartegiocatori[2][1].valore;
            printf(ANSI_COLOR_YELLOW "\nSomma mazzo 2: %d\n" ANSI_COLOR_RESET, somme[2]);
        } else sceltasplit = 2; 
    } 
    if (sceltasplit > 1) {
        if (cartegiocatori[1][0].valore == 1) somme[1] += sceglivaloreassoutente(&cartegiocatori[1][0], &assi[1], false, somme[1]);
        else somme[1] += cartegiocatori[1][0].valore;
        if (cartegiocatori[1][1].valore == 1) somme[1] += sceglivaloreassoutente(&cartegiocatori[1][1], &assi[1], false, somme[1]);
        else somme[1] += cartegiocatori[1][1].valore;    
        printf(ANSI_COLOR_CYAN "\n\nIn totale hai %d" ANSI_COLOR_RESET, somme[1]);
        continua = false;
    } 
    Sleep(1000);
    if(issplit){
        bool mano1 = false;
        bool mano2 = false;
        bool mano3 = false;
        if ((cartegiocatori[1][0].valore == cartegiocatori[1][1].valore) && (cartegiocatori[2][0].valore == cartegiocatori[2][1].valore)){
            printf(ANSI_COLOR_YELLOW "\n\nHai la possibilita' di splittare. Vuoi splittare le tue carte? Dovrai puntare la stessa puntata iniziale.\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
            scanf("%d", &sceltasplit);
            if(sceltasplit == 1){
                cartegiocatori = realloc(cartegiocatori, (4) * sizeof(Carta *));
                cartegiocatori[3] = malloc(ARRAY_DIMENSION * sizeof(Carta));
                somme = realloc(somme, (4) * sizeof(int));
                somme[3] = 0;
                assi = realloc(assi, (4) * sizeof(int));
                assi[3] = 0;
                raddoppia = realloc(raddoppia, (3) * sizeof(bool));
                raddoppia[2] = false;
                aggiornaammontare(&contogiocatore, -puntata);
                printf(ANSI_COLOR_YELLOW "\nSaldo aggiornato: %d euro\n" ANSI_COLOR_RESET, contogiocatore.ammontare);
                righecartegiocatore++;
                printf(ANSI_COLOR_YELLOW "\nQuale mazzo vuoi splittare?\n1) 1\n2) 2\n3) Entrambi\n-" ANSI_COLOR_RESET);
                int sceltamazzosplit;
                scanf("%d", &sceltamazzosplit);
                switch (sceltamazzosplit)
                {
                case 1:{
                    mano1 = true;
                    mano3 = true;
                }
                    break;
                case 2:{
                    mano2 = true;
                    mano3 = true;
                }
                    break;
                case 3: {
                    righecartegiocatore++;
                    cartegiocatori = realloc(cartegiocatori, (5) * sizeof(Carta *));
                    cartegiocatori[4] = malloc(ARRAY_DIMENSION * sizeof(Carta));
                    somme = realloc(somme, (5) * sizeof(int));
                    somme[4] = 0;
                    assi = realloc(assi, (5) * sizeof(int));
                    assi[4] = 0;
                    raddoppia = realloc(raddoppia, (4) * sizeof(bool));
                    raddoppia[3] = false;
                    aggiornaammontare(&contogiocatore, -puntata);
                    printf(ANSI_COLOR_YELLOW "\nMazzo numero 1" ANSI_COLOR_RESET);
                    cartegiocatori[3][0] = cartegiocatori[1][1];
                    cartegiocatori[1][1] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[1][0], true);
                    stampacarta(cartegiocatori[1][1], true);
                    somme[1] = cartegiocatori[1][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[1][0], &assi[1], false, somme[1]) : cartegiocatori[1][0].valore;
                    somme[1] += cartegiocatori[1][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[1][1], &assi[1], false, somme[1]) : cartegiocatori[1][1].valore;
                    printf(ANSI_COLOR_YELLOW "\nSomma mazzo 1: %d\n" ANSI_COLOR_RESET, somme[1]);
                    printf(ANSI_COLOR_YELLOW "\nMazzo numero 3" ANSI_COLOR_RESET);
                    cartegiocatori[3][1] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[3][0], true);
                    stampacarta(cartegiocatori[3][1], true);                
                    somme[3] = cartegiocatori[3][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[3][0], &assi[3], false, somme[3]) : cartegiocatori[3][0].valore;
                    somme[3] += cartegiocatori[3][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[3][1], &assi[3], false, somme[3]) : cartegiocatori[3][1].valore;
                    printf(ANSI_COLOR_YELLOW "\nSomma mazzo 3: %d\n" ANSI_COLOR_RESET, somme[3]);           
                    printf(ANSI_COLOR_YELLOW "\nMazzo numero 2" ANSI_COLOR_RESET);
                    cartegiocatori[4][0] = cartegiocatori[2][1];
                    cartegiocatori[2][1] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[2][0], true);
                    stampacarta(cartegiocatori[2][1], true);
                    somme[2] = cartegiocatori[2][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[2][0], &assi[2], false, somme[2]) : cartegiocatori[2][0].valore;
                    somme[2] += cartegiocatori[2][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[2][1], &assi[2], false, somme[2]) : cartegiocatori[2][1].valore;
                    printf(ANSI_COLOR_YELLOW "\nSomma mazzo 2: %d\n" ANSI_COLOR_RESET, somme[2]);    
                    printf(ANSI_COLOR_YELLOW "\nMazzo numero 4" ANSI_COLOR_RESET);
                    cartegiocatori[4][1] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[4][0], true);
                    stampacarta(cartegiocatori[4][1], true);                
                    somme[4] = cartegiocatori[4][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[4][0], &assi[4], false, somme[4]) : cartegiocatori[4][0].valore;
                    somme[4] += cartegiocatori[4][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[4][1], &assi[4], false, somme[4]) : cartegiocatori[4][1].valore;
                    printf(ANSI_COLOR_YELLOW "\nSomma mazzo 4: %d\n" ANSI_COLOR_RESET, somme[4]);                
                }
                default: {
                    mano1 = true;
                    mano3 = true;
                }
                    break;
                }
            }           
        }
        else if((cartegiocatori[1][0].valore == cartegiocatori[1][1].valore) || (cartegiocatori[2][0].valore == cartegiocatori[2][1].valore)){
            printf(ANSI_COLOR_YELLOW "\n\nHai la possibilita' di splittare. Vuoi splittare le tue carte? Dovrai puntare la stessa puntata iniziale.\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
            scanf("%d", &sceltasplit);
            if(sceltasplit == 1){
                cartegiocatori = realloc(cartegiocatori, (4) * sizeof(Carta *));
                cartegiocatori[3] = malloc(ARRAY_DIMENSION * sizeof(Carta));
                somme = realloc(somme, (4) * sizeof(int));
                assi = realloc(assi, (4) * sizeof(int));
                raddoppia = realloc(assi, (3) * sizeof(bool));
                aggiornaammontare(&contogiocatore, -puntata);
                printf(ANSI_COLOR_YELLOW "\nSaldo aggiornato: %d euro\n" ANSI_COLOR_RESET, contogiocatore.ammontare);
                righecartegiocatore++;
                if(cartegiocatori[1][0].valore == cartegiocatori[1][1].valore) mano1 = true;
                else if(cartegiocatori[2][0].valore == cartegiocatori[2][1].valore) mano2 = true;
                mano3 = true;
            }
        } 
        if (mano1) {
            printf(ANSI_COLOR_YELLOW "\nMazzo numero 1" ANSI_COLOR_RESET);
            cartegiocatori[3][0] = cartegiocatori[1][1];
            cartegiocatori[1][1] = daicarte(carte, &dimensionedelmazzo, true);
            stampacarta(cartegiocatori[1][0], true);
            stampacarta(cartegiocatori[1][1], true);
            somme[1] = cartegiocatori[1][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[1][0], &assi[1], false, somme[1]) : cartegiocatori[1][0].valore;
            somme[1] += cartegiocatori[1][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[1][1], &assi[1], false, somme[1]) : cartegiocatori[1][1].valore;
            printf(ANSI_COLOR_YELLOW "\nSomma mazzo 1: %d\n" ANSI_COLOR_RESET, somme[1]);
        }
        if (mano2) {
            printf(ANSI_COLOR_YELLOW "\nMazzo numero 2" ANSI_COLOR_RESET);
            cartegiocatori[3][0] = cartegiocatori[2][1];
            cartegiocatori[2][1] = daicarte(carte, &dimensionedelmazzo, true);
            stampacarta(cartegiocatori[2][0], true);
            stampacarta(cartegiocatori[2][1], true);
            somme[2] = cartegiocatori[2][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[2][0], &assi[2], false, somme[2]) : cartegiocatori[2][0].valore;
            somme[2] += cartegiocatori[2][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[2][1], &assi[2], false, somme[2]) : cartegiocatori[2][1].valore;
            printf(ANSI_COLOR_YELLOW "\nSomma mazzo 2: %d\n" ANSI_COLOR_RESET, somme[2]);                
        }
        if (mano3) {
            printf(ANSI_COLOR_YELLOW "\nMazzo numero 3" ANSI_COLOR_RESET);
            cartegiocatori[3][1] = daicarte(carte, &dimensionedelmazzo, true);
            stampacarta(cartegiocatori[3][0], true);
            stampacarta(cartegiocatori[3][1], true);                
            somme[3] = cartegiocatori[3][0].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[3][0], &assi[3], false, somme[3]) : cartegiocatori[3][0].valore;
            somme[3] += cartegiocatori[3][1].valore == 1 ? sceglivaloreassoutente(&cartegiocatori[3][1], &assi[3], false, somme[3]) : cartegiocatori[3][1].valore;
            printf(ANSI_COLOR_YELLOW "\nSomma mazzo 3: %d\n" ANSI_COLOR_RESET, somme[3]);                
        }
    }
    // quarto step-->chiedi carte
    for (int i = 1; i <= righecartegiocatore && assisplit < 1; i++){
        continua = true; 
        if(somme[i] == 21) continua = false;
        for (int j = 0; j < ARRAY_DIMENSION && continua; j++){
            bool isnotpuntata = false;
            printf(ANSI_COLOR_YELLOW "\n\nMazzo numero %d - somma: %d" ANSI_COLOR_RESET, i, somme[i]);
            Sleep(1000);
            if(contogiocatore.ammontare >= puntata) printf(ANSI_COLOR_CYAN "\nCosa vuoi fare?\n1) Chiedi carta\n2) Fermati\n3) Raddoppia\n-" ANSI_COLOR_RESET);
            else {
                printf(ANSI_COLOR_CYAN "\nCosa vuoi fare?\n1) Chiedi carta\n2) Fermati\n-" ANSI_COLOR_RESET);
                isnotpuntata = true;
            }
            scanf("%d", &scelta);
            if(isnotpuntata){
                if(scelta == 3) scelta = 1;
            }
            switch (scelta) {
                case 1: {
                    cartegiocatori[i][j] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[i][j], true);
                    if (cartegiocatori[i][j].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][j], &assi[i], false, somme[i]);
                    else somme[i] += cartegiocatori[i][j].valore;  
                    if(somme[i] > 21){                      
                        for(int k = 0; k < righecartegiocatore; k++){
                            if(cartegiocatori[i][k].valore == 11){
                                cartegiocatori[i][k].valore = 1;
                                somme[i] -= 10;
                            }
                        }
                    }
                    printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, somme[i]);
                    if(somme[i] == 21) continua = false;
                    else if(somme[i] > 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_RED "\n\nQuesto mazzo ha sballato" ANSI_COLOR_RESET);
                        continua = false;
                    }
                } break;
                case 2: {
                    printf(ANSI_COLOR_YELLOW "\nTi sei fermato" ANSI_COLOR_RESET);
                    continua = false;
                    if(assi[i] > 0){
                        int valoretemp = 0; 
                        printf(ANSI_COLOR_YELLOW "\nHai degli assi da gestire" ANSI_COLOR_RESET);
                        for (int a = 0; a < assi[i]; a++) {
                            valoretemp = sceglivaloreassoutente(&cartegiocatori[i][j], &assi[i], true, somme[i]);
                            if (valoretemp == 11) somme[i] += 10;
                            printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, somme[i]);                        
                        }
                        if(somme[i] > 21){                      
                            for(int k = 0; k < righecartegiocatore; k++){
                                if(cartegiocatori[i][k].valore == 11){
                                    cartegiocatori[i][k].valore = 1;
                                    somme[i] -= 10;
                                }
                            }
                        }
                        if(somme[i] > 21){
                            Sleep(1000);
                            printf(ANSI_COLOR_RED "\n\nQuesto mazzo ha sballato" ANSI_COLOR_RESET);
                            break;
                        } 
                    }
                } break;
                case 3: {
                    if(contogiocatore.ammontare >= puntata){
                        aggiornaammontare(&contogiocatore, -puntata);
                        printf(ANSI_COLOR_YELLOW "\nSaldo aggiornato: %d euro\n" ANSI_COLOR_RESET, contogiocatore.ammontare);
                        cartegiocatori[i][j] = daicarte(carte, &dimensionedelmazzo, true);
                        stampacarta(cartegiocatori[i][j], true);
                        if (cartegiocatori[i][j].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][j], &assi[i], false, somme[i]);
                        else somme[i] += cartegiocatori[i][j].valore;
                        if(somme[i] > 21){                      
                            for(int k = 0; k < righecartegiocatore; k++){
                                if(cartegiocatori[i][k].valore == 11){
                                    cartegiocatori[i][k].valore = 1;
                                    somme[i] -= 10;
                                }
                            }
                        }
                        printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, somme[i]);
                        if(somme[i] > 21){
                            Sleep(1000);
                            printf(ANSI_COLOR_RED "\n\nQuesto mazzo ha sballato" ANSI_COLOR_RESET);
                        } 
                        raddoppia[i - 1] = true;
                        continua = false;                        
                    } else printf(ANSI_COLOR_YELLOW "\nNon hai abbastanza soldi per raddoppiare" ANSI_COLOR_RESET);
                }
                break;
                default:{
                    cartegiocatori[i][j] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[i][j], true);
                    if (cartegiocatori[i][j].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][j], &assi[i], false, somme[i]);
                    else somme[i] += cartegiocatori[i][j].valore;  
                    if(somme[i] > 21){                      
                        for(int k = 0; k < righecartegiocatore; k++){
                            if(cartegiocatori[i][k].valore == 11){
                                cartegiocatori[i][k].valore = 1;
                                somme[i] -= 10;
                            }
                        }
                    }
                    printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, somme[i]);
                    if(somme[i] == 21) continua = false;
                    else if(somme[i] > 21){
                        Sleep(1000);
                        printf(ANSI_COLOR_RED "\n\nQuesto mazzo ha sballato" ANSI_COLOR_RESET);
                        continua = false;
                    }
                }
                break;
            }               
        }
    }
    Sleep(1000);
    printf(ANSI_COLOR_CYAN "\n\nI tuoi mazzi:" ANSI_COLOR_RESET);
    for (int i = 1; i <= righecartegiocatore; i++) printf(ANSI_COLOR_CYAN "\n-Numero %d: %d" ANSI_COLOR_RESET, i, somme[i]);
    // quinto pezzo --> chiedi carte banco
    Sleep(1000);
    stampacarta(cartegiocatori[0][1], false);    
    printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
    bool soft17 = false;
    if((cartegiocatori[0][0].valore == 1 && cartegiocatori[0][1].valore == 6) || (cartegiocatori[0][0].valore == 6 && cartegiocatori[0][1].valore == 1)){
            soft17 = true;
            somme[0] = 7;
            printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' un soft 17, quindi o 7 o 17" ANSI_COLOR_RESET); 
    } else printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, somme[0]); 
    for (int i = 0; somme[0] < 17; i++) {
        Sleep(1000);        
        cartegiocatori[0][i] = daicarte(carte, &dimensionedelmazzo, false);
        stampacarta(cartegiocatori[0][i], false);        
        if (cartegiocatori[0][i].valore == 1) somme[0] += sceglivaloreassobanco(somme[0]);
        else somme[0] += cartegiocatori[0][i].valore;    
        if(cartegiocatori[0][i].valore <= 4 && soft17) {
            soft17 = false;
            somme[0] += 10;
        }
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, somme[0]);
    } 
    Sleep(1000);
    printf(ANSI_COLOR_MAGENTA "\n\nIl banco si ferma" ANSI_COLOR_RESET);
    // sesto pezzo --> tirare le somme e vedere chi ha vinto
    int contatoreperse = 0;
    int contatorevinte = 0;
    for(int i = 1; i <= righecartegiocatore; i++){
        if(somme[i] > 21) contatoreperse++;
        else contatorevinte++;
    }
    if (contatoreperse == righecartegiocatore){
        Sleep(1000);
        printf(ANSI_COLOR_RED "\n\nHai sballato con tutti i mazzi, hai perso tutto" ANSI_COLOR_RESET);
        return 1;
    }
    if(somme[0] > 21){
        Sleep(1000);
        int countersoldivinti = 0;
        for(int i = 0; i < contatorevinte; i++){
            if(raddoppia[i]){
                countersoldivinti += puntata * 4;
                aggiornaammontare(&contogiocatore, (puntata * 4));
            } 
            else{
                countersoldivinti += puntata * 2;
                aggiornaammontare(&contogiocatore, (puntata * 2));
            } 
        }        
        printf(ANSI_COLOR_GREEN"\n\nIl banco ha sballato, hai vinto %d euro" ANSI_COLOR_RESET, countersoldivinti / 2);
        return 1;
    }  
    int puntatatemp = 0; 
    Sleep(1000);
    for(int i = 1; i <= righecartegiocatore; i++){
        if(somme[0] < somme[i] && somme[i] <= 21){
            Sleep(1000);
            if(raddoppia[i - 1]){
                puntatatemp = puntata * 4;
                aggiornaammontare(&contogiocatore, puntatatemp);
            }  
            else{
                puntatatemp = puntata * 2;
                aggiornaammontare(&contogiocatore, puntatatemp);
            }             
            printf(ANSI_COLOR_GREEN "\n\nMazzo %d ha vinto %d euro" ANSI_COLOR_RESET, i, puntatatemp / 2);
        } else if(somme[0] > somme[i] || somme[i] > 21){
            Sleep(1000);
            if(raddoppia[i - 1]) puntatatemp = puntata * 2;
            else puntatatemp = puntata;
            printf(ANSI_COLOR_RED "\n\nMazzo %d ha perso %d euro" ANSI_COLOR_RESET, i, puntatatemp);
        } else if(somme[0] == somme[i]){
            Sleep(1000);
            if(raddoppia[i - 1]){
                puntatatemp = puntata * 2;
                aggiornaammontare(&contogiocatore, puntatatemp);
            }  
            else{
                puntatatemp = puntata;
                aggiornaammontare(&contogiocatore, puntatatemp);
            }            
            printf(ANSI_COLOR_YELLOW "\n\nMazzo %d ha pareggiato. Ti vengono restituiti %d euro" ANSI_COLOR_RESET, i, puntatatemp); 
        }
    }
}

