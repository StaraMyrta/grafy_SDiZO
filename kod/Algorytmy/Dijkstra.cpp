#include "Dijkstra.h"

Dijkstra::Dijkstra(int rozm)
{
    //Alokacja pami�ci dla odpowiednich tablic.
    odleglosc = new int[rozm];
    poprzednik = new int[rozm];
}

Dijkstra::~Dijkstra()
{
    //Dealokacja tablic dynamicznych.
    delete[] odleglosc;
    delete[] poprzednik;
}

void Dijkstra::algorytmMacierz(Macierz* macierzSasiedztwa, int wierzcholekStartu)
{
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        odleglosc[i] = INT_MAX;             //Dla ka�dego wierzcho�ka ustawiona zostaje odleg�o�� na niesko�czono��.
        poprzednik[i] = -1;                 //Poprzednik jest niezdefiniowany.
    }

    odleglosc[wierzcholekStartu] = 0;       //Wierzcho�ek poczatkowy ma odleg�o�� r�wn� zero.

    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)                      //Wype�nienie kolejki priorytetowej.
    {
        ElemListy item{ i, odleglosc[i] };
        kolejkaPriorytetowa.dodaj(item);
    }

    while (!kolejkaPriorytetowa.czyPusta())
    {
        auto krawedz = kolejkaPriorytetowa.zdejmij();                              //Dop�ki kolejka nie jest pusta, usuwany jest wierzcho�ek o najni�szym priorytecie.
        for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)                  //Dla ka�dego s�siada wykonana zostaje relaksacja kraw�dzi.
        {
            int waga = macierzSasiedztwa->znajdzKrawedz(krawedz.wierzcholek, i);
            if (waga != INT_MAX)
            {
                if (odleglosc[krawedz.wierzcholek] + waga < odleglosc[i] && odleglosc[krawedz.wierzcholek] != INT_MAX)
                {
                    ElemListy elem = { i, odleglosc[i] };
                    odleglosc[i] = odleglosc[krawedz.wierzcholek] + waga;
                    poprzednik[i] = krawedz.wierzcholek;
                    kolejkaPriorytetowa.zaktualizujKolejke(elem, { i, odleglosc[i] });
                }
            }
        }
    }
}
void Dijkstra::algorytmLista(Lista* macierzSasiedztwa, int wierzcholekStartu)
{
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        odleglosc[i] = INT_MAX;
        poprzednik[i] = -1;
    }

    odleglosc[wierzcholekStartu] = 0;
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        ElemListy item{ i, odleglosc[i] };
        kolejkaPriorytetowa.dodaj(item);
    }

    while (!kolejkaPriorytetowa.czyPusta())
    {
        auto item = kolejkaPriorytetowa.zdejmij();
        for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
        {
            int waga = macierzSasiedztwa->znajdzKrawedz(item.wierzcholek, i);
            if (waga != INT_MAX)
            {
                if (odleglosc[item.wierzcholek] + waga < odleglosc[i] && odleglosc[item.wierzcholek] != INT_MAX)
                {
                    ElemListy elem = { i, odleglosc[i] };
                    odleglosc[i] = odleglosc[item.wierzcholek] + waga;
                    poprzednik[i] = item.wierzcholek;
                    kolejkaPriorytetowa.zaktualizujKolejke(elem, { i, odleglosc[i] });
                }
            }
        }
    }
}

int* Dijkstra::pierwszyElementOdleglosc()
{
    return odleglosc;
}

int* Dijkstra::pierwszyElementPoprzednikow()
{
    return poprzednik;
}