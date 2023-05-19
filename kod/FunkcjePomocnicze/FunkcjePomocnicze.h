#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include "Krawedz.h"

using namespace std;

///Klasa statyczna, kt�ra zawiera funkcje pomocnicze.
class FunkcjePomocnicze
{
public:
    ///Sprawdza czy dana warto�� wyst�puje w li�cie.
    ///\param list - lista dla kt�rej b�dzie wykonana operacja.
    ///\param x - szukana warto��.
    ///\return true je�li zosta�a znaleziona, false - w przeciwnym wypadku.
    static bool contains(list<int>& list, int x)
    {
        return find(list.begin(), list.end(), x) != list.end();
    }
    ///Sprawdza czy lista kraw�dzi nie zawiera podanej.
    ///\param edgeList - lista kraw�dzi.
    ///\param edge - kraw�d� do znalezienia.
    ///\return true je�li zostanie odnaleziona, w przeciwnym wypadku false.
    static bool znajdzKrawedz(list<Krawedz>& edgeList, Krawedz& edge)
    {
        return find(edgeList.begin(), edgeList.end(), edge) != edgeList.end();
    }
    ///Sprawdza czy wektor kraw�dzi nie zawiera podanej.
    ///\param edgeList - wektor kraw�dzi.
    ///\param edge - kraw�d� do znalezienia.
    ///\return true je�li zostanie odnaleziona, w przeciwnym wypadku false.
    static bool znajdzKrawedz(vector<Krawedz>& edgeVector, Krawedz& edge)
    {
        return find(edgeVector.begin(), edgeVector.end(), edge) != edgeVector.end();
    }
};