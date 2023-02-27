
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>


using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

struct Adresat
{
    int id = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik jedenUytkownik;
    string daneUzytkownika = "";
    string bufor [3];

    fstream plik;
    uzytkownicy.clear();
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == true)
    {
        cin.sync();
        while (getline(plik, bufor[0], '|') &&
                getline(plik, bufor[1], '|') &&
                getline(plik, bufor[2], '|'))
        {
            jedenUytkownik.idUzytkownika = atoi(bufor[0].c_str());
            jedenUytkownik.nazwa = bufor[1];
            jedenUytkownik.haslo = bufor[2];
            uzytkownicy.push_back(jedenUytkownik);
        }
    }
    plik.close();

}

void odczytywanieDanychZPlikuTekstowego(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{

    Adresat jedenAdresat;
    string daneAdresata = "";
    string bufor [7];
    int idUzytkownikaZPliku = 0;

    std::fstream plik;
    adresaci.clear();
    plik.open("KsiazkaAdresowa.txt", ios::in);


    if(plik.good() == true)
    {
    cin.sync();

    while (getline(plik, bufor[0], '|') &&
            getline(plik, bufor[1], '|') &&
            getline(plik, bufor[2], '|') &&
            getline(plik, bufor[3], '|') &&
            getline(plik, bufor[4], '|') &&
           getline(plik, bufor[5], '|') &&
            getline(plik, bufor[6], '|'))
    {
        idUzytkownikaZPliku = atoi(bufor[1].c_str());
        if (idZalogowanegoUzytkownika == idUzytkownikaZPliku)
        {

        jedenAdresat.id = atoi(bufor[0].c_str());
        jedenAdresat.idUzytkownika = atoi(bufor[1].c_str());
        jedenAdresat.imie = bufor[2];
        jedenAdresat.nazwisko = bufor[3];
        jedenAdresat.numerTelefonu = bufor[4];
        jedenAdresat.email = bufor[5];
        jedenAdresat.adres = bufor[6];
        adresaci.push_back(jedenAdresat);

        }
    }
    }
    plik.close();
}

void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string nazwaUzytkownika, hasloUzytkownika;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik Osoba;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        while(itr -> nazwa == nazwaUzytkownika)
        {
            cout << "Taki uztkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwaUzytkownika;
        }
    }

    cout << "Podaj haslo: ";
    cin >> hasloUzytkownika;

    if (uzytkownicy.empty() == true)  // jezeli ksiazka adresowa jest pusta
    {
        Osoba.idUzytkownika = 1;           // to nowy adresat ma id=1
    }
    else
    {
        Osoba.idUzytkownika = uzytkownicy.back().idUzytkownika + 1; // pobierz id ostatniej osoby z ksiazki adresowej i zwieksz wartosc o jeden.
    }

    Osoba.nazwa = nazwaUzytkownika;
    Osoba.haslo = hasloUzytkownika;

    uzytkownicy.push_back(Osoba);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += to_string(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> nazwa + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
    }
    cout<< "Konto zalozone." <<endl;
    Sleep(1000);
}

int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string nazwaUzytkownika, hasloUzytkownika;
    bool znalezionyUzytkownik = 0;
    int proby = 0;
    cout << "Podaj nazwe uzytkownika: ";
    cin >>  nazwaUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> nazwa == nazwaUzytkownika)
        {
            znalezionyUzytkownik = 1;
            for(int iloscProb = 0; iloscProb < 3; iloscProb++)
            {
                proby = iloscProb + 1;
                cout << "Podaj haslo. Pozostalo prob " << 3 - iloscProb << ":";
                cin >> hasloUzytkownika;
                if (itr -> haslo == hasloUzytkownika)
                {
                    cout<< "Zalogowales sie."<<endl;
                    return itr -> idUzytkownika;
                }
            }
            if( proby == 3)
            {
                cout << "Podales 3 razy bledne haslo.Poczekaj przez 3 sekundy przed kolejna proba." << endl;
            }
        }
    }

    if(!znalezionyUzytkownik)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << "Nie ma uzytkownika z takim loginem." << endl;
    }

    Sleep(1000);
    return 0;
}

string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};

    while (true)
    {
        cin.sync();
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie";
    }
    return znak;
}

/*
void zapisywanieDanychDoPlikuTekstowego(vector <Adresat> &adresaci)
{
     //string liniaZDanymiAdresata = "";

    ofstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::trunc); // ios::trunc powoduje wyczyszczenie zawartości pliku

    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {

            if (itr == adresaci.begin())
            {
                plik << itr -> id << '|';
                plik << itr -> idUzytkownika << '|';
                plik << itr -> imie << '|';
                plik << itr -> nazwisko << '|';
                plik << itr -> numerTelefonu << '|';
                plik << itr -> email << '|';
                plik << itr -> adres << '|';
            }
            else
            {
                plik << endl << itr -> id << '|';
                plik << itr -> idUzytkownika << '|';
                plik << itr -> imie << '|';
                plik << itr -> nazwisko << '|';
                plik << itr -> numerTelefonu << '|';
                plik << itr -> email << '|';
                plik << itr -> adres << '|';
            }
        }
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}
*/

void usunLinieZPliku (int idZalogowanegoUzytkownika)
{
    vector <string> linieDoUsuniecia;
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowZostawic = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku;
    bool znalezionaLinia;

    fstream plik;
    ofstream nowyPlik;

    linieDoUsuniecia.clear();
    plik.open("KsiazkaAdresowa.txt", ios::in); // aby otworzyc plik do odczytu
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            ileZnakowZostawic = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (unsigned int i = 0; i < linia.size(); i++)
            {
                ileZnakowZostawic = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscPionowychKresek++;
                    wyraz = linia.substr (poczatek,ileZnakowZostawic);
                    idUzytkownikaZPliku = atoi(wyraz.c_str());
                    if ( iloscPionowychKresek == 2 && idZalogowanegoUzytkownika == idUzytkownikaZPliku)
                    {
                        linieDoUsuniecia.push_back(linia);
                        break;
                    }
                    poczatek = poczatek + ileZnakowZostawic + 1;
                }
            }
        }
        plik.close();
    }

    nowyPlik.open("Adresaci_tymczasowy.txt");
    plik.open("KsiazkaAdresowa.txt", ios::in);

     while (getline(plik,linia))
    {
        znalezionaLinia = false;
        for (unsigned int i = 0; i < linieDoUsuniecia.size(); i++ )
        {
            if (linia == linieDoUsuniecia[i])
            {
                znalezionaLinia = true;
            }
        }
        if (znalezionaLinia == false)
            nowyPlik << linia << endl;

    }

    nowyPlik.close();
    plik.close();
    remove("KsiazkaAdresowa.txt");
    rename("Adresaci_tymczasowy.txt","KsiazkaAdresowa.txt");
}

void zapisywanieDanychDoPlikuTekstowego(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{

    string liniaZDanymiZnajomego = "";

    usunLinieZPliku(idZalogowanegoUzytkownika);

    ofstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app); // ios::app powoduje dopisanie do zawartości pliku

    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            liniaZDanymiZnajomego += to_string(itr -> id) + '|';
            liniaZDanymiZnajomego += to_string(itr -> idUzytkownika) + '|';
            liniaZDanymiZnajomego += itr -> imie + '|';
            liniaZDanymiZnajomego += itr -> nazwisko + '|';
            liniaZDanymiZnajomego += itr -> numerTelefonu + '|';
            liniaZDanymiZnajomego += itr -> email + '|';
            liniaZDanymiZnajomego += itr -> adres + '|';

            plik << liniaZDanymiZnajomego << endl;
            liniaZDanymiZnajomego = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");


    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

int znajdzKolejnyNumerIdAdresata()
{
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowZostawic = 0;
    int poczatek = 0 ;
    int najwiekszyNumerID = 0;
    int aktualnyNumerID = 0;
    int kolejnyNumerID = 0;
    fstream plik;

    plik.open("KsiazkaAdresowa.txt",ios::in); // aby otworzyc plik do odczytu
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            poczatek = 0;
            iloscPionowychKresek = 0;
            ileZnakowZostawic = 1;
            if (linia[1] == '|')
            {
                iloscPionowychKresek++;
                wyraz = linia.substr (poczatek, ileZnakowZostawic);
                aktualnyNumerID = atoi(wyraz.c_str());

                if (aktualnyNumerID > najwiekszyNumerID)
                {
                    najwiekszyNumerID = aktualnyNumerID;
                }

            }

        }
    }
    kolejnyNumerID = najwiekszyNumerID + 1;
    return kolejnyNumerID;

}
void dodajOsobe(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    Adresat nowyAdresat;
    string imie, nazwisko, numerTelefonu, email, adres;

    cout << "Podaj imie: ";
    imie = wczytajLinie();

    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();

    cout << "Podaj numer telefonu: ";
    numerTelefonu = wczytajLinie();

    cout << "Podaj email: ";
    email = wczytajLinie();

    cout << "Podaj adres: ";
    adres = wczytajLinie();

    cout << imie << endl;
    cout << nazwisko << endl;
    cout << numerTelefonu << endl;
    cout << email << endl;
    cout << adres << endl;

    nowyAdresat.id = znajdzKolejnyNumerIdAdresata();
    nowyAdresat.idUzytkownika = idZalogowanegoUzytkownika;
    nowyAdresat.imie = imie;
    nowyAdresat.nazwisko = nazwisko;
    nowyAdresat.numerTelefonu = numerTelefonu;
    nowyAdresat.email = email;
    nowyAdresat.adres = adres;

    adresaci.push_back(nowyAdresat);

    string liniaZDanymiZnajomego = "";
    ofstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app); // ios::app powoduje dopisanie do zawartości pliku

    if (plik.good() == true)
    {
        liniaZDanymiZnajomego += to_string(nowyAdresat.id) + '|';
        liniaZDanymiZnajomego += to_string(nowyAdresat.idUzytkownika) + '|';
        liniaZDanymiZnajomego += nowyAdresat.imie + '|';
        liniaZDanymiZnajomego += nowyAdresat.nazwisko + '|';
        liniaZDanymiZnajomego += nowyAdresat.numerTelefonu + '|';
        liniaZDanymiZnajomego += nowyAdresat.email + '|';
        liniaZDanymiZnajomego += nowyAdresat.adres + '|';

        plik << liniaZDanymiZnajomego << endl;
        liniaZDanymiZnajomego = "";
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }



    system("pause");


}
void wyszukajPoImieniu(vector <Adresat> adresaci)
{
    string imie;
    bool czyIstniejeKontakt = false;
    cout << "Podaj imie wyszukiwanego kontaktu: ";
    imie = wczytajLinie();

    for (unsigned int i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].imie == imie)
        {
            cout << "Kontakt o imieniu " << imie << " to: ";
            cout << endl << adresaci[i].id << endl;
            cout << adresaci[i].imie << endl;
            cout << adresaci[i].nazwisko << endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].email << endl;
            cout << adresaci[i].adres << endl;
            czyIstniejeKontakt = true;
        }
    }

    if (czyIstniejeKontakt == false)
    {
        cout << "Nie znaleziono w dokumencie .txt" << endl;
    }

    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat> adresaci)
{
    string nazwisko;
    bool czyIstniejeKontakt = false;
    cout << "Podaj nazwisko wyszukiwanego kontaktu: ";
    nazwisko = wczytajLinie();

    for (unsigned int i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].nazwisko == nazwisko)
        {
            cout << "Kontakt o nazwisku " << nazwisko << " to: ";
            cout << endl << adresaci[i].id << endl;
            cout << adresaci[i].imie << endl;
            cout << adresaci[i].nazwisko << endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].email << endl;
            cout << adresaci[i].adres << endl;
            czyIstniejeKontakt = true;
        }
    }
    if (czyIstniejeKontakt == false)
    {
        cout << "Nie znaleziono w dokumencie .txt" << endl;
    }

    system("pause");
}

void wyswietlWszystkichAdresatow(vector <Adresat> adresaci)
{
    for (unsigned int i = 0; i < adresaci.size(); i++)
    {
        cout << "Id:                      " << adresaci[i].id << endl;
        cout << "Imie:                    " << adresaci[i].imie << endl;
        cout << "Nazwisko:                " << adresaci[i].nazwisko << endl;
        cout << "Numer telefonu:          " << adresaci[i].numerTelefonu << endl;
        cout << "Email:                   " << adresaci[i].email << endl;
        cout << "Adres:                   " << adresaci[i].adres << endl;
    }
    system("pause");
}

void usunAdresata(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    int idUsuwanegoAdresata;
    char wybor;
    cout << "Podaj ID adresata do usuniecia: ";
    cin >> idUsuwanegoAdresata;
    bool czyIstniejeAdresat = false;

    for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> id == idUsuwanegoAdresata)
        {
            czyIstniejeAdresat = true;
            cout << "Czy na pewno chcesz usunac uzytkownika o numerze ID " << idUsuwanegoAdresata << "? Jesli tak wpisz: t " << endl;
            wybor =  wczytajZnak();

            if (wybor == 't')
            {
                adresaci.erase(itr);
                cout << "Adresat zostal usuniety." << endl;
                zapisywanieDanychDoPlikuTekstowego(adresaci, idZalogowanegoUzytkownika);
                break;
            }
            else
            {
                cout << "Wybrany adresat NIE zostal usuniety";
                break;
            }

        }

    }
    if (czyIstniejeAdresat == false)
    {
        cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
    }

}

void edytujKontakt(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    int poszukiwanyNumerID;
    char wybranaPozycjaMenu;
    string noweDane = "";

    cout << "Wyszukanie adresata. Podaj numer ID znajomego: ";
    cin >> poszukiwanyNumerID;

    for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        while (itr->id == poszukiwanyNumerID)
        {

            cout << endl << "Edycja kontaktu." << endl << endl;
            cout << "Imie: " << itr -> imie << endl;
            cout << "Nazwisko: " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: " << itr -> email << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
            cout << "1.Edytuj imie" << endl;
            cout << "2.Edytuj nazwisko" << endl;
            cout << "3.Edytuj numer telefonu" << endl;
            cout << "4.Edytuj email" << endl;
            cout << "5.Edytuj adres" << endl;
            cout << "6.Powrot do menu" << endl<<endl;
            wybranaPozycjaMenu = wczytajZnak();


            switch (wybranaPozycjaMenu)
            {
            case '1':

                cout << "Podaj nowe imie: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> imie = noweDane;
                cout << itr -> imie;
                zapisywanieDanychDoPlikuTekstowego(adresaci, idZalogowanegoUzytkownika);
                break;

            case '2':
                cout << "Podaj nowe nazwisko: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> nazwisko = noweDane;
                zapisywanieDanychDoPlikuTekstowego(adresaci, idZalogowanegoUzytkownika);
                break;

            case '3':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> numerTelefonu = noweDane;
                zapisywanieDanychDoPlikuTekstowego(adresaci, idZalogowanegoUzytkownika);
                break;

            case '4':
                cout << "Podaj nowy adres e-mail: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> email = noweDane;
                zapisywanieDanychDoPlikuTekstowego(adresaci, idZalogowanegoUzytkownika);
                break;

            case '5':
                cout << "Podaj nowy adres: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> adres = noweDane;
                zapisywanieDanychDoPlikuTekstowego(adresaci, idZalogowanegoUzytkownika);
                break;

            case '6':
                return;
                break;

            default:
                cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                break;
            }
        }
    }
}

void zapiszDaneUzytkownikowDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string liniaZDanymiUzytkownika = "";
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += to_string(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> nazwa + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string hasloUzytkownika;
    int pozycjaZnalezionejOsoby = 0;
    cout << "Podaj nowe haslo: ";
    cin >> hasloUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[pozycjaZnalezionejOsoby].haslo = hasloUzytkownika;
            cout << "Haslo zostalo zmienione"<< endl;
            Sleep(1500);
        }
        pozycjaZnalezionejOsoby++;
    }
    zapiszDaneUzytkownikowDoPliku(uzytkownicy);
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;
    wczytajUzytkownikowZPliku(uzytkownicy);
    char wybor;

    while (true)
    {
        wczytajUzytkownikowZPliku(uzytkownicy);
        if(idZalogowanegoUzytkownika == 0)
        {
           system("cls");
            cout << "1.Rejestracja" << endl;
            cout << "2.Logowanie" << endl;
            cout << "9.Zamknij program" << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            switch(wybor)
            {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                break;
            case '9':
                exit(0);
                break;
            }
        }
        else
        {
            odczytywanieDanychZPlikuTekstowego(adresaci, idZalogowanegoUzytkownika);
            system("cls");
            cout << ">>>> KSIAZKA ADRESOWA <<<<" << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "------------------" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "------------------" << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            switch(wybor)
            {
            case '1':
                dodajOsobe(adresaci, idZalogowanegoUzytkownika);
                break;
            case '2':
                wyszukajPoImieniu(adresaci);
                break;
            case '3':
                wyszukajPoNazwisku(adresaci);
                break;
            case '4':
                wyswietlWszystkichAdresatow(adresaci);
                break;
            case '5':
                usunAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            case '6':
                edytujKontakt(adresaci, idZalogowanegoUzytkownika);
                break;
            case '7':
                zmienHaslo(uzytkownicy,idZalogowanegoUzytkownika);
                break;
            case '8':
                idZalogowanegoUzytkownika = 0;
                break;

            case '9':
                return (0);
                break;
            }
        }

    }
    return 0;
}
