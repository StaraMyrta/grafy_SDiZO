#include "TestDrzewa.h"

TestDrzewa::TestDrzewa()
{
    macierz = nullptr;
    lista = nullptr;
}

TestDrzewa::~TestDrzewa()
{
    if (macierz != nullptr && lista != nullptr)
    {
        delete macierz;
        delete lista;
    }
}

void TestDrzewa::stworzGraf(int iloscWierzcholkow, int gestosc)
{
    if (macierz != nullptr && lista != nullptr)
    {
        delete macierz;
        delete lista;
    }
    macierz = new Macierz(iloscWierzcholkow);
    lista = new Lista(iloscWierzcholkow);

    //Maksymalna iloœæ krawêdzi to n(n-1)/2, uwzglêdniaj¹c gêstoœæ trzeba wynik przemno¿yæ przez gêstoœæ i zaokr¹gliæ w dó³. 
    int maxKrawedzi = floor((iloscWierzcholkow * (iloscWierzcholkow - 1) * gestosc / 200));
    int licznikKrawedzi = 0;
    //Generujemy drzewo rozpinaj¹ce.
    for (int i = 0; i < iloscWierzcholkow - 1; i++)
    {
        //Dla problemu minimalnego drzewa rozpinaj¹cego krawêdzie s¹ nieskierowane.
        int waga = (rand() % maxKrawedzi) + 1;
        macierz->dodajKrawedz(i, i + 1, waga);
        macierz->dodajKrawedz(i + 1, i, waga);

        lista->dodajKrawedz(i, i + 1, waga);
        lista->dodajKrawedz(i + 1, i, waga);

        licznikKrawedzi++;
    }

    //Dodanie pozosta³e krawêdzie (zawsze zostanie wygenerowane chocia¿ drzewo rozpinaj¹ce).
    while (licznikKrawedzi < maxKrawedzi)
    {
        int poczatek = rand() % iloscWierzcholkow;
        int koniec = rand() % iloscWierzcholkow;
        int waga = (rand() % maxKrawedzi) + 1;
        if (poczatek != koniec)         //Wyeliminowanie mo¿liwoœci stworzenia pêtli
        {
            if (macierz->znajdzKrawedz(poczatek, koniec) == INT_MAX)
            {
                macierz->dodajKrawedz(poczatek, koniec, waga);
                macierz->dodajKrawedz(koniec, poczatek, waga);

                lista->dodajKrawedz(poczatek, koniec, waga);
                lista->dodajKrawedz(koniec, poczatek, waga);
                licznikKrawedzi++;
            }
        }
    }
}

PomiarCzasu TestDrzewa::primTest(int rozmWierzcholki, int gestosc, Prim* prim)
{
    PomiarCzasu czasPomiar{};
    czasPomiar.pierwszy = 0;
    czasPomiar.drugi = 0;
    for (int i = 0; i < 100; i++)
    {
        stworzGraf(rozmWierzcholki, gestosc);
        int maxKrawedzi = floor((rozmWierzcholki * (rozmWierzcholki - 1) * gestosc / 200));
            prim->ustawZmienne(rozmWierzcholki, maxKrawedzi, 0);
        pomiar.czasStart();
        prim->algorytmMacierz(macierz);
        pomiar.czasStop();
        czasPomiar.pierwszy += pomiar.jakiCzasTrwania();

//        pomiar.czasStart();
//        prim->algorytmLista(lista);
//        pomiar.czasStop();
//        czasPomiar.drugi += pomiar.jakiCzasTrwania();
    }

    czasPomiar.pierwszy /= 100;
    czasPomiar.drugi /= 100;
    return czasPomiar;
}

PomiarCzasu TestDrzewa::kruskalTest(int rozmWierzcholki, int gestosc, Kruskal* kruskal)
{
    PomiarCzasu czasPomiar{};
    czasPomiar.pierwszy = 0;
    czasPomiar.drugi = 0;
    for (int i = 0; i < 100; i++)
    {
        stworzGraf(rozmWierzcholki, gestosc);
        pomiar.czasStart();
        kruskal->algorytmMacierz(macierz);
        pomiar.czasStop();
        czasPomiar.pierwszy += pomiar.jakiCzasTrwania();

        kruskal->usunWyniki();
        pomiar.czasStart();
        kruskal->algorytmLista(lista);
        kruskal->usunWyniki();
        pomiar.czasStop();
        czasPomiar.drugi += pomiar.jakiCzasTrwania();
    }

    czasPomiar.pierwszy /= 100;
    czasPomiar.drugi /= 100;
    return czasPomiar;
}

void TestDrzewa::testyCzasu()
{
    int rozmWierzcholki[] = { 50, 100, 150, 200, 250 };
    int gestosci[] = { 25, 50, 75, 99 };
    for (auto count : rozmWierzcholki)
    {
            auto* prim = new Prim();
       for (auto gestosc : gestosci)
        {
               auto czas = primTest(count, gestosc, prim);
           cout << czas.pierwszy << " " << czas.drugi << endl;
        }
   delete prim;
    }

//    auto* kruskal = new Kruskal();
//    for (auto count : rozmWierzcholki)
    {
//        for (auto gestosc : gestosci)
        {
//            auto czas = kruskalTest(count, gestosc, kruskal);
//           cout << count << " " << gestosc << "% " << czas.pierwszy << " " << czas.drugi << endl;
        }
    }
//    delete kruskal;
}