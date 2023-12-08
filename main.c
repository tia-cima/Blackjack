#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h> // sleep

const int ARRAY_DIMENSION = 10;
void gioca();
int daicarte();
int scelta;
int sommacarteutente;
int sommacartecomputer;
int counter = 2;
int continua = 1;
int cartaUtente[10];
int cartaComputer[10];

int main() {
    srand(time(NULL));
    counter = 2;
    continua = 1;
    do {
        sommacarteutente = 0;
        sommacartecomputer = 0;
        printf("BENVENUTO AL BLACKJACK! SELEZIONA UNA OPZIONE:\n1 PER INIZIARE UNA NUOVA PARTITA\n2 PER USCIRE\n-");
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
    cartaUtente[0] = daicarte(); 
    sommacarteutente += cartaUtente[0];
    cartaUtente[1] = daicarte();
    sommacarteutente += cartaUtente[1];
    cartaComputer[0] = daicarte(); 
    sommacartecomputer += cartaUtente[0];
    cartaComputer[1] = daicarte();
    printf("Tu hai %d e %d. In totale hai %d\n", cartaUtente[0], cartaUtente[1], cartaUtente[0] + cartaUtente[1]);
    printf("L'avversario ha %d e %d. In totale ha %d\n\n", cartaComputer[0], cartaComputer[1], cartaComputer[0] + cartaComputer[1]);
    if((cartaComputer[0] + cartaComputer[1]) == 21){
        Sleep(1000);
        printf("Il banco ha fatto blackjack, hai perso\n\n");
        return;
    } else if ((cartaUtente[0] + cartaUtente[1]) == 21){
        Sleep(1000);
        printf("Hai fatto blackjack! Hai vinto\n\n");
        return;       
    }
    do {
        printf("Cosa vuoi fare?\n1 carta \n2 stai\n-");
        scanf("%d", &scelta);
        switch (scelta)
        {
            case 1:
            {
                cartaUtente[counter] = daicarte();
                sommacarteutente += cartaUtente[counter];
                printf("\nCarta %d. La somma delle tue carte è %d\n", cartaUtente[counter], sommacarteutente);
                if(sommacarteutente > 21){
                    printf("Hai sballato\n\n");
                    return;
                }  
                else if(sommacarteutente == 21){
                    printf("Hai vinto!\n\n"); // il banco vince, modificare
                    return;   
                } 
            } break;
            case 2: {
                printf("Ti sei fermato. \n\n");
                continua = 0;
            } break;
            default:
                break;
        }
        counter++;
    }while(continua > 0);
    counter = 2;
    // algoritmo cpu
    do {
        cartaComputer[counter] = daicarte();
        sommacartecomputer += cartaComputer[counter];
        printf("Cpu ha pescato %d. La somma delle sue carte è %d\n", cartaComputer[counter], sommacartecomputer);
        Sleep(500);
    }while(sommacartecomputer < 16);
    if(sommacartecomputer > 21){
        printf("Cpu ha sballato\n");
        return;
    }  
    else if(sommacartecomputer == 21){
        printf("Cpu ha vinto\n"); // il banco vince, modificare
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

int daicarte(){
    return (rand() % 10) + 1;
}