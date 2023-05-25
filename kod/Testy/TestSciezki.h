#include "../Algorytmy/Dijkstra.h"
#include "../Algorytmy/FordBellman.h"
#include "Pomiar.h"
#include <fstream>

/// Klasa s³u¿¹ca do testowania wydajnoœci algorytmów problemu najkrótszej œcie¿ki.
class TestSciezki
{
private:
    Macierz* macierz;       //WskaŸnik na obiekt klasy macierzy s¹siedztwa.
    Lista* lista;           //WskaŸnik na obiekt klasy listy s¹siedztwa.
    Pomiar pomiar;          //Obiekt klasy s³u¿acej do wykonywania pomiarów.
    void stworzGraf(int rozmWierzcholki, int gestosc);                   //Tworzy graf o 'rozm' wierzcho³kach oraz 'gestosc' gêstoœci.
    PomiarCzasu dijkstraTest(int rozmWierzcholki, int gestosc, Dijkstra* dijkstra);             //Testuje wydajnoœæ wykonywania siê algorytmu Dijkstry.
    PomiarCzasu fordBellmanTest(int rozmWierzcholki, int gestosc, FordBellman* fordBellman);    //Testuje wydajnoœæ wykonywania siê algorytmu Forda-Bellmana.
public:
    TestSciezki();          //Konstruktor klasy.
    ~TestSciezki();         //Destruktor klasy.
    void testyCzasu();      //Przeprowadza testy czasu wykonania dla zdefiniowanych wielkoœci grafu.
};