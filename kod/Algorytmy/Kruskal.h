#pragma once
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include "../Reprezentacje/Macierz.h"
#include "../Reprezentacje/Lista.h"
#include "../FunkcjePomocnicze/FunkcjePomocnicze.h"
#include "../FunkcjePomocnicze/Krawedz.h"

//Struktura reprezentuj¹ca zbiór.
struct Zbior
{
    int rodzic;             //Rodzic zbioru.
    int ranga;              //Ranga zbioru.
};


class Kruskal               //Klasa dla algorytmu Kruskala.
{
private:

    list<Krawedz> listaKrawedzi;                                       //Lista krawêdzi drzewa MST.
    static int znajdz(Zbior* zbiory, int element);                      //Zwraca indeks zbioru, do którego nale¿y dany element.
    static void polaczZbiory(Zbior* zbiory, int pierwszy, int drugi);   //£¹czy zbiory wed³ug rangi.
public:
    Kruskal();              //Konstruktor klasy.
    ~Kruskal();             //Desktruktor klasy.
    void algorytmMacierz(Macierz* macierzSasiedztwa);                   //Wykonuje algorytm dla grafu w postaci macierzy s¹siedztwa.
    void algorytmLista(Lista* macierzSasiedztwa);                       //Wykonuje algorytm dla grafu w postaci listy s¹siedztwa.
    list<Krawedz>& znajdzListeKrawedzi();                              //Zwraca listê krawêdzi drzewa MST.
    void usunWyniki();      //Usuwa wyniki dzia³ania algorytmu poprzez wyczyszczenie kontenerów.
};