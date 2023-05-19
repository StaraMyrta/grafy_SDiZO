#pragma once

#include <iostream>
#include <iomanip>
#include <climits>
#include <math.h>
#include <string>

//Klasa reprezentuj¹ca macierz s¹siedztwa.
class Macierz
{
private:
    int* baza;                      //Tablica przechowuj¹ca strukturê grafu.
    int rozm;                       //Iloœæ krawêdzi w grafie.
public:
    explicit Macierz(int rozm);     //Konstruktor klasy.
    ~Macierz();                     //Desktruktor klasy.
    void dodajKrawedz(int wierzcholekPocz, int wierzcholekKon, int waga);   //Dodaje krawêdŸ do grafu.
    void usunKrawedz(int wierzcholekPocz, int wierzcholekKon);              //Usuwa krawêdŸ z grafu.
    int znajdzKrawedz(int wierzcholekPocz, int wierzcholekKon);             //Sprawdza czy krawêdŸ istnieje w grafie. Zwraca wagê znalezionego wierzcho³ka lub zero, jeœli nie zosta³ znaleziony.
    int rozmiar();                  //Zwraca iloœæ wierzcho³ków grafu.
    void wyswietl();                //Wyœwietla graf.
};