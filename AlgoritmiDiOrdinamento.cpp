#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void riempiVett(int v[], int dim) {
    for (int i = 0; i < dim; i++) {
        v[i] = rand() % 10 + 1;
    }
}

void copiaVett(int v1[], int v2[], int dim) {
    for (int i = 0; i < dim; i++) {
        v2[i] = v1[i];
    }
}

void stampaVett(int v[], int dim) {
    for (int i = 0; i < dim; i++) {
        cout << v[i] << "\t";
    }
    cout << endl;
}

void scambia(int& a, int& b, unsigned int& Asg) {
    int c = a;
    Asg++;
    a = b;
    Asg++;
    b = c;
    Asg++;
}

void shiftR(int v[], int dim, int i, int temporanea, unsigned int& Asg, unsigned int& Cft) {
    int j = i - 1;                              //Iniziamo a guardare l'elemento precedente.
    Asg++;
    while ((j >= 0 ) && (v[j] > temporanea)) {  //Finche' non siamo ancora arrivati all'estremo della sinistra e quello precedente e' maggiore di quello presente,
        Cft += 2;
        v[j + 1] = v[j];                        //sovrascriviamo la posizione di quello presente con quello precedente.
        Asg++;
        //stampaVett(v, dim)
        //v[j] = 0; //solo per scopi estetici
        Asg++;
        j--;                                    //Facciamo un passo a sinistra per vedere se possiamo ancora shiftare gli elementi.
        Asg++;
    }
    v[j + 1] = temporanea;                      //Quando non possiamo piu' shiftare gli elementi, oppure quando arriviamo all'estremo a sinistra, inseriamo l'elemento iniziale qua
    Asg++;
    stampaVett(v, dim);
}

void insertionSort(int v[], int dim, unsigned int& Asg, unsigned int& Cft) {
    for (int i = 1; i < dim; i++) {     //Per ogni elemento a destra di quello a sinistra,
        int temporanea = v[i];          //appogiamo il secondo su una variabile temporanea,
        Asg++;
        shiftR(v, dim, i, temporanea, Asg, Cft);  //shift right
    }
}

void selectionSort(int v[], int dim, unsigned int& Asg, unsigned int& Cft) {
    int i_min;                          //cerchiamo l'elemento minore.
    Asg++;
    for (int i = 0; i < dim - 1; i++) { //Per ogni elemento tranne l'ultimo,
        i_min = i;                      //prendiamo prima quello piu' a sinistra.
        Asg++;
        for (int j = i; j < dim; j++) { //Per i restanti a destra,
            if (v[j] < v[i_min]) {      //confrontiamolo con quello piu' a sinistra,
                Cft++;
                i_min = j;              //se e' piu' piccolo prendiamolo.
                Asg++;
            }
        }
        scambia(v[i], v[i_min], Asg);        //scambiamo il piu' piccolo con quello piu' a sinistra
        stampaVett(v, dim);
    }
}

void bubbleSort(int v[], int dim, unsigned int& Asg, unsigned int& Cft) {
    bool scambio;                           //Controllo di scambi.
    Asg++;
    do {
        Cft++;
        scambio = false;                    //Per ora nessun scambio.
        Asg++;
        for (int i = 0; i < dim - 1; i++) { //Per ogni elemento tranne l'ultimo,
            if (v[i + 1] < v[i]) {          //se quello succesisvo e' minore di questo elemento,
                Cft++;
                scambia(v[i], v[i + 1], Asg);    //scambiamoli.
                stampaVett(v, dim);
                scambio = true;             //C'e' un scambio.
                Asg++;
            }
        }
    } while (scambio);                      //Fai un altra volta finche' ci sono scambi
    Cft--; //perche' il do-while esegue il codice almeno 1 volta
}                                           //(finche' il vettore non e' ancora ordinato)

int main() {
    srand(time(NULL));

    const int dim = 10;
    int vInsertionSort[dim];
    int vSelectionSort[dim];
    int vBubbleSort[dim];

    riempiVett(vInsertionSort, dim);
    cout << "===Vettore iniziale===" << endl;
    stampaVett(vInsertionSort, dim);
    cout << endl;

    copiaVett(vInsertionSort, vSelectionSort, dim);
    copiaVett(vInsertionSort, vBubbleSort, dim);

    unsigned int nAsgInsSort = 0;
    unsigned int nAsgSelSort = 0;
    unsigned int nAsgBubSort = 0;

    unsigned int nCftInsSort = 0;
    unsigned int nCftSelSort = 0;
    unsigned int nCftBubSort = 0;

    cout << "===Insertion sort===" << endl;
    stampaVett(vInsertionSort, dim);
    insertionSort(vInsertionSort, dim, nAsgInsSort, nCftInsSort);
    cout << "Numero di assegnazioni: " << nAsgInsSort << endl << endl;
    cout << "Numero di confronti: " << nCftInsSort << endl << endl;
    cout << "Numero di operazioni: " << nAsgInsSort + nCftInsSort << endl << endl;

    cout << "===Selection sort===" << endl;
    stampaVett(vSelectionSort, dim);
    selectionSort(vSelectionSort, dim, nAsgSelSort, nCftSelSort);
    cout << "Numero di assegnazioni: " << nAsgSelSort << endl << endl;
    cout << "Numero di confronti: " << nCftSelSort << endl << endl;
    cout << "Numero di operazioni: " << nAsgSelSort + nCftSelSort << endl << endl;

    cout << "===Bubble sort===" << endl;
    stampaVett(vBubbleSort, dim);
    bubbleSort(vBubbleSort, dim, nAsgBubSort, nCftBubSort);
    cout << "Numero di assegnazioni: " << nAsgBubSort << endl << endl;
    cout << "Numero di confronti: " << nCftBubSort << endl << endl;
    cout << "Numero di operazioni: " << nAsgBubSort + nCftBubSort << endl << endl;
}
