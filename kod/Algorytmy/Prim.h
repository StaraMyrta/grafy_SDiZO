#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../Reprezentacje/Macierz.h"
#include "../Reprezentacje/Lista.h"
#include "../FunkcjePomocnicze/Kolejka2.h"
#include "../FunkcjePomocnicze/MST.h"

using namespace std;

//Klasa dla algorytmu Prima.
class Prim
{
private:
    int rozm;
    int v;
    Kolejka2* Q;
    Krawedz2 e;
    MST* T;                // Minimalne drzewo rozpinaj¹ce
    MST* G;                // Graf
    Wezel* p;
    bool* visited;
    int wierzcholekStartowy;
public:
    Prim();            //Konstruktor klasy.
    ~Prim();                            //Destruktor klasy.
    void ustawZmienne(int wierzcholki, int krawedzie, int wierzcholekStartowy); //Definiuje wierzcholek poczatkowy
    void algorytmMacierz(Macierz* macierzSasiedztwa);       //Wykonuje algorytm dla grafu w postaci macierzy s¹siedztwa.
    void algorytmLista(Lista* macierzSasiedztwa);           //Wykonuje algorytm dla grafu w postaci listy s¹siedztwa.
    void wyswietl();         //Wyswietla reprezentacje MST.
};