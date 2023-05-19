#pragma once
#include<iostream>
#include "Kolejka2.h"

using namespace std;

//Definicja obiektu minimalnego drzewa rozpinaj�cego
struct Wezel
{
    Wezel* next;
    int v, weight;
};

class MST
{
private:
    Wezel** A;                  //Tablica list s�siedztwa
    int Alen;                    //Liczba kom�rek w tablicy
    int weight;                  //Waga ca�ego drzewa
public:
    MST(int n);
    ~MST();
    void addKrawedz(Krawedz2 e);
    Wezel* getAList(int n);
    void print();
};