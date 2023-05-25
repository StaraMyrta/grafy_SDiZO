#include "../Algorytmy/Dijkstra.h"
#include "../Algorytmy/FordBellman.h"
#include "Pomiar.h"
#include <fstream>

/// Klasa s�u��ca do testowania wydajno�ci algorytm�w problemu najkr�tszej �cie�ki.
class TestSciezki
{
private:
    Macierz* macierz;       //Wska�nik na obiekt klasy macierzy s�siedztwa.
    Lista* lista;           //Wska�nik na obiekt klasy listy s�siedztwa.
    Pomiar pomiar;          //Obiekt klasy s�u�acej do wykonywania pomiar�w.
    void stworzGraf(int rozmWierzcholki, int gestosc);                   //Tworzy graf o 'rozm' wierzcho�kach oraz 'gestosc' g�sto�ci.
    PomiarCzasu dijkstraTest(int rozmWierzcholki, int gestosc, Dijkstra* dijkstra);             //Testuje wydajno�� wykonywania si� algorytmu Dijkstry.
    PomiarCzasu fordBellmanTest(int rozmWierzcholki, int gestosc, FordBellman* fordBellman);    //Testuje wydajno�� wykonywania si� algorytmu Forda-Bellmana.
public:
    TestSciezki();          //Konstruktor klasy.
    ~TestSciezki();         //Destruktor klasy.
    void testyCzasu();      //Przeprowadza testy czasu wykonania dla zdefiniowanych wielko�ci grafu.
};