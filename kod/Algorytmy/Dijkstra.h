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
    Kolejka<ElemListy> kolejkaPriorytetowa;     //Kolejka priorytetowa dla wierzcho³ków
    int* odleglosc;                             //Tablica najkrótszych odleg³oœci do wierzcho³ków.
    int* poprzednik;                            //Tablica poprzedników dla wierzcho³ków.
public:
    explicit Dijkstra(int rozm);                //Konstruktor klasy algorytmu Dijkstry.
    ~Dijkstra();                                //Destruktor klasy algorytmu Dijkstry.
    void algorytmMacierz(Macierz* macierzSasiedztwa, int wierzcholekStartu);    //Wykonuje algorytm dla grafu w postaci macierzy s¹siedztwa.
    void algorytmLista(Lista* macierzSasiedztwa, int wierzcholekStartu);        //Wykonuje algorytm dla grafu w postaci listy s¹siedztwa.
    int* pierwszyElementOdleglosc();            //Zwraca wskaŸnik na pierwszy element tablicy od³eg³oœci.
    int* pierwszyElementPoprzednikow();         //Zwraca wskaŸnik na pierwszy element tablicy poprzedników.
};