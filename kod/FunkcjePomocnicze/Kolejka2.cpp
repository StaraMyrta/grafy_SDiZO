#include<iostream>
#include "Kolejka2.h"

//Konstruktor - tworzy n elementow� tablic� heap na kopiec
Kolejka2::Kolejka2(int n)
{
    Heap = new Krawedz2[n];         //Tworzymy tablic�
    hpos = 0;                      //Pozycja w kopcu
}

//Destruktor - usuwa kopiec z pami�ci
Kolejka2::~Kolejka2()
{
    delete[] Heap;
}

//Zwraca kraw�d� z pocz�tku kopca
Krawedz2 Kolejka2::front()
{
    return Heap[0];
}

//Umieszcza w kopcu now� kraw�d� i odtwarza struktur� kopca
void Kolejka2::push(Krawedz2 e)
{
    int i, j;

    i = hpos++;                    //Obliczamy pozycj� rodzica
    j = (i - 1) >> 1;            //i ustawiamy na koniec kopca

    //Szukamy miejsca w kopcu dla e
    while (i && (Heap[j].weight > e.weight))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;                //Kraw�d� e wstawiamy do kopca
}

//Usuwa korze� z kopca i odtwarza jego struktur�
void Kolejka2::pop()
{
    int i, j;
    Krawedz2 e;

    if (hpos)
    {
        e = Heap[--hpos];

        i = 0;
        j = 1;

        while (j < hpos)
        {
            if ((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
            if (e.weight <= Heap[j].weight) break;
            Heap[i] = Heap[j];
            i = j;
            j = (j << 1) + 1;
        }

        Heap[i] = e;
    }
}