#include "Macierz.h"

using namespace std;

Macierz::Macierz(int rozm)
{
    //Alokacja pamiêæ dla tablicy przechowuj¹cej informacje o grafie.
    this->rozm = rozm;
    baza = new int[rozm * rozm];

    //Zeracja tablicê.
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
        //Brak krawêdzi to 'INT_MAX' w macierzy sasiedztwa.
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
        //Zwracamy wagê krawêdzi dla danych wierzcho³ków.
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
    //Iloœæ wierzcho³ków grafu.
    return rozm;
}

void Macierz::wyswietl()
{
    //Obliczamy iloœæ cyfr potrzebn¹ do zapisania danej liczby.
    int padding = ceil(log10(rozm * rozm));
    for (int i = 0; i < rozm; i++)
    {
        for (int j = 0; j < rozm; j++)
        {
            int value = baza[i * rozm + j];
            if (value == INT_MAX) value = 0;
            //Wyrównacja do lewej na podstawie maksymalnej wielkoœci.
            cout << setw(padding) << value << ' ';
        }
        cout << "\n";
    }
}