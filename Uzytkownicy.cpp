#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdio>
#include "Uzytkownicy.h"

using namespace std;

int Uzytkownik::logowanie(vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow) {
    string login, haslo;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;

    for (vector <Uzytkownik> :: iterator i = uzytkownicy.begin(); i != uzytkownicy.end(); i++) {
        if (i -> login == login) {
            for (int proby=0; proby<3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> haslo;
                if (i -> haslo == haslo) {
                    cout << "Poprawnie zalogowano." << endl;
                    Sleep(1000);
                    return i -> idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Zaczekaj przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma takiego uzytkownika." << endl;
    Sleep (1500);
    return 0;
}

void zapiszUzytkownikaDoPliku (vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow) {

    fopen("Uzytkownicy.txt","w");

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plik.good()) {
        for (int i = 0; i< iloscUzytkownikow; i++) {
            plik << uzytkownicy[i].idUzytkownika << "|" << uzytkownicy[i].login << "|" << uzytkownicy[i].haslo << "|" << endl;
        }
        plik.close();
    }
}

int Uzytkownik::rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    Uzytkownik temp;
    string login, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;
    int i=0;

    while (i<iloscUzytkownikow) {
        if (uzytkownicy[i].login == login) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> login;
            i=0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    temp.idUzytkownika = iloscUzytkownikow + 1;
    temp.login = login;
    temp.haslo = haslo;

    uzytkownicy.push_back(temp);
    iloscUzytkownikow++;

    zapiszUzytkownikaDoPliku(uzytkownicy,iloscUzytkownikow);

    cout << "Konto zostalo poprawnie zalozone." << endl;
    Sleep(1000);

    return iloscUzytkownikow;
}

int wczytajUzytkownikow (vector <Uzytkownik> &uzytkownicy) {

    int iloscUzytkownikow = 0;
    Uzytkownik wczytywanyUzytkownik;

    string linia;
    fstream plik;
    int nr_linii = 1;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good()==false) {
        return iloscUzytkownikow;
    }

    while (getline(plik,linia,'|')) {
        if (linia == "") {
            return iloscUzytkownikow;
        }
        switch(nr_linii) {
        case 1:
            wczytywanyUzytkownik.idUzytkownika = atoi(linia.c_str());
            break;
        case 2:
            wczytywanyUzytkownik.login = linia;
            break;
        case 3:
            wczytywanyUzytkownik.haslo = linia;
            break;
        }

        if (nr_linii == 3) {

            iloscUzytkownikow++;
            nr_linii = 0;
            uzytkownicy.push_back(wczytywanyUzytkownik);
        }
        nr_linii ++;
    }
    plik.close();
    return iloscUzytkownikow;
}

void zmienHasloUzytkownika(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika, int iloscUzytkownikow) {

    system("cls");
    string noweHaslo;
    cout << "Wprowadz nowe haslo: " << endl;
    while(true) {
        cin >> noweHaslo;
        for (vector <Uzytkownik> :: iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
            if (itr -> idUzytkownika == idZalogowanegoUzytkownika) {
                if (itr -> haslo == noweHaslo) {
                    system("cls");
                    cout << "Haslo musi sie roznic od poprzedniego. Wprowadz nowe haslo ponownie." << endl;
                } else {
                    itr -> haslo = noweHaslo;
                    zapiszUzytkownikaDoPliku(uzytkownicy, iloscUzytkownikow);
                    cout << "Haslo zostalo zmienione."<< endl;
                    Sleep(2000);
                    return;
                }
            }
        }
    }
}
