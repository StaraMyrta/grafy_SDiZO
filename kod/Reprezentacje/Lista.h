#pragma once

#include <iostream>
#include <climits>
#include <list>

using namespace std;

//Struktura reprezentuj�ca element listy.
struct ElemListy
{
    int wierzcholek;                                //Numer wierzcho�ka.
    int waga;                                       //Waga danego po��czenia.

    bool operator==(const ElemListy& elem)          //Por�wnanie ze sob� dw�w element�w listy. true-r�wne, false-r�ne
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

class Lista                                     //Klasa reprezentuj�ca list� sasiedztwa.
{
private:

    list<ElemListy>* baza;                     //Tablica przechowuj�ca struktur� grafu.

    int rozm;                                   //Ilo�� kraw�dzi w grafie.

    //Znajduje element w li�cie.
    //Iterator - wskazuje na dany element, w przeciwnym wypadku iterator wskazuje na end().
    static list<ElemListy>::iterator znajdzWierzcholek(list<ElemListy>& lista, int wierzcholek);

public:
    explicit Lista(int rozm);                   //Konstruktor klasy.
    ~Lista();                                   //Desktruktor klasy.
    void dodajKrawedz(int wierzcholekPocz, int wierzcholekKon, int waga);   //Dodaje kraw�d� do grafu.
    void usunKrawedz(int wierzcholekPocz, int wierzcholekKon);              //Usuwa kraw�d� z grafu.
    int znajdzKrawedz(int wierzcholekPocz, int wierzcholekKon);             //Sprawdza czy kraw�d� istnieje w grafie.
    list<ElemListy>& sasiedziWierzcholka(int wierzcholek);                  //Zwraca list� kraw�dzi s�siaduj�cych dla danego wierzcho�ka.
    int rozmiar();                              //Zwraca liczb� wierzcho�k�w w grafie.
    void wyswietl();                            //Wy�wietla list� sasiedztwa.
};