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
        visited[i] = false;       // Inicjujemy tablicê odwiedzin

    for (int i = 0; i < rozm; i++)
    {
        for (int j = i+1; j < rozm; j++)//Jeœli miêdzy wierzcho³kami jest krawêdŸ, dodajemy j¹ jako skierowan¹ w oba kierunki.
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

    // Tworzymy minimalne drzewo rozpinaj¹ce

    v = wierzcholekStartowy;                         // Wierzcho³ek startowy
    visited[v] = true;          // Oznaczamy go jako odwiedzonego

    for (int i = 1; i < rozm; i++)       // Do drzewa dodamy n - 1 krawêdzi grafu
    {
        for (p = G->getAList(v); p; p = p->next) // Przegl¹damy listê s¹siadów
            if (!visited[p->v])    // Jeœli s¹siad jest nieodwiedzony, 
            {
                e.v1 = v;                // to tworzymy krawêdŸ
                e.v2 = p->v;
                e.weight = p->weight;
                Q->push(e);            // Dodajemy j¹ do kolejki priorytetowej
            }
        do
        {
            e = Q->front();            // Pobieramy krawêdŸ z kolejki
            Q->pop();
        } while (visited[e.v2]); // KrawêdŸ prowadzi poza drzewo?

        T->addKrawedz(e);             // Dodajemy krawêdŸ do drzewa rozpinaj¹cego
        visited[e.v2] = true;     // Oznaczamy drugi wierzcho³ek jako odwiedzony
        v = e.v2;
    }
}

void Prim::algorytmLista(Lista* listaSasiedztwa)
{

    for (int i = 0; i < rozm; i++)
        visited[i] = false;       // Inicjujemy tablicê odwiedzin

    for (int i = 0; i < rozm; i++)
    {
        for (int j = i + 1; j < rozm; j++)//Jeœli miêdzy wierzcho³kami jest krawêdŸ, dodajemy j¹ jako skierowan¹ w oba kierunki.
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

    // Tworzymy minimalne drzewo rozpinaj¹ce

    v = wierzcholekStartowy;                         // Wierzcho³ek startowy
    visited[v] = true;          // Oznaczamy go jako odwiedzonego

    for (int i = 1; i < rozm; i++)       // Do drzewa dodamy n - 1 krawêdzi grafu
    {
        for (p = G->getAList(v); p; p = p->next) // Przegl¹damy listê s¹siadów
            if (!visited[p->v])    // Jeœli s¹siad jest nieodwiedzony, 
            {
                e.v1 = v;                // to tworzymy krawêdŸ
                e.v2 = p->v;
                e.weight = p->weight;
                Q->push(e);            // Dodajemy j¹ do kolejki priorytetowej
            }
        do
        {
            e = Q->front();            // Pobieramy krawêdŸ z kolejki
            Q->pop();
        } while (visited[e.v2]); // KrawêdŸ prowadzi poza drzewo?

        T->addKrawedz(e);             // Dodajemy krawêdŸ do drzewa rozpinaj¹cego
        visited[e.v2] = true;     // Oznaczamy drugi wierzcho³ek jako odwiedzony
        v = e.v2;
    }
}

void Prim::wyswietl()
{
    T->print();
}
