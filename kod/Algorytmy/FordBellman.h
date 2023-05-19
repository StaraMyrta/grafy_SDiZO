#pragma once

#include <string>
#include <climits>
#include "../Reprezentacje/Macierz.h"
#include "../Reprezentacje/Lista.h"

//Klasa dla algorytmu Forda-Bellmana.
class FordBellman
{
private:
    int* odleglosc;                     //Tablica najkr�tszych odleg�o�ci do wierzcho�k�w.
    int* poprzednik;                    //Tablica poprzednik�w dla wierzcho�k�w.
public:
    explicit FordBellman(int rozm);     //Konstruktor klasy.
    ~FordBellman();                     //Destruktor klasy.
    void algorytmMacierz(Macierz* macierzSasiedztwa, int wierzcholekStartu);    //Wykonuje algorytm dla grafu w postaci macierzy s�siedztwa.
    void algorytmLista(Lista* macierzSasiedztwa, int wierzcholekStartu);        //Wykonuje algorytm dla grafu w postaci listy s�siedztwa.
    int* pierwszyElementOdleglosc();    //Zwraca wska�nik na pierwszy element tablicy od�eg�o�ci.
    int* pierwszyElementPoprzednikow(); //Zwraca wska�nik na pierwszy element tablicy poprzednik�w.
};