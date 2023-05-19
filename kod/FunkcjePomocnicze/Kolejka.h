#pragma once
#include <iostream>
#include <vector>

using namespace std;

// Klasa generyczna kolejki priorytetowej (wymaga implementacji odpowiednich operatorów).
template<class T>
class Kolejka
{
private:
    // Sta³a opisuj¹ca wyj¹tek.
    const string EXCEPTION_DESC = "Kopiec jest pusty!";
    // Wektor elementów kolejki priorytetowej.
    vector<T> baza;
    // Iloœæ wierzcho³ków kopca.
    int ileWierzcholkow;
    // Naprawia kopiec w górê od zadanego indeksu.
    void naprawKopiecGora(int indeks);
    // Naprawia kopiec w dó³ od zadanego indeksu.
    void naprawKopiecDol(int indeks);
public:
    // Konstruktor klasy Kolejka.
    explicit Kolejka();
    // Destruktor klasy Kolejka.
    ~Kolejka();
    // Dodaje element do kolejki priorytetowej.
    void dodaj(T element);
    // Zamienia wartoœæ elementu 'existing', który znajduje siê w kolejce na 'newValue' i aktualizuje kopiec.
    void zaktualizujKolejke(T existing, T newValue);
    // Œci¹ga minimalny element, usuwa go z kopca oraz przywraca jego w³asnoœci.
    T zdejmij();
    // Sprawdza czy dany element znajduje siê w kolejce.
    bool znajdz(T element);
    // Czyœci kolejkê.
    void wyczysc();
    // Sprawdza czy kolejka jest pusta.
    bool czyPusta();
};

template<class T>
Kolejka<T>::Kolejka()
{
    ileWierzcholkow = 0;
}

template<class T>
Kolejka<T>::~Kolejka() = default;

template<class T>
void Kolejka<T>::dodaj(T element)
{
    //Standardowe dodanie elementu do kopca.
    int indeks = ileWierzcholkow;
    ileWierzcholkow++;
    baza.push_back(element);
    naprawKopiecGora(indeks);
}

template<class T>
void Kolejka<T>::zaktualizujKolejke(T existing, T newValue)
{
    for (int i = 0; i < ileWierzcholkow; i++)
    {
        //Jeœli element zostanie znaleziony, zamieniamy wartoœæ i aktualizujemy kopiec.
        if (baza[i] == existing)
        {
            baza[i] = newValue;
            if (i == 0)
            {
                naprawKopiecDol(0);
                return;
            }
            T parent = baza[(i - 1) / 2];
            if (baza[i] < parent) naprawKopiecGora(i);
            else naprawKopiecDol(i);
            return;
        }
    }
}

template<class T>
T Kolejka<T>::zdejmij()
{
    if (ileWierzcholkow == 0)throw length_error(EXCEPTION_DESC);

    ileWierzcholkow--;

    //Zapisujemy wartoœæ szczytu kopca i usuwamy go.
    T root = baza[0];
    baza[0] = baza[ileWierzcholkow];
    baza.erase(baza.begin() + ileWierzcholkow);
    naprawKopiecDol(0);
    return root;
}

template<class T>
void Kolejka<T>::naprawKopiecGora(int indeks)
{
    //Standardowa naprawa kopca w górê.
    int parent = (indeks - 1) / 2;
    T fixVertex = baza[indeks];
    while (indeks > 0 && baza[parent] > fixVertex)
    {
        T temp = baza[indeks];
        baza[indeks] = baza[parent];
        baza[parent] = temp;
        indeks = parent;
        parent = (indeks - 1) / 2;
    }
}

template<class T>
void Kolejka<T>::naprawKopiecDol(int indeks)
{
    if (indeks >= ileWierzcholkow) return; // sprawdzenie, czy indeks jest prawid³owy

    //Standardowa naprawa kopca w dó³.
    T fixVertex = baza[indeks];
    int wnuki = 2 * indeks + 1;
    while (wnuki < ileWierzcholkow)
    {
        if (wnuki + 1 < ileWierzcholkow && baza[wnuki] > baza[wnuki + 1]) wnuki++;
        if (fixVertex <= baza[wnuki]) break;
        T temp = baza[indeks];
        baza[indeks] = baza[wnuki];
        baza[wnuki] = temp;
        indeks = wnuki;
        wnuki = 2 * wnuki + 1;
    }
}

template<class T>
bool Kolejka<T>::znajdz(T element)
{
    for (int i = 0; i < ileWierzcholkow; i++)
    {
        if (baza[i] == element) return true;
    }
    return false;
}

template<class T>
void Kolejka<T>::wyczysc()
{
    baza.wyczysc();
    ileWierzcholkow = 0;
}

template<class T>
bool Kolejka<T>::czyPusta()
{
    return ileWierzcholkow == 0;
}