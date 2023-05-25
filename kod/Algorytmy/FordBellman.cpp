#include "FordBellman.h"

FordBellman::FordBellman(int rozm)
{
    //Alokacja pamiêæ dla odpowiednich tablic.
    odleglosc = new int[rozm];
    poprzednik = new int[rozm];
}

FordBellman::~FordBellman()
{
    //Dealokacja tablice dynamiczne.
    delete[] odleglosc;
    delete[] poprzednik;
}

void FordBellman::algorytmMacierz(Macierz* macierzSasiedztwa, int wierzcholekStartu)
{
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        odleglosc[i] = INT_MAX;             //Dla ka¿dego wierzcho³ka ustawiona zostaje odleg³oœæ na nieskoñczonoœæ.
        poprzednik[i] = -1;                 //Poprzednik jest niezdefiniowany.
    }

    odleglosc[wierzcholekStartu] = 0;       //Odleg³oœæ do wierzcho³ka poczatkowego jest równa 0.

    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        //Dla ka¿dej krawêdzi (w reprezentacji macierzowej musimy przejœæ przez wszystkie mo¿liwe),
        //wykonanie relaksacji.
        for (int u = 0; u < macierzSasiedztwa->rozmiar(); u++)
        {
            for (int v = 0; v < macierzSasiedztwa->rozmiar(); v++)
            {
                int waga = macierzSasiedztwa->znajdzKrawedz(u, v);
                if (waga != INT_MAX)
                {
                    if (odleglosc[u] + waga < odleglosc[v] && odleglosc[u] != INT_MAX)
                    {
                        odleglosc[v] = odleglosc[u] + waga;
                        poprzednik[v] = u;
                    }
                }
            }
        }
    }
}

void FordBellman::algorytmLista(Lista* macierzSasiedztwa, int wierzcholekStartu)
{
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        odleglosc[i] = INT_MAX;
        poprzednik[i] = -1;
    }

    odleglosc[wierzcholekStartu] = 0;
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        for (int u = 0; u < macierzSasiedztwa->rozmiar(); u++)
        {
            //W reprezentacji listowej wystarczy przejœcie przez odpowiednie listy dla ka¿dego z wierzcho³ków.
            for (auto item : macierzSasiedztwa->sasiedziWierzcholka(u))
            {
                if (odleglosc[u] + item.waga < odleglosc[item.wierzcholek] && odleglosc[u] != INT_MAX)
                {
                    odleglosc[item.wierzcholek] = odleglosc[u] + item.waga;
                    poprzednik[item.wierzcholek] = u;
                }
            }
        }
    }
}

int* FordBellman::pierwszyElementOdleglosc()
{
    return odleglosc;
}

int* FordBellman::pierwszyElementPoprzednikow()
{
    return poprzednik;
}