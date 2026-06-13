#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Film {
    unsigned int cod_film;
    float valutazione_media = {0};
    unsigned int visualizzazioni = 0;
    unsigned int voti_positivi = 0;
};

struct Valutazione {
    float stelle;
    int cod_film;
};

struct Giudice {
    Valutazione valutazioni[10];
};

void generaCod_film(Film v[], int dim) {
    for (int i = 0; i < dim; i++) {
        v[i].cod_film = i;
    }
}

void scegliFilm(Giudice v[], int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < 10; j++) {
            v[i].valutazioni[j].cod_film = rand() % dim; //da 0 a dim escluso
        }
    }
}

void generaValutazioni(Giudice v[], int dim) {
    for (int i = 0; i < dim; i++) {
        //cout << "Giudice " << i + 1 << ": ";
        for (int j = 0; j < 10; j++) {
            v[i].valutazioni[j].stelle = (rand() % 10 + 1) / 2.0; //numeri da 0.5 a 5
            //cout << v[i].valutazioni[j].stelle << " ";
        }
        //cout << endl;
    }
}

void calcValutazioneMedia(Giudice g[], Film f[], int dim_g, int dim_f) {
    //metti come accumulatore film[i].valutazione_media
    //per capire di quale film si tratta usa i cod_film

    //per ogni film...
    for (int x = 0; x < dim_f; x++) {
        //conta la quantita' di voti
        int c = 0;
        //guarda il voto di ogni giudice
        for (int i = 0; i < dim_g; i++) {
            for (int j = 0; j < 10; j++) {
                //se il cod_film del voto corrisponde al cod_film del film
                if (g[i].valutazioni[j].cod_film == f[x].cod_film) {
                    //somma il voto alla valutazione media del film
                    f[x].valutazione_media += g[i].valutazioni[j].stelle;
                    f[x].visualizzazioni++;
                    if (g[i].valutazioni[j].stelle >= 4.0) {
                        f[x].voti_positivi++;
                    }
                }
            }
        }
        f[x].valutazione_media /= float(f[x].visualizzazioni);
    }
}

void InsertionSort(Film v[], int dim) {
    for (int i = 1; i < dim; i++) {
        Film temporanea = v[i];
        int j = i - 1;
        while ((j >= 0 ) && (v[j].valutazione_media < temporanea.valutazione_media)) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = temporanea;
    }
}

void stampaVett(Film v[], int dim) {
    for (int i = 0; i < dim; i++) {
        cout << "Film " << v[i].cod_film << ": " << v[i].valutazione_media << endl;
    }
    cout << endl;
}

void stampaMaggiorNumDiVisualizzazioni(Film v[], int dim) {
    Film m = v[0];
    for (int i = 1; i < dim; i++) {
        if (m.visualizzazioni < v[i].visualizzazioni) {
            m = v[i];
        }
    }
    cout << "Film piu' visto: " << m.cod_film << endl;
}

void stampaPiuVotato(Film v[], int dim) {
    Film m = v[0];
    for (int i = 1; i < dim; i++) {
        if (m.voti_positivi < v[i].voti_positivi) {
            m = v[i];
        }
    }
    cout << "Film piu' votato: " << m.cod_film << endl;
}

int main() {
    srand(time(NULL));

    const int dim_film = 25;
    Film film[dim_film];

    const int dim_giudici = 100;
    Giudice giudici[dim_giudici];

    generaCod_film(film, dim_film);
    scegliFilm(giudici, dim_giudici);

    generaValutazioni(giudici, dim_giudici);
    calcValutazioneMedia(giudici, film, dim_giudici, dim_film);

    //Insertion sort in ordine decrescente per il vettore film[] in base a film[i].valutazione_media
    InsertionSort(film, dim_film);

    //stampa i risultati
    stampaVett(film, dim_film);

    stampaMaggiorNumDiVisualizzazioni(film, dim_film);
    stampaPiuVotato(film, dim_film);
}
