#include "Lista.h"

using namespace std;

Lista::Lista(int rozm)
{
    this->rozm = rozm;
    //Alokacja pami�ci na 'rozm' list.
    baza = new list<ElemListy>[rozm];
}

Lista::~Lista()
{
    delete[] baza;
}

void Lista::dodajKrawedz(int wierzcholekPocz, int wierzcholekKon, int waga)
{
    try
    {
        //Tworzymy nowy element grafu o zadanej wadze.
        ElemListy krawedz{};
        krawedz.wierzcholek = wierzcholekKon;
        krawedz.waga = waga;
        baza[wierzcholekPocz].push_back(krawedz);
    }
    catch (out_of_range&)
    {
        cout << "nieprawidlowe dane!" << endl;
    }
}

void Lista::usunKrawedz(int wierzcholekPocz, int wierzcholekKon)
{
    try
    {
        //Znaleziony i usuniety jest wierzcho�ek je�li iterator nie wskazuje na koniec listy.
        auto x = znajdzWierzcholek(baza[wierzcholekPocz], wierzcholekKon);
        if (x != baza[wierzcholekPocz].end())
            baza[wierzcholekPocz].erase(x);
    }
    catch (out_of_range&)
    {
        cout << "nieprawidlowe dane!" << endl;
    }
}

int Lista::znajdzKrawedz(int wierzcholekPocz, int wierzcholekKon)
{
    //Zwracamy przepustowo�� kraw�dzi dla danych wierzcho�k�w.
    for (auto item : baza[wierzcholekPocz])
    {
        if (item.wierzcholek == wierzcholekKon) return item.waga;
    }
    return INT_MAX;
}

list<ElemListy>::iterator Lista::znajdzWierzcholek(list<ElemListy>& lista, int wierzcholek)
{
    //Iteracja po li�cie a� do znalezienia danego wierzcho�ka.
    return find_if(lista.begin(), lista.end(), [wierzcholek](const ElemListy& elem)
        {
            return elem.wierzcholek == wierzcholek;
        });
}

list<ElemListy>& Lista::sasiedziWierzcholka(int wierzcholek)
{
    //Zwraca list� s�siad�w dla danego wierzcho�ka.
    return baza[wierzcholek];
}

int Lista::rozmiar()
{
    //Zwraca ilo�� wierzcho�k�w grafu.
    return rozm;
}

void Lista::wyswietl()
{
    //Wy�wietla ci�g znak�w reprezentuj�cy graf w postaci listy sasiedztwa.
    for (int i = 0; i < rozm; i++)
    {
        cout << i << ": ";
        for (auto item : baza[i]) cout << item.wierzcholek << "(" << item.waga << "), ";
        cout << "\b\b" << "  " << "\n";
    }
}