#include "Menu.h"

using namespace std;

Menu::Menu() = default;

Menu::~Menu() = default;

void Menu::wybor()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz co chcesz zrobic:" << endl;
    cout << "1. Stworzenie grafu nieskierowanego (1)" << endl;
    cout << "2. Stworzenie grafu skierowanego (2)" << endl;
    cout << "3. Wyswietlenie grafu (3)" << endl;
    cout << "4. Wyznaczenie minimalnego drzewa rozpinajacego (4)" << endl;
    cout << "5. Wyznaczenie najkrotszej sciezki w grafie (5)" << endl;
    cout << "6. Cofnij (6)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie menu wybranej struktury.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomenda = true;                              //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.
        if (wejscie == 1)
        {
            wczytajPlikNieskierowany();
        }
        if (wejscie == 2)
        {
            wczytajPlikSkierowany();
        }
        if (wejscie == 3)
        {
            wyswietlenie();
        }
        else if (wejscie == 4)
        {
            wyborDrzewa();
        }
        else if (wejscie == 5)
        {
            wyborSciezki();
        }
        else if (wejscie == 6)
        {
            powrot = true;
            nieznanaKomenda = false;
        }
        else
        {
            cout << "Nieznana komenda! Sprobuj jeszcze raz:" << endl;
            wybor();
        }
    }
}

void Menu::wczytajPlikNieskierowany()
{
    //Standardowe wczytywanie z pliku.
    string nazwa;
    cout << "\nPodaj nazwe pliku: ";
    cin >> nazwa;
    ifstream plik;
    plik.open(nazwa);

    if (plik.is_open())
    {
        if (macierz != nullptr)
        {
            delete macierz;
        }
        if (lista != nullptr)
        {
            delete lista;
        }

        plik >> ileKrawedzi;
        plik >> ileWierzcholkow;
        plik >> wierzcholekStartowy;
        plik >> wierzcholekKoncowy;
        lista = new Lista(ileWierzcholkow);
        macierz = new Macierz(ileWierzcholkow);

        for (int i = 0; i < ileKrawedzi; i++)       //Krawêdzie s¹ nieskierowane
        {
            int poczatek, koniec, waga;
            plik >> poczatek >> koniec >> waga;
            macierz->dodajKrawedz(poczatek, koniec, waga);
            macierz->dodajKrawedz(koniec, poczatek, waga);
            lista->dodajKrawedz(poczatek, koniec, waga);
            lista->dodajKrawedz(koniec, poczatek, waga);
        }
        wyswietlenie();
    }
    else cout << "Podana nazwa pliku jest nieprawidlowa!" << endl;
    plik.close();

    wyborDrzewa();
}

void Menu::wczytajPlikSkierowany()
{
    //Standardowe wczytywanie z pliku.
    string nazwa;
    cout << "\nPodaj nazwe pliku: ";
    cin >> nazwa;
    ifstream plik;
    plik.open(nazwa);

    if (plik.is_open())
    {
        if (macierz != nullptr)
        {
            delete macierz;
        }
        if (lista != nullptr)
        {
            delete lista;
        }

        plik >> ileKrawedzi;
        plik >> ileWierzcholkow;
        plik >> wierzcholekStartowy;
        plik >> wierzcholekKoncowy;
        lista = new Lista(ileWierzcholkow);
        macierz = new Macierz(ileWierzcholkow);

        for (int i = 0; i < ileKrawedzi; i++)       //Krawêdzie s¹ skierowane
        {
            int poczatek, koniec, waga;
            plik >> poczatek >> koniec >> waga;
            macierz->dodajKrawedz(poczatek, koniec, waga);
            lista->dodajKrawedz(poczatek, koniec, waga);
        }
        wyswietlenie();
    }
    else cout << "Podana nazwa pliku jest nieprawidlowa!" << endl;
    plik.close();

    wyborSciezki();
}

void Menu::wyswietlenie()
{
    if (macierz != nullptr && lista != nullptr)
    {
        cout << "\nLista sasiedztwa:" << endl;
        lista->wyswietl();
        cout << "\nMacierz sasiedztwa:" << endl;
        macierz->wyswietl();
    }
    else cout << "\nGraf jest pusty!" << endl;
    wybor();
}

void Menu::wyborDrzewa()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz dzialanie:" << endl;
    cout << "1. Algorytm Kruskala (1)" << endl;
    cout << "2. Algorytm Prima (2)" << endl;
    cout << "3. Wykonanie testow dla obu algorytmów (algorytm Prima tylko dla reprezentacji macierzowej) (3)" << endl;
    cout << "4. Powrot do glownego menu (4)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie wybranej akcji.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomenda = true;                                 //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.

         if (wejscie == 1)
        {
            drzewoKruskala();
        }
        else if (wejscie == 2)
        {
            drzewoPrima();
        }
        else if (wejscie == 3)
        {
            drzewoTesty();
        }
        else if (wejscie == 4)
        {
            powrot = true;
            nieznanaKomenda = false;
        }
        else
        {
            cout << "Nieznana komenda! Sprobuj jeszcze raz:" << endl;
            wyborDrzewa();
        }
    }
    wybor();
}

void Menu::drzewoPrima()
{
    //Wykonanie algorytmu Prima dla obu reprezentacji grafu.
    if (macierz == nullptr || lista == nullptr)
    {
        cout << "\nGraf jest pusty!" << endl;
        return;
    }

    auto* prim = new Prim();
    prim->ustawZmienne(ileWierzcholkow, ileKrawedzi, wierzcholekStartowy);
    prim->algorytmMacierz(macierz);
    cout << "\nMacierz sasiedztwa: " << endl;
    prim->wyswietl();

    prim->algorytmLista(lista);
    cout << "\nLista sasiedztwa: " << endl;
    prim->wyswietl();

    delete prim;

    wyborDrzewa();
}

void Menu::drzewoKruskala()
{
    //Wykonanie algorytmu Kruskala dla obu reprezentacji grafu.
    if (macierz == nullptr || lista == nullptr)
    {
        cout << "\nGraf jest pusty!" << endl;
        return;
    }

    auto* kruskal = new Kruskal();
    kruskal->algorytmMacierz(macierz);
    cout << "\nWynik dla macierzy sasiedztwa: " << endl;
    wyswietlDrzewoKruskala(kruskal->znajdzListeKrawedzi());
    kruskal->usunWyniki();

    kruskal->algorytmLista(lista);
    cout << "\nWynik dla listy sasiedztwa: " << endl;
    wyswietlDrzewoKruskala(kruskal->znajdzListeKrawedzi());
    kruskal->usunWyniki();

    delete kruskal;

    wyborDrzewa();
}

void Menu::wyswietlDrzewoKruskala(list<Krawedz>& listaKrawedzi)
{
    //Wyœwietla wynik dzia³ania algorytmu (lista krawêdzi nale¿¹cych do MST).
    int mstWeight = 0;
    cout << "Krawedzie nalezace do MST: " << endl;
    for (auto krawedz : listaKrawedzi)
    {
        cout << krawedz.poczatek << ", " << krawedz.koniec << ", waga: " << krawedz.waga << endl;
        mstWeight += krawedz.waga;
    }
    cout << "Waga drzewa wynosi: " << mstWeight << endl;
}

void Menu::wyborSciezki()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz dzialanie:" << endl;
    cout << "1. Algorytm Dijkstry (1)" << endl;
    cout << "2. Algorytm Bellmana-Forda (2)" << endl;
    cout << "3. Wykonanie testow dla obu algorytmow (3)" << endl;
    cout << "4. Powrot do glownego menu (4)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie wybranej akcji.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomenda = true;                                 //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.

        if (wejscie == 1)
        {
            sciezkaDijkstra();
        }
        else if (wejscie == 2)
        {
            sciezkaFordBellman();
        }
        else if (wejscie == 3)
        {
            sciezkaTesty();
        }
        else if (wejscie == 4)
        {
            powrot = true;
            nieznanaKomenda = false;
        }
        else
        {
            cout << "Nieznana komenda! Sprobuj jeszcze raz:" << endl;
            wyborSciezki();
        }
    }
    wybor();
}

void Menu::sciezkaDijkstra()
{
    //Wykonuje algorytm Dijkstry dla obu reprezentacji grafu.
    if (macierz == nullptr || lista == nullptr)
    {
        cout << "\nGraf jest pusty!" << endl;
        return;
    }

    auto* dijkstra = new Dijkstra(macierz->rozmiar());
    dijkstra->algorytmMacierz(macierz, wierzcholekStartowy);
    cout << "\nMacierz sasiedztwa: " << endl;
    wyswietlSciezke(dijkstra->pierwszyElementOdleglosc(), dijkstra->pierwszyElementPoprzednikow());
    cout << endl;

    dijkstra->algorytmLista(lista, wierzcholekStartowy);
    cout << "Lista sasiedztwa: " << endl;
    wyswietlSciezke(dijkstra->pierwszyElementOdleglosc(), dijkstra->pierwszyElementPoprzednikow());
    delete dijkstra;
    wyborSciezki();
}

void Menu::sciezkaFordBellman()
{
    //Wykonuje algorytm Forda-Bellmana dla obu reprezentacji grafu.
    if (macierz == nullptr || lista == nullptr)
    {
        cout << "\nGraf jest pusty!" << endl;
        return;
    }

    auto* fordBellman = new FordBellman(macierz->rozmiar());
    fordBellman->algorytmMacierz(macierz, wierzcholekStartowy);
    cout << "\nMacierz sasiedztwa: " << endl;
    wyswietlSciezke(fordBellman->pierwszyElementOdleglosc(), fordBellman->pierwszyElementPoprzednikow());
    cout << endl;

    fordBellman->algorytmLista(lista, wierzcholekStartowy);
    cout << "Lista sasiedztwa: " << endl;
    wyswietlSciezke(fordBellman->pierwszyElementOdleglosc(), fordBellman->pierwszyElementPoprzednikow());
    delete fordBellman;
    wyborSciezki();
}

void Menu::wyswietlSciezke(int* odleglosc, int* poprzednik)
{
    //Wyœwietla wynik dzia³ania algorytmu (w obu przypadkach tablice odleg³oœci i poprzedników).
    string reprezentacja;
    string wierzcholek;

    for (int i = 0; i < macierz->rozmiar(); i++)
    {
        if (odleglosc[i] == INT_MAX) continue;
        int wierzcholekRoboczy = i;
        while (wierzcholekRoboczy != wierzcholekStartowy)
        {
            wierzcholek.insert(0, to_string(poprzednik[wierzcholekRoboczy]) + " -> ");
            wierzcholekRoboczy = poprzednik[wierzcholekRoboczy];
        }

        wierzcholek.append(to_string(i));
        reprezentacja.append(to_string(i) + " (koszt = " + to_string(odleglosc[i]) + "): ");
        reprezentacja.append(wierzcholek + "\n");
        wierzcholek = "";
    }
    cout << reprezentacja;
}

void Menu::sciezkaTesty()
{
    auto* test = new TestSciezki();
    test->testyCzasu();
    delete test;
}

void Menu::drzewoTesty()
{
    auto* test = new TestDrzewa();
    test->testyCzasu();
    delete test;
}