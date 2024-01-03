#include "Conto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_COLOR_RED     "\x1b[31m" // sconfitta
#define ANSI_COLOR_GREEN   "\x1b[32m" // vittoria
#define ANSI_COLOR_YELLOW  "\x1b[33m" // info
#define ANSI_COLOR_MAGENTA "\x1b[35m" // banco
#define ANSI_COLOR_CYAN    "\x1b[36m" // utente
#define ANSI_COLOR_RESET   "\x1b[0m" // reset

int creaidgiocatore();

void impostaconto(Conto* contopersona){
    printf(ANSI_COLOR_YELLOW "\nQuanto vuoi caricare sul tuo conto? Solo cifre intere\n-" ANSI_COLOR_RESET);
    int valore;
    scanf("%d", &valore);
    contopersona->ammontare = valore;
    contopersona->id = creaidgiocatore();
    char nomefile[20]; //20 utenti
    sprintf(nomefile, "data/%d.txt", contopersona->id);
    FILE *file = fopen(nomefile, "w");
    fprintf(file, "%d", contopersona->ammontare);
    fclose(file);
}

void recuperaconto(Conto* contopersona){
    printf(ANSI_COLOR_YELLOW "\nInserisci l'ID\n-" ANSI_COLOR_RESET);
    int recuperaid;
    scanf("%d", &recuperaid);
    contopersona->id = recuperaid;
    char nomefile[20];
    sprintf(nomefile, "data/%d.txt", contopersona->id);
    FILE *file = fopen(nomefile, "r");
    fscanf(file, "%d", &contopersona->ammontare);
    fclose(file);
}

void aggiornaammontare(Conto* contopersona, int nuovovalore){
    char nomefile[20]; //20 utenti
    int ammontarevecchio;
    sprintf(nomefile, "data/%d.txt", contopersona->id);
    FILE *fileleggi = fopen(nomefile, "r");
    fscanf(fileleggi, "%d", &ammontarevecchio);
    fclose(fileleggi);
    contopersona->ammontare = (ammontarevecchio + nuovovalore);
    FILE *filescrivi = fopen(nomefile, "w");
    fprintf(filescrivi, "%d", contopersona->ammontare);
    fclose(filescrivi);
}

int ottieniid(Conto* contopersona){
    return contopersona->id;
}

int ottieniammontare(Conto* contopersona){
    return contopersona->ammontare;
}

int creaidgiocatore(){
    FILE *file = fopen("data/id.txt", "r+");
    int count = 1;
    if (file == NULL) {
        file = fopen("data/id.txt", "w");
        fputc('1', file);
    } else {
        while (fgetc(file) != EOF) {
            count++;
        }
        fseek(file, 0, SEEK_END);
        fputc('1', file);
    }
    fclose(file);
    return count;
}
