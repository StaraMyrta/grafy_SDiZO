#pragma once

#include <string>
#include <climits>
#include "../Reprezentacje/Macierz.h"
#include "../Reprezentacje/Lista.h"

//Klasa dla algorytmu Forda-Bellmana.
class FordBellman
{
private:
    int* odleglosc;                     //Tablica najkrótszych odleg³oœci do wierzcho³ków.
    int* poprzednik;                    //Tablica poprzedników dla wierzcho³ków.
public:
    explicit FordBellman(int rozm);     //Konstruktor klasy.
    ~FordBellman();                     //Destruktor klasy.
    void algorytmMacierz(Macierz* macierzSasiedztwa, int wierzcholekStartu);    //Wykonuje algorytm dla grafu w postaci macierzy s¹siedztwa.
    void algorytmLista(Lista* macierzSasiedztwa, int wierzcholekStartu);        //Wykonuje algorytm dla grafu w postaci listy s¹siedztwa.
    int* pierwszyElementOdleglosc();    //Zwraca wskaŸnik na pierwszy element tablicy od³eg³oœci.
    int* pierwszyElementPoprzednikow(); //Zwraca wskaŸnik na pierwszy element tablicy poprzedników.
};