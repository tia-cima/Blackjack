#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


const int ARRAY_DIMENSION = 10;
void gioca();
int daicarte();
int nuovamossa(int counter);
int controllo(int sommacarteutente);
int scelta;
int counter = 2;
int *counterPtr;
int continua = 1;
int cartaUtente[10];
int *cartaUtentePtr;
int cartaComputer[10];
int *cartaComputerPtr;

int main()
{
    srand(time(NULL));
    // int scelta;
    // printf("BENVENUTO AL BLACKJACK! SELEZIONA UNA OPZIONE:\n1 PER INIZIARE UNA NUOVA PARTITA \n2 PER USCIRE \n");
    // scanf("%d", &scelta);
    // switch (scelta)
    // {
    // case 1:
    //     gioca();
    //     break;
    // default:
    //     break;
    // }
    // return 0;
    gioca();

}
int daicarte(){
    return (rand() % 11) + 1;
}
int controllo(int sommacarte){
    if(sommacarte > 21) return 0; 
    else if(sommacarte == 21) return 1; 
    else return 2;
} 
void gioca(){   
    cartaUtentePtr = cartaUtente;
 
    printf("Distribuisco le carte.\n\n");
    cartaUtente[0] = daicarte(); 
    cartaUtente[1] = daicarte();
    cartaComputer[0] = daicarte(); 
    cartaComputer[1] = daicarte();
    printf("Tu hai %d e %d. In totale hai %d\n", cartaUtente[0], cartaUtente[1], cartaUtente[0] + cartaUtente[1]);
    printf("L'avversario ha %d e %d. In totale ha %d\n\n", cartaComputer[0], cartaComputer[1], cartaComputer[0] + cartaComputer[1]);
    if((cartaComputer[0] + cartaComputer[1]) == 21){
        printf("Il banco ha fatto blackjack, hai perso");
        gioca();
    } else if ((cartaUtente[0] + cartaUtente[1]) == 21){
        printf("Hai fatto blackjack! Hai vinto");
        gioca();       
    }
    do {
        continua = nuovamossa(counter);
        counter++;
    }while(continua > 0);

    printf("Ti sei fermato. \n");
    // int sum = 0;
    // for(int i = 0; i < counter; i++){
    //     printf("%d ", cartaUtente[i]);
    //     sum += cartaUtente[i];
    // }
    // printf("\nsomma: %d", sum);

}

int nuovamossa(int counter){
    printf("Cosa vuoi fare?\n1 carta \n2 stai\n-");
    scanf("%d", &scelta);
    switch (scelta)
    {
    case 1:
        *(cartaUtentePtr + counter) = daicarte();
        int sommacarteutente = 0;
        for(int j = 0; j < counter + 1; j++){
            sommacarteutente += cartaUtente[j];
        }
        printf("Hai preso %d. La somma delle tue carte è %d\n", cartaUtente[counter], sommacarteutente);
        switch (controllo(sommacarteutente))
        {
        case 0:{
            printf("Hai sballato");
            return 0;    
            break;            
        }
        case 1:{
            printf("Hai vinto");
            return 0;    
            break;            
        }
        case 2:{
            return sommacarteutente;    
            break;            
        }
        default:
            break;
        }
    case 2: 
        return 0;
    default:
        break;
}
}

