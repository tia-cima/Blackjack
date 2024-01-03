#include <stdbool.h>

typedef struct {
    int valore; 
    char tipo;  
    bool isRegina;
    bool isJack;
    bool isRe;
} Carta;

void popolamazzo(Carta* array);
void stampamazzo(Carta* array);
void stampacarta(Carta valore, bool isutente);
Carta daicarte(Carta* array, int* dimensionedelmazzo, bool isutente);
