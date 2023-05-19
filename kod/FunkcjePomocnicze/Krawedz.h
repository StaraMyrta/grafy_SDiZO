#pragma once

///Struktura opisuj¹ca krawêdŸ.
struct Krawedz
{
    ///Wierzcho³ek pocz¹tkowy krawêdzi.
    int poczatek;
    ///Wierzcho³ek koñcowy krawêdzi.
    int koniec;
    ///Waga krawêdzi.
    int waga;
    ///Sprawdza czy krawêdzie s¹ równe (w przypadku MST s¹ nieskierowane).
    ///\param item - krawêdŸ do porównania.
    ///\return true jeœli krawêdzie s¹ równe, w przeciwnym wypadku false.
    bool operator==(const Krawedz& item)
    {
        return (this->poczatek == item.poczatek && this->koniec == item.koniec && this->waga == item.waga) ||
            (this->poczatek == item.koniec && this->koniec == item.poczatek && this->waga == item.waga);
    }
    ///Sprawdza czy krawêdzie s¹ ró¿ne.
    ///\param item - krawêdŸ do porównania.
    ///\return true jeœli krawêdzie s¹ ró¿ne, w przeciwnym wypadku false.
    bool operator!=(const Krawedz& item)
    {
        return !this->operator==(item);
    }
    ///Sprawdza czy waga krawêdzi jest mniejsza od danej.
    ///\param item - krawêdŸ do porównania.
    ///\return true jeœli waga krawêdzi jest mniejsza, w przeciwnym wypadku false.
    bool operator<(const Krawedz& item)
    {
        return this->waga < item.waga;
    }
    ///Sprawdza czy waga krawêdzi jest mniejsza b¹dŸ równa od danej.
    ///\param item - krawêdŸ do porównania.
    ///\return true jest waga krawêdzi jest mniejsza lub równa, w przeciwnym wypadku false.
    bool operator<=(const Krawedz& item)
    {
        return this->waga <= item.waga;
    }
    ///Sprawdza czy waga krawêdzi jest wiêksza od danej.
    ///\param item - krawêdŸ do porównania.
    ///\return true jest waga krawêdzi jest wiêksza, w przeciwnym wypadku false.
    bool operator>(const Krawedz& item)
    {
        return this->waga > item.waga;
    }
};