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
        cout << "B³¹d sk³adni: " << input << "\n";
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
            cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia transpozycji.\n";
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
            cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia wyznacznika.\n";
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
            cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia wyznacznika.\n";
    }
}

void Interpreter::PrzetworzDlugoscWektora(const std::string& input)
{
    regex pattern(R"(dlugosc\((\w+)\))");
    smatch match;
    if (regex_match(input, match, pattern)) {
        string nazwa = match[1];

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

void Interpreter::PrzetworzIloczynSkalarny(const std::string& input)
{
    std::regex pattern(R"(\s*iloczynskalarny\((\w+)\s*,\s*(\w+)\s*\))");
    std::smatch match;
    if (std::regex_match(input, match, pattern)) {
        // nazwa macierzy
        std::string w1 = match[1]; // Pierwszy wektor
        std::string w2 = match[2]; // Drugi wektor
        // SprawdŸ, czy wektory istniej¹ w mapie
        if (vectors.find(w1) != vectors.end() && vectors.find(w2) != vectors.end()) {
            std::cout << "Iloczyn skalarny wektorów " << w1 << " i " << w2
                << " to " << vectors[w1].iloczynSkalarny(vectors[w2]) << std::endl;
        }
        else {
            std::cout << "B³êdne wektory!" << std::endl;
        }
    }
    else {
        std::cout << "B³êdny format wejœcia!" << std::endl;
    }
}

void Interpreter::PrzetworzMnozenieStala(const std::string& input)
{
    // Regex dopasowuj¹cy liczbê zmiennoprzecinkow¹ i nazwê macierzy
    std::regex pattern(R"(\s*mnozeniestala\(\s*([+-]?\d+(\.\d+)?)\s*,\s*(\w+)\s*\))");
    std::smatch match;

    // Dopasowanie
    if (std::regex_match(input, match, pattern)) {
        // Pobranie liczby zmiennoprzecinkowej
        double stala = std::stod(match[1].str());
        // Pobranie nazwy macierzy
        std::string nazwa = match[3].str();

        // Sprawdzenie, czy macierz istnieje w mapie
        if (macierze.find(nazwa) != macierze.end()) {
            macierze[nazwa].MnozenieStala(stala);
            macierze[nazwa].Wypisz();
        }
        else {
            std::cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        std::cout << "B³¹d sk³adni polecenia mno¿enia przez sta³¹.\n";
    }
}

void Interpreter::PrzetworzKatWektory(const std::string& input)
{
    regex pattern(R"(katwektory\(\s*(\w+)\s*,\s*(\w+)\s*\))");
    smatch match;
    if (regex_match(input, match, pattern)) {
        string w1 = match[1];
        string w2 = match[2];
        if (vectors.find(w1) != vectors.end() && vectors.find(w2) != vectors.end()) {
            cout << "K¹t miêdzy wektorami " << w1 << " i " << w2 << " to " << vectors[w1].katMiedzyWektorami(vectors[w2]) << endl;
        }
        else {
            cout << "B³¹d: wektor " << w1 << "/" << w2 << " nie istnieje.\n";
        }
    }
    else {
        cout << "B³¹d sk³adni polecenia k¹ta miêdzy wektorami.\n";
    }
}





