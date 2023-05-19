#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include "Krawedz.h"

using namespace std;

///Klasa statyczna, która zawiera funkcje pomocnicze.
class FunkcjePomocnicze
{
public:
    ///Sprawdza czy dana wartoœæ wystêpuje w liœcie.
    ///\param list - lista dla której bêdzie wykonana operacja.
    ///\param x - szukana wartoœæ.
    ///\return true jeœli zosta³a znaleziona, false - w przeciwnym wypadku.
    static bool contains(list<int>& list, int x)
    {
        return find(list.begin(), list.end(), x) != list.end();
    }
    ///Sprawdza czy lista krawêdzi nie zawiera podanej.
    ///\param edgeList - lista krawêdzi.
    ///\param edge - krawêdŸ do znalezienia.
    ///\return true jeœli zostanie odnaleziona, w przeciwnym wypadku false.
    static bool znajdzKrawedz(list<Krawedz>& edgeList, Krawedz& edge)
    {
        return find(edgeList.begin(), edgeList.end(), edge) != edgeList.end();
    }
    ///Sprawdza czy wektor krawêdzi nie zawiera podanej.
    ///\param edgeList - wektor krawêdzi.
    ///\param edge - krawêdŸ do znalezienia.
    ///\return true jeœli zostanie odnaleziona, w przeciwnym wypadku false.
    static bool znajdzKrawedz(vector<Krawedz>& edgeVector, Krawedz& edge)
    {
        return find(edgeVector.begin(), edgeVector.end(), edge) != edgeVector.end();
    }
};