#include <stdio.h>
#include <stdlib.h>

void gioca();
short daicarte();

int main()
{
    int scelta;
    printf("BENVENUTO AL BLACKJACK! SELEZIONA UNA OPZIONE:\n1 PER INIZIARE UNA NUOVA PARTITA \n2 PER USCIRE \n");
    scanf("%d", &scelta);
    switch (scelta)
    {
    case 1:
        gioca();
        break;
    default:
        break;
    }
    return 0;
}

void gioca(){
    printf("Distribuisco le carte.");
    int cartaUtente[10];
    int cartaComputer[10];
    cartaUtente[0] = daicarte(); 
    cartaUtente[1] = daicarte();
    cartaComputer[0] = daicarte(); 
    cartaComputer[1] = daicarte();
    int cartaComputer = daicarte();
    printf("Tu hai %d\n%d\n", cartaUtente[0], cartaUtente[1]);
    printf("\nL'avversario ha %d\n%d\n", cartaComputer[0], cartaComputer[1]);
    if((cartaComputer[0] + cartaComputer[1]) == 21){
        printf("Il banco ha fatto blackjack, hai perso");
        gioca();
    } else if ((cartaUtente[0] + cartaUtente[1]) == 21){
        printf("Hai fatto blackjack! Hai vinto");
        gioca();       
    }
    printf("Cosa vuoi fare?\n1 carta \n2 stai: ");
    int scelta;
    scanf("%d", &scelta);
    switch (scelta)
    {
    case 1:
        cartaUtente[2] = daicarte();
        break;
    
    default:
        break;
    }
}

short daicarte(){
    return (rand() % 21) + 1;
}