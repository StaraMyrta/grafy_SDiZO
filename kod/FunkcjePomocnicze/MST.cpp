#include<iostream>
#include "MST.h"

//Konstruktor - tworzy tablicê pustych list s¹siedztwa
MST::MST(int n)
{
    int i;

    A = new Wezel * [n];         //Tworzymy tablicê dynamiczn¹
    for (i = 0; i < n; i++) A[i] = NULL; //i wype³niamy j¹ pustymi listami
    Alen = n - 1;                  //Zapamiêtujemy d³ugoœæ tablicy
    weight = 0;                    //Zerujemy wagê drzewa
}

//Destruktor - usuwa listy oraz tablicê s¹siedztwa
MST::~MST()
{
    int i;
    Wezel* p, * r;

    for (i = 0; i <= Alen; i++)
    {
        p = A[i];
        while (p)
        {
            r = p;                     //Zapamiêtujemy wskazanie
            p = p->next;               //Przesuwamy siê do nastêpnego elementu listy
            delete r;                  //Usuwamy element
        }
    }

    delete[] A;                  //Usuwamy tablicê list s¹siedztwa
}

//Dodaje krawêdŸ do drzewa
void MST::addKrawedz(Krawedz2 e)
{
    Wezel* p;

    weight += e.weight;            //Do wagi drzewa dodajemy wagê krawêdzi
    p = new Wezel;                 //Tworzymy nowy wêze³
    p->v = e.v2;                   //Wierzcho³ek koñcowy
    p->weight = e.weight;          //Waga krawêdzi
    p->next = A[e.v1];          //Dodajemy p do listy wierzcho³ka v1
    A[e.v1] = p;

    p = new Wezel;                 //To samo dla krawêdzi odwrotnej
    p->v = e.v1;                   //Wierzcho³ek koñcowy
    p->weight = e.weight;          //Waga krawêdzi
    p->next = A[e.v2];          //Dodajemy p do listy wierzcho³ka v2
    A[e.v2] = p;
}

//Zwraca wskaŸnik pocz¹tku listy s¹siadów wierzcho³ka
Wezel* MST::getAList(int n)
{
    return A[n];
}

//Wyœwietla zawartoœæ drzewa oraz jego wagê
void MST::print()
{
    int i;
    Wezel* p;

    cout << endl;
    for (i = 0; i <= Alen; i++)
    {
        cout << i << ", ";
        for (p = A[i]; p; p = p->next)
        {
            cout << p->v << ", waga:" << p->weight << " ";
            break;
        }
        cout << endl;
    }
    cout << endl << endl << "Waga drzewa wynosi: " << weight << endl << endl;
    weight = 0;
}
