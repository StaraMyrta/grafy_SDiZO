#pragma once

#include <iostream>
#include <iomanip>
#include <climits>
#include <math.h>
#include <string>

//Klasa reprezentuj�ca macierz s�siedztwa.
class Macierz
{
private:
    int* baza;                      //Tablica przechowuj�ca struktur� grafu.
    int rozm;                       //Ilo�� kraw�dzi w grafie.
public:
    explicit Macierz(int rozm);     //Konstruktor klasy.
    ~Macierz();                     //Desktruktor klasy.
    void dodajKrawedz(int wierzcholekPocz, int wierzcholekKon, int waga);   //Dodaje kraw�d� do grafu.
    void usunKrawedz(int wierzcholekPocz, int wierzcholekKon);              //Usuwa kraw�d� z grafu.
    int znajdzKrawedz(int wierzcholekPocz, int wierzcholekKon);             //Sprawdza czy kraw�d� istnieje w grafie. Zwraca wag� znalezionego wierzcho�ka lub zero, je�li nie zosta� znaleziony.
    int rozmiar();                  //Zwraca ilo�� wierzcho�k�w grafu.
    void wyswietl();                //Wy�wietla graf.
};