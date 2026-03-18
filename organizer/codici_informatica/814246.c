/* Luca Giusto 814246 */

#include <stdio.h>
#include <stdlib.h>

#define FINE '0' /* valore che termina la sequenza */
#define V 4 /* dimensione del vettore "alfabeto" */
#define C 'A' /* carattere della sottostringa */
#define L 3 /* lunghezza della sottostringa */

char alfabeto[V]; /* variabile globale contenente l'alfabeto di simboli
                  ammessi */

/* La parte principale del programma è formato da un ciclo do-while, il 
quale, fin tanto che la variabile c è diversa da 0, legge dallo standard
input il valore della variabile c e incrementa la variabile pos. Al suo 
interno, inoltre, sono presenti 4 blocchi if e 2 blocchi else: se c è 
uguale a 0 (a),il programma si interrompe, altrimenti prosegue. Inoltre,
se c non appartiene all'alfabeto consentito (b), si interrompe, 
stampando un errore (f). In ultima, se c è proprio uguale ad A (c), 
incrementa la variabile a; se quest'ultima variabile raggiunge o supera 
il valore di 3 (e), il programma incrementa la variabile n e inserisce 
la posizione corrente in testa alla lista concatenata tramite la 
funzione "inserisci". Se il punto (c) non è verificato, la  variabile a 
assume il valore 0, e i punti (d) e (e) non vengono eseguiti. 
Se alla fine del ciclo do-while non sono state trovate delle 
sottostringhe, e quindi la variabile n non è stata valorizzata, 
il programma stampa la seguente dicitura, altrimenti stampa il valore di
n (con la funzione "printf") e i valori presenti nella lista concatenata 
tramite la fumzione "stampa" */

/* Ho inserito ulteriori commenti prima di ogni funzione */

/* Di seguito ho creato un nuovo tipo in modo da non dover ripetere la 
dichiarazione della struttura, la quale rapprestenta una lista 
concatenata. Essa, all'inizio dell'esecuzione, è vuota, e verrà via via 
riempita con i valori (inseriti dalla testa della lista) calcolati dal 
programma. Questo è possibile grazie alla presenza di una variabile di 
tipo puntatore (1) che punta alla testa della lista, variabile che 
inizialmente avrà valore NULL */

typedef struct occorrenza REP; 
struct occorrenza {
    int posizione;
    REP *prox;
};                                         

/* La funzione "stampa" qui di seguito percorre la lista, e stampa via 
via il campo posizione */

void stampa (REP *t) {
    while (t != NULL) {
        printf("%d ", t->posizione);
        t = t->prox;
    }
    printf("\n");
    return;
}

/* La funzione qui di seguito ha il compito di allocare lo spazio 
necessario per un nuovo elemento di tipo REP, assegnare al suo campo 
posizione un valore b e di produrre come risultato un puntatore a questo 
nuovo elemento */

REP *nuova_occorrenza (int b) {
    REP *r;
    r = (REP *) malloc (sizeof(REP));
    if (r == NULL) exit(EXIT_FAILURE);
    r->posizione = b;
    r->prox = NULL;
    return r;
}

/* La funzione di inserimento definita di seguito dichiara una variabile
di tipo puntatore a REP (nuova), alla quale assegna il risultato 
dell'invocazione della funzione nuova_occorrenza */

REP *inserisci(int b, REP *t) {
    REP *nuova;
    nuova = nuova_occorrenza (b);
    nuova->prox = t;
    return nuova;
}

/* Quella che segue è una funzione che riceve come argomento una 
variabile x di tipo carattere, e restituisce, come risultato, un intero. 
Tramite un ciclo for, verifica che la variabile x sia contenuta nello
alfabeto. Se sì, restituisce come risultato 1, ed esce dal ciclo tramite 
un'istruzione break. Altrimenti, restituisce come risultato 0. */

int verifica(char x) { 
    int risultato = 0; 
    for (int i=0; i < V; i++) {
        if (x == alfabeto[i]) {
            risultato = 1;
        break; 
        }
    }
    return risultato;
}
            
    
int main (int argc, char * argv[]) {
    
    alfabeto[0] = 'A';
    alfabeto[1] = 'C';
    alfabeto[2] = 'T';
    alfabeto[3] = 'G';
    
    char c = 0; /* variabile introdotta tramite lo standard input */
    int a = 0; /* variabile utilizzata per contare i caratteri A 
               presenti in una stringa */
    int n = 0; /* variabile che indica il numero delle sottostringhe di
               caratteri AAA */
    int pos = 1; /* variabile che indica la posizione raggiunta
                 all'interno del flusso dei dati di input */
    
    REP *testa;                                        	       /* (1) */
    testa = NULL;
    
    do {
    
        scanf(" %c", &c);
        ++pos;
        
        if (c != FINE) {                         	       /* (a) */
            if (verifica(c) == 1) {                  	       /* (b) */
                if (c == C) {                                  /* (c) */
                    ++a;
                }
                else {                                         /* (d) */
                    a = 0;
                }
                if (a >= L) {                                  /* (e) */
                    ++n;
                    testa = inserisci(pos-L, testa);
                }
            }        
            else {                                             /* (f) */
            printf("Valore non compreso nell'alfabeto. \n");
            exit(EXIT_FAILURE);
            }
        }
            
    } while (c != FINE);
    
    if (n == 0) {
        printf("Nessun risultato trovato. \n");
    }
    
    else {
        printf("%d ", n);
        stampa(testa);
    }
    
    exit(EXIT_SUCCESS);
}
