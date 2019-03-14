#include <iostream>
using namespace std;

#define ZADANIA 4
#define MASZYNY 2

int sumaWszystkichCzasow(int tablica_czasow[][ZADANIA], int nrMaszyny, int nrZadania)
{
    int suma = 0;
    for (int i = 0; i < nrMaszyny; i++)
    {
        for (int j = 0; j < nrZadania; j++)
        {
            suma += tablica_czasow[i][j];
        }
    }
    return suma;
}

bool sprawdzZadanie(int kolejnoscZadan[ZADANIA], int zadanie) {
    for (int i=0; i < ZADANIA; i++) {
        if (kolejnoscZadan[i] == zadanie) {
            return false;
        }
    }
    return true;
}

int main()
{
    // Algorytm Johnson'a dla dwuch maszyn

    // Tablice do przechowywania zadań
    const int nrMaszyny = 3, nrZadania = 4;
    int tablica_czasow[nrMaszyny][nrZadania];
    int kolejnosc_zadan[ZADANIA];
    int lista_1[ZADANIA];
    int lista_2[ZADANIA];

    for (int i = 0; i < nrZadania; i++) // wypełnienie pustych list
        kolejnosc_zadan[i] = -1;
    for (int i = 0; i < nrZadania; i++) // wypełnienie pustych list
        lista_1[i] = lista_2[i] = -1;

    // Uzupełnienie lisy czasami
    // tablica_czasow[0][0] = 6;
    // tablica_czasow[0][1] = 9;
    // tablica_czasow[0][2] = 4;
    // tablica_czasow[0][3] = 7;
    // tablica_czasow[0][4] = 6;
    // tablica_czasow[0][5] = 5;

    // tablica_czasow[1][0] = 4;
    // tablica_czasow[1][1] = 8;
    // tablica_czasow[1][2] = 9;
    // tablica_czasow[1][3] = 2;
    // tablica_czasow[1][4] = 3;
    // tablica_czasow[1][5] = 6;
    tablica_czasow[0][0] = 5;
    tablica_czasow[0][1] = 4;
    tablica_czasow[0][2] = 4;
    tablica_czasow[0][3] = 3;

    tablica_czasow[1][0] = 5;
    tablica_czasow[1][1] = 5;
    tablica_czasow[1][2] = 4;
    tablica_czasow[1][3] = 5;

    tablica_czasow[2][0] = 3;
    tablica_czasow[2][1] = 2;
    tablica_czasow[2][2] = 5;
    tablica_czasow[2][3] = 7;

    int suma = sumaWszystkichCzasow(tablica_czasow, nrMaszyny, nrZadania);

    // przypadek dla 3 maszyn
    if (nrMaszyny == 3) {
        for (int j=0; j < nrZadania; j++) {
            tablica_czasow[0][j] = tablica_czasow[0][j] + tablica_czasow[1][j]; // uzupełnianie sumą czasów 1 i 2 maszyny
            tablica_czasow[1][j] = tablica_czasow[1][j] + tablica_czasow[2][j]; // uzupełnianie sumą czasów 2 i 3 maszyny
        }
    }
    
    // wyswietlanie tablicy czasów
    for (int i=0; i < MASZYNY; i++) {
        cout << "Maszyna " << i << ": ";
        for (int j=0; j < nrZadania; j++)
            cout << tablica_czasow[i][j] << " ";
        cout << endl;
    }


    // szukanie najmniejszej wartosci
    int zadanieOstatecznie=0, maszynaOstatecznie=0;
    int remisCzas = -1, remisZadanie=-1, remisMaszyna=-1;
    int granica = 0;
    int k = 0;
    while (k != nrZadania)
    {
        int najkrotszyCzas = suma;

        for (int i=0; i < MASZYNY; i++) {
            for (int j=0; j < nrZadania; j++) {
                // szukanie remisu
                // if (tablica_czasow[i][j] == remisCzas && sprawdzZadanie(kolejnosc_zadan, j)) {
                //     cout << "Wykryto remis " << tablica_czasow[i][j] << " <- na m " << i + 1 << " | z: " << j+1<< endl;
                //     if ((i == remisMaszyna) && (i == 0)) {       //remis na maszynie 1
                //         tablica_czasow[i+1][j] > tablica_czasow[i+1][remisZadanie] ? j : remisZadanie;
                //     }
                //     if ((i == remisMaszyna) && (i != 0)) {       //remis na maszynie 1
                //         tablica_czasow[i-1][j] > tablica_czasow[i-1][remisZadanie] ? j : remisZadanie;
                //     }
                // }

                if ((tablica_czasow[i][j] <= najkrotszyCzas) && sprawdzZadanie(kolejnosc_zadan, j)) {   // jak zadanie już było to false
                    najkrotszyCzas = tablica_czasow[i][j];
                    zadanieOstatecznie = j;
                    maszynaOstatecznie = i;
                }
            }
        }
        remisCzas = najkrotszyCzas;
        remisZadanie = zadanieOstatecznie;
        remisMaszyna = maszynaOstatecznie;
        
        cout << k << " - Najkrótszy czas: -> " << najkrotszyCzas << " <- na maszyniie " << maszynaOstatecznie + 1 << " | zadanie: " << zadanieOstatecznie+1 << endl;

        if (maszynaOstatecznie == 0) {  
            for (int i=0; i < nrZadania; i++) {     // daje zadanie na koniec lisy
                if (lista_1[i] == -1) {
                    lista_1[i] = zadanieOstatecznie;
                    break;
                }
            }
        }

        if (maszynaOstatecznie == 1) {
            for (int i=nrZadania-2; i >= 0; i--) {  // przesuwa listę o jeden w prawo
                lista_2[i+1] = lista_2[i];
            }
            lista_2[0] = zadanieOstatecznie;        // daje zadanie na początek listy
        }

        // dodaje zadanie do listy zadań, które nie będą dalej brane pod uwagę
        kolejnosc_zadan[k] = zadanieOstatecznie;

        k++;
    }

    cout << "L1: ";
    for (int i=0; i < nrZadania; i++) {
        cout << lista_1[i]+1 << " ";
    }
    cout << endl << "L2: ";
    for (int i=0; i < nrZadania; i++) {
        cout << lista_2[i]+1 << " ";
    }
    cout << endl << "KZ: ";

    // przepisanie zawartości obu list do jednej wspólnej
    for (int i=0, j=0; i < nrZadania; i++) {
        if (lista_1[i] != -1) {
            kolejnosc_zadan[i] = lista_1[i];
            j++;
        }
        else  {
            kolejnosc_zadan[i] = lista_2[i-j];
        }
        cout << kolejnosc_zadan[i]+1 << " "; 
    }
    cout << endl;

    return 0;
}
