#pragma once

#include <iostream>

class Menu
{
private:
	int wejscie;
	bool powrot = false;
	bool nieznanaKomenda = true;
public:
	Menu();
	void wybor();
};