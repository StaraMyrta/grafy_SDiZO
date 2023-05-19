#include "Menu.h"

using namespace std;

Menu::Menu() = default;

Menu::~Menu() = default;

void Menu::wybor()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz co chcesz zrobic:" << endl;
    cout << "1. Wyswietlenie grafu (1)" << endl;
    cout << "2. Wyznaczenie minimalnego drzewa rozpinajacego (2)" << endl;
    cout << "3. Wyznaczenie najkrotszej sciezki w grafie (3)" << endl;
    cout << "4. Cofnij (4)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie menu wybranej struktury.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomkonieca = true;                                 //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.

        if (wejscie == 1)
        {
            wyswietlenie();
        }
        else if (wejscie == 2)
        {
            wyborDrzewa();
        }
        else if (wejscie == 3)
        {
            wyborSciezki();
        }
        else if (wejscie == 4)
        {
            powrot = true;
            nieznanaKomkonieca = false;
        }
        else
        {
            cout << "Nieznana komenda! Sprobuj jeszcze raz:" << endl;
            wybor();
        }
    }
}

void Menu::wyborTworzenieDrzewo()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz co chcesz zrobic:" << endl;
    cout << "1. Wczytanie danych z pliku (1)" << endl;
    cout << "2. Losowe stworzenie grafu (2)" << endl;
    cout << "3. Powrot do glownego menu (3)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie wybranej akcji.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomkonieca = true;                                 //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.

        if (wejscie == 1)
        {
            wczytajPlikDrzewo();
        }
        else if (wejscie == 2)
        {
            stworzLosowoDrzewo();
        }
        else if (wejscie == 3)
        {
            powrot = true;
            nieznanaKomkonieca = false;
        }
        else
        {
            cout << "Nieznana komenda! Sprobuj jeszcze raz:" << endl;
            wyborTworzenieDrzewo();
        }
    }
    wyborDrzewa();
}

void Menu::wczytajPlikDrzewo()
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

void Menu::stworzLosowoDrzewo()
{//Wczytanie parametry generowanego grafu od u¿ytkownika.
    int iloscWierzcholkow, gestosc;
    cout << "\nPodaj liczbe wierzcholkow grafu: ";
    cin >> iloscWierzcholkow;
    cout << "Podaj gestosc grafu (w %): ";
    cin >> gestosc;

    if (macierz != nullptr && lista != nullptr)
    {
        delete macierz;
        delete lista;
    }
    macierz = new Macierz(iloscWierzcholkow);
    lista = new Lista(iloscWierzcholkow);

    //Maksymalna iloœæ krawêdzi to n(n-1)/2, uwzglêdniaj¹c gêstoœæ trzeba wynik przemno¿yæ przez gêstoœæ i zaokr¹gliæ w dó³. 
    int maxKrawedzi = floor((iloscWierzcholkow*(iloscWierzcholkow-1)* gestosc/200));
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

    //Dodajemy pozosta³e krawêdzie (zawsze zostanie wygenerowane chocia¿ drzewo rozpinaj¹ce).
    while (licznikKrawedzi < maxKrawedzi)
    {
        int poczatek = rand() % iloscWierzcholkow;
        int koniec = rand() % iloscWierzcholkow;
        int waga = (rand() % maxKrawedzi) + 1;

        if (macierz->znajdzKrawedz(poczatek, koniec) == 0)
        {
            macierz->dodajKrawedz(poczatek, koniec, waga);
            macierz->dodajKrawedz(koniec, poczatek, waga);

            lista->dodajKrawedz(poczatek, koniec, waga);
            lista->dodajKrawedz(koniec, poczatek, waga);
            licznikKrawedzi++;
        }
    }
    wyborDrzewa();
}

void Menu::wyborTworzenieSciezka()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz co chcesz zrobic:" << endl;
    cout << "1. Wczytanie danych z pliku (1)" << endl;
    cout << "2. Losowe stworzenie grafu (2)" << endl;
    cout << "3. Powrot do glownego menu (3)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie wybranej akcji.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomkonieca = true;                                 //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.

        if (wejscie == 1)
        {
            wczytajPlikSciezka();
        }
        else if (wejscie == 2)
        {
            stworzLosowoSciezka();
        }
        else if (wejscie == 3)
        {
            powrot = true;
            nieznanaKomkonieca = false;
        }
        else
        {
            cout << "Nieznana komenda! Sprobuj jeszcze raz:" << endl;
            wyborTworzenieSciezka();
        }
    }
    wyborSciezki();
}

void Menu::wczytajPlikSciezka()
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

void Menu::stworzLosowoSciezka()
{
    //Wczytujemy parametry generowanego grafu od u¿ytkownika.
    int iloscWierzcholkow, gestosc;
    cout << "\nPodaj liczbe wierzcholkow grafu: ";
    cin >> iloscWierzcholkow;
    cout << "Podaj gestosc grafu (w %): ";
    cin >> gestosc;

    if (macierz != nullptr && lista != nullptr)
    {
        delete macierz;
        delete lista;
    }
    macierz = new Macierz(iloscWierzcholkow);
    lista = new Lista(iloscWierzcholkow);

    //Maksymalna iloœæ wierzcho³ków to suma ci¹gu arytmetycznego an = n.
    int maxKrawedzi = static_cast<int>(gestosc / 100.0f * (((iloscWierzcholkow + 1) / 2.0f) * iloscWierzcholkow));
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

    //Dodajemy pozosta³e krawêdzie (zawsze zostanie wygenerowane chocia¿ drzewo rozpinaj¹ce).
    while (licznikKrawedzi < maxKrawedzi)
    {
        int poczatek = rand() % iloscWierzcholkow;
        int koniec = rand() % iloscWierzcholkow;
        int waga = (rand() % maxKrawedzi) + 1;

        if (macierz->znajdzKrawedz(poczatek, koniec) == 0)
        {
            macierz->dodajKrawedz(poczatek, koniec, waga);
            macierz->dodajKrawedz(koniec, poczatek, waga);

            lista->dodajKrawedz(poczatek, koniec, waga);
            lista->dodajKrawedz(koniec, poczatek, waga);
            licznikKrawedzi++;
        }
    }

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
}

void Menu::wyborDrzewa()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz dzialanie:" << endl;
    cout << "1. Stworz graf nieskierowany (1)" << endl;
    cout << "2. Algorytm Kruskala (2)" << endl;
    cout << "3. Algorytm Prima (3)" << endl;
    cout << "4. Wykonanie testow dla obu algorytmow(4)" << endl;
    cout << "5. Powrot do glownego menu (5)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie wybranej akcji.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomkonieca = true;                                 //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.

        if (wejscie == 1)
        {
            wyborTworzenieDrzewo();
        }
        else if (wejscie == 2)
        {
            drzewoKruskala();
        }
        else if (wejscie == 3)
        {
            drzewoPrima();
        }
        else if (wejscie == 4)
        {
            drzewoTesty();
        }
        else if (wejscie == 5)
        {
            powrot = true;
            nieznanaKomkonieca = false;
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

void Menu::drzewoTesty()
{
    auto* test = new TestDrzewa();
    test->testyCzasu();
    delete test;
}

void Menu::wyborSciezki()
{
    cout << endl;                                               //Wybór dzia³ania.
    cout << "Wybierz dzialanie:" << endl;
    cout << "1. Stworzenie grafu skierowanego (1)" << endl;
    cout << "2. Algorytm Dijkstry (2)" << endl;
    cout << "3. Algorytm Bellmana-Forda (3)" << endl;
    cout << "4. Wykonanie testow dla obu algorytmow (4)" << endl;
    cout << "5. Powrot do glownego menu (5)" << endl;
    cout << "Wybierz opcje: ";
    powrot = false;                                             //Wczytanie danych z konsoli do 'wejscie' i wywo³anie wybranej akcji.
    while (!powrot)
    {
        cin >> wejscie;
        nieznanaKomkonieca = true;                                 //Jeœli komenda to 'powrot' ustawione zostaj¹ flagi umo¿liwiaj¹ce wyjœcie z pêtli.

        if (wejscie == 1)
        {
            wyborTworzenieSciezka();
        }
        else if (wejscie == 2)
        {
            sciezkaDijkstra();
        }
        else if (wejscie == 3)
        {
            sciezkaFordBellman();
        }
        else if (wejscie == 4)
        {
            sciezkaTesty();
        }
        else if (wejscie == 4)
        {
            powrot = true;
            nieznanaKomkonieca = false;
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