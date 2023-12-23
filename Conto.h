typedef struct {
    int id;
    int ammontare; 
} Conto;

void impostaconto(Conto* contopersona);
void recuperaconto(Conto* contopersona);
void aggiornaammontare(Conto* contopersona);
int ottieniid(Conto* contopersona);
int ottieniammontare(Conto* contopersona);
