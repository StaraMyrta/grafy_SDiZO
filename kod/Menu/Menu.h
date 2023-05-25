#pragma once

#include <iostream>
#include "../Algorytmy/Prim.h"
#include "../Algorytmy/Kruskal.h"
#include "../Algorytmy/Dijkstra.h"
#include "../Algorytmy/FordBellman.h"
#include "../Testy/TestSciezki.h"
#include "../Testy/TestDrzewa.h"
#include "../FunkcjePomocnicze/MST.h"

class Menu
{
public:
	Menu();
	~Menu();
	void wybor();

private:

	Lista* lista{};
	Macierz* macierz{};

	int ileKrawedzi;
	int ileWierzcholkow;
	int wierzcholekStartowy;
	int wierzcholekKoncowy;

	int wejscie;
	bool powrot = false;
	bool nieznanaKomenda = true;

	void wczytajPlikNieskierowany();
	void wczytajPlikSkierowany();
	void wyswietlenie();
	void wyborDrzewa();
	void drzewoPrima();
	static void wyswietlDrzewoPrima(int* key, int* polaczenie, int rozm);
	void drzewoKruskala();
	static void wyswietlDrzewoKruskala(list<Krawedz>& listaKrawedzi);
	void wyborSciezki();
	void sciezkaDijkstra();
	void sciezkaFordBellman();
	void wyswietlSciezke(int* odleglosc, int* poprzednik);

	void drzewoTesty();
	void sciezkaTesty();
};