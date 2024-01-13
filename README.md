# Blackjack in C

## Descrizione

Il programma consiste nella versione di blackjack giocata negli Stati Uniti, nei casinò online e in alcune navi da crociera. E' strutturato quindi in modo tale da garantire un'esperienza il quanto più realistica seguendo il regolamento di questa versione:

- **Il banco ha inizialmente due carte, di cui una nascosta**
- **Si può splittare in totale 3 volte, con un limite di 4 mazzi**
- **Pagamento alla pari e assicurazioni consentite**
- **Blackjack solo con asso + 10 e paga 3 a 2**

Il gioco comprende tutti questi aspetti in aggiunta alle fondamentali strutture che compongono il gioco:

- **Mazzo da 52 carte**
- **Gestione degli assi**
- **Puntate**
- **Conto in euro**

Il gioco è banco vs utente. Non ci sono altri giocatori, quindi sarà una partita 1v1.

## Funzionalità

- **Esperienza di gioco autentica**: Questa riproduzione del blackjack usando il linguaggio C presenta tutti gli aspetti di una partita di blackjack utente vs banco.
- **Gestione del mazzo**: Il mazzo di carte è gestito dinamicamente, con la possibilità di rimescolarlo quando necessario. Infatti, le carte vengono estratte da un array da 52 elementi di tipo **Carta**.
- **Gestione degli assi**: Gli assi sono gestiti come nel gioco originale, quindi con la possibilità di scegliere se farlo valere 1, 11 o se scegliere in un secondo momento.
- **Puntate**: Gli utenti possono scegliere tra diverse opzioni di puntata.
- **Gestione del conto**: Gli utenti possono creare un nuovo conto o accedere a un conto esistente. Su questo conto, l'utente potrà caricare la quantità di denaro da usare in una sessione e salvare il proprio conto per accedervi in un secondo momento.
- **Strutture specifiche del gioco**: Sono supportati split fino a 3 volte, assicurazioni, pagamento alla pari, raddoppi di puntata e molto altro.

## Componenti del programma

### Tipi personalizzati

Con l'obiettivo di rendere la UX il più realistica possibile, ho dovuto creare ed implementare due nuovi tipi tramite ADT:

- Il tipo **Carta**, creato apposta per rappresentare ogni carta del mazzo. Questo tipo permette di rappresentare, in una sola struttura, il **valore della carta** *(1, 2 ...10)*, il **tipo della carta** *(cuori, picche...)* e, in caso, la sua **figura** *(jack, regina, re)*.<br>In realtà, solo il valore della carta è rilevante ai fini del funzionamento del programma, in quanto nel blackjack tipo e figure non sono importanti. Ho scelto comunque di implementarli perché alla fine il programma non viene rallentato più di tanto, immerge sempre di più l'esperienza d'uso proprio come se fosse un vero blackjack e anche perché in futuro intendo usare questo codice per crearne una versione avanzata con interfaccia grafica, database dedicato e altre feature che usando la programmazione imperativa con linguaggio C non potrebbero essere implementate così facilmente. Infine, in caso si volessero creare altri giochi con le carte francesi, il tipo è già pronto insieme ai suoi metodi.<br>In questa libreria viene usata a sua volta la libreria `<string.h>` per consentirmi di usare le parole *cuori*, *re* durante la fase di stampa della carta.

- Il tipo **Conto**, che consente all'utente di creare, modificare e accedere ai propri soldi che carica in modo da poter effettuare le puntate. Non è importante ai fini del funzionamento del programma, in quanto è possibile giocare anche senza fare puntate semplicemente eliminandone i riferimenti, ma ho deciso di crearlo sempre per rendere l'esperienza il più realistica possibile. <br>Dal lato tecnico, i dati dell'utente sono immagazzinati in file. In ogni file, chiamato come l'id dell'utente, viene immagazzinato solo il valore intero dei suoi soldi. Il tipo **Conto** è poi in grado di rintracciare l'utente che si logga proprio dall'id, che viene poi usato per cercare il file corrispondente, accedere ad esso leggendo il contenuto che ripeto è solo il valore intero dei soldi rimanenti e infine restituire questo valore al programma principale. Nel programma viene gestito tramite la variabile `contopersona`, che ne gestisce l'id e l'ammontare.<br>Ciò è un banale tentativo di creare un infrastruttura che in C non ha senso creare per questo programma, quella di una vera e propria appplicazione con database per lo storage dei dati dell'utente. Infatti, se avessi voluto creare una cosa così complicata, non avrei scelto il C come linguaggio ma qualcosa di più sensato per operazioni di questo tipo.  

- In aggiunta a queste due nuove librerie che danno vita a due nuovi tipi, è stata creata anche la terza libreria che si basa sulla libreria **Carta**, ovvero la libreria **Blackjack**. Essa non definisce nuovi tipi ma funge da *helper* al gioco principale fornendo metodi basici per la gestione del gioco del blackjack in quello che è appunto il flusso del main, con l'obiettivo di snellire e velocizzare il programma delegando alcune task a questa libreria che prende i fondamenti di **Carta** e li sviluppa aggiungendo alcune delle regole che caratterizzano il blackjack. 

#### Libreria Carta

- Si occupa di gestire tutti gli aspetti relativi alle carte da gioco francesi a 52 carte. Essa è stata creata in modo tale da essere staccata dal blackjack e di poterla utilizzare quindi per altir giochi come il poker.
- Ha 4 funzioni principali:

  - `popolamazzo()`, che come dice il nome popola il mazzo con le 52 carte. Aggiunge per ogni carta valore, radice ed eventuale figura. Viene usata all'inizio del gioco e ogni volta che il mazzo termina le sue carte.
  - `stampamazzo()`, usata poco, stampa tutto il mazzo.
  - `stampacarta()`, ogni volta che viene erogata una carta questa funzione viene chiamata e ne stampa le relative proprietà.
  - `daicarte()`, la principale, consente di erogare una carta e allo stesso tempo sottrarre quella carta dal mazzo e controllare che esso non sia vuoto. In caso, chiama `popolamazzo()`. Per erogare una carta si estrae un numero casuale da 0 a `dimensionedelmazzo`, variabile intera che tiene traccia di quante carte rimangono nel mazzo.

#### Libreria Conto

- Si occupa di gestire i soldi dell'utente.
- Ha 6 funzioni, di cui 5 principali e una che non viene portata all'interno del main:

  - `impostaconto()`, usata per chi iscrive la prima volta alla piattaforma, crea l'id del giocatore tramite la funzione `creaidgiocatore()`, l'unica non pubblicata in `Conto.h`, e ne aggiorna l'ammontare in base a ciò che riceve in input. Restituisce i dettagli poi nella variabile `contopersona`.
  - `recuperaconto()`, restituisce il conto del giocatore in base all'id.
  - `aggiornaammontare()`, la principale, aggiorna l'ammontare del giocatore in base ad id e soldi da modificare.
  - `ottieniid()`, non usata, restituisce l'id del giocatore in base alla variabile `contopersona`.
  - `ottieniammontare()`, anch'essa non usata, restituisce l'ammontare in base a `contopersona`.
  - `creaidgiocatore()`, controlla a quale utente si è arrivati nel file `id.txt` e in base a quello stabilisce l'id del nuovo utente, creando il suo file e aggiungendo la relativa entry nel file `id.txt`.

#### Libreria Blackjack

- Fornisce aiuto al programma principale immagazzinando funzioni che aiutano la riusabilità e il mantenimento del codice.
- Ha 3 funzioni principali:
  - `sceglipuntata()`, che permette all'utente di scegliere quanto giocarsi. Ogni puntata è conservata nel vettore `puntate` aggiornabile con nuove puntate semplicemente aggiungendo il valore desiderato nel vettore. Infatti, è tutto gestito dinamicamente e non ci sarà bisogno di modificare cicli o altre porzioni di codice per gestire una nuova puntata.
  - `sceglivaloreassoutente()`, che sceglie quale valore dell'asso far uscire. Può farlo automaticamente o in base alla scelta dell'utente. Infatti, se determina che un eventuale 11 farebbe sballare il mazzo allora restituisce 1, altrimenti può far scegliere all'utente quanto farlo valere. Può anche gestire un eventuale scelta in seguito del valore dell'asso, aggiornando `assi` tramite un counter di interi che viene poi assegnato alla cella di questo vettore. 
  - `sceglivaloreassobanco()`, stessa cosa di prima ma per il banco, che decide senza bisogno di scelta manuale da parte dell'utente. 

### Programma principale

#### Dichiarazione

Alla base del programma c'è l'array `carte`, di tipo **Carta**, composto da 52 elementi, ovvero le carte del mazzo. Questo array sarà usato per qualsiasi operazione riguardante la parte del gioco vero e proprio, ovvero l'estrazione delle carte. La dimensione di questo array è determinata dalla variabile `dimensionedelmazzo`, che gioca un ruolo cruciale nel programma in quanto è la variabile su cui si baserà il rimescolamento delle carte quando nell'array `carte` saranno esauriti i valori ma anche per tenere traccia di quante carte sono state fin ora estratte.

Per la gestione del conto, c'è la variabile `contogiocatore`, di tipo **Conto**, che si occuperà di restituire e modificare l'ammontare in denaro che l'utente ha a disposizione per le sue puntate. Dopo ogni mossa che comporta l'aggiornamento di quest'ultimo, come per esempio l'assicurazione, esso viene immediatamente aggiornato.

Qualsiasi mano (che sia del banco e dell'utente, compreso eventualmente i vari split) è gestita all'interno della matrice `cartegiocatori`. Essa è una matrice di vettori **Carta**, dove la prima riga è riservata esclusivamente alle carte del banco. Dalla seconda in poi invece le righe sono riservate alle carte del giocatore. A livello di codice essa è una matrice di puntatori a vettori **Carta**, caratterizzata dal fatto che è una matrice con allocazione dinamica. Infatti, essa ad inizio programma viene allocata in memoria per solamente le prime due righe. Ogni volta che poi si presenta uno split, essa viene allargata di uno per far spazio al nuovo vettore di **Carta**.

Seguono la stessa logica anche i vettori `somme`, `assi` e `raddoppia`. Essi sono fondamentali per tener traccia di qualsiasi azione e scelta l'utente faccia durante una particolare mano. Il vettore `assi` serve per tener traccia di quanti assi quella mano totalizza, in modo tale che, se il giocatore scegliesse di gestirli dopo, si possa tener traccia di questa scelta e gestira quando l'utente si fermerà. Il vettore `somme` è forse quello più importante fra i tre, perché tiene traccia dell'ammontare di ogni mano. Infatti, le strutture di controllo alla fine della funzione `gioca()` si basano proprio sulle celle di questo vettore per controllare i risultati delle varie mani. Infine il vettore `raddoppia` serve per tener traccia di quale mano il giocatore effettua un raddoppio, per poi capire alla fine quanto restituire in termini di denaro in caso di vittoria o pareggio. Quando si raddoppia, non si potrà più chiedere carta per quella mano. Le celle di questi vettori sono istanziate all'inizio del codice ed ogni volta che il giocatore effettua uno split, dato che le mani aumentano e c'è bisogno di tracciare anche loro. 

Infine le costanti del tipo `ANSI_COLOR...` servono per colorare i vari messaggi stampati in output. Ciò serve per dare una maggiore leggibilità al programma. Ogni colore ha un significato:

- **Rosso**: messaggi di sconfitta.
- **Verde**: messaggi di vittoria.
- **Giallo**: messaggi di info.
- **Magenta**: messaggi relativi alle mosse del banco.
- **Ciano**: messaggi relativi alle mosse dell'utente.

#### Main()

Nel main, come prima cosa, viene fatto creare un account all'utente o, in caso di account già esistente, viene fatto l'accesso, restituendo l'ammontare salvato precedentemente.
Successivamente, viene chiesto se procedere o no con il caricamento di nuovi fondi, obbligatorio per i nuovi account.

Si è ora pronti per giocare. Ciò avviene usando la funzione `gioca()`, di fondamentale importanza perché contiene al suo interno tutto il gioco.<br>Ho scelto di procedere in questo modo in quanto essa è rinchiusa in un ciclo `while(1)` infinito, perciò ogni volta che la partita finisce, invece che uscire dal programma, semplicemente si esce dalla funzione e si rientra subito dopo, in quanto si può uscire dalla funzione ma non dal while.

#### Gioca()

La funzione `gioca()`, come già detto, racchiude tutta la logica del blackjack.

Viene chieso innanzitutto quanto si vuole puntare usando la funzione `sceglipuntata()`, che restituisce il valore da puntare. La gestione delle puntate, come ho già detto, viene gestita in tempo reale in base alle scelte dell'utente. Ogni volta che toccherà puntare altri soldi durante il corso della partita, questi soldi verranno subito scalati dal conto del giocatore. Le eventuali vincite finali saranno strutturate in modo tale che l'utente veda quanto ha vinto contando anche i soldi restituiti dalle puntate, perciò il quantitativo della vittoria prenderà in considerazione l'ultimo valore aggiornato del conto del giocatore.

Dopodiché, si procede con la logica pari passo del blackjack:

1. Vengono date all'utente le prime due carte tramite la funzione `daicarte()`. Stesso discorso per il banco, dove però una rimane nascosta.<br>Queste due carte finiscono nei rispettivi vettori della matrice. Ogni operazione di restituzione di una carta non comporta solo quello. Infatti, ogni volta che questa funzione viene invocata, subito dopo viene invocata la funzione `stampacarta()`, che stampa appunto il valore della carta, la radice (fiori, picche...) e quale figura è. Subito dopo si procede con il memorizzare il valore della carta all'interno della somma della mano, quindi nel vettore `somme` nella cella relativa. Qua avviene anche la determinazione dell'asso, se 1, 11 o se scegliere il valore in un secondo momento.
2. Vengono eseguiti i primi controlli sulle carte appena erogate. Essi riguardano principalmente gli assi, in quanto questa fase del gioco rappresenta l'unico momento in cui è possibile fare un blackjack. Il blackjack di per se non è fare 21 con le carte ma avere un 10 e un asso. Detto questo, i vari controlli comprendono intanto il controllare se o banco o utente abbia fatto blackjack. In caso di doppio blackjack, la partita finisce in pareggio con la restituzione dei soldi della puntata all'utente. Successivamente, si annidano ancora di più per dare vita alle assicurazioni e al pagamento alla pari. Entrambe avvengono se il banco ha come prima carta pescata un asso. In caso l'utente non abbia fatto blackjack, allora comparirà l'opzione di assicurazione, che consente di giocare metà della propria puntata per riguadagnare tutti i soldi persi in caso il banco abbia come carta nascosta un 10. Il secondo tipo di controllo invece riguarda il pagamento alla pari, che capita nel momento in cui l'utente ha fatto blackjack ma il banco ha un asso come carta scoperta. Viene chiesto quindi se si è disposti ad accettare una vincita di una puntata normale piuttosto che una 3 a 2 classica del blackjack utente, in quanto può essere che anche il banco abbia blackjack e che quindi la partita finisca in pareggio.
3. In caso di carte di valore uguale, il giocatore può decidere se splittare. Questo comporta la divisione della mano in due mazzi distinti, ciascuno con, come prima carta, una delle due carte uscite all'inizio. L'utente qua si giocherà un'altra puntata dello stesso valore di quella iniziale. Se l'utente deciderà di splittare, allora il processo sarà uguale identico al punto 2, solamente con la nuova riga nella matrice `cartegiocatore` che rappresenta la nuova mano. Vengono anche allocate nuove celle per i 3 vettori.
4. In caso di ulteriori carte dello stesso valore, allora l'utente può decidere se splittare un ulteriore volta per un massimo di 4 mazzi se entrambi i mazzi inziali abbiano entrambi due carte dello stesso valore.
5. A prescindere dal numero di mazzi in gioco, si procede ora con il gioco vero e proprio, quindi ora l'utente potrà decidere se chiedere carta, fermarsi o raddoppiare. Questa scelta viene effettuata per ogni mazzo grazie ad un ciclo che tiene conto di a quale mazzo si è arrivati. Infatti, la variabile intera `righecartegiocatore` serve proprio a questo, per capire quante mani ci sono in gioco. Su questa variabile si basa non solo questo processo ma anche quello di determinazione del risultato della partita per ogni mano, quindi merita una menzione.
6. In base alle scelte del giocatore, quando tutte le sue mani sono gestite si procede con il gestire le carte del banco. Per erogare le carte, il banco si basa esclusivamente sulla regola per la quale deve tirare carta fino ad un minimo di 17. Non potrà chiedere più carte, anche se con il valore uscito perderebbe tutte le mani. In caso di soft 17, ovvero la situazione in cui le sue prime carte iniziali sono un asso e un 6, il banco ha un po' più versatilità, infatti se con un soft 17 dovesse uscire una carta inferiore a 5 il valore della somma delle sue carte prenderebbe come partenza il 17,mentre con un valore superiore o uguale a 5, in caso di somma con 17 il banco sballerebbe, perciò porta la sua somma iniziale a 7 e procede a tirare carta fino al vero e proprio 17.
7. Si arriva ora alla parte finale in cui si controllano le somme si capisce quanto l'utente ha vinto. Come prima cosa vengono eseguiti controlli sull'utente che sballa con tutti i mazzi, che comporta la perdita di tutto, o se il mazzo sballa. Importante capire che se il mazzo sballa non è detto che automaticamente il giocatore vince tutto, perche ogni volta che il giocatore sballa con un mazzo, esso perde a prescindere da quello che farà il banco. Il giocatore vincerà sempre con qualsiasi valore minore o uguale a 21 se il mazzo sballa.<br>Comunque, dopo questi controlli preliminari, grazie alla variabile `righecartegiocatore` si gestisce ogni mazzo individualmente, confrontando la sua somma con quella del banco. In base al risultato, viene gestito il conto dell'utente, tenendo conto di eventuali raddoppi.
8. Inizia così una nuova partita.

## Aspetti

### Aspetti Logici

- Il controllo sui valori delle somme delle carte sono una serie di `if` annidati. Si diramano principalmente in condizioni se l'utente/banco ha sballato, ha fatto blackjack o se la somma di uno è più grande dell'altra.

- Il banco non è ne intelligenza artificiale ne un'altra persona. Segue semplicemente la regola base che il banco deve chiedere carta minimo fino a 17, e se il totale delle sue carte è inferiore a quello dell'utente, chiede ancora carte, altrimenti si ferma.

- Il conto funziona attraverso i file. Su di essi, chiamati come l'id del giocatore che inserisce in fase di creazione, verrà immagazzinato l'ammontare di euro caricati dal giocatore. Per tener traccia dell'id da usare per il prossimo account da creare, esiste un file `id.txt` che contiene una serie di caratteri *1*. Questi caratteri servono per contare il numero di id, e quindi di account, creati fin ora. Ogni volta che creo un utente, un carattere *1* viene aggiunto al file e l'utente prende l'id calcolato come quantità di *1* + 1.

- L'asso del banco è determinato in base alle carte dell'utente. In base alla situazione, viene deciso qual è il valore corretto da assegnare.

- Le puntate sono gestite dinamicamente. E' possibile aggiungere nuove entries senza modificare il codice, basta solo aggiungere il valore da immettere nella dichiarazione dell'array `puntate`.

- La stampa delle carte è effettuata tramite la funzione `stampacarta()`. Essa non solo stampa il valore, ma anche tipo ed eventuale figura della carta in base ai valori della carta passata.

- Il mazzo è di 52 carte vere. Ad ogni mano, le carte uscite vengono rimosse dal mazzo. Nel momento in cui il mazzo contiene 0 carte, esso viene ripopolato. L'estrazione di una carta avviene scegliendo un numero random da 0 a `dimensionedelmazzo` in quel momento, che varia in base alla quantità di carte uscite.

- Viene usato un menu a scelta per ogni tipo di interazione con il programma. La scelta è gestita usando non i valori direttamente da usare ma scegliendo, fra un range di risposte, quella desiderata.

- Dopo ogni interazione con l'utente, il programma si riserva un secondo di sleep in modo tale da non confondere l'utente andando troppo veloce. Le varie funzioni `sleep()`, che vanno dai 1 ai 2 secondi massimo, servono proprio per questo, per limitare la velocità del programma e non farlo risultare troppo incomprensibile all'utente, che non riuscirebbe sennò a stare al passo con la frequenza di stampa delle istruzioni.

- Per rendere più versatili le funzioni, ho adottato delle variabili booleane che mi aiutavano a differenziare la funzione per due casi distinti dello stesso tipo. Per esempio, la scelta del valore dell'asso è stata differenziata in scelta durante la partita e scelta dopo essersi fermati. Ciò è stato possibile con il parametro `isfermato`, che come dice il nome riusciva a far capire al programma quando l'utente si è fermato.

- Ogni output è caratterizzato da un colore diverso tramite le costanti del tipo `ANSI_COLOR...`, con l'obiettivo di dare una maggiore leggibilità al programma. Ogni colore ha un significato:
  - **Rosso**: messaggi di sconfitta.
  - **Verde**: messaggi di vittoria.
  - **Giallo**: messaggi di info.
  - **Magenta**: messaggi relativi alle mosse del banco.
  - **Ciano**: messaggi relativi alle mosse dell'utente.

### Aspetti Tecnici

- Il codice sfrutta librerie standard come `<stdio.h>`, `<stdbool.h>` `<stdlib.h>` per task comuni come l'utilizzo di funzioni I/O, booleane e puntatori, e librerie più specifiche come `<time.h>` e `<windows.h>` per le funzioni random e sleep.
- Le librerie custom create da me `Carte.h` e `Conto.h` sono implementate sottoforma di ADT. Vogliono infatti ricordare un oggetto, perciò il loro codice sorgente è strutturato come se fosse un oggetto vero e proprio, con attributi definiti attraverso `struct` e metodi che non sono altro che normali funzioni protette grazie ai file `.h`, che ne mostrano solo gli attributi e il prototipo.
- Vengono usati puntatori per dialogare attraverso le varie funzioni dei tipi di dato **Carta** e **Conto**. Per esempio, `dimensionedelmazzo` è sempre passata come riferimento poiché ho bisogno di accedere continuamente al suo valore originale e non ad una sua copia. Stesso discorso per la carta estratta in quel momento, che va passata alle varie funzioni di stampa e controllo. Il passaggio per valore è usato raramente.
- I file vengono gestiti in read/write e append.
- L'eseguibile è compatibile solo con il sistema operativo windows, in quanto usa la libreria `<windows.h>` per le funzioni `sleep()`.

## Considerazioni Finali

Ho già realizzato un blackjack in passato usando javascript, a cui si può giocare qua (<https://www.blackjack-it.com/>).

Uno dei tanti obiettivi di questo software, oltre che per l'esame orale di programmazione, era quello di migliorare questa versione già esistente, obsoleta e non realistica. Intendo perciò tradurre questo codice in linguaggi più adatti ad applicazioni web, che sono in grado di gestire database e interfacce grafiche.

Infatti, ogni elemento del codice è pensato proprio per essere tradotto in elementi più specifici, ad esempio la stampa della carta, che avviene per ora solo come scritta, sarà usata per determinare quale foto della carta emettere a video piuttosto che una scritta poco chiara, oppure il conto utente sarà trasformato da file in database con relativo supporto alle microtransazioni che consentiranno a chi usa l'applicazione di caricare soldi veri.

Tornando al codice C, ho cercato di usare ogni argomento affrontato nel programma di studi in modo tale non solo da far risultare questo software il più completo e standard possibile ma anche per permettermi di ripassare argomenti già visti nei precedenti anni di studio.