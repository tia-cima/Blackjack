# Blackjack in C

## Descrizione
Il programma consiste in un blackjack a tutti gli effetti con tutti gli aspetti che caratterizzano questo gioco: 
- **Mazzo da 52 carte**
- **Gestione degli assi**
- **Puntate**
- **Conto in euro**

Il gioco è banco vs utente. Non ci sono altri giocatori, quindi sarà una partita 1v1.

Il banco non è ne intelligenza artificiale ne un'altra persona. Segue semplicemente la regola base che il banco deve chiedere carta minimo fino a 17, e se il totale delle sue carte è inferiore a quello dell'utente, chiede ancora carte, altrimenti si ferma. 

Altri dettagli verranno approfonditi in seguito. 


## Tipi personalizzati
Con l'obiettivo di rendere la UX il più realistica possibile, ho dovuto creare ed implementare due nuovi tipi tramite ADT: 

- Il tipo **Carta**, creato apposta per rappresentare ogni carta del mazzo. Questo tipo permette di rappresentare, in un solo tipo, il **valore della carta** *(1, 2 ...10)*, il **tipo della carta** *(cuori, picche...)* e, in caso, la sua **figura** *(jack, regina, re)*. Ciò vale per ogni carta.<br>In realtà, solo il valore della carta è rilevante ai fini del funzionamento del programma, in quanto nel blackjack tipo e figure non sono importanti. Ho scelto comunque di implementarli perché alla fine il programma non lo rallentano, dato che dopo ogni azione c'è uno sleep di 1 secondo (dopo lo vedremo meglio) e comunque è una soluzione carina perché immerge sempre di più l'esperienza d'uso proprio come se fosse un vero blackjack, ma anche perché in futuro intendo usare questo codice per creare un'interfaccia grafica e predisporre in questo modo il software mi consentirà in futuro poi di implementarlo in maniera molto più semplice. Infine, in caso si volessero creare altri giochi con le carte francesi, il tipo è già pronto, insieme ai suoi metodi. 

- Il tipo **Conto**, che consente all'utente di creare, modificare e accedere ai propri soldi che carica in modo da poter effettuare le puntate.<br>Non è importante ai fini del funzionamento del programma, in quanto è possibile giocare anche senza fare puntate semplicemente eliminando i riferimenti a questo tipo nel main, ma è fondamentale se poi un giorno questo software venisse implementato in una piattaforma più grande ma anche per il discorso dell'esperienza realistica. <br>Dal lato tecnico, i dati dell'utente sono immagazzinati in file. In ogni file, chiamato come l'id dell'utente, viene immagazzinato solo il valore intero dei soldi che rimangono all'utente. Il tipo **Conto** è poi in grado di rintracciare l'utente che si logga proprio dall'id che l'utente immetterà in fase di esecuzione, che viene poi usato per cercare il file corrispondente, accedere ad esso leggendo il contenuto che ripeto è solo il valore intero dei soldi rimanenti e infine restituire questo valore al programma principale.<br>Ciò è un banale tentativo di creare un infrastruttura che in C non ha senso creare per questo programma, quella di una vera e propria appplicazione con database per lo storage dei dati dell'utente. Infatti, se avessi voluto creare una cosa così complicata, non avrei scelto il C come linguaggio ma qualcosa di più sensato per operazioni di questo tipo.  


## Programma principale
### Dichiarazione
Alla base del programma c'è l'array `carte`, di tipo *Carta*, composto da 52 elementi, ovvero le carte del mazzo. Questo array sarà usato per qualsiasi operazione riguardante la parte del gioco vero e proprio, ovvero l'estrazione delle carte. La dimensione di questo array è determinata dalla variabile `dimensionedelmazzo`, che gioca un ruolo cruciale nel programma in quanto è la variabile su cui si baserà il rimescolamento delle carte quando nell'array `carte` saranno esauriti i valori.<br>
L'utente e il banco avranno il proprio array di tipo *Carta*, che contiene le carte estratte. 

Per la gestione del conto, c'è la variabile `contogiocatore`, di tipo *Conto*, che si occuperà di restituire e modificare l'ammontare in denaro che l'utente ha a disposizione per le sue puntate. 

Altre variabili utili per la compresione del programma sono `sommacarteutente`, che contiene la somma delle carte estratte per l'utente ottenuta come somma delle varie celle di `carteUtente`.<br>Stesso discorso vale per `sommacartecomputer` per l'array `carteComputer`.<br>L'array `puntate` gestisce dinamicamente i tipi di puntate che possono essere effettuati. Infatti, è in grado di gestire, manualmente, l'inserimento di nuovi valori solamente all'interno della dichiarazione. Le funzioni associate sono poi in grado di gestire l'entrata di nuovi valori senza bisogno di altre modifiche. 

Infine, menzione d'onore per le costanti del tipo `ANSI_COLOR...`, che servono per colorare i vari messaggi stampati in output. Ciò serve per dare una maggiore leggibilità al programma. Ogni colore ha un significato: 
- **Rosso**: messaggi di sconfitta.
- **Verde**: messaggi di vittoria.
- **Giallo**: messaggi di info. 
- **Magenta**: messaggi relativi alle mosse del banco. 
- **Ciano**: messaggi relativi alle mosse dell'utente. 

### Main()
Nel main, come prima cosa viene fatto creare un account all'utente o, in caso di account già esistente, viene fatto l'accesso, restituendo l'ammontare salvato precedentemente. 
Successivamente, viene chiesto se procedere o no con il caricamento di nuovi fondi, obbligatorio per i nuovi account. 

Si è ora pronti per giocare. Ciò avviene usando la funzione `gioca()`, di fondamentale importanza perché contiene al suo interno tutto il gioco.<br>Ho scelto di procedere in questo modo in quanto essa è rinchiusa in un ciclo `while(1)` infinito, perciò ogni volta che la partita finisce, invece che uscire dal programma, semplicemente si esce dalla funzione e si rientra subito dopo, in quanto si può uscire dalla funzione ma non dal while. 

Dopo la fine di ogni partita viene aggiornato il counter di partite vinte/perse e l'ammontare vinto/perso dall'utente

### Gioca()
La funzione `gioca()`, come già detto, racchiude tutta la logica del blackjack. 


## Funzionalità
- **Gestione del Mazzo**: Il mazzo di carte è gestito dinamicamente, con la possibilità di rimescolarlo quando necessario. Infatti, le carte che vengono estratte non sono determinate randomicamente ma estratte da un mazzo di carte (un array da 52 elementi carta)
- **Puntate**: Gli utenti possono scegliere tra diverse opzioni di puntata.
- **Gestione del Conto**: Gli utenti possono creare un nuovo conto o accedere a un conto esistente.

## Istruzioni per l'Uso
1. Avvia il programma.
2. Scegli se creare un nuovo account o accedere a uno esistente.
3. Seleziona l'importo da puntare.
4. Il gioco procede con la distribuzione delle carte.
5. Decidi se chiedere un'altra carta o fermarti.
6. Il gioco confronta il totale delle tue carte con quello del banco per determinare il vincitore.

## Dettagli Tecnici
- Il codice sfrutta librerie standard come `<stdio.h>` e `<stdlib.h>`.
- Sono implementate funzioni personalizzate per la gestione delle carte e dei conti.
- Il gioco utilizza un approccio basato su menu per la navigazione e le scelte dell'utente.

## Considerazioni Finali
Questo progetto è un'esercitazione pratica nel campo della programmazione in C, con un focus particolare sulla gestione della memoria e sulle strutture dati.

