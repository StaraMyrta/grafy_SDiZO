#include <iostream>
#include <ctime>
#include "Menu/Menu.h"

using namespace std;

int main()
{
    auto* menu = new Menu();            //Wywołanie Menu, umożliwiającego użytkownikowi wybór struktur i operacji poprzez konsolę
    menu->wybor();
    delete menu;
    return 0;
}