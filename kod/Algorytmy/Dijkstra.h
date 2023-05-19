#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>
#include "../Reprezentacje/Macierz.h"
#include "../Reprezentacje/Lista.h"
#include "../FunkcjePomocnicze/FunkcjePomocnicze.h"
#include "../FunkcjePomocnicze/Kolejka.h"

//Klasa dla algorytmu Dijkstry.
class Dijkstra
{
private:
    Kolejka<ElemListy> kolejkaPriorytetowa;     //Kolejka priorytetowa dla wierzcho�k�w
    int* odleglosc;                             //Tablica najkr�tszych odleg�o�ci do wierzcho�k�w.
    int* poprzednik;                            //Tablica poprzednik�w dla wierzcho�k�w.
public:
    explicit Dijkstra(int rozm);                //Konstruktor klasy algorytmu Dijkstry.
    ~Dijkstra();                                //Destruktor klasy algorytmu Dijkstry.
    void algorytmMacierz(Macierz* macierzSasiedztwa, int wierzcholekStartu);    //Wykonuje algorytm dla grafu w postaci macierzy s�siedztwa.
    void algorytmLista(Lista* macierzSasiedztwa, int wierzcholekStartu);        //Wykonuje algorytm dla grafu w postaci listy s�siedztwa.
    int* pierwszyElementOdleglosc();            //Zwraca wska�nik na pierwszy element tablicy od�eg�o�ci.
    int* pierwszyElementPoprzednikow();         //Zwraca wska�nik na pierwszy element tablicy poprzednik�w.
};