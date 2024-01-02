# Blackjack in C

## Descrizione
Il programma consiste in un blackjack a tutti gli effetti con tutti gli aspetti che caratterizzano questo gioco: 
- **Mazzo da 52 carte**
- **Gestione degli assi**
- **Puntate**
- **Conto in euro**

Il gioco è banco vs utente. Non ci sono altri giocatori, quindi sarà una partita 1v1.


## Funzionalità
- **Esperienza di gioco autentica**: Questa riproduzione del blackjack usando il linguaggio C presenta tutti gli aspetti di una partita di blackjack utente vs banco.
- **Gestione del mazzo**: Il mazzo di carte è gestito dinamicamente, con la possibilità di rimescolarlo quando necessario. Infatti, le carte che vengono estratte non sono determinate randomicamente ma estratte da un mazzo di carte (un array da 52 elementi carta).
- **Gestione degli assi**: Gli assi sono gestiti come nel gioco originale, quindi con la possibilità di scegliere se farlo valere 1, 11 o se scegliere in un secondo momento.
- **Puntate**: Gli utenti possono scegliere tra diverse opzioni di puntata.
- **Gestione del conto**: Gli utenti possono creare un nuovo conto o accedere a un conto esistente. Su questo conto, l'utente potrà caricare la quantità di denaro da usare in una sessione e salvare il proprio conto per accedervi in un secondo momento.


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


Viene chieso innanzitutto quanto si vuole puntare usando la funzione `sceglipuntata()`, che restituisce il valore da puntare (la puntata non viene scalata subito, ovvero appena si decide quanto puntare l'ammontare dell'utente rimane invariato. In caso di vincita, verrà poi aggiunta la somma vinta e in caso di perdità allora si che verranno sottratti i soldi dal file con l'ammontare. Ho deciso di fare così perché notavo un rallentamento minimo nella fase di aggiornamento dell'ammontare nel momento in cui andavo a puntare).

Dopodiché, si procede con la logica pari passo del blackjack: 
1. Vengono date all'utente le prime due carte tramite la funzione `daicarte()`. Stesso discorso per il banco, però una rimane nascosta.<br>Queste due carte finiscono nei rispettivi vettori.
2. Vengono eseguiti i primi controlli su eventuali blackjack usciti con queste due carte o se uno dei due ha sballato. Importanti sono i controlli sull'uscita degli assi. Infatti, in caso dovesse uscire un asso fra le prime due carte, la funzione `sceglivaloreassoutente()` si occupa di far scegliere cosa farne dell'asso, se vale 1, 11 o se scegliere dopo in base alle altre carte. Questa è una feature molto importante di questa funzione, in quanto scegliere immediatamente se far valere l'asso 1 o 11 può penalizzare l'utente, mentre invece può decidere dopo, in base alle carte uscite, quanto farlo valere. 
3. Si procede con l'erogare le carte all'utente. Anche qua controlli sul valore della somma delle carte e check su eventuali assi
4. Si procede poi con l'erogazione delle carte del banco. Per farlo, una iterazione con condizione `sommacartecomputer < 17` traduce la regola generale del blackjack che il banco deve per forza tirare fino a 17. 
5. Vengono ancora eseguiti controlli sul valore della somma delle carte del banco
6. In caso il banco non sballi o non vinca per blackjack, allora un'altra iterazione viene eseguita, facendo tirare il banco fino a quando non eguaglia o supera la somma delle carte dell'utente (a menoche non sia già così. In questo caso, il banco si fermerà subito senza tirare altre carte).
7. Quando il banco otterrà una somma di carte maggiore o uguale a 17 (condizione necessaria per farsì che il banco possa continuare a giocare) e superiore alla somma delle carte dell'utente (non è detto in quanto può anche sballare, ma l'obiettivo è quello ovviamente di avere una somma maggiore dell'utente per farsì che il banco vinca), si arriverà al bilancio e confronto delle somme e di conseguenza al decretamento del vincitore. 


## Aspetti Logici
- Il gioco utilizza un approccio basato su menu per la navigazione e le scelte dell'utente.

- Il banco non è ne intelligenza artificiale ne un'altra persona. Segue semplicemente la regola base che il banco deve chiedere carta minimo fino a 17, e se il totale delle sue carte è inferiore a quello dell'utente, chiede ancora carte, altrimenti si ferma. 

- Il conto funziona attraverso i file. Su di essi, chiamati come l'id del giocatore che inserisce in fase di creazione, verrà immagazzinato l'ammontare di euro caricati dal giocatore. 

- L'asso del banco è determinato in base alle carte dell'utente. In base alla situazione, viene deciso qual è il valore corretto da assegnare.

- Le puntate sono gestite dinamicamente. E' possibile aggiungere nuove entries senza modificare il codice, basta solo aggiungere il valore da immettere nella dichiarazione dell'array `puntate`.

- La stampa delle carte è effettuata tramite la funzione `stampacarta()`. Essa non solo stampa il valore, ma anche tipo ed eventuale figura della carta in base ai valori della carta passata. 

- Il mazzo è di 52 carte vere. Ad ogni mano, le carte uscite vengono rimosse dal mazzo. Nel momento in cui il mazzo contiene 0 carte, esso viene ripopolato. L'estrazione di una carta avviene scegliendo un numero random da 0 a `dimensionedelmazzo` in quel momento, che varia in base alla quantità di carte uscite. 

- Viene usato un menu a scelta per ogni tipo di interazione con il programma. La scelta è gestita usando non i valori direttamente da usare ma scegliendo, fra un range di risposte, quella desiderata. 

- Dopo ogni interazione con l'utente, il programma si riserva un secondo di sleep in modo tale da non confondere l'utente andando troppo veloce. Le varie funzioni `sleep()`, che vanno dai 1 ai 2 secondi massimo, servono proprio per questo, per limitare la velocità del programma e non farlo risultare troppo veloce e incomprensibile all'utente, che non riesce a stare al passo con la velocità con la quale vengono stampate le istruzioni.

- Ogni output è caratterizzato da un colore diverso tramite le costanti del tipo `ANSI_COLOR...`, con l'obiettivo di dare una maggiore leggibilità al programma. Ogni colore ha un significato: 
  - **Rosso**: messaggi di sconfitta.
  - **Verde**: messaggi di vittoria.
  - **Giallo**: messaggi di info. 
  - **Magenta**: messaggi relativi alle mosse del banco. 
  - **Ciano**: messaggi relativi alle mosse dell'utente. 

## Aspetti Tecnici
- Il codice sfrutta librerie standard come `<stdio.h>`, `<stdbool.h>` `<stdlib.h>` per task comuni come l'utilizzo di funzioni I/O, booleane e puntatori, e librerie più specifiche come `<time.h>` e `<windows.h>` per le funzioni random e sleep. 
- Le librerie custom create da me `Carte.h` e `Conto.h` sono implementate sottoforma di ADT. Vogliono infatti ricordare un oggetto, perciò il loro codice sorgente è strutturato come se fosse un oggetto vero e proprio, con attributi definiti attraverso `struct` e metodi che non sono altro che normali funzioni protette grazie ai file `.h`, che ne mostrano solo gli attributi e il prototipo dei metodi. 
- Vengono usati puntatori per dialogare attraverso le varie funzioni dei tipi di dato **Carta** e **Conto**. Per esempio, `dimensionedelmazzo` è sempre passata come riferimento poiché ho bisogno di accedere continuamente al suo valore originale e non ad una sua copia. Stesso discorso per la carta estratta in quel momento, che va passata alle varie funzioni di stampa e controllo. Il passaggio per valore è usato raramente. 
- I file vengono gestiti in read/write e append.
- L'eseguibile è compatibile solo con il sistema operativo windows, in quanto usa la libreria `<windows.h>` per le funzioni `sleep()`. 

## Considerazioni Finali
Ho già realizzato un blackjack in passato usando javascript, a cui si può giocare qua (https://www.blackjack-it.com/). 

Uno dei tanti obiettivi di questo software, oltre che per l'esame orale di programmazione, era anche in futuro di usarlo per creare una versione del già esistente software migliorata. Infatti, ogni elemento di questo programma è stato pensato per essere poi usato in qualcosa di più grande, come il conto utente, da implementare in futuro con database e microtransazioni, o la gestione e il tipo delle carte, da implementare poi con foto di carte vere anziché di scritte. 

Ciò non toglie che sia stato un progetto difficile da realizzare. Anzi, proprio perché volevo usare qualsiasi cosa affrontata nel corso per imparare a usare meglio questo linguaggio, che nel corso dei miei studi ho visto solo in terza superiore grossolanamente, il progetto si è complicato più di quanto mi aspettassi all'inizio. 

Confrontanto i due sorgenti, quello del blackjack che realizzai in javascript e questo qua, all'inizio quando ho iniziato a programmare quest'ultimo mi aspettavo si di fare qualcosa di più complesso ma mai così, e devo dire che sono molto soddisfatto, sia di quanto ho appreso durante la programmazione di questo software sia del prodotto finale.
