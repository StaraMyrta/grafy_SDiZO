#include "../Algorytmy/Prim.h"
#include "../Algorytmy/Kruskal.h"
#include "Pomiar.h"
#include <fstream>

//Klasa s�u��ca do testowania wydajno�ci algorytm�w problemu najmniejszego drzewa rozpinaj�cego.
class TestDrzewa
{
private:
    Macierz* macierz;       //Wska�nik na obiekt klasy macierzy s�siedztwa.
    Lista* lista;           //Wska�nik na obiekt klasy listy s�siedztwa.
    Pomiar pomiar;          //Obiekt klasy s�u�acej do wykonywania pomiar�w.
    void stworzGraf(int rozmWierzcholki, int gestosc);                              //Tworzy graf o 'rozm' wierzcho�kach oraz 'gestosc' g�sto�ci.
    PomiarCzasu primTest(int rozmWierzcholki, int gestosc, Prim* prim);             //Testuje wydajno�� wykonywania si� algorytmu Prima.
    PomiarCzasu kruskalTest(int rozmWierzcholki, int gestosc, Kruskal* kruskal);    //Testuje wydajno�� wykonywania si� algorytmu Kruskala.
public:
    TestDrzewa();           //Konstruktor klasy.
    ~TestDrzewa();          //Destruktor klasy.
    void testyCzasu();      //Przeprowadza testy czasu wykonania dla zdefiniowanych wielko�ci grafu.
};