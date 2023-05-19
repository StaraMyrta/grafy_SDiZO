#include<iostream>
#include "MST.h"

//Konstruktor - tworzy tablic� pustych list s�siedztwa
MST::MST(int n)
{
    int i;

    A = new Wezel * [n];         //Tworzymy tablic� dynamiczn�
    for (i = 0; i < n; i++) A[i] = NULL; //i wype�niamy j� pustymi listami
    Alen = n - 1;                  //Zapami�tujemy d�ugo�� tablicy
    weight = 0;                    //Zerujemy wag� drzewa
}

//Destruktor - usuwa listy oraz tablic� s�siedztwa
MST::~MST()
{
    int i;
    Wezel* p, * r;

    for (i = 0; i <= Alen; i++)
    {
        p = A[i];
        while (p)
        {
            r = p;                     //Zapami�tujemy wskazanie
            p = p->next;               //Przesuwamy si� do nast�pnego elementu listy
            delete r;                  //Usuwamy element
        }
    }

    delete[] A;                  //Usuwamy tablic� list s�siedztwa
}

//Dodaje kraw�d� do drzewa
void MST::addKrawedz(Krawedz2 e)
{
    Wezel* p;

    weight += e.weight;            //Do wagi drzewa dodajemy wag� kraw�dzi
    p = new Wezel;                 //Tworzymy nowy w�ze�
    p->v = e.v2;                   //Wierzcho�ek ko�cowy
    p->weight = e.weight;          //Waga kraw�dzi
    p->next = A[e.v1];          //Dodajemy p do listy wierzcho�ka v1
    A[e.v1] = p;

    p = new Wezel;                 //To samo dla kraw�dzi odwrotnej
    p->v = e.v1;                   //Wierzcho�ek ko�cowy
    p->weight = e.weight;          //Waga kraw�dzi
    p->next = A[e.v2];          //Dodajemy p do listy wierzcho�ka v2
    A[e.v2] = p;
}

//Zwraca wska�nik pocz�tku listy s�siad�w wierzcho�ka
Wezel* MST::getAList(int n)
{
    return A[n];
}

//Wy�wietla zawarto�� drzewa oraz jego wag�
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
