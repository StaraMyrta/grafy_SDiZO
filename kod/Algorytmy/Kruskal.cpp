#include "Kruskal.h"

Kruskal::Kruskal() = default;

Kruskal::~Kruskal() = default;

int Kruskal::znajdz(Zbior* zbiory, int element)
{
    //Metoda kompresji œcie¿ek - zwraca reprezentanta danej grupy.
    if (zbiory[element].rodzic != element)
        zbiory[element].rodzic = znajdz(zbiory, zbiory[element].rodzic);
    return zbiory[element].rodzic;
}

void Kruskal::polaczZbiory(Zbior* zbiory, int pierwszy, int drugi)
{
    //Znajdacja reprezentanta dla obu elementów.
    int pierwszyKorzen = znajdz(zbiory, pierwszy);
    int drugiKorzen = znajdz(zbiory, drugi);

    //Jeœli rangi s¹ ró¿ne, przy ³¹czeniu pozostaj¹ takie same.
    if (zbiory[pierwszyKorzen].ranga < zbiory[drugiKorzen].ranga)
        zbiory[pierwszyKorzen].rodzic = drugiKorzen;
    else if (zbiory[pierwszyKorzen].ranga > zbiory[drugiKorzen].ranga)
        zbiory[drugiKorzen].rodzic = pierwszyKorzen;
    else
    {
        //£¹czenie elementów o tej samej randze zwiêksza wysokoœæ drzewa.
        zbiory[drugiKorzen].rodzic = pierwszyKorzen;
        zbiory[pierwszyKorzen].ranga++;
    }
}

void Kruskal::algorytmMacierz(Macierz* macierzSasiedztwa)
{
    //Wektor przechowuj¹cy krawêdzie grafu.
    vector<Krawedz> krawedzVector;
    //Zmienna pomocnicza (wystarczy przejœæ po krawêdziach nale¿¹cych do przek¹tnej g³ównej
    //oraz znajduj¹cych siê pod ni¹, poniewa¿ macierz jest symetryczna).
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

    //Sortowanie krawêdzi rosn¹co wzglêdem wagi.
    sort(krawedzVector.begin(), krawedzVector.end());
    //Alokacja pamiêci dla podzbiorów.
    auto* zbiory = new Zbior[macierzSasiedztwa->rozmiar()];
    for (int i = 0; i < macierzSasiedztwa->rozmiar(); i++)
    {
        //Dla ka¿dego podzbioru (pocz¹tkowo ka¿dy wierzcho³ek)
        //ustawiamy reprezentanta jako jego samego oraz rangê równ¹ 0.
        zbiory[i].rodzic = i;
        zbiory[i].ranga = 0;
    }

    int krawedzIndex = 0;
    while (listaKrawedzi.size() < macierzSasiedztwa->rozmiar() - 1)
    {
        //Pobranie krawêdzi o najmniejszej wadze.
        Krawedz currentKrawedz = krawedzVector[krawedzIndex];
        krawedzIndex++;

        //Znalezienie reprezentantów grup do których nale¿¹ wierzcho³ek pocz¹tkowy i koñcowy.
        int poczatekSet = znajdz(zbiory, currentKrawedz.poczatek);
        int koniecSet = znajdz(zbiory, currentKrawedz.koniec);
        //Jeœli wierzcho³ki s¹ w innych podzbiorach, ³¹czymy je, a krawêdŸ dodajemy do listy krawêdzi MST.
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
        //Dla listy s¹siedztwa, przechodzimy po ka¿dym z wierzcho³ków
        //i sprawdzamy czy taka krawêdŸ nie zosta³a ju¿ dodana.
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
    //Czyœcimy wynik dzia³ania algorytmu.
    listaKrawedzi.clear();
}