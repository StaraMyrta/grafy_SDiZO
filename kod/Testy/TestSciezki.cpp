#include "TestSciezki.h"

TestSciezki::TestSciezki()
{
    macierz = nullptr;
    lista = nullptr;
}

TestSciezki::~TestSciezki()
{
    if (macierz != nullptr && lista != nullptr)
    {
        delete macierz;
        delete lista;
    }
}

void TestSciezki::stworzGraf(int wierzcholekStartu, int rozmWierzcholki, int gestosc)
{
    if (macierz != nullptr && lista != nullptr)
    {
        delete macierz;
        delete lista;
    }
    macierz = new Macierz(rozmWierzcholki);
    lista = new Lista(rozmWierzcholki);

    int maxKrawedzs = static_cast<int>(gestosc / 100.0f * (rozmWierzcholki * rozmWierzcholki));
    int krawedzCount = 0;
    //Generacja drzewo rozpinaj¹ce.
    for (int i = 0; i < rozmWierzcholki; i++)
    {
        if (i == wierzcholekStartu) continue;
        int waga = (rand() % maxKrawedzs) + 1;
        macierz->dodajKrawedz(wierzcholekStartu, i, waga);
        lista->dodajKrawedz(wierzcholekStartu, i, waga);
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
            lista->dodajKrawedz(poczatek, koniec, waga);
            krawedzCount++;
        }
    }
}

PomiarCzasu TestSciezki::dijkstraTest(int rozmWierzcholki, int gestosc, Dijkstra* dijkstra)
{
    PomiarCzasu timePomiar{};
    timePomiar.pierwszy = 0;
    timePomiar.drugi = 0;
    for (int i = 0; i < 100; i++)
    {
        int wierzcholekStartu = rand() % rozmWierzcholki;
        stworzGraf(wierzcholekStartu, rozmWierzcholki, gestosc);
        pomiar.czasStart();
        dijkstra->algorytmMacierz(macierz, wierzcholekStartu);
        pomiar.czasStop();
        timePomiar.pierwszy += pomiar.jakiCzasTrwania();

        pomiar.czasStart();
        dijkstra->algorytmLista(lista, wierzcholekStartu);
        pomiar.czasStop();
        timePomiar.drugi += pomiar.jakiCzasTrwania();
    }
    timePomiar.pierwszy /= 100;
    timePomiar.drugi /= 100;
    return timePomiar;
}

PomiarCzasu TestSciezki::fordBellmanTest(int rozmWierzcholki, int gestosc, FordBellman* fordBellman)
{
    PomiarCzasu timePomiar{};
    timePomiar.pierwszy = 0;
    timePomiar.drugi = 0;
    for (int i = 0; i < 100; i++)
    {
        int wierzcholekStartu = rand() % rozmWierzcholki;
        stworzGraf(wierzcholekStartu, rozmWierzcholki, gestosc);
        pomiar.czasStart();
        fordBellman->algorytmMacierz(macierz, wierzcholekStartu);
        pomiar.czasStop();
        timePomiar.pierwszy += pomiar.jakiCzasTrwania();

        pomiar.czasStart();
        fordBellman->algorytmLista(lista, wierzcholekStartu);
        pomiar.czasStop();
        timePomiar.drugi += pomiar.jakiCzasTrwania();
    }
    timePomiar.pierwszy /= 100;
    timePomiar.drugi /= 100;
    return timePomiar;
}

void TestSciezki::testyCzasu()
{
    int rozmWierzcholkis[] = { 100, 200, 300, 400, 500 };
    int densities[] = { 20, 50, 75, 99 };
    ofstream file;
    file.open("sptResult.txt");
    if (file.is_open())
    {
        for (auto count : rozmWierzcholkis)
        {
            auto* dijkstra = new Dijkstra(count);
            for (auto gestosc : densities)
            {
                auto time = dijkstraTest(count, gestosc, dijkstra);
                file << time.pierwszy << " " << time.drugi << "\n";
            }
            delete dijkstra;
        }

        file << "\n";
        for (auto count : rozmWierzcholkis)
        {
            auto* fordBellman = new FordBellman(count);
            for (auto gestosc : densities)
            {
                auto time = fordBellmanTest(count, gestosc, fordBellman);
                file << time.pierwszy << " " << time.drugi << "\n";
            }
            delete fordBellman;
        }
    }
    file.close();
}