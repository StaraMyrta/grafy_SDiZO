#pragma once
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include "../Reprezentacje/Macierz.h"
#include "../Reprezentacje/Lista.h"
#include "../FunkcjePomocnicze/FunkcjePomocnicze.h"
#include "../FunkcjePomocnicze/Krawedz.h"

//Struktura reprezentuj�ca zbi�r.
struct Zbior
{
    int rodzic;             //Rodzic zbioru.
    int ranga;              //Ranga zbioru.
};


class Kruskal               //Klasa dla algorytmu Kruskala.
{
private:

    list<Krawedz> listaKrawedzi;                                       //Lista kraw�dzi drzewa MST.
    static int znajdz(Zbior* zbiory, int element);                      //Zwraca indeks zbioru, do kt�rego nale�y dany element.
    static void polaczZbiory(Zbior* zbiory, int pierwszy, int drugi);   //��czy zbiory wed�ug rangi.
public:
    Kruskal();              //Konstruktor klasy.
    ~Kruskal();             //Desktruktor klasy.
    void algorytmMacierz(Macierz* macierzSasiedztwa);                   //Wykonuje algorytm dla grafu w postaci macierzy s�siedztwa.
    void algorytmLista(Lista* macierzSasiedztwa);                       //Wykonuje algorytm dla grafu w postaci listy s�siedztwa.
    list<Krawedz>& znajdzListeKrawedzi();                              //Zwraca list� kraw�dzi drzewa MST.
    void usunWyniki();      //Usuwa wyniki dzia�ania algorytmu poprzez wyczyszczenie kontener�w.
};