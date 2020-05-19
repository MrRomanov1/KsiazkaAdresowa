#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdio>

using namespace std;

class Uzytkownik {
public:

    int idUzytkownika;
    string login, haslo;

    static int logowanie(vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow);
    static int rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow);
};

void zapiszUzytkownikaDoPliku (vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow);
int wczytajUzytkownikow (vector <Uzytkownik> &uzytkownicy);
void zmienHasloUzytkownika(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika, int iloscUzytkownikow);
