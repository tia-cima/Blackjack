//TODO split finire di testare
//TODO double testare 
//TODO insurance testare
//TODO even money testare

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
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

int gioca();
int* somme;
int* assi;
bool* raddoppia;
int scelta;
int dimensionedelmazzo = 52;
int puntata;
int righecartegiocatore = 1;
int assisplit = 0;
bool continua = true;
Carta carte[52];
Carta** cartegiocatori;
Conto contogiocatore;

int main() {
    srand(time(NULL));
    popolamazzo(carte);
    // printf("\n\n#########################\nBENVENUTO AL BLACKJACK!\n-'q' rappresenta le carte quadri\n-'p' rappresenta le carte picche\n-'c' rappresenta le carte cuori\n-'f' rappresenta le carte fiori" ANSI_COLOR_GREEN "\nIl colore verde rappresenta i messaggi di vittoria" ANSI_COLOR_RESET ANSI_COLOR_RED "\nIl colore rosso rappresenta i messaggi di sconfitta" ANSI_COLOR_RESET ANSI_COLOR_YELLOW "\nIl colore giallo rappresenta i messaggi di info" ANSI_COLOR_RESET ANSI_COLOR_CYAN "\nIl colore azzurro rappresenta le tue mosse" ANSI_COLOR_RESET ANSI_COLOR_MAGENTA "\nIl colore magenta rappresenta le mosse del banco" ANSI_COLOR_RESET "\nBuon divertimento!\n#########################\n");
    // printf(ANSI_COLOR_YELLOW "\nPrima di cominciare, hai gia' un account o vuoi crearne uno nuovo? Ti servirà per riaccedere ai tuoi crediti anche in futuro\n1) Crea account\n2) Accedi ad account esistente (ID richiesto)\n-");
    // int sceltaccount = 0;
    // scanf("%d", &sceltaccount);
    // switch (sceltaccount) {
    //     case 1:{
    //         impostaconto(&contogiocatore); 
    //         printf(ANSI_COLOR_YELLOW "\nBenvenuto giocatore %d, hai caricato %d euro. Buona fortuna!" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
    //     } break;
    //     case 2:{
    //         recuperaconto(&contogiocatore); 
    //         printf(ANSI_COLOR_YELLOW "\nBentornato %d! Il tuo conto e' di %d. Vuoi ricaricarlo o procedere con questo quantitativo?\n1) Ricarica\n2) Non ricaricare\n-" ANSI_COLOR_RESET, contogiocatore.id, contogiocatore.ammontare);
    //         int procedi = 0;
    //         scanf("%d", &procedi);
    //         switch (procedi)
    //         {
    //         case 1:{
    //             printf(ANSI_COLOR_YELLOW "\nQuanto vuoi caricare sul tuo conto? Solo cifre intere\n-" ANSI_COLOR_RESET);
    //             int valore;
    //             scanf("%d", &valore);
    //             aggiornaammontare(&contogiocatore, valore);
    //             printf(ANSI_COLOR_YELLOW "\nRicarica effettuata con successo, nuovo ammontare pari a %d euro. Buona fortuna!" ANSI_COLOR_RESET, contogiocatore.ammontare);
    //         }            
    //             break;
    //         case 2:{
    //             printf(ANSI_COLOR_YELLOW "\nBuona fortuna!" ANSI_COLOR_RESET);
    //         }
    //         default:
    //             break;
    //         }
    //     } break;
    //     default:
    //         break;
    // }            
    contogiocatore.id = 1;
    contogiocatore.ammontare = 1500;
    while(1) gioca();   
    return 0;
}

int gioca(){     
    righecartegiocatore = 1;    
    puntata = 0;
    assisplit = 0;
    continua = true;
    raddoppia = (bool *)malloc((righecartegiocatore + 1) * sizeof(bool));  
    for(int i = 0; i < (righecartegiocatore + 1); i++)    raddoppia[i] = false;
    somme = (int *)malloc((righecartegiocatore + 1) * sizeof(int));  
    for(int i = 0; i < (righecartegiocatore + 1); i++)    somme[i] = 0;
    assi = (int *)malloc((righecartegiocatore + 1) * sizeof(int));  
    for(int i = 0; i < (righecartegiocatore + 1); i++)    assi[i] = 0;
    cartegiocatori = (Carta **)malloc((righecartegiocatore + 1) * sizeof(Carta *));
    for (int i = 0; i < (righecartegiocatore + 1); i++) cartegiocatori[i] = (Carta *)malloc(ARRAY_DIMENSION * sizeof(Carta));    
    Sleep(2000);
    printf(ANSI_COLOR_YELLOW "\n\n#########################\nComincio una nuova partita\nCrediti rimasti: %d\n#########################\n" ANSI_COLOR_RESET, contogiocatore.ammontare);
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
    // secondo pezzo --> distribuzione delle carte
    cartegiocatori[1][0] = daicarte(carte, &dimensionedelmazzo, true); 
    cartegiocatori[1][1] = daicarte(carte, &dimensionedelmazzo, true);
    stampacarta(cartegiocatori[1][0], true);
    stampacarta(cartegiocatori[1][1], true);    
    Sleep(1000);
    cartegiocatori[0][0] = daicarte(carte, &dimensionedelmazzo, false); 
    cartegiocatori[0][1] = daicarte(carte, &dimensionedelmazzo, false);
    stampacarta(cartegiocatori[0][0], false);
    if(cartegiocatori[0][0].valore == 1 && cartegiocatori[1][0].valore == 10 && cartegiocatori[1][1].valore == 11)    {
        printf(ANSI_COLOR_YELLOW "\n\nHai fatto blackjack, mentre il banco ha un asso. Hai la possibilita' di interrompere ora la partita vincendo l'importo della tua puntata. Vuoi farlo?\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
        int sceltaeven;
        scanf("%d", &sceltaeven);
        if(sceltaeven == 1){
            stampacarta(cartegiocatori[0][1], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, (puntata * 2));
            if(cartegiocatori[0][1].valore == 10) printf(ANSI_COLOR_GREEN "\nIl banco ha fatto blackjack, ma hai deciso di scegliere l'opzione even money. Hai vinto l'ammontare di una vincita normale" ANSI_COLOR_RESET);
            else printf(ANSI_COLOR_GREEN "\nIl banco non ha fatto blackjack, ma hai deciso di scegliere l'opzione even money. Hai vinto l'ammontare di una vincita normale" ANSI_COLOR_RESET);
            return 1;
        }
    } else if(cartegiocatori[0][0].valore == 1){
        printf(ANSI_COLOR_YELLOW "\n\nAttenzione! Il banco ha un asso come prima carta. Vuoi procedere con l'assicurazione?\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
        int sceltassicurazione;
        scanf("%d", &sceltassicurazione);
        if(sceltassicurazione == 1){
            aggiornaammontare(&contogiocatore, -(puntata / 2));
            if(cartegiocatori[0][1].valore == 10){
                stampacarta(cartegiocatori[0][1], false);
                printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_MAGENTA "\nIl banco ha fatto blackjack. Complimenti per aver acquistato l'assicurazione" ANSI_COLOR_RESET);
                aggiornaammontare(&contogiocatore, puntata);
                return 1;
            } else {
                printf(ANSI_COLOR_YELLOW "\nIl banco non ha un 10, percio' non potra' fare blackjack. Perdi i soldi dell'assicurazione");
            }
        }
    }
    printf(ANSI_COLOR_MAGENTA "\nL'altra carta rimane nascosta." ANSI_COLOR_RESET);
    if (cartegiocatori[0][0].valore == 1) somme[0] += sceglivaloreassobanco(somme[0]);
    else somme[0] += cartegiocatori[0][0].valore;
    if (cartegiocatori[0][1].valore == 1) somme[0] += sceglivaloreassobanco(somme[0]);
    else somme[0] += cartegiocatori[0][1].valore;    
    if ((cartegiocatori[0][0].valore == 1 && cartegiocatori[0][1].valore == 10) || (cartegiocatori[0][0].valore == 10 && cartegiocatori[0][1].valore == 1)) {
        if ((cartegiocatori[1][0].valore == 1 && cartegiocatori[1][1].valore == 10) || (cartegiocatori[1][0].valore == 10 && cartegiocatori[1][1].valore == 1)) {
            Sleep(1000);
            stampacarta(cartegiocatori[0][1], false);
            printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "\nAvete entrambi fatto blackjack, la partita finisce qui" ANSI_COLOR_RESET);
            aggiornaammontare(&contogiocatore, puntata);
            return 1;
        }
    } 
    if ((cartegiocatori[0][0].valore == 1 && cartegiocatori[0][1].valore == 10) || (cartegiocatori[0][0].valore == 10 && cartegiocatori[0][1].valore == 1)) {
        Sleep(1000);
        stampacarta(cartegiocatori[0][1], false);
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_RED "\nIl banco ha fatto blackjack, la partita finisce qui" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, -puntata);
        return 1;
    } 
    if ((cartegiocatori[1][0].valore == 1 && cartegiocatori[1][1].valore == 10) || (cartegiocatori[1][0].valore == 10 && cartegiocatori[1][1].valore == 1)) {
        Sleep(1000);
        stampacarta(cartegiocatori[0][1], false);
        printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "\nHai fatto blackjack, la partita finisce qui" ANSI_COLOR_RESET);
        aggiornaammontare(&contogiocatore, (puntata + (puntata * 1,5)));   
        return 1;    
    } 
    //terzo step --> split
    for(int i = 1; i <= righecartegiocatore && continua; i++){
        if(cartegiocatori[i][0].valore == cartegiocatori[i][1].valore && contogiocatore.ammontare >= puntata * 2){
            printf(ANSI_COLOR_YELLOW "\n\nHai la possibilita' di splittare. Vuoi splittare le tue carte? Dovrai puntare la stessa puntata iniziale.\n1) Si\n2) No\n-" ANSI_COLOR_RESET);
            int sceltasplit = 1;
            // scanf("%d", &sceltasplit);
            if(sceltasplit == 1){
                continua = true;
                aggiornaammontare(&contogiocatore, -puntata);
                righecartegiocatore++;               
                somme = (int *)realloc(somme, (righecartegiocatore + 1) * sizeof(int));
                somme[righecartegiocatore] = 0; 
                assi = (int *)realloc(assi, (righecartegiocatore + 1) * sizeof(int));
                assi[righecartegiocatore] = 0; 
                cartegiocatori = (Carta **)realloc(cartegiocatori, (righecartegiocatore + 1) * sizeof(Carta *));
                cartegiocatori[righecartegiocatore] = (Carta *)malloc(ARRAY_DIMENSION * sizeof(Carta));
                cartegiocatori[righecartegiocatore][0] = cartegiocatori[i][1];           
                if (cartegiocatori[i][0].valore == 1 && cartegiocatori[i][1].valore == 1) {
                    assisplit++;
                    somme[righecartegiocatore] += sceglivaloreassoutente(&cartegiocatori[i][0], &assi[i], false);
                } else somme[righecartegiocatore] += cartegiocatori[i][0].valore;                    
                cartegiocatori[righecartegiocatore][1] = daicarte(carte, &dimensionedelmazzo, true);
                if (cartegiocatori[righecartegiocatore][1].valore == 1) somme[righecartegiocatore] += sceglivaloreassoutente(&cartegiocatori[righecartegiocatore][1], &assi[righecartegiocatore], false);
                else somme[righecartegiocatore] += cartegiocatori[righecartegiocatore][1].valore;  
                stampacarta(cartegiocatori[righecartegiocatore][0], true);
                stampacarta(cartegiocatori[righecartegiocatore][1], true);    
                printf(ANSI_COLOR_CYAN "\nSomma mazzo numero %d: %d\n" ANSI_COLOR_RESET,i, somme[righecartegiocatore]);         
            } else {
                if (cartegiocatori[i][0].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][0], &assi[i], false);
                else somme[i] += cartegiocatori[1][0].valore;
                if (cartegiocatori[i][1].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][1], &assi[i], false);
                else somme[i] += cartegiocatori[i][1].valore;    
                printf(ANSI_COLOR_CYAN "\n\nIn totale hai %d" ANSI_COLOR_RESET, somme[i]);
                continua = false;
            }
        } else {
                if (cartegiocatori[i][0].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][0], &assi[i], false);
                else somme[i] += cartegiocatori[1][0].valore;
                if (cartegiocatori[i][1].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][1], &assi[i], false);
                else somme[i] += cartegiocatori[i][1].valore;    
                printf(ANSI_COLOR_CYAN "\n\nIn totale hai %d" ANSI_COLOR_RESET, somme[i]);
                continua = false;
        }
    }      
    // quarto step-->chiedi carte
    for (int i = 1; i <= righecartegiocatore && assisplit < 1; i++){
        continua = true; 
        for (int j = 0; j < ARRAY_DIMENSION && continua; j++){
            printf(ANSI_COLOR_YELLOW "\n\nMazzo numero %d" ANSI_COLOR_RESET, i);
            Sleep(1000);
            printf(ANSI_COLOR_CYAN "\n\nCosa vuoi fare?\n1) Chiedi carta\n2) Fermati\n3) Raddoppia\n-" ANSI_COLOR_RESET);
            scanf("%d", &scelta);
            switch (scelta) {
                case 1: {
                    cartegiocatori[i][j] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[i][j], true);
                    if (cartegiocatori[i][j].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][j], &assi[i], false);
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
                        printf(ANSI_COLOR_RED "\n\nHai sballato, hai perso" ANSI_COLOR_RESET);
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
                            valoretemp = sceglivaloreassoutente(&cartegiocatori[i][j], &assi[i], true);
                            if (valoretemp == 11) somme[i] += 10;
                            printf(ANSI_COLOR_CYAN "\nLa somma delle tue carte e' %d" ANSI_COLOR_RESET, somme[i]);                        
                        }
                        if(somme[i] > 21){
                            Sleep(1000);
                            printf(ANSI_COLOR_RED "\n\nQuesto mazzo ha sballato" ANSI_COLOR_RESET);
                            break;
                        } 
                    }
                } break;
                case 3: {
                    aggiornaammontare(&contogiocatore, -puntata);
                    raddoppia[i] = true;
                    cartegiocatori[i][j] = daicarte(carte, &dimensionedelmazzo, true);
                    stampacarta(cartegiocatori[i][j], true);
                    if (cartegiocatori[i][j].valore == 1) somme[i] += sceglivaloreassoutente(&cartegiocatori[i][j], &assi[i], false);
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
                        printf(ANSI_COLOR_RED "\n\nHai sballato, hai perso" ANSI_COLOR_RESET);
                    }
                    continua = false;
                }
                break;
                default:
                break;
            }               
        }
    }
    printf(ANSI_COLOR_CYAN "\n\nI tuoi mazzi:\n" ANSI_COLOR_RESET);
    for (int i = 1; i <= righecartegiocatore; i++) printf(ANSI_COLOR_CYAN "-Numero %d: %d\n" ANSI_COLOR_RESET, i, somme[i]);
    // quinto pezzo --> chiedi carte banco
    Sleep(1000);
    stampacarta(cartegiocatori[0][1], false);
    printf(ANSI_COLOR_MAGENTA "Era la sua carta nascosta" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, somme[0]);
    int i;
    for (i = 0; somme[0] < 17; i++) {
        Sleep(1000);
        cartegiocatori[0][i] = daicarte(carte, &dimensionedelmazzo, false);
        stampacarta(cartegiocatori[0][i], false);
        if (cartegiocatori[0][i].valore == 1) somme[0] += sceglivaloreassobanco(somme[0]);
        else somme[0] += cartegiocatori[0][i].valore;    
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, somme[0]);
    } 
    Sleep(1000);
    continua = false;
    for (int j = 1; j <= righecartegiocatore; j++) {
        if (somme[j] <= 21) { 
            if (somme[0] < somme[j]) {
                continua = true;  
                break;
            }
        }
    }
    while(continua){
        Sleep(1000);
        cartegiocatori[0][i] = daicarte(carte, &dimensionedelmazzo, false);
        stampacarta(cartegiocatori[0][i], false);
        if (cartegiocatori[0][i].valore == 1) somme[0] += sceglivaloreassobanco(somme[0]);
        else somme[0] += cartegiocatori[0][i].valore;    
        printf(ANSI_COLOR_MAGENTA "\nLa somma delle sue carte e' %d" ANSI_COLOR_RESET, somme[0]);
        for (int j = 1; j <= righecartegiocatore; j++) {
            if (somme[j] <= 21) {
                if (somme[0] < somme[j]) {
                    continua = true;  
                    break;
                }
            }
        }
        if (somme[0] > 21 || !continua) break;
    }
    if(somme[0] > 21){
        Sleep(1000);
        printf(ANSI_COLOR_GREEN"\n\nIl banco ha sballato, hai vinto!" ANSI_COLOR_RESET);
        for(int i = 0; i < righecartegiocatore; i++){
            if(raddoppia[i]) aggiornaammontare(&contogiocatore, (puntata * 4));
            else aggiornaammontare(&contogiocatore, puntata);
        }
        return 1;
    }  
    printf(ANSI_COLOR_MAGENTA "\n\nIl banco si ferma" ANSI_COLOR_RESET);
    // sesto pezzo --> tirare le somme e vedere chi ha vinto
    Sleep(1000);
    for(int i = 1; i <= righecartegiocatore; i++){
        if(somme[0] < somme[i] && somme[i] <= 21){
            Sleep(1000);
            printf(ANSI_COLOR_GREEN "\n\nMazzo %d ha vinto!" ANSI_COLOR_RESET, i);
            if(raddoppia[i]) aggiornaammontare(&contogiocatore, (puntata * 4));
            else aggiornaammontare(&contogiocatore, (puntata * 2)); 
        } else if(somme[0] > somme[i] || somme[i] > 21){
            Sleep(1000);
            printf(ANSI_COLOR_RED "\n\nMazzo %d ha perso" ANSI_COLOR_RESET, i);
        } else if(somme[0] == somme[i]){
            Sleep(1000);
            printf(ANSI_COLOR_YELLOW "\n\nMazzo %d ha pareggiato" ANSI_COLOR_RESET, i);
            if(raddoppia[i]) aggiornaammontare(&contogiocatore, puntata);
            aggiornaammontare(&contogiocatore, puntata);
        }
    }
    free(cartegiocatori);
    free(somme);
    free(raddoppia);
    free(assi);
}

