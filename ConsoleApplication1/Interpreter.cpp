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
    /////////////////////mozliwosc rozbudowy o kolejnne moduly np macierz odwrotna (funkcje juz napisane)//////////////////////
    else {
        cout << "Nieznana komenda: " << input << "\n";
    }
}

void Interpreter::PrzetworzPrzypisanie(const string& input) {
    //wyrazenia regularne nazwa ZB = ZB
    regex pattern(R"(\s*(\w+)\s*=\s*(.+))");
    smatch match;
    if (regex_match(input, match, pattern)) {
        //nazwa macierzy
        string nazwa = match[1];
        //wartosci do wpisania w macierz [...] lub dzialanie do wykonania
        string wyrazenie = match[2];

        if (wyrazenie[0] == '[') {
            UtworzMacierz(nazwa, wyrazenie);
        }
        else {
            WykonajOperacje(nazwa, wyrazenie);
        }
    }
    else {
        cout << "B��d sk�adni: " << input << "\n";
    }
}

void Interpreter::UtworzMacierz(const string& nazwa, const string& dane) {
    regex matrixPattern(R"(\[(.+)\])");
    smatch match;
    //danie juz bez nawaisow []
    if (regex_match(dane, match, matrixPattern)) {
        string wiersze = match[1];
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
            cout << "B��d: tylko macierze kwadratowe s� obs�ugiwane.\n";
        }
    }
    else {
        cout << "B��d sk�adni danych macierzy.\n";
    }
}

void Interpreter::WykonajOperacje(const string& nazwa, const string& wyrazenie) {
    regex operationPattern(R"(\s*(\w+)\s*([+\-*/])\s*(\w+))");
    smatch match;
    if (regex_match(wyrazenie, match, operationPattern)) {
        string op1 = match[1];
        string operacja = match[2];
        string op2 = match[3];

        if (macierze.find(op1) != macierze.end() && macierze.find(op2) != macierze.end()) {
            Macierz wynik(WykonajDzialanie(macierze[op1], operacja, macierze[op2]));
            macierze[nazwa] = wynik;
            wynik.ZmienNazwe(nazwa[0]);
            wynik.Wypisz();
        }
        else {
            cout << "B��d: Jedna z macierzy nie istnieje.\n";
        }
    }
    else {
        cout << "B��d sk�adni operacji.\n";
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
    regex pattern(R"(transpozycja\((\w+)\))");
    smatch match;
    if (regex_match(input, match, pattern)) {
        string nazwa = match[1];

        if (macierze.find(nazwa) != macierze.end()) {
            Macierz wynik = macierze[nazwa];
            wynik.Trasponuj();
            cout << "Macierz " << nazwa << " po transpozycji:\n";
            wynik.Wypisz();
        }
        else {
            cout << "B��d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B��d sk�adni polecenia transpozycji.\n";
    }
}

void Interpreter::PrzetworzWyznacznik(const string& input) {
    regex pattern(R"(wyznacznik\((\w+)\))");
    smatch match;
    if (regex_match(input, match, pattern)) {
        string nazwa = match[1];

        if (macierze.find(nazwa) != macierze.end()) {
            double det = macierze[nazwa].Det();
            cout << "Wyznacznik macierzy " << nazwa << " wynosi: " << det << "\n";
        }
        else {
            cout << "B��d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B��d sk�adni polecenia wyznacznika.\n";
    }
}

void Interpreter::PrzetworzWyswietlanie(const string& input)
{
    regex pattern(R"(wyswietl\((\w+)\))");
    smatch match;
    if (regex_match(input, match, pattern)) {
        string nazwa = match[1];

        if (macierze.find(nazwa) != macierze.end()) {
            macierze[nazwa].Wypisz();
        }
        else {
            cout << "B��d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B��d sk�adni polecenia wyznacznika.\n";
    }
}


