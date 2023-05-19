#include "Kruskal.h"

Kruskal::Kruskal() = default;

Kruskal::~Kruskal() = default;

int Kruskal::znajdz(Zbior* zbiory, int element)
{
    //Metoda kompresji �cie�ek - zwraca reprezentanta danej grupy.
    if (zbiory[element].rodzic != element)
        zbiory[element].rodzic = znajdz(zbiory, zbiory[element].rodzic);
    return zbiory[element].rodzic;
}

void Kruskal::polaczZbiory(Zbior* zbiory, int pierwszy, int drugi)
{
    //Znajdacja reprezentanta dla obu element�w.
    int pierwszyKorzen = znajdz(zbiory, pierwszy);
    int drugiKorzen = znajdz(zbiory, drugi);

    //Je�li rangi s� r�ne, przy ��czeniu pozostaj� takie same.
    if (zbiory[pierwszyKorzen].ranga < zbiory[drugiKorzen].ranga)
        zbiory[pierwszyKorzen].rodzic = drugiKorzen;
    else if (zbiory[pierwszyKorzen].ranga > zbiory[drugiKorzen].ranga)
        zbiory[drugiKorzen].rodzic = pierwszyKorzen;
    else
    {
        //��czenie element�w o tej samej randze zwi�ksza wysoko�� drzewa.
        zbiory[drugiKorzen].rodzic = pierwszyKorzen;
        zbiory[pierwszyKorzen].ranga++;
    }
}

void Kruskal::algorytmMacierz(Macierz* macierzSasiedztwa)
{
    //Wektor przechowuj�cy kraw�dzie grafu.
    vector<Krawedz> krawedzVector;
    //Zmienna pomocnicza (wystarczy przej�� po kraw�dziach nale��cych do przek�tnej g��wnej
    //oraz znajduj�cych si� pod ni�, poniewa� macierz jest symetryczna).
    int diagonal = 1;
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        for (int j = 0; j < diagonal; j++)
        {
            int waga = macierzSasiedztwa->znajdzKrawedz(i, j);
            if (waga != INT_MAX)
            {
                Krawedz krawedz = { i, j, waga };
                krawedzVector.push_back(krawedz);
            }
        }
        diagonal++;
    }

    //Sortowanie kraw�dzi rosn�co wzgl�dem wagi.
    sort(krawedzVector.begin(), krawedzVector.end());
    //Alokacja pami�ci dla podzbior�w.
    auto* zbiory = new Zbior[macierzSasiedztwa->rozmiar()];
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        //Dla ka�dego podzbioru (pocz�tkowo ka�dy wierzcho�ek)
        //ustawiamy reprezentanta jako jego samego oraz rang� r�wn� 0.
        zbiory[i].rodzic = i;
        zbiory[i].ranga = 0;
    }

    int krawedzIndex = 0;
    while (listaKrawedzi.size() < macierzSasiedztwa->rozmiar() - 1)
    {
        //Pobranie kraw�dzi o najmniejszej wadze.
        Krawedz currentKrawedz = krawedzVector[krawedzIndex];
        krawedzIndex++;

        //Znalezienie reprezentant�w grup do kt�rych nale�� wierzcho�ek pocz�tkowy i ko�cowy.
        int poczatekSet = znajdz(zbiory, currentKrawedz.poczatek);
        int koniecSet = znajdz(zbiory, currentKrawedz.koniec);
        //Je�li wierzcho�ki s� w innych podzbiorach, ��czymy je, a kraw�d� dodajemy do listy kraw�dzi MST.
        if (poczatekSet != koniecSet)
        {
            listaKrawedzi.push_back(currentKrawedz);
            polaczZbiory(zbiory, poczatekSet, koniecSet);
        }
    }
    delete[] zbiory;
}

void Kruskal::algorytmLista(Lista* lista)
{
    vector<Krawedz> krawedzVector;
    for (int i = 0; i < lista->rozmiar(); i++)
    {
        //Dla listy s�siedztwa, przechodzimy po ka�dym z wierzcho�k�w
        //i sprawdzamy czy taka kraw�d� nie zosta�a ju� dodana.
        list<ElemListy>& row = lista->sasiedziWierzcholka(i);
        for (auto krawedz : row)
        {
            Krawedz item = { i, krawedz.wierzcholek, krawedz.waga };
            if (!FunkcjePomocnicze::znajdzKrawedz(krawedzVector, item)) krawedzVector.push_back(item);
        }
    }

    sort(krawedzVector.begin(), krawedzVector.end());
    auto* zbiory = new Zbior[lista->rozmiar()];
    for (int i = 0; i < lista->rozmiar(); i++)
    {
        zbiory[i].rodzic = i;
        zbiory[i].ranga = 0;
    }

    int krawedzIndex = 0;
    while (listaKrawedzi.size() < lista->rozmiar() - 1)
    {
        Krawedz currentKrawedz = krawedzVector[krawedzIndex];
        krawedzIndex++;

        int poczatekSet = znajdz(zbiory, currentKrawedz.poczatek);
        int koniecSet = znajdz(zbiory, currentKrawedz.koniec);
        if (poczatekSet != koniecSet)
        {
            listaKrawedzi.push_back(currentKrawedz);
            polaczZbiory(zbiory, poczatekSet, koniecSet);
        }
    }
    delete[] zbiory;
}

list<Krawedz>& Kruskal::znajdzListeKrawedzi()
{
    return listaKrawedzi;
}

void Kruskal::usunWyniki()
{
    //Czy�cimy wynik dzia�ania algorytmu.
    listaKrawedzi.clear();
}