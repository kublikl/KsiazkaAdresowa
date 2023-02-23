#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>


using namespace std;

struct Adresat
{
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

int odczytywanieDanychZPlikuTekstowego(vector <Adresat> &adresaci, int iloscOsob)
{

    Adresat jedenAdresat;
    string daneAdresata = "";
    string bufor [6];

    std::fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if(plik.good() == false)
    {
        cout << "Plik nie istnieje";
        getchar();
    }

    cin.sync();
    while (getline(plik, bufor[0], '|') &&
            getline(plik, bufor[1], '|') &&
            getline(plik, bufor[2], '|') &&
            getline(plik, bufor[3], '|') &&
            getline(plik, bufor[4], '|') &&
            getline(plik, bufor[5], '|'))
    {
        jedenAdresat.id = atoi(bufor[0].c_str());
        jedenAdresat.imie = bufor[1];
        jedenAdresat.nazwisko = bufor[2];
        jedenAdresat.numerTelefonu = bufor[3];
        jedenAdresat.email = bufor[4];
        jedenAdresat.adres = bufor[5];
        adresaci.push_back(jedenAdresat);
        iloscOsob++;
    }
    plik.close();
    return iloscOsob;
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

void zapisywanieDanychDoPlikuTekstowego(vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::trunc); // ios::trunc powoduje wyczyszczenie zawartości pliku

    if (plik.good() == true)
    {
        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
        plik << endl << itr -> id << '|';
        plik << itr -> imie << '|';
        plik << itr -> nazwisko << '|';
        plik << itr -> numerTelefonu << '|';
        plik << itr -> email << '|';
        plik << itr -> adres << '|';
        }
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

int dodajOsobe(vector <Adresat> &adresaci, int &iloscOsob)
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

    nowyAdresat.id = iloscOsob + 1;
    nowyAdresat.imie = imie;
    nowyAdresat.nazwisko = nazwisko;
    nowyAdresat.numerTelefonu = numerTelefonu;
    nowyAdresat.email = email;
    nowyAdresat.adres = adres;

    adresaci.push_back(nowyAdresat);

    zapisywanieDanychDoPlikuTekstowego(adresaci);
    system("pause");

    return ++iloscOsob;

}

void wyszukajPoImieniu(vector <Adresat> &adresaci)
{
    string imie;
    bool czyIstniejeKontakt = false;
    cout << "Podaj imie wyszukiwanego kontaktu: ";
    imie = wczytajLinie();

    for (int i = 0; i < adresaci.size(); i++)
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

void wyszukajPoNazwisku(vector <Adresat> &adresaci)
{
    string nazwisko;
    bool czyIstniejeKontakt = false;
    cout << "Podaj nazwisko wyszukiwanego kontaktu: ";
    nazwisko = wczytajLinie();

    for (int i = 0; i < adresaci.size(); i++)
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

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci, int iloscOsob)
{
    for (int i = 0; i < adresaci.size(); i++)
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

void usunAdresata(vector <Adresat> &adresaci)
{
    int idUsuwanegoAdresata;
    char wybor;
    cout << "Podaj ID adresata do usuniecia: ";
    cin >> idUsuwanegoAdresata;

    for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr -> id == idUsuwanegoAdresata)
        {

            cout << "Czy na pewno chcesz usunac uzytkownika o numerze ID " << idUsuwanegoAdresata << "? Jesli tak wpisz: t " << endl;
            wybor =  wczytajZnak();

            if (wybor == 't')
            {
                adresaci.erase(itr);
                cout << "Adresat zostal usuniety." << endl;
                return;
            }
            else
            {
                return;
            }

        }

    }

         cout << "Nie znaleziono adresata o podanym ID." << endl;
}

void edytujKontakt(vector<Adresat> &adresaci)
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
                break;

            case '2':
                cout << "Podaj nowe nazwisko: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> nazwisko = noweDane;
                break;

            case '3':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> numerTelefonu = noweDane;
                break;

            case '4':
                cout << "Podaj nowy adres e-mail: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> email = noweDane;
                break;

            case '5':
                cout << "Podaj nowy adres e-mail: ";
                cin.sync();
                noweDane = wczytajLinie();
                itr -> email = noweDane;
                break;

            case '6':
                return;
                break;
            }
        }
    }
}

int main()
{

    vector <Adresat> adresaci;
    int iloscOsob = 0;
    iloscOsob = odczytywanieDanychZPlikuTekstowego(adresaci, iloscOsob);
    char wybor;

    while (true)
    {
        system("cls");
        cout << ">>>> KSIAZKA ADRESOWA <<<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        wybor = wczytajZnak();

        switch(wybor)
        {
        case '1':
            iloscOsob = dodajOsobe(adresaci, iloscOsob);
            break;
        case '2':
            wyszukajPoImieniu(adresaci);
            break;
        case '3':
            wyszukajPoNazwisku(adresaci);
            break;
        case '4':
            wyswietlWszystkichAdresatow(adresaci, iloscOsob);
            break;
        case '5':
            usunAdresata(adresaci);
            zapisywanieDanychDoPlikuTekstowego(adresaci);
            break;
        case '6':
            edytujKontakt(adresaci);
            zapisywanieDanychDoPlikuTekstowego(adresaci);
            break;
        case '9':
            return (0);
            break;
        }
    }

     return 0;
}



