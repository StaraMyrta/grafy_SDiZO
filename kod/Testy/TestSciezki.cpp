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

void TestSciezki::stworzGraf(int iloscWierzcholkow, int gestosc)
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
        //Dla problemu najkrótszej œcie¿ki krawêdzie s¹ skierowane.
        int waga = (rand() % maxKrawedzi) + 1;
        macierz->dodajKrawedz(i, i + 1, waga);

        lista->dodajKrawedz(i, i + 1, waga);

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

                lista->dodajKrawedz(poczatek, koniec, waga);
                licznikKrawedzi++;
            }
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
        stworzGraf(rozmWierzcholki, gestosc);
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
        stworzGraf(rozmWierzcholki, gestosc);
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
    int rozmWierzcholkis[] = { 50, 100, 150, 200, 250 };
    int densities[] = { 25, 50, 75, 99 };
    for (auto count : rozmWierzcholkis)
    {
        auto* dijkstra = new Dijkstra(count);
        for (auto gestosc : densities)
        {
            auto time = dijkstraTest(count, gestosc, dijkstra);
            cout << "Dijkstra :" << count << " wierzcholkow " << gestosc << "% gestosci " << time.pierwszy << " " << time.drugi << endl;
        }
        delete dijkstra;
    }

    for (auto count : rozmWierzcholkis)
    {
        auto* fordBellman = new FordBellman(count);
        for (auto gestosc : densities)
        {
            auto time = fordBellmanTest(count, gestosc, fordBellman);
            cout << "Ford-Bellman :" << count << " wierzcholkow " << gestosc << "% gestosci " << time.pierwszy << " " << time.drugi << endl;
        }
        delete fordBellman;
    }
}