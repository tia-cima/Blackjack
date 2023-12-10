//TODO array di 52 carte da usare al posto del rand. ogni volta che esce una carta, toglierla dal mazzo
//TODO algoritmo migliorato
//TODO risolvere perche non restarta quando supero le carte dell'avversario
//TODO assi


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h> // sleep
#include "Carte.h"
#define ARRAY_DIMENSION 10

Carta carte[52];
Carta* cartePtr = carte;
void gioca();
int scelta;
int sommacarteutente;
int sommacartecomputer;
int counter = 2;
int continua = 1;
int dimensionedelmazzo = 52;

Carta cartaUtente[ARRAY_DIMENSION];
Carta cartaComputer[ARRAY_DIMENSION];

int main() {
    srand(time(NULL));
    counter = 2;
    continua = 1;
    popolamazzo(carte);
    // stampamazzo(carte);
    do {
        sommacarteutente = 0;
        sommacartecomputer = 0;
        printf("BENVENUTO AL BLACKJACK!\nI CARATTERI 'q', 'p', 'c' e 'f' RAPPRESENTANO RISPETTIVAMENTE LE CARTE QUADRI, PICCHE, CUORI E FIORI\nSELEZIONA UNA OPZIONE:\n1 PER INIZIARE UNA NUOVA PARTITA\n2 PER USCIRE\n-");
        scanf("%d", &scelta);
        switch (scelta) {
        case 1:
            gioca();
            break;
        case 2:
            printf("Grazie per aver giocato!\n");
            break;
        default:
            printf("Scelta non valida.\n");
        }
    } while (scelta != 2);
    return 0;
}

void gioca(){   

    printf("Distribuisco le carte.\n\n");
    Sleep(1000);
    cartaUtente[0] = daicarte(carte, &dimensionedelmazzo); 
    sommacarteutente += cartaUtente[0].valore;
    cartaUtente[1] = daicarte(carte, &dimensionedelmazzo);
    sommacarteutente += cartaUtente[1].valore;
    cartaComputer[0] = daicarte(carte, &dimensionedelmazzo); 
    sommacartecomputer += cartaComputer[0].valore;
    cartaComputer[1] = daicarte(carte, &dimensionedelmazzo);
    sommacartecomputer += cartaComputer[1].valore;
    printf("Tu hai il %d di %c e il %d di %c. In totale hai %d\n", cartaUtente[0].valore, cartaUtente[0].tipo, cartaUtente[1].valore, cartaUtente[1].tipo, cartaUtente[0].valore + cartaUtente[1].valore);
    printf("L'avversario ha pescato %d e l'altra carta nascosta.\n\n", cartaComputer[0]);
    if((cartaComputer[0].valore + cartaComputer[1].valore) == 21){
        Sleep(1000);
        printf("Il banco ha fatto blackjack, hai perso\n\n");
        return;
    } else if ((cartaUtente[0].valore + cartaUtente[1].valore) == 21){        
        Sleep(1000);
        if((cartaComputer[0].valore + cartaComputer[1].valore) == 21){
            printf("Cpu ha vinto, il banco vince in caso di pareggio\n");
            return;
        }
        else{
            printf("Hai fatto blackjack! Hai vinto\n\n");
            return;   
        }
    }
    do {
        printf("Cosa vuoi fare?\n1 carta \n2 stai\n-");
        scanf("%d", &scelta);
        switch (scelta)
        {
            case 1:
            {
                cartaUtente[counter] = daicarte(carte, &dimensionedelmazzo);
                sommacarteutente += cartaUtente[counter].valore;
                printf("\nCarta %d. La somma delle tue carte e' %d\n", cartaUtente[counter].valore, sommacarteutente);
                if(sommacarteutente > 21){
                    printf("Hai sballato\n\n");
                    return;
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
    // algoritmo cpu
    printf("\nIl banco scopre la sua carta nascosta: %d\n", cartaComputer[1]);
    while(sommacartecomputer < 16) {
        cartaComputer[counter] = daicarte(carte, &dimensionedelmazzo);
        sommacartecomputer += cartaComputer[counter].valore;
        printf("Cpu ha pescato %d. La somma delle sue carte e' %d\n", cartaComputer[counter].valore, sommacartecomputer);
        Sleep(500);
    }
    printf("Cpu si ferma\n\n");
    if(sommacartecomputer > 21){
        printf("Cpu ha sballato\n");
        return;
    }  
    else if(sommacartecomputer == 21){
        printf("Cpu ha vinto\n");
        return;   
    } 
    printf("Somma carte user: %d\nSomma carte cpu: %d\n\n", sommacarteutente, sommacartecomputer);

    if(sommacartecomputer > sommacarteutente){
        printf("Cpu ha vinto\n");
        return;
    } else if (sommacarteutente > sommacartecomputer){
        printf("Hai vinto!\n");
        return;
    } else if (sommacartecomputer == sommacarteutente){
        printf("Cpu ha vinto, il banco vince in caso di pareggio\n");
        return;
    }
}
