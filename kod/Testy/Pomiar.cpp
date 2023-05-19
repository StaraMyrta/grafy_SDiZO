#include "Pomiar.h"

using namespace std;

Pomiar::Pomiar()
{
    czasTrwania = 0;
}

void Pomiar::czasStart()
{
    licznikWlaczony = chrono::high_resolution_clock::now();         //Ustawienie pocz¹tkowego czasu wykonywania.
}

void Pomiar::czasStop()
{
    licznikWylaczony = chrono::high_resolution_clock::now();        //Ustawienie koñcowego czasu wykonywania i zapisanie ró¿nicy do 'czasTrwania'.
    chrono::duration<double, micro> time = licznikWylaczony - licznikWlaczony;
    czasTrwania = time.count();
}

double Pomiar::jakiCzasTrwania()
{
    return czasTrwania;                                             //Zwrócenie czasu trwania testowanej operacji.
}