#include <iostream>
#include "Prim.h"

Prim::Prim() = default;

Prim::~Prim() = default;


void Prim::ustawZmienne(int wierzcholki, int krawedzie, int wierzcholek)
{
    rozm = wierzcholki;
    Q = new Kolejka2(krawedzie);
    T = new MST(rozm);
    G = new MST(rozm);
    visited = new bool[rozm];
    wierzcholekStartowy = wierzcholek;
}

void Prim::algorytmMacierz(Macierz* macierzSasiedztwa)
{
    for (int i = 0; i < rozm; i++)
        visited[i] = false;       // Inicjujemy tablic� odwiedzin

    for (int i = 0; i < rozm; i++)
    {
        for (int j = i+1; j < rozm; j++)//Je�li mi�dzy wierzcho�kami jest kraw�d�, dodajemy j� jako skierowan� w oba kierunki.
        {
            int weight = macierzSasiedztwa->znajdzKrawedz(i, j);
            if (weight != INT_MAX)
            {
                e.weight = weight;
                e.v1 = i;
                e.v2 = j;
                G->addKrawedz(e);             
                
                e.weight = weight;
                e.v1 = j;
                e.v2 = i;
                G->addKrawedz(e);             // i umieszczamy je w G
            }
            
        }
    }

    // Tworzymy minimalne drzewo rozpinaj�ce

    v = wierzcholekStartowy;                         // Wierzcho�ek startowy
    visited[v] = true;          // Oznaczamy go jako odwiedzonego

    for (int i = 1; i < rozm; i++)       // Do drzewa dodamy n - 1 kraw�dzi grafu
    {
        for (p = G->getAList(v); p; p = p->next) // Przegl�damy list� s�siad�w
            if (!visited[p->v])    // Je�li s�siad jest nieodwiedzony, 
            {
                e.v1 = v;                // to tworzymy kraw�d�
                e.v2 = p->v;
                e.weight = p->weight;
                Q->push(e);            // Dodajemy j� do kolejki priorytetowej
            }
        do
        {
            e = Q->front();            // Pobieramy kraw�d� z kolejki
            Q->pop();
        } while (visited[e.v2]); // Kraw�d� prowadzi poza drzewo?

        T->addKrawedz(e);             // Dodajemy kraw�d� do drzewa rozpinaj�cego
        visited[e.v2] = true;     // Oznaczamy drugi wierzcho�ek jako odwiedzony
        v = e.v2;
    }
}

void Prim::algorytmLista(Lista* listaSasiedztwa)
{

    for (int i = 0; i < rozm; i++)
        visited[i] = false;       // Inicjujemy tablic� odwiedzin

    for (int i = 0; i < rozm; i++)
    {
        for (int j = i + 1; j < rozm; j++)//Je�li mi�dzy wierzcho�kami jest kraw�d�, dodajemy j� jako skierowan� w oba kierunki.
        {
            int weight = listaSasiedztwa->znajdzKrawedz(i, j);
            if (weight != INT_MAX)
            {
                e.weight = weight;
                e.v1 = i;
                e.v2 = j;
                G->addKrawedz(e);

                e.weight = weight;
                e.v1 = j;
                e.v2 = i;
                G->addKrawedz(e);             // i umieszczamy je w G
            }

        }
    }

    // Tworzymy minimalne drzewo rozpinaj�ce

    v = wierzcholekStartowy;                         // Wierzcho�ek startowy
    visited[v] = true;          // Oznaczamy go jako odwiedzonego

    for (int i = 1; i < rozm; i++)       // Do drzewa dodamy n - 1 kraw�dzi grafu
    {
        for (p = G->getAList(v); p; p = p->next) // Przegl�damy list� s�siad�w
            if (!visited[p->v])    // Je�li s�siad jest nieodwiedzony, 
            {
                e.v1 = v;                // to tworzymy kraw�d�
                e.v2 = p->v;
                e.weight = p->weight;
                Q->push(e);            // Dodajemy j� do kolejki priorytetowej
            }
        do
        {
            e = Q->front();            // Pobieramy kraw�d� z kolejki
            Q->pop();
        } while (visited[e.v2]); // Kraw�d� prowadzi poza drzewo?

        T->addKrawedz(e);             // Dodajemy kraw�d� do drzewa rozpinaj�cego
        visited[e.v2] = true;     // Oznaczamy drugi wierzcho�ek jako odwiedzony
        v = e.v2;
    }
}

void Prim::wyswietl()
{
    T->print();
}
