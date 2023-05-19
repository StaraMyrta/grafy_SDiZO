#include "../Algorytmy/Prim.h"
#include "../Algorytmy/Kruskal.h"
#include "Pomiar.h"
#include <fstream>

//Klasa s³u¿¹ca do testowania wydajnoœci algorytmów problemu najmniejszego drzewa rozpinaj¹cego.
class TestDrzewa
{
private:
    Macierz* macierz;       //WskaŸnik na obiekt klasy macierzy s¹siedztwa.
    Lista* lista;           //WskaŸnik na obiekt klasy listy s¹siedztwa.
    Pomiar pomiar;          //Obiekt klasy s³u¿acej do wykonywania pomiarów.
    void stworzGraf(int rozmWierzcholki, int gestosc);                              //Tworzy graf o 'rozm' wierzcho³kach oraz 'gestosc' gêstoœci.
    PomiarCzasu primTest(int rozmWierzcholki, int gestosc, Prim* prim);             //Testuje wydajnoœæ wykonywania siê algorytmu Prima.
    PomiarCzasu kruskalTest(int rozmWierzcholki, int gestosc, Kruskal* kruskal);    //Testuje wydajnoœæ wykonywania siê algorytmu Kruskala.
public:
    TestDrzewa();           //Konstruktor klasy.
    ~TestDrzewa();          //Destruktor klasy.
    void testyCzasu();      //Przeprowadza testy czasu wykonania dla zdefiniowanych wielkoœci grafu.
};