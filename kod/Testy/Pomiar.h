#pragma once
#include <chrono>

using namespace std;


struct PomiarCzasu                  //Struktura opisuj¹ca czas wykonania dla obu algorytmów.
{
    double pierwszy;
    double drugi;
};

class Pomiar                        //Klasa s³u¿¹ca do jednolitego wykonywania pomiarów czasu trwania algorytmów.
{
private:
    double czasTrwania;             //Zmienna przechowuj¹ca informacjê o d³ugoœci wykonywania zadanej akcji w mikrosekundach.
    chrono::high_resolution_clock::time_point licznikWlaczony;          //Zmienna przechowuj¹ca czas startu pomiaru.
    chrono::high_resolution_clock::time_point licznikWylaczony;         //Zmienna przechowuj¹ca czas koñca pomiaru.
public:

    Pomiar();                       //Konstruktor klasy.
    void czasStart();               //Rozpoczyna odmierzanie czasu.
    void czasStop();                //Koñczy odmierzanie czasu.
    double jakiCzasTrwania();       //Zwraca czas w mikrosekundach, który up³yn¹³ dla ostatniego pomiaru.
};