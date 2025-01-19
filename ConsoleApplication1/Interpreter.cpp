#include "Interpreter.h"

using namespace std;

void Interpreter::Interpretuj(const string& input) {
    if (input.find('=') != string::npos) {
        PrzetworzPrzypisanie(input);
    }
    else if (input.find("transpozycja") != string::npos) {
        PrzetworzTranspozycje(input);
    }
    else if (input.find("wyswietl") != string::npos) { 
        PrzetworzWyswietlanie(input);
    }
    else if (input.find("wyznacznik") != string::npos) {
        PrzetworzWyznacznik(input);
    }
    else if (input.find("dlugosc") != string::npos) {
        PrzetworzDlugoscWektora(input);
    }
    else if (input.find("iloczynskalarny") != string::npos) {
        PrzetworzIloczynSkalarny(input);
    }
    else if (input.find("mnozeniestala") != string::npos) {
        PrzetworzMnozenieStala(input);
    }
    else if (input.find("katwektory") != string::npos) {
        PrzetworzKatWektory(input);
    }
    /////////////////////mozliwosc rozbudowy o kolejnne moduly np macierz odwrotna (funkcje juz napisane)//////////////////////
    else {
        cout << "Nieznana komenda: " << input << "\n";
    }
}


void Interpreter::PrzetworzPrzypisanie(const string& input) {
    MyRegex pattern;
    pattern.Analizuj(input,"swsd=sa");
        if(isalpha(pattern.zZapisane(1)[0])) {

        string nazwa = pattern.zZapisane(1);

        string wyrazenie = pattern.zZapisane(2);

        if (wyrazenie[0] == '[') {
            UtworzMacierz(nazwa, wyrazenie);
        }
        else {
            WykonajOperacje(nazwa, wyrazenie);
        }
    }
    else {
        cout << "B³¹d sk³adni: " << input << "\n";
    }
}



void Interpreter::UtworzMacierz(const string& nazwa, const string& dane) {
    MyRegex pattern;
    pattern.Analizuj(dane, "z[]"); 
    string wiersze = pattern.zZapisane(1);

    if (!wiersze.empty()) {
        istringstream stream(wiersze);
        string wiersz;
        vector<vector<double>> elementy;

        while (getline(stream, wiersz, ';')) {
            istringstream rowStream(wiersz);
            vector<double> wierszElementy;
            double liczba;
            while (rowStream >> liczba) {
                wierszElementy.push_back(liczba);
            }
            elementy.push_back(wierszElementy);
        }

        if (elementy.size() == elementy[0].size()) { // Sprawdzenie, czy macierz jest kwadratowa
            int wymiar = elementy.size();
            Macierz nowaMacierz(wymiar, nazwa[0]);
            for (int i = 0; i < wymiar; i++) {
                for (int j = 0; j < wymiar; j++) {
                    nowaMacierz.UstawWartosc(i, j, elementy[i][j]);
                }
            }
            macierze[nazwa] = nowaMacierz;
            nowaMacierz.Wypisz();
        }
        else {
            if (elementy.size() == 1 && elementy[0].size() == 2) {
                Vector nowyWektor(nazwa[0], elementy[0][0], elementy[0][1]);
                vectors[nazwa] = nowyWektor;
                nowyWektor.Wypisz();
            }
            else {
                cout << "B³¹d: tylko macierze kwadratowe i wektory s¹ obs³ugiwane.\n";
            }
        }
    }
    else {
        cout << "B³¹d sk³adni danych macierzy.\n";
    }
}


void Interpreter::WykonajOperacje(const string& nazwa, const string& wyrazenie) {
    MyRegex pattern;
    pattern.Analizuj(wyrazenie, "swsoswso"); // Dopasowuje wzorzec: operand1 operator operand2
    string op1 = pattern.zZapisane(1);
    string operacja = pattern.zZapisane(2);
    string op2 = pattern.zZapisane(3);

    if (!op1.empty() && !operacja.empty() && !op2.empty()) {
        if (macierze.find(op1) != macierze.end() && macierze.find(op2) != macierze.end()) {
            Macierz wynik(WykonajDzialanie(macierze[op1], operacja, macierze[op2]));
            macierze[nazwa] = wynik;
            wynik.ZmienNazwe(nazwa[0]);
            wynik.Wypisz();
        }
        else {
            cout << "B³¹d: Jedna z macierzy nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni operacji.\n";
    }
}


Macierz Interpreter::WykonajDzialanie(const Macierz& m1, const string& operacja, const Macierz& m2) {
    if (operacja == "+") {
        return m1 + m2;
    }
    else if (operacja == "-") {
        return m1 - m2;
    }
    else if (operacja == "*") {
        return m1 * m2;
    }
    else if (operacja == "/") {
        return m1 / m2;
    }
    else {
        throw invalid_argument("Nieznana operacja: " + operacja);
    }
}


void Interpreter::PrzetworzTranspozycje(const string& input) {
    MyRegex pattern;
    pattern.Analizuj(input, "c\"transpozycja\"p()w");
    string nazwa = pattern.zZapisane(1);

    if (!nazwa.empty()) {
        if (macierze.find(nazwa) != macierze.end()) {
            Macierz wynik = macierze[nazwa];
            wynik.Trasponuj();
            cout << "Macierz " << nazwa << " po transpozycji:\n";
            wynik.Wypisz();
        }
        else {
            cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia transpozycji.\n";
    }
   
}


void Interpreter::PrzetworzWyznacznik(const string& input) {
    MyRegex pattern;
    pattern.Analizuj(input, "c\"wyznacznik\"p()w"); // Dopasowuje wzorzec: wyznacznik(nazwa)
    string nazwa = pattern.zZapisane(1);

    if (!nazwa.empty()) {
        if (macierze.find(nazwa) != macierze.end()) {
            double det = macierze[nazwa].Det();
            cout << "Wyznacznik macierzy " << nazwa << " wynosi: " << det << "\n";
        }
        else {
            cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia wyznacznika.\n";
    }
    
    
}


void Interpreter::PrzetworzWyswietlanie(const string& input)
{
    MyRegex pattern;

    // Analizuj dane wejœciowe
    pattern.Analizuj(input, "c\"wyswietl\"p()w");

    // Pobierz nazwê macierzy z zapisanych danych
    string nazwa = pattern.zZapisane(1);

    if (!nazwa.empty()) {
        // SprawdŸ, czy macierz istnieje w mapie
        if (macierze.find(nazwa) != macierze.end()) {
            Macierz wynik = macierze[nazwa];
            cout << "Wyœwietlanie macierzy " << nazwa << ":\n";
            wynik.Wypisz();
        }
        else {
            cout << "B³¹d: Macierz \"" << nazwa << "\" nie istnieje.\n";
        }
    }
    else {
        // Obs³uga b³êdu sk³adni
        cout << "B³¹d sk³adni polecenia \"wyswietl\". Poprawny format: wyswietl(NazwaMacierzy).\n";
    }
    
}


void Interpreter::PrzetworzDlugoscWektora(const string& input) {
    MyRegex pattern;
    pattern.Analizuj(input, "c\"dlugosc\"p()sw"); // Dopasowuje wzorzec: dlugosc(nazwa)
    string nazwa = pattern.zZapisane(1);

    if (!nazwa.empty()) {
        if (vectors.find(nazwa) != vectors.end()) {
            double len = vectors[nazwa].dlugoscWektora();
            cout << "D³ugoœæ wektora " << nazwa << " wynosi: " << len << "\n";
        }
        else {
            cout << "B³¹d: Wektor " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia d³ugoœci wektora.\n";
    }
}


void Interpreter::PrzetworzIloczynSkalarny(const std::string& input) {
    MyRegex pattern;
    pattern.Analizuj(input, "c\"iloczynskalarny\"sp()swsd,sw"); // Dopasowuje wzorzec: iloczynskalarny(w1,w2)
    string w1 = pattern.zZapisane(1);
    string w2 = pattern.zZapisane(2);

  
    if (!w1.empty() && !w2.empty()) {
        if (vectors.find(w1) != vectors.end() && vectors.find(w2) != vectors.end()) {
            cout << "Iloczyn skalarny wektorów " << w1 << " i " << w2
                << " to " << vectors[w1].iloczynSkalarny(vectors[w2]) << endl;
        }
        else {
            cout << "B³¹d: Wektor " << w1 << " lub " << w2 << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia iloczynu skalarnego.\n";
    }
}


void Interpreter::PrzetworzMnozenieStala(const std::string& input) {
    MyRegex pattern;
    pattern.Analizuj(input, "c\"mnozeniestala\"p()sld,sw"); // Dopasowuje wzorzec: mnozeniestala(stala,nazwa)
    string stalaStr = pattern.zZapisane(1);
    string nazwa = pattern.zZapisane(2);

    if (!stalaStr.empty() && !nazwa.empty()) {
        double stala = std::stod(stalaStr);
        if (macierze.find(nazwa) != macierze.end()) {
            macierze[nazwa].MnozenieStala(stala);
            macierze[nazwa].Wypisz();
        }
        else {
            cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia mno¿enia przez sta³¹.\n";
    }
}


void Interpreter::PrzetworzKatWektory(const std::string& input)
{
    MyRegex pattern;
    pattern.Analizuj(input, "c\"katwektory\"sp()swsd,sw"); // Dopasowuje wzorzec: iloczynskalarny(w1,w2)
    string w1 = pattern.zZapisane(1);
    string w2 = pattern.zZapisane(2);
   
    if (!w1.empty() && !w2.empty()) {
        if (vectors.find(w1) != vectors.end() && vectors.find(w2) != vectors.end()) {
            cout << "K¹t miêdzy wektorami  " << w1 << " i " << w2
                << " to " << vectors[w1].katMiedzyWektorami(vectors[w2]) << endl;
        }
        else {
            cout << "B³¹d: Wektor " << w1 << " lub " << w2 << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia iloczynu skalarnego.\n";
    }
}





