#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstdio>

using namespace std;

struct Uzytkownik {
    int idUzytkownika = 0;
    string login = "", haslo = "";
};

struct Osoba {

    int idAdresata = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";

};

string sprawdzPoprawnoscTelefonu() {
    string numerTelefonu;
    int i, dlugoscNumeru;

    cin.sync();
    getline(cin,numerTelefonu);
    dlugoscNumeru = numerTelefonu.length();
    i=0;

    while (i<dlugoscNumeru) {
        if ((numerTelefonu [i] >= '0')&&(numerTelefonu[i] <='9') || (numerTelefonu[i] == 32)) {
            i++;
        } else {
            cout << "Numer telefonu jest bledny. Wprowadz ponownie numer telefonu: ";
            cin.sync();
            getline(cin,numerTelefonu);
            dlugoscNumeru = numerTelefonu.length();
            i=0;
        }
    }
    return numerTelefonu;
}

string sprawdzPoprawnoscEmail() {
    string email;
    int dlugoscEmaila;
    int iloscMalp;  //sprawdzam czy jest znak @
    int iloscKropek;//sprawdzam czy jest kropka po znaku @
    int pozycjaMalpy, i, j;

    for (;;) {
        cin >> email;
        dlugoscEmaila = email.length();
        iloscMalp = 0;
        pozycjaMalpy = 0;
        iloscKropek = 0;
        i = 0;

        while (i < dlugoscEmaila) {
            if (email[i] == '@') {
                iloscMalp++;
                pozycjaMalpy = i;
            }
            i++;
        }

        j = pozycjaMalpy;

        while (j < dlugoscEmaila) {
            if (email[j] == '.') {
                iloscKropek++;
            }
            j++;
        }
        if ((iloscMalp == 1) && (iloscKropek > 0) && (dlugoscEmaila >4 )) {
            return email;
        } else {
            cout << "Niepoprawny adres email. Wprowadz ponownie: ";
        }
    }
}

void zapiszDoPlikuTymczasowego (Osoba aktuanyAdresat) {

    fstream plikTymczasowy;
    plikTymczasowy.open("Ksiazka_adresowa_tymczasowy.txt", ios::out | ios::app);

    plikTymczasowy << aktuanyAdresat.idAdresata<< "|" << aktuanyAdresat.idUzytkownika << "|" << aktuanyAdresat.imie << "|" << aktuanyAdresat.nazwisko << "|" << aktuanyAdresat.numerTelefonu << "|" << aktuanyAdresat.email << "|" << aktuanyAdresat.adres << "|" << endl;
    plikTymczasowy.close();
}

void zapiszEdytowanaOsobeDoPlikuTymczasowego (vector <Osoba> osoby, int idDoEdycji) {
    fstream plikTymczasowy;
    plikTymczasowy.open("Ksiazka_adresowa_tymczasowy.txt", ios::out | ios::app);

    for (vector <Osoba> :: iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if ( itr -> idAdresata == idDoEdycji) {
            plikTymczasowy << itr -> idAdresata << "|" << itr -> idUzytkownika << "|" << itr ->  imie << "|" << itr ->  nazwisko << "|" << itr ->  numerTelefonu << "|" << itr ->  email << "|" << itr ->  adres << "|" << endl;
        }
    }
    plikTymczasowy.close();
}

void zapiszEdycjeDoPliku(vector <Osoba> osoby, int idDoEdycji) {

    int nr_linii = 1;
    string linia;
    bool czyLiczbaRownaID = false;
    Osoba daneDoWczytania;
    fstream plikZDanymi;
    plikZDanymi.open("Ksiazka_adresowa.txt", ios::in);

    while (getline(plikZDanymi,linia,'|')) {
        if (linia == "") {
            return;
        }
        switch(nr_linii) {
        case 1:
            if  (atoi(linia.c_str()) == idDoEdycji) {
                czyLiczbaRownaID = true;
            } else {
                daneDoWczytania.idAdresata = atoi(linia.c_str());
            };
            break;
        case 2:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.idUzytkownika = atoi(linia.c_str());
            }
            break;
        case 3:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.imie = linia;
            }
            break;
        case 4:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.nazwisko = linia;
            }
            break;
        case 5:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.numerTelefonu = linia;
            }
            break;
        case 6:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.email = linia;
            }
            break;
        case 7:
            if (czyLiczbaRownaID == false) {
                daneDoWczytania.adres = linia;
            }
            break;
        }
        if (nr_linii == 7) {
            if (czyLiczbaRownaID == false) {
                zapiszDoPlikuTymczasowego(daneDoWczytania);
            } else {
                zapiszEdytowanaOsobeDoPlikuTymczasowego(osoby, idDoEdycji);
            }
            czyLiczbaRownaID = false;
            nr_linii = 0;
        }
        nr_linii ++;
    }
    plikZDanymi.close();
    remove ("Ksiazka_adresowa.txt");
    rename ("Ksiazka_adresowa_tymczasowy.txt","Ksiazka_adresowa.txt");
}

void edytujImie(vector <Osoba> &osoby, int idDoEdycji) {

    system("cls");
    string imieDoEdycji;
    cout << "Podaj nowe imie: ";
    cin >> imieDoEdycji;

    for (vector <Osoba>::iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> idAdresata == idDoEdycji) {
            itr -> imie = imieDoEdycji;
        }
    }
    cout << "Zmieniono imie na: " << imieDoEdycji << endl;
    zapiszEdycjeDoPliku(osoby, idDoEdycji);
    cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
    getch();
}

void edytujNazwisko(vector <Osoba> &osoby, int idDoEdycji) {

    system("cls");
    string nazwiskoDoEdycji;
    cout << "Podaj nowe nazwisko: ";
    cin >> nazwiskoDoEdycji;

    for (vector <Osoba>::iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> idAdresata == idDoEdycji) {
            itr -> nazwisko = nazwiskoDoEdycji;
        }
    }
    cout << "Zmieniono nazwisko na: " << nazwiskoDoEdycji << endl;
    zapiszEdycjeDoPliku(osoby, idDoEdycji);
    cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
    getch();
}

void edytujNumerTelefonu(vector <Osoba> &osoby, int idDoEdycji) {

    system("cls");
    string numerDoEdycji;
    cout << "Podaj nowy numer telefonu: ";
    numerDoEdycji = sprawdzPoprawnoscTelefonu();

    for (vector <Osoba>::iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> idAdresata == idDoEdycji) {
            itr -> numerTelefonu = numerDoEdycji;
        }
    }
    cout << "Zmieniono numer telefonu na: " << numerDoEdycji << endl;
    zapiszEdycjeDoPliku(osoby, idDoEdycji);
    cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
    getch();
}

void edytujEmail(vector <Osoba> &osoby, int idDoEdycji) {

    system("cls");
    string emailDoEdycji;
    cout << "Podaj nowy adres email: ";
    emailDoEdycji = sprawdzPoprawnoscEmail();

    for (vector <Osoba>::iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> idAdresata == idDoEdycji) {
            itr -> email = emailDoEdycji;
        }
    }
    cout << "Zmieniono email na: " << emailDoEdycji << endl;
    zapiszEdycjeDoPliku(osoby, idDoEdycji);
    cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
    getch();
}

void edytujAdres(vector <Osoba> &osoby, int idDoEdycji) {

    system("cls");
    string adresDoEdycji;
    cout << "Podaj nowy adres: ";
    cin >> adresDoEdycji;

    for (vector <Osoba>::iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> idAdresata == idDoEdycji) {
            itr -> adres = adresDoEdycji;
        }
    }
    cout << "Zmieniono adres na: " << adresDoEdycji << endl;
    zapiszEdycjeDoPliku(osoby, idDoEdycji);
    cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
    getch();
}

void wyswietlOsoby(vector <Osoba> osoby) {

    system("cls");
    if (osoby.empty()) {
        cout << "Nie masz zapisanych zadnych osob."<< endl;
    } else {
        for (vector <Osoba> :: iterator i = osoby.begin(); i != osoby.end(); i++) {

            cout << "Numer ID:          " << i -> idAdresata << endl;
            cout << "Imie i nazwisko:   " << i -> imie << " " << i -> nazwisko << endl;
            cout << "Adres email:       "<<i -> email << endl;
            cout << "Numer telefonu:    "<< i -> numerTelefonu<<endl;
            cout << "Adres:             "<<i -> adres << endl << endl;
        }
    }
}

bool sprawdzCzyPodaneIdIstnieje (vector <Osoba> osoby,int idDoEdycji) {

    bool sprawdzacz = false;
    for (vector <Osoba> :: iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> idAdresata == idDoEdycji) {
            sprawdzacz = true;
        }
    }
    return sprawdzacz;
}

void wyswietlMenuEdycji() {
    system("cls");
    cout << "Jakie dane chcesz edytowac: " << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Email" << endl;
    cout << "4. Numer telefonu" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu glownego" << endl;
}

void edytujOsobe(vector <Osoba> &osoby) {

    system("cls");
    wyswietlOsoby(osoby);
    int idDoEdycji;
    cout << "Pod ktorym numerem ID znajduje sie osoba, ktora chcesz edytowac: ";
    cin >> idDoEdycji;

    if (sprawdzCzyPodaneIdIstnieje(osoby, idDoEdycji) == 1) {
        char wybor;
        while (true) {

            wyswietlMenuEdycji();
            cin >> wybor;

            if (wybor == '1') {
                edytujImie(osoby,idDoEdycji);
            } else if (wybor == '2') {
                edytujNazwisko(osoby,idDoEdycji);
            } else if (wybor == '3') {
                edytujEmail(osoby,idDoEdycji);
            } else if (wybor == '4') {
                edytujNumerTelefonu(osoby, idDoEdycji);
            } else if (wybor == '5') {
                edytujAdres(osoby, idDoEdycji);
            } else if (wybor == '6') {
                break;
            }
        }
    } else {
        system("cls");
        cout << "Nie znaleziono osoby o podanym numerze ID." << endl;
        cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
        getch();
    }
}

void uzuwanieZPliku(int iloscOsob, int idDoUsuniecia) {

    int nr_linii = 1;
    string linia;
    bool czyLiczbaRownaID = false;
    Osoba usuwanyAdresat;
    fstream plikZDanymi;
    plikZDanymi.open("Ksiazka_adresowa.txt", ios::in);

    while (getline(plikZDanymi,linia,'|')) {
        if (linia == "") {
            return;
        }
        switch(nr_linii) {
        case 1:
            if  (atoi(linia.c_str()) == idDoUsuniecia) {
                czyLiczbaRownaID = true;
            } else {
                usuwanyAdresat.idAdresata = atoi(linia.c_str());
            };
            break;
        case 2:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.idUzytkownika = atoi(linia.c_str());
            }
            break;
        case 3:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.imie = linia;
            }
            break;
        case 4:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.nazwisko = linia;
            }
            break;
        case 5:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.numerTelefonu = linia;
            }
            break;
        case 6:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.email = linia;
            }
            break;
        case 7:
            if (czyLiczbaRownaID == false) {
                usuwanyAdresat.adres = linia;
            }
            break;
        }

        if (nr_linii == 7) {

            if (czyLiczbaRownaID == false) {
                zapiszDoPlikuTymczasowego (usuwanyAdresat);
            }
            czyLiczbaRownaID = false;
            nr_linii = 0;
        }
        nr_linii ++;
    }
    plikZDanymi.close();
    remove ("Ksiazka_adresowa.txt");
    rename ("Ksiazka_adresowa_tymczasowy.txt","Ksiazka_adresowa.txt");
}

int sprawdzOstatnieID() {

    int ostatnieID = 0;
    string linia;
    fstream plik;
    int nr_linii = 1;
    plik.open("Ksiazka_adresowa.txt", ios::in);

    if (plik.good()==false) {
        return ostatnieID;
    }

    while (getline(plik,linia,'|')) {

        switch(nr_linii) {
        case 1:
            if (atoi(linia.c_str()) == 0) {
                return ostatnieID;
            } else {
                ostatnieID = atoi(linia.c_str());
            }
            break;
        }

        if (nr_linii == 7) {
            nr_linii = 0;
        }
        nr_linii++;
    }
    plik.close();
    return ostatnieID;
}

void zapiszNowaOsobeDoPliku(Osoba pomocnicza) {

    fstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << pomocnicza.idAdresata<< "|" << pomocnicza.idUzytkownika << "|" << pomocnicza.imie << "|" << pomocnicza.nazwisko << "|" << pomocnicza.numerTelefonu << "|" << pomocnicza.email << "|" << pomocnicza.adres << "|" << endl;
    }
    plik.close();
}

void wyszukajPoImieniu(vector <Osoba> osoby) {
    system("cls");
    string szukaneImie;
    cout << "Wprowadz szukane imie: ";
    cin >> szukaneImie;
    int licznik = 0;
    system("cls");

    for (vector <Osoba> :: iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> imie == szukaneImie) {
            cout << "Numer ID: " << itr -> idAdresata << endl;
            cout << "Imie i nazwisko: " << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Adres email: "<< itr -> email << endl;
            cout << "Numer telefonu: "<< itr -> numerTelefonu<<endl;
            cout << "Adres: "<< itr -> adres << endl << endl;
            licznik++;
        }
    }

    if (licznik == 0) {
        cout << "Nie znaleziono osob o takim imieniu.";
        Sleep(3000);
    } else {
        Sleep(5000);
    }
}

void wyszukajPoNazwisku(vector <Osoba> osoby) {
    system("cls");
    string szukaneNazwisko;
    cout << "Wprowadz szukane nazwisko: ";
    cin >> szukaneNazwisko;
    int licznik = 0;
    system("cls");

    for (vector <Osoba> :: iterator itr = osoby.begin(); itr != osoby.end(); itr++) {
        if (itr -> nazwisko == szukaneNazwisko) {
            cout << "Numer ID: " << itr -> idAdresata << endl;
            cout << "Imie i nazwisko: " << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Adres email: "<< itr -> email << endl;
            cout << "Numer telefonu: "<< itr -> numerTelefonu<<endl;
            cout << "Adres: "<< itr -> adres << endl << endl;
            licznik++;
        }
    }

    if (licznik == 0) {
        cout << "Nie znaleziono osob o takim nazwisku.";
        Sleep(3000);
    } else {
        Sleep(5000);
    }
}

int usunOsobe(vector <Osoba> &osoby, int iloscOsob) {

    system("cls");
    wyswietlOsoby(osoby);

    char wybor;
    int idDoUsuniecia;
    cout << "Pod ktorym numerem ID znajduje sie osoba, ktora chcesz usunac: ";
    cin >> idDoUsuniecia;

    if (sprawdzCzyPodaneIdIstnieje(osoby,idDoUsuniecia) == 1) {
        for (vector <Osoba>::iterator itr = osoby.begin(); itr != osoby.end() ; itr++) {
            if (itr -> idAdresata == idDoUsuniecia) {
                cout << "Czy na pewno chcesz usunac " <<itr -> imie << " " << itr -> nazwisko << "?"<< endl;
                cout << "(t/n)";
            }
        }
        while(true) {
            cin >> wybor;
            if (wybor == 't') {
                for (vector <Osoba>:: iterator itr = osoby.begin(); itr != osoby.end() ; itr++) {
                    if (itr -> idAdresata == idDoUsuniecia) {
                        osoby.erase(itr);
                        itr--;
                    }
                }
                iloscOsob--;
                cout << "Usunieto wybrana osobe." << endl;
                uzuwanieZPliku(iloscOsob, idDoUsuniecia);
                cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
                getch();
                return iloscOsob;

            } else if (wybor == 'n') {
                return iloscOsob;
            }
        }
    } else {
        system("cls");
        cout << "Nie znaleziono osoby o podanym numerze ID." << endl;
        cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
        getch();
        return iloscOsob;
    }
}

int wczytajOsoby(vector <Osoba> &osoby,int idZalogowanegoUzytkownika) {

    int iloscOsob = 0;
    Osoba wczytywanaOsoba;
    string linia;
    fstream plik;
    int nr_linii = 1;
    plik.open("Ksiazka_adresowa.txt", ios::in);

    if (plik.good()==false) {
        return iloscOsob;
    }
    while (getline(plik,linia,'|')) {
        if (linia == "") {
            return iloscOsob;
        }
        switch(nr_linii) {
        case 1:
            wczytywanaOsoba.idAdresata = atoi(linia.c_str());
            break;
        case 2:
            wczytywanaOsoba.idUzytkownika = atoi(linia.c_str());
            break;
        case 3:
            wczytywanaOsoba.imie = linia;
            break;
        case 4:
            wczytywanaOsoba.nazwisko = linia;
            break;
        case 5:
            wczytywanaOsoba.numerTelefonu = linia;
            break;
        case 6:
            wczytywanaOsoba.email = linia;
            break;
        case 7:
            wczytywanaOsoba.adres = linia;
            break;
        }
        if (nr_linii == 7) {
            iloscOsob++;
            nr_linii = 0;

            if (wczytywanaOsoba.idUzytkownika == idZalogowanegoUzytkownika) {
                osoby.push_back(wczytywanaOsoba);
            }
        }
        nr_linii ++;
    }
    plik.close();
    return iloscOsob;
}

Osoba pobierzDaneOsoby () {

    Osoba wprowadzanaOsoba;

    cout << "Podaj imie: ";
    cin >> wprowadzanaOsoba.imie;
    cout << "Podaj nazwisko: ";
    cin >> wprowadzanaOsoba.nazwisko;
    cout << "Podaj adres email: ";
    wprowadzanaOsoba.email = sprawdzPoprawnoscEmail();
    cout << "Podaj numer telefonu: ";
    wprowadzanaOsoba.numerTelefonu = sprawdzPoprawnoscTelefonu();
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, wprowadzanaOsoba.adres);

    cout << "Czy podane dane sa prawidlowe (t/n)?" << endl;
    cout << "Imie: " << wprowadzanaOsoba.imie << endl << "Nazwisko: " << wprowadzanaOsoba.nazwisko << endl;
    cout << "Email: "<< wprowadzanaOsoba.email << endl << "Numer telefonu: "<< wprowadzanaOsoba.numerTelefonu << endl;
    cout << "Adres: "<< wprowadzanaOsoba.adres << endl;

    return wprowadzanaOsoba;
}

int utworzOsobe(vector <Osoba> &osoby, int iloscOsob, int idZalogowanegoUzytkownika) {

    Osoba wprowadzanaOsoba;
    char wybor;
    system("cls");

    while (wybor != 't') {

        wprowadzanaOsoba = pobierzDaneOsoby();
        cin >> wybor;
        system("cls");
    }

    if (iloscOsob == 0) {
        wprowadzanaOsoba.idAdresata = 1;
    } else {
        wprowadzanaOsoba.idAdresata = sprawdzOstatnieID() + 1;
    }

    wprowadzanaOsoba.idUzytkownika = idZalogowanegoUzytkownika;
    osoby.push_back(wprowadzanaOsoba);
    zapiszNowaOsobeDoPliku(wprowadzanaOsoba);
    iloscOsob++;

    cout << "Dodano " << wprowadzanaOsoba.imie << " "<< wprowadzanaOsoba.nazwisko << endl;
    Sleep(2000);

    return iloscOsob;
}

int logowanie(vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow) {
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

int rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
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

int wylogujUzytkownika (vector <Osoba> &osoby, int idZalogowanegoUzytkownika) {

    char wybor;
    cout << "Czy na pewno chcesz sie wylogowac (t/n)?" << endl;

    while (true) {
        cin >> wybor;
        if (wybor == 't') {
            idZalogowanegoUzytkownika = 0;
            osoby.clear();
            cout << "Poprawnie wylogowano.";
            Sleep(2000);
            return idZalogowanegoUzytkownika;
        } else if (wybor == 'n') {
            return idZalogowanegoUzytkownika;
        } else {
            system("cls");
            cout << "Niepoprawny wybor." << endl << "Czy na pewno chcesz sie wylogowac (t/n)?" << endl;
        }
    }
}

void wyswietlMenuGlowne() {
    system("cls");
    cout << "Witaj w ksiazce adresowej. Wybierz funkcje."  << endl;
    cout << "1. Wprowadzanie danych" << endl;
    cout << "2. Wyszukiwanie po imieniu" << endl;
    cout << "3. Wyszukiwanie po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich znajomych"<<endl;
    cout << "5. Usun znajomego"<<endl;
    cout << "6. Edytuj znajomego"<<endl;
    cout << "7. Zmien haslo"<<endl;
    cout << "8. Wyloguj"<<endl;
    cout << "9. Zakoncz program" << endl;
}

void wyswietlMenuLogowania() {
    system("cls");
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Zakoncz program" << endl;
}

int main() {
    vector <Osoba> osoby;
    vector <Uzytkownik> uzytkownicy;

    int iloscOsob = 0;
    int iloscUzytkownikow = 0;
    int idZalogowanegoUzytkownika = 0;

    iloscUzytkownikow = wczytajUzytkownikow(uzytkownicy);

    char wybor;

    while (true) {
        if (idZalogowanegoUzytkownika == 0) {

            wyswietlMenuLogowania();
            cin >> wybor;

            if (wybor == '1') {
                iloscUzytkownikow = rejestracja(uzytkownicy,iloscUzytkownikow);
            } else if (wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                if (idZalogowanegoUzytkownika !=0) {
                    iloscOsob = wczytajOsoby (osoby, idZalogowanegoUzytkownika);
                }
            } else if (wybor == '9') {
                exit(0);
            }
        } else {
            wyswietlMenuGlowne();
            cin >> wybor;

            if (wybor == '1') {
                iloscOsob = utworzOsobe(osoby, iloscOsob, idZalogowanegoUzytkownika);
            } else if (wybor == '2') {
                wyszukajPoImieniu(osoby);
            } else if (wybor == '3') {
                wyszukajPoNazwisku(osoby);
            } else if (wybor == '4') {
                wyswietlOsoby(osoby);
                cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
                getch();
            } else if (wybor == '5') {
                iloscOsob = usunOsobe(osoby, iloscOsob);
            } else if (wybor == '6') {
                edytujOsobe (osoby);
            } else if (wybor == '7') {
                zmienHasloUzytkownika (uzytkownicy, idZalogowanegoUzytkownika, iloscUzytkownikow);
            } else if (wybor == '8') {
                idZalogowanegoUzytkownika = wylogujUzytkownika(osoby,idZalogowanegoUzytkownika);
            } else if (wybor == '9') {
                exit(0);
            }
        }
    }
    return 0;
}
