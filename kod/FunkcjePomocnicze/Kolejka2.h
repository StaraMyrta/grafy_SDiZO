#pragma once
#include<iostream>

using namespace std;

//Definicja obiektu kolejki priorytetowej dla algorytm�w Prima i Dijkstry
struct Krawedz2
{
    int v1, v2, weight;            //Wierzcho�ki kraw�dzi, waga kraw�dzi
};

class Kolejka2
{
  private:
    Krawedz2* Heap;
    int hpos;
  public:
    Kolejka2( int n );
    ~Kolejka2( );
    Krawedz2 front( );
    void push (Krawedz2 e );
    void pop( );
};