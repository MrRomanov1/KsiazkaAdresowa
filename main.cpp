#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

struct Osoba {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";

};

bool sprawdzCzyPodaneIdIstnieje (vector <Osoba> osoby,int idDoEdycji, int iloscOsob) {

    bool sprawdzacz = false;
    for (int i = 0; i< iloscOsob; i++) {
        if (osoby[i].id == idDoEdycji) {
            sprawdzacz = true;
        }
    }
    return sprawdzacz;
}

void zapiszDoPliku(vector <Osoba> osoby, int iloscOsob) {

    fopen("Ksiazka_adresowa.txt","w");

    fstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::out | ios::app);

    if (plik.good()) {

        for (int i =0; i< iloscOsob; i++) {
            plik << osoby[i].id << "|" << osoby[i].imie << "|" << osoby[i].nazwisko << "|" << osoby[i].numerTelefonu << "|" << osoby[i].email << "|" << osoby[i].adres << "|" << endl;
        }
        plik.close();
    }
}

void wyswietlOsoby(vector <Osoba> osoby, int iloscOsob) {

    system("cls");
    if (iloscOsob == 0) {
        cout << "Nie masz zapisanych zadnych osob."<< endl;
    } else {
        for (int i = 0; i < iloscOsob; i++) {

            cout << "Numer ID: " << osoby[i].id << endl;
            cout << "Imie i nazwisko: " << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "Adres email: "<<osoby[i].email << endl;
            cout << "Numer telefonu: "<< osoby[i].numerTelefonu<<endl;
            cout << "Adres: "<<osoby[i].adres << endl << endl;
        }
    }
}

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

void edytujImie(vector <Osoba> &osoby, int idDoEdycji, int iloscOsob) {

    system("cls");
    string imieDoEdycji;
    cout << "Podaj nowe imie: ";
    cin >> imieDoEdycji;

    for (int i = 0; i< iloscOsob; i++) {
        if (osoby[i].id == idDoEdycji) {
            osoby[i].imie = imieDoEdycji;
        }
    }
    cout << "Zmieniono imie na: " << imieDoEdycji << endl;

    zapiszDoPliku(osoby,iloscOsob);
}

void edytujNazwisko(vector <Osoba> &osoby, int idDoEdycji, int iloscOsob) {

    system("cls");
    string nazwiskoDoEdycji;
    cout << "Podaj nowe nazwisko: ";
    cin >> nazwiskoDoEdycji;

    for (int i = 0; i< iloscOsob; i++) {
        if (osoby[i].id == idDoEdycji) {
            osoby[i].nazwisko = nazwiskoDoEdycji;
        }
    }
    cout << "Zmieniono nazwisko na: " << nazwiskoDoEdycji << endl;

    zapiszDoPliku(osoby,iloscOsob);
}

void edytujEmail(vector <Osoba> &osoby, int idDoEdycji, int iloscOsob) {

    system("cls");
    string emailDoEdycji;
    cout << "Podaj nowy adres email: ";

    emailDoEdycji = sprawdzPoprawnoscEmail();

    for (int i = 0; i< iloscOsob; i++) {
        if (osoby[i].id == idDoEdycji) {
            osoby[i].email = emailDoEdycji;
        }
    }
    cout << "Zmieniono email na: " << emailDoEdycji << endl;
    zapiszDoPliku(osoby,iloscOsob);
}

void edytujTelefon(vector <Osoba> &osoby, int idDoEdycji, int iloscOsob) {

    system("cls");
    string telefonDoEdycji;
    cout << "Podaj nowe numer telefonu: ";
    telefonDoEdycji = sprawdzPoprawnoscTelefonu();

    for (int i = 0; i< iloscOsob; i++) {
        if (osoby[i].id == idDoEdycji) {
            osoby[i].numerTelefonu = telefonDoEdycji;
        }
    }
    cout << "Zmieniono numer telefonu na: " << telefonDoEdycji << endl;
    zapiszDoPliku(osoby,iloscOsob);
}

void edytujAdres(vector <Osoba> &osoby, int idDoEdycji, int iloscOsob) {

    system("cls");
    string adresDoEdycji;
    cout << "Podaj nowy adres: ";
    cin.sync();
    getline(cin,adresDoEdycji);

    for (int i = 0; i< iloscOsob; i++) {
        if (osoby[i].id == idDoEdycji) {
            osoby[i].adres = adresDoEdycji;
        }
    }
    cout << "Zmieniono adres na: " << adresDoEdycji << endl;
    zapiszDoPliku(osoby,iloscOsob);
}

void edytujOsobe(vector <Osoba> &osoby, int iloscOsob) {

    system("cls");
    wyswietlOsoby(osoby, iloscOsob);

    int idDoEdycji;
    cout << "Pod ktorym numerem ID znajduje sie osoba, ktora chcesz edytowac: ";
    cin >> idDoEdycji;

    if (sprawdzCzyPodaneIdIstnieje(osoby,idDoEdycji,iloscOsob) == 1) {

        char wybor;

        while (true) {
            cout << "Jakie dane chcesz edytowac: " << endl;

            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Email" << endl;
            cout << "4. Numer telefonu" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu glownego" << endl;

            cin >> wybor;

            if (wybor == '1') {
                edytujImie(osoby,idDoEdycji,iloscOsob);
            } else if (wybor == '2') {
                edytujNazwisko(osoby,idDoEdycji,iloscOsob);
            } else if (wybor == '3') {
                edytujEmail(osoby,idDoEdycji,iloscOsob);
            } else if (wybor == '4') {
                edytujTelefon(osoby, idDoEdycji,iloscOsob);
            } else if (wybor == '5') {
                edytujAdres(osoby, idDoEdycji,iloscOsob);
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

int usunOsobe(vector <Osoba> &osoby, int iloscOsob) {

    system("cls");
    wyswietlOsoby(osoby, iloscOsob);

    char wybor;
    int idDoEdycji;
    cout << "Pod ktorym numerem ID znajduje sie osoba, ktora chcesz usunac: ";
    cin >> idDoEdycji;

    if (sprawdzCzyPodaneIdIstnieje(osoby,idDoEdycji,iloscOsob) == 1) {
        for (int i = 0; i < iloscOsob ; i++) {
            if (osoby[i].id == idDoEdycji) {
                cout << "Czy na pewno chcesz usunac " <<osoby[i].imie << " " << osoby[i].nazwisko << "?"<< endl;
                cout << "(t/n)";
            }
        }
        while(true) {

            cin >> wybor;
            if (wybor == 't') {
                for (vector <Osoba>:: iterator itr = osoby.begin(); itr != osoby.end() ; itr++) {
                    if (itr -> id == idDoEdycji) {
                        osoby.erase(itr);
                        itr--;
                    }
                }
                iloscOsob--;
                cout << "Usunieto wybrana osobe." << endl;
                zapiszDoPliku(osoby,iloscOsob);
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

int utworzOsobe(vector <Osoba> &osoby,int iloscOsob) {

    Osoba pomocnicza;
    char wybor;
    system("cls");

    while (wybor != 't') {
        cout << "Podaj imie: ";
        cin >> pomocnicza.imie;
        cout << "Podaj nazwisko: ";
        cin >> pomocnicza.nazwisko;
        cout << "Podaj adres email: ";
        pomocnicza.email = sprawdzPoprawnoscEmail();
        cout << "Podaj numer telefonu: ";
        pomocnicza.numerTelefonu = sprawdzPoprawnoscTelefonu();
        cout << "Podaj adres: ";
        cin.sync();
        getline(cin, pomocnicza.adres);

        cout << "Czy podane dane sa prawidlowe (t/n)?" << endl;
        cout << "Imie: " << pomocnicza.imie << endl << "Nazwisko: " << pomocnicza.nazwisko << endl;
        cout << "Email: "<< pomocnicza.email << endl << "Numer telefonu: "<< pomocnicza.numerTelefonu << endl;
        cout << "Adres: "<< pomocnicza.adres << endl;
        cin >> wybor;
        system("cls");
    }

    if (iloscOsob == 0) {
        pomocnicza.id = 1;
    } else {
        pomocnicza.id = osoby[iloscOsob-1].id + 1;
    }

    osoby.push_back(pomocnicza);

    iloscOsob++;
    zapiszDoPliku(osoby,iloscOsob);

    cout << "Dodano " << pomocnicza.imie << " "<< pomocnicza.nazwisko << endl;
    Sleep(2000);

    return iloscOsob;
}

int wczytajOsoby(vector <Osoba> &osoby) {

    int iloscOsob = 0;
    Osoba temp;

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
            temp.id = atoi(linia.c_str());

            break;
        case 2:
            temp.imie = linia;

            break;
        case 3:
            temp.nazwisko = linia;

            break;
        case 4:
            temp.numerTelefonu = linia;

            break;
        case 5:
            temp.email = linia;
            break;
        case 6:
            temp.adres = linia;
            break;
        }

        if (nr_linii == 6) {

            iloscOsob++;
            nr_linii = 0;
            osoby.push_back(temp);
        }
        nr_linii ++;

    }
    plik.close();
    return iloscOsob;
}

void wyszukajPoImieniu(vector <Osoba> osoby, int iloscOsob) {
    system("cls");
    string imie;
    cout << "Wprowadz szukane imie: ";
    cin >> imie;
    int i=0;
    int licznik = 0;
    system("cls");

    while ( i<iloscOsob ) {
        if (osoby[i].imie == imie) {
            cout << "Numer ID: " << osoby[i].id << endl;
            cout << "Imie i nazwisko: " << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "Adres email: "<< osoby[i].email << endl;
            cout << "Numer telefonu: "<< osoby[i].numerTelefonu<<endl;
            cout << "Adres: "<< osoby[i].adres << endl << endl;
            licznik++;
        }

        i++;
    }
    if (licznik == 0) {
        cout << "Nie znaleziono osob o takim imieniu.";
        Sleep(3000);
    } else {
        Sleep(5000);
    }
}

void wyszukajPoNazwisku(vector <Osoba> osoby, int iloscOsob) {
    system("cls");
    string nazwisko;
    cout << "Wprowadz szukane nazwisko: ";
    cin >> nazwisko;
    int i=0;
    int licznik = 0;
    system("cls");

    while ( i<iloscOsob ) {
        if (osoby[i].nazwisko == nazwisko) {
            cout << "Imie i nazwisko: " << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "Adres email: "<< osoby[i].email << endl;
            cout << "Numer telefonu: "<< osoby[i].numerTelefonu<<endl;
            cout << "Adres: "<< osoby[i].adres << endl << endl;
            licznik++;
        }
        i++;
    }
    if (licznik == 0) {
        cout << "Nie znaleziono osob o takim nazwisku.";
        Sleep(3000);
    } else {
        Sleep(5000);
    }
}

int main() {
    vector <Osoba> osoby;
    int iloscOsob;
    char wybor;

    iloscOsob = wczytajOsoby(osoby);

    while (true) {
        system("cls");
        cout << "Witaj w ksiazce adresowej. Wybierz funkcje."  << endl;
        cout << "1. Wprowadzanie danych" << endl;
        cout << "2. Wyszukiwanie po imieniu" << endl;
        cout << "3. Wyszukiwanie po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich znajomych"<<endl;
        cout << "5. Usun znajomego"<<endl;
        cout << "6. Edytuj znajomego"<<endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1') {
            iloscOsob = utworzOsobe(osoby,iloscOsob);
        } else if (wybor == '2') {
            wyszukajPoImieniu(osoby,iloscOsob);
        } else if (wybor == '3') {
            wyszukajPoNazwisku(osoby,iloscOsob);
        } else if (wybor == '4') {
            wyswietlOsoby(osoby, iloscOsob);
            cout << "Nacisnij dowolny przycisk, aby kontynuowac." << endl;
            getch();
        } else if (wybor == '5') {
            iloscOsob = usunOsobe(osoby, iloscOsob);
        } else if (wybor == '6') {
            edytujOsobe (osoby, iloscOsob);
        } else if (wybor == '9') {
            exit(0);
        }
    }
    return 0;
}
