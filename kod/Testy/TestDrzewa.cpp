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

void TestDrzewa::stworzGraf(int rozmWierzcholki, int gestosc)
{
    if (macierz != nullptr && lista != nullptr)
    {
        delete macierz;
        delete lista;
    }
    macierz = new Macierz(rozmWierzcholki);
    lista = new Lista(rozmWierzcholki);

    //Maksymalna iloœæ wierzcho³ków to suma ci¹gu arytmetycznego an = n.
    int maxKrawedzs = static_cast<int>(gestosc / 100.0f * (((rozmWierzcholki + 1) / 2.0f) * rozmWierzcholki));
    int krawedzCount = 0;
    //Generacja drzewo rozpinaj¹ce.
    for (int i = 0; i < rozmWierzcholki - 1; i++)
    {
        //Dla problemu minimalnego drzewa rozpinaj¹cego krawêdzie s¹ nieskierowane.
        int waga = (rand() % maxKrawedzs) + 1;
        macierz->dodajKrawedz(i, i + 1, waga);
        macierz->dodajKrawedz(i + 1, i, waga);

        lista->dodajKrawedz(i, i + 1, waga);
        lista->dodajKrawedz(i + 1, i, waga);
        krawedzCount++;
    }

    //Dodajemy pozosta³e krawêdzie (zawsze zostanie wygenerowane chocia¿ drzewo rozpinaj¹ce).
    while (krawedzCount < maxKrawedzs)
    {
        int poczatek = rand() % rozmWierzcholki;
        int koniec = rand() % rozmWierzcholki;
        int waga = (rand() % maxKrawedzs) + 1;

        if (macierz->znajdzKrawedz(poczatek, koniec) == 0)
        {
            macierz->dodajKrawedz(poczatek, koniec, waga);
            macierz->dodajKrawedz(koniec, poczatek, waga);

            lista->dodajKrawedz(poczatek, koniec, waga);
            lista->dodajKrawedz(koniec, poczatek, waga);
            krawedzCount++;
        }
    }
}

PomiarCzasu TestDrzewa::primTest(int rozmWierzcholki, int gestosc, Prim* prim)
{
    PomiarCzasu timePomiar{};
    timePomiar.pierwszy = 0;
    timePomiar.drugi = 0;
    for (int i = 0; i < 100; i++)
    {
        stworzGraf(rozmWierzcholki, gestosc);
        pomiar.czasStart();
        prim->algorytmMacierz(macierz);
        pomiar.czasStop();
        timePomiar.pierwszy += pomiar.jakiCzasTrwania();

        pomiar.czasStart();
        prim->algorytmLista(lista);
        pomiar.czasStop();
        timePomiar.drugi += pomiar.jakiCzasTrwania();
    }

    timePomiar.pierwszy /= 100;
    timePomiar.drugi /= 100;
    return timePomiar;
}

PomiarCzasu TestDrzewa::kruskalTest(int rozmWierzcholki, int gestosc, Kruskal* kruskal)
{
    PomiarCzasu timePomiar{};
    timePomiar.pierwszy = 0;
    timePomiar.drugi = 0;
    for (int i = 0; i < 100; i++)
    {
        stworzGraf(rozmWierzcholki, gestosc);
        pomiar.czasStart();
        kruskal->algorytmMacierz(macierz);
        pomiar.czasStop();
        timePomiar.pierwszy += pomiar.jakiCzasTrwania();

        kruskal->usunWyniki();
        pomiar.czasStart();
        kruskal->algorytmLista(lista);
        kruskal->usunWyniki();
        pomiar.czasStop();
        timePomiar.drugi += pomiar.jakiCzasTrwania();
    }

    timePomiar.pierwszy /= 100;
    timePomiar.drugi /= 100;
    return timePomiar;
}

void TestDrzewa::testyCzasu()
{
    int rozmWierzcholkis[] = { 100, 200, 300, 400, 500 };
    int densities[] = { 20, 50, 75, 99 };
    ofstream file;
    file.open("mstResult.txt");
    if (file.is_open())
    {
//        for (auto count : rozmWierzcholkis)
        {
//                auto* prim = new Prim(count);
//           for (auto gestosc : densities)
            {
//                   auto time = primTest(count, gestosc, prim);
//               file << time.pierwszy << " " << time.drugi << "\n";
            }
//       delete prim;
        }

        file << "\n";
        auto* kruskal = new Kruskal();
        for (auto count : rozmWierzcholkis)
        {
            for (auto gestosc : densities)
            {
                auto time = kruskalTest(count, gestosc, kruskal);
                file << time.pierwszy << " " << time.drugi << "\n";
            }
        }
        delete kruskal;
    }
    file.close();
}