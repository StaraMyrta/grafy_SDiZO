#pragma once

#include <iostream>
#include <climits>
#include <list>

using namespace std;

//Struktura reprezentuj¹ca element listy.
struct ElemListy
{
    int wierzcholek;                                //Numer wierzcho³ka.
    int waga;                                       //Waga danego po³¹czenia.

    bool operator==(const ElemListy& elem)          //Porównanie ze sob¹ dwów elementów listy. true-równe, false-ró¿ne
    {
        return this->wierzcholek == elem.wierzcholek && this->waga == elem.waga;
    }
    bool operator<(const ElemListy& elem)
    {
        return this->waga < elem.waga;
    }
    bool operator<=(const ElemListy& elem)
    {
        return this->waga <= elem.waga;
    }
    bool operator>(const ElemListy& elem)
    {
        return this->waga > elem.waga;
    }
};

class Lista                                     //Klasa reprezentuj¹ca listê sasiedztwa.
{
private:

    list<ElemListy>* baza;                     //Tablica przechowuj¹ca strukturê grafu.

    int rozm;                                   //Iloœæ krawêdzi w grafie.

    //Znajduje element w liœcie.
    //Iterator - wskazuje na dany element, w przeciwnym wypadku iterator wskazuje na end().
    static list<ElemListy>::iterator znajdzWierzcholek(list<ElemListy>& lista, int wierzcholek);

public:
    explicit Lista(int rozm);                   //Konstruktor klasy.
    ~Lista();                                   //Desktruktor klasy.
    void dodajKrawedz(int wierzcholekPocz, int wierzcholekKon, int waga);   //Dodaje krawêdŸ do grafu.
    void usunKrawedz(int wierzcholekPocz, int wierzcholekKon);              //Usuwa krawêdŸ z grafu.
    int znajdzKrawedz(int wierzcholekPocz, int wierzcholekKon);             //Sprawdza czy krawêdŸ istnieje w grafie.
    list<ElemListy>& sasiedziWierzcholka(int wierzcholek);                  //Zwraca listê krawêdzi s¹siaduj¹cych dla danego wierzcho³ka.
    int rozmiar();                              //Zwraca liczbê wierzcho³ków w grafie.
    void wyswietl();                            //Wyœwietla listê sasiedztwa.
};