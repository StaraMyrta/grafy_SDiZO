#pragma once
#include<iostream>
#include "Kolejka2.h"

using namespace std;

//Definicja obiektu minimalnego drzewa rozpinaj¹cego
struct Wezel
{
    Wezel* next;
    int v, weight;
};

class MST
{
private:
    Wezel** A;                  //Tablica list s¹siedztwa
    int Alen;                    //Liczba komórek w tablicy
    int weight;                  //Waga ca³ego drzewa
public:
    MST(int n);
    ~MST();
    void addKrawedz(Krawedz2 e);
    Wezel* getAList(int n);
    void print();
};