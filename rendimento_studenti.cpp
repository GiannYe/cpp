#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void stampaMat(float mat[][10], int r, int c) {
    //stampa le intestazioni
    cout << "   ";
    for (int i = 0; i < r; i++) {
        cout << "M" << i + 1 << "\t";
    }
    cout << endl;

    //stampa una linea di separazione
    cout << "   ";
    for (int i = 0; i < r; i++) {
        cout << "____" << "\t";
    }
    cout << endl;

    //stampa gli elementi e i valori
    for (int i = 0; i < r; i++) {
        cout << i + 1 << " |";
        for (int j = 0; j < c; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void stampaVett(float v[], int dim) {
    for (int i = 0; i < dim; i++) {
        cout << v[i] << "  ";
    }
    cout << endl;
}

float ass(float n) {
    if (n < 0) {
        return -n;
    }
    return n;
}

void popolamentoMat(float mat[][10], int r, int c) {
    /*
    per generare voti da 2 a 10 includendo anche i 2.5, 3.5, 4.5 ecc,
    generiamo un numero casuale da 4 a 20 e dividiamolo per 2. Se cosi'
    torna un numero pari, allora in voto sara' un voto intero. se e'
    dispari, allora quel 1 in piu' diventera' un 0.5
    */
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = (rand() % 17 + 4) / 2.0;
        }
    }
}

void calcMediaVoti(float mat[][10], float mediaVoti[], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            mediaVoti[i] += mat[i][j];
        }
        mediaVoti[i] /= c;
    }
}

float Max(float v[], int dim) {
    if (dim == 1) {
        return v[0];
    } else {
        float m = Max(v, dim - 1);
        if (v[dim - 1] > m) {
            return v[dim - 1];
        } else {
            return m;
        }
    }
}

int ricerca(float v[], int dim, float input) {
    /* iterativa
    int c = 0;
    for (int i = 0; i < dim; i++) {
        if (ass(v[i] - input) <= 0.5) {
            c++;
        }
    }
    return c;
    */

    //ricorsiva
    int a = 0;
    if (dim == 1) {
        if (ass(v[0] - input) <= 0.5) {
            a = 1;
        }
        return a;
    } else {
        if (ass(v[dim - 1] - input) <= 0.5) {
            a = 1;
        }
        return ricerca(v, dim - 1, input) + a;
    }
}

int main() {
    srand(time(NULL));

    int N_STUD;
    const int MATERIE = 10;

    cout << "Numero di studenti: ";
    cin >> N_STUD;
    cout << endl;

    float mat[N_STUD][MATERIE];
    /*
    si fa N_STUD come la quantita' di righe, perche' essa
    potrebbe essere un numero molto grosso, dunque e'
    meglio scorrere su e giu' anziche' scorrere a destra e
    a sinistra
    */

    popolamentoMat(mat, N_STUD, MATERIE);
    stampaMat(mat, N_STUD, MATERIE);

    float mediaVoti[N_STUD] = {0};

    calcMediaVoti(mat, mediaVoti, N_STUD, MATERIE);
    cout << "medie: ";
    stampaVett(mediaVoti, N_STUD);
    cout << "Media max: " << Max(mediaVoti, N_STUD) << endl;

    int input;
    cout << "Inserisci un voto: ";
    cin >> input;
    cout << "Quantita' di medie simili: " << ricerca(mediaVoti, N_STUD, input) << endl;
}
