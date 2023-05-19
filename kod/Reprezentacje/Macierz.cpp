#include "Macierz.h"

using namespace std;

Macierz::Macierz(int rozm)
{
    //Alokacja pami�� dla tablicy przechowuj�cej informacje o grafie.
    this->rozm = rozm;
    baza = new int[rozm * rozm];

    //Zeracja tablic�.
    for (int i = 0; i < rozm; i++)
        for (int j = 0; j < rozm; j++)
            baza[i * rozm + j] = INT_MAX;
}

Macierz::~Macierz()
{
    delete[] baza;
}

void Macierz::dodajKrawedz(int wierzcholekPocz, int wierzcholekKon, int waga)
{
    try
    {
        baza[wierzcholekPocz * rozm + wierzcholekKon] = waga;
    }
    catch (out_of_range&)
    {
        cout << "nieprawidlowe dane!" << endl;
    }
}

void Macierz::usunKrawedz(int wierzcholekPocz, int wierzcholekKon)
{
    try
    {
        //Brak kraw�dzi to 'INT_MAX' w macierzy sasiedztwa.
        baza[wierzcholekPocz * rozm + wierzcholekKon] = INT_MAX;
    }
    catch (out_of_range&)
    {
        cout << "nieprawidlowe dane!" << endl;
    }
}

int Macierz::znajdzKrawedz(int wierzcholekPocz, int wierzcholekKon)
{
    int value = 0;
    try
    {
        //Zwracamy wag� kraw�dzi dla danych wierzcho�k�w.
        value = baza[wierzcholekPocz * rozm + wierzcholekKon];
    }
    catch (out_of_range&)
    {
        cout << "nieprawidlowe dane!" << endl;
    }
    return value;
}

int Macierz::rozmiar()
{
    //Ilo�� wierzcho�k�w grafu.
    return rozm;
}

void Macierz::wyswietl()
{
    //Obliczamy ilo�� cyfr potrzebn� do zapisania danej liczby.
    int padding = ceil(log10(rozm * rozm));
    for (int i = 0; i < rozm; i++)
    {
        for (int j = 0; j < rozm; j++)
        {
            int value = baza[i * rozm + j];
            if (value == INT_MAX) value = 0;
            //Wyr�wnacja do lewej na podstawie maksymalnej wielko�ci.
            cout << setw(padding) << value << ' ';
        }
        cout << "\n";
    }
}