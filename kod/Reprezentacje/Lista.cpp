#include "Lista.h"

using namespace std;

Lista::Lista(int rozm)
{
    this->rozm = rozm;
    //Alokacja pamiêci na 'rozm' list.
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
        //Znaleziony i usuniety jest wierzcho³ek jeœli iterator nie wskazuje na koniec listy.
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
    //Zwracamy przepustowoœæ krawêdzi dla danych wierzcho³ków.
    for (auto item : baza[wierzcholekPocz])
    {
        if (item.wierzcholek == wierzcholekKon) return item.waga;
    }
    return INT_MAX;
}

list<ElemListy>::iterator Lista::znajdzWierzcholek(list<ElemListy>& lista, int wierzcholek)
{
    //Iteracja po liœcie a¿ do znalezienia danego wierzcho³ka.
    return find_if(lista.begin(), lista.end(), [wierzcholek](const ElemListy& elem)
        {
            return elem.wierzcholek == wierzcholek;
        });
}

list<ElemListy>& Lista::sasiedziWierzcholka(int wierzcholek)
{
    //Zwraca listê s¹siadów dla danego wierzcho³ka.
    return baza[wierzcholek];
}

int Lista::rozmiar()
{
    //Zwraca iloœæ wierzcho³ków grafu.
    return rozm;
}

void Lista::wyswietl()
{
    //Wyœwietla ci¹g znaków reprezentuj¹cy graf w postaci listy sasiedztwa.
    for (int i = 0; i < rozm; i++)
    {
        cout << i << ": ";
        for (auto item : baza[i]) cout << item.wierzcholek << "(" << item.waga << "), ";
        cout << "\b\b" << "  " << "\n";
    }
}