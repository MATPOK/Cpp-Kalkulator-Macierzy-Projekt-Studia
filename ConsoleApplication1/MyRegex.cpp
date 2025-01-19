#include "MyRegex.h"

void MyRegex::uCiag(string& wzor)
{
    ciag = wzor;
}

void MyRegex::uDlugosc(int& wzor)
{
    dlugosc = wzor;
}


void MyRegex::wZapisane() const
{
    int i = 0;
    while (i <= iloscZapisanych-1) {
        cout << zapisane[i]<<endl;
        i++;
    }
}

std::string MyRegex::zZapisane(int index) const {
    if (index >= 0 && index < iloscZapisanych) {
        return zapisane[index];
    }
    return ""; // Zwróæ pusty ci¹g, jeœli indeks jest poza zakresem
}


string MyRegex::All()
{
    Nadpisz(ciag);
    return ciag;
}

std::string MyRegex::Spacja() {
    ciag.erase(0, ciag.find_first_not_of(" ")); // Usuñ wiod¹ce spacje
    dlugosc = ciag.size();
    return ciag;
}


string MyRegex::Operator()
{
    string pom = "";
    int i = 0;
    
    
        if (ciag[i] == '+' || ciag[i] == '-' || ciag[i] == '*' || ciag[i] == '/') {
            pom = ciag[i];
            Nadpisz(pom);
            string zwracana = "";
            for (int dl_pom = pom.size(); dl_pom <= dlugosc - 1; dl_pom++) {
                zwracana += ciag[dl_pom];
            }
            ciag = zwracana;
            dlugosc = ciag.size();
            return zwracana;
        }
        
    
    string zwracana = "";
    for (int dl_pom = pom.size(); dl_pom <= dlugosc - 1; dl_pom++) {
        zwracana += ciag[dl_pom];
    }
    ciag = zwracana;
    dlugosc = ciag.size();
    return zwracana;
}

string MyRegex::Wyrazenie() 
{
    string pom = "";
    int i = 0;
    
    while (i <= dlugosc - 1) {
        cout << ciag[i];
        if (isalpha(ciag[i])) {
            pom += ciag[i];
        }
        else {
            if (pom != "") {
                Nadpisz(pom);
            }
            string zwracana = "";
            for (int dl_pom = pom.size(); dl_pom <= dlugosc - 1; dl_pom++) {
                zwracana += ciag[dl_pom];
            }
            ciag = zwracana;
            dlugosc = ciag.size();
            return zwracana;
        }
        i++;
    }
    Nadpisz(pom);
    int dl_pom = pom.size();
    string zwracana = "";
    for (int dl_pom = pom.size(); dl_pom <= dlugosc - 1; dl_pom++) {
        zwracana += ciag[dl_pom];
    }
    ciag = zwracana;
    dlugosc = ciag.size();
    return zwracana;
}

bool MyRegex::Cokolwiek(const string& szukane) {
    int dl_szukanej = szukane.size();

    
    for (int i = 0; i <= dlugosc - dl_szukanej; i++) {
        
        if (ciag.substr(i, dl_szukanej) == szukane) {
            
            ciag = ciag.substr(i + dl_szukanej); 
            dlugosc = ciag.size(); 
            return true;
        }
    }

    return false; 
}

std::string MyRegex::DowolnyZnak(char znak) {
    std::string pom = "";
    size_t pozycja = ciag.find(znak); // Znajduje pozycjê pierwszego wyst¹pienia znaku

    if (pozycja != std::string::npos) {
        // Zwraca czêœæ ci¹gu po znalezionym znaku
        pom = ciag.substr(pozycja + 1);
        ciag = pom; // Aktualizuje g³ówny ci¹g
        cout << ciag;
        dlugosc = ciag.size();
    }
    return pom;
}


//string MyRegex::Pomiedzy(char z1, char z2) {
//    size_t poczatek = ciag.find(z1); // Znajduje pierwsze '('
//    size_t koniec = ciag.find(z2, poczatek); // Znajduje ')' po '('
//
//    if (poczatek != string::npos && koniec != string::npos) {
//        string zawartosc = ciag.substr(poczatek + 1, koniec - poczatek - 1); // Wyci¹ga zawartoœæ miêdzy nawiasami
//        ciag = zawartosc;
//        dlugosc = ciag.size();
//        //Nadpisz(zawartosc);
//        return zawartosc;
//    }
//
//    return ""; // Zwraca pusty ci¹g, jeœli nawiasów brak
//}

string MyRegex::PomiedzyDoPrzypisywania(char z1, char z2) {
    size_t poczatek = ciag.find(z1); // Znajduje pierwsze '('
    size_t koniec = ciag.find(z2, poczatek); // Znajduje ')' po '('

    if (poczatek != string::npos && koniec != string::npos) {
        string zawartosc = ciag.substr(poczatek + 1, koniec - poczatek - 1); // Wyci¹ga zawartoœæ miêdzy nawiasami
        
        Nadpisz(zawartosc);
        return zawartosc;
    }

    return ""; // Zwraca pusty ci¹g, jeœli nawiasów brak
}

std::string MyRegex::Pomiedzy(char z1, char z2) {
    size_t poczatek = ciag.find(z1);
    size_t koniec = ciag.find(z2, poczatek + 1);

    if (poczatek != std::string::npos && koniec != std::string::npos) {
        std::string zawartosc = ciag.substr(poczatek + 1, koniec - poczatek - 1);
        ciag = zawartosc;
        dlugosc = ciag.size();
        cout << endl << "Zawartosc to " << zawartosc << endl;
        return zawartosc;
    }
    return "";
}









string MyRegex::Liczba()
{
    string pom = "";
    int i = 0;

    while (i <= dlugosc - 1) {
        cout << ciag[i];
        if (isdigit(ciag[i]) || ciag[i] == '.' || ciag[i] == '-') {
            pom += ciag[i];
        }
        else {
            if (pom != "") {
                Nadpisz(pom);
            }
            string zwracana = "";
            for (int dl_pom = pom.size(); dl_pom <= dlugosc - 1; dl_pom++) {
                zwracana += ciag[dl_pom];
            }
            ciag = zwracana;
            dlugosc = ciag.size();
            return zwracana;
        }
        i++;
    }
    Nadpisz(pom);
    int dl_pom = pom.size();
    string zwracana = "";
    for (int dl_pom = pom.size(); dl_pom <= dlugosc - 1; dl_pom++) {
        zwracana += ciag[dl_pom];
    }
    ciag = zwracana;
    dlugosc = ciag.size();
    return zwracana;
}

void MyRegex::Nadpisz(string wyrazenie)
{
    zapisane[iloscZapisanych] = wyrazenie;
    iloscZapisanych++;
}

string* MyRegex::Analizuj(const string& input, string wyrazenie)
{

    string wynik, pom;
    dlugosc = input.size();
    ciag = input;
    zapisane[0] = ciag;

    for (int i = 0; i <= wyrazenie.size() - 1; i++) {
        cout <<endl<< wyrazenie[i];
        wZapisane();
        switch (wyrazenie[i]) {

        case 'a':
            All();
            break;

        case 's':
            Spacja();
            break;

        case 'o':
            Operator();
            break;

        case 'w':
            Wyrazenie();
            
            cout << endl<<ciag;
            break;

        case 'c': {
            pom = wyrazenie.substr(i);
          
            size_t poczatek = pom.find('"'); // Znajduje pierwszy znak '"'
            size_t koniec = pom.find('"', poczatek + 1); // Znajduje drugi znak '"'

            if (poczatek != string::npos && koniec != string::npos) {
                string zawartosc = pom.substr(poczatek + 2, koniec - poczatek - 2); // Wyci¹ga zawartoœæ miêdzy cudzys³owami
                
                if (!Cokolwiek(zawartosc)) {
                    cout << "Nie znaleziono wzorca: " << zawartosc << endl;
                }
            }
            i = koniec;
            break;
        }


        case 'd':
            DowolnyZnak(wyrazenie[i + 1]);
            i += 1;
            cout << endl<<ciag;
            break;

        case 'p':
            Pomiedzy(wyrazenie[i + 1], wyrazenie[i + 2]);
            i += 2;
            cout << endl<<ciag;
           
            break;

        case 'z':
            PomiedzyDoPrzypisywania(wyrazenie[i + 1], wyrazenie[i + 2]);
            i += 2;
            cout << endl << ciag;

            break;

        case 'l':
            Liczba();

            cout << endl << ciag;
            break;
        default:
            // Jeœli ¿aden przypadek nie pasuje, opcjonalny kod
            break;
        }
        
    }
    
    return zapisane;
}

