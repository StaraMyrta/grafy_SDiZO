#pragma once

///Struktura opisuj�ca kraw�d�.
struct Krawedz
{
    ///Wierzcho�ek pocz�tkowy kraw�dzi.
    int poczatek;
    ///Wierzcho�ek ko�cowy kraw�dzi.
    int koniec;
    ///Waga kraw�dzi.
    int waga;
    ///Sprawdza czy kraw�dzie s� r�wne (w przypadku MST s� nieskierowane).
    ///\param item - kraw�d� do por�wnania.
    ///\return true je�li kraw�dzie s� r�wne, w przeciwnym wypadku false.
    bool operator==(const Krawedz& item)
    {
        return (this->poczatek == item.poczatek && this->koniec == item.koniec && this->waga == item.waga) ||
            (this->poczatek == item.koniec && this->koniec == item.poczatek && this->waga == item.waga);
    }
    ///Sprawdza czy kraw�dzie s� r�ne.
    ///\param item - kraw�d� do por�wnania.
    ///\return true je�li kraw�dzie s� r�ne, w przeciwnym wypadku false.
    bool operator!=(const Krawedz& item)
    {
        return !this->operator==(item);
    }
    ///Sprawdza czy waga kraw�dzi jest mniejsza od danej.
    ///\param item - kraw�d� do por�wnania.
    ///\return true je�li waga kraw�dzi jest mniejsza, w przeciwnym wypadku false.
    bool operator<(const Krawedz& item)
    {
        return this->waga < item.waga;
    }
    ///Sprawdza czy waga kraw�dzi jest mniejsza b�d� r�wna od danej.
    ///\param item - kraw�d� do por�wnania.
    ///\return true jest waga kraw�dzi jest mniejsza lub r�wna, w przeciwnym wypadku false.
    bool operator<=(const Krawedz& item)
    {
        return this->waga <= item.waga;
    }
    ///Sprawdza czy waga kraw�dzi jest wi�ksza od danej.
    ///\param item - kraw�d� do por�wnania.
    ///\return true jest waga kraw�dzi jest wi�ksza, w przeciwnym wypadku false.
    bool operator>(const Krawedz& item)
    {
        return this->waga > item.waga;
    }
};