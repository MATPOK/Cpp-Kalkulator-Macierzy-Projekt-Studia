#include "Interpreter.h"


void Interpreter::Interpretuj(const std::string& input) {
    if (input.find('=') != std::string::npos) {
        PrzetworzPrzypisanie(input);
    }
    else if (input.find("transpozycja") != std::string::npos) {
        PrzetworzTranspozycje(input);
    }
    else if (input.find("wyswietl") != std::string::npos) { 
        PrzetworzWyswietlanie(input);
    }
    else if (input.find("wyznacznik") != std::string::npos) {
        PrzetworzWyznacznik(input);
    }
    /////////////////////mozliwosc rozbudowy o kolejnne moduly np macierz odwrotna (funkcje juz napisane)//////////////////////
    else {
        std::cout << "Nieznana komenda: " << input << "\n";
    }
}

void Interpreter::PrzetworzPrzypisanie(const std::string& input) {
    //wyrazenia regularne nazwa ZB = ZB
    std::regex pattern(R"(\s*(\w+)\s*=\s*(.+))");
    std::smatch match;
    if (std::regex_match(input, match, pattern)) {
        //nazwa macierzy
        std::string nazwa = match[1];
        //wartosci do wpisania w macierz [...] lub dzialanie do wykonania
        std::string wyrazenie = match[2];

        if (wyrazenie[0] == '[') {
            UtworzMacierz(nazwa, wyrazenie);
        }
        else {
            WykonajOperacje(nazwa, wyrazenie);
        }
    }
    else {
        std::cout << "B³¹d sk³adni: " << input << "\n";
    }
}

void Interpreter::UtworzMacierz(const std::string& nazwa, const std::string& dane) {
    std::regex matrixPattern(R"(\[(.+)\])");
    std::smatch match;
    //danie juz bez nawaisow []
    if (std::regex_match(dane, match, matrixPattern)) {
        std::string wiersze = match[1];
        std::istringstream stream(wiersze);
        std::string wiersz;
        std::vector<std::vector<double>> elementy;

        while (std::getline(stream, wiersz, ';')) {
            std::istringstream rowStream(wiersz);
            std::vector<double> wierszElementy;
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
            std::cout << "B³¹d: tylko macierze kwadratowe s¹ obs³ugiwane.\n";
        }
    }
    else {
        std::cout << "B³¹d sk³adni danych macierzy.\n";
    }
}

void Interpreter::WykonajOperacje(const std::string& nazwa, const std::string& wyrazenie) {
    std::regex operationPattern(R"(\s*(\w+)\s*([+\-*/])\s*(\w+))");
    std::smatch match;
    if (std::regex_match(wyrazenie, match, operationPattern)) {
        std::string op1 = match[1];
        std::string operacja = match[2];
        std::string op2 = match[3];

        if (macierze.find(op1) != macierze.end() && macierze.find(op2) != macierze.end()) {
            Macierz wynik(WykonajDzialanie(macierze[op1], operacja, macierze[op2]));
            macierze[nazwa] = wynik;
            wynik.ZmienNazwe(nazwa[0]);
            wynik.Wypisz();
        }
        else {
            std::cout << "B³¹d: Jedna z macierzy nie istnieje.\n";
        }
    }
    else {
        std::cout << "B³¹d sk³adni operacji.\n";
    }
}

Macierz Interpreter::WykonajDzialanie(const Macierz& m1, const std::string& operacja, const Macierz& m2) {
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
        throw std::invalid_argument("Nieznana operacja: " + operacja);
    }
}

void Interpreter::PrzetworzTranspozycje(const std::string& input) {
    std::regex pattern(R"(transpozycja\((\w+)\))");
    std::smatch match;
    if (std::regex_match(input, match, pattern)) {
        std::string nazwa = match[1];

        if (macierze.find(nazwa) != macierze.end()) {
            Macierz wynik = macierze[nazwa];
            wynik.Trasponuj();
            std::cout << "Macierz " << nazwa << " po transpozycji:\n";
            wynik.Wypisz();
        }
        else {
            std::cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        std::cout << "B³¹d sk³adni polecenia transpozycji.\n";
    }
}

void Interpreter::PrzetworzWyznacznik(const std::string& input) {
    std::regex pattern(R"(wyznacznik\((\w+)\))");
    std::smatch match;
    if (std::regex_match(input, match, pattern)) {
        std::string nazwa = match[1];

        if (macierze.find(nazwa) != macierze.end()) {
            double det = macierze[nazwa].Det();
            std::cout << "Wyznacznik macierzy " << nazwa << " wynosi: " << det << "\n";
        }
        else {
            std::cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        std::cout << "B³¹d sk³adni polecenia wyznacznika.\n";
    }
}

void Interpreter::PrzetworzWyswietlanie(const std::string& input)
{
    std::regex pattern(R"(wyswietl\((\w+)\))");
    std::smatch match;
    if (std::regex_match(input, match, pattern)) {
        std::string nazwa = match[1];

        if (macierze.find(nazwa) != macierze.end()) {
            macierze[nazwa].Wypisz();
        }
        else {
            std::cout << "B³¹d: Macierz " << nazwa << " nie istnieje.\n";
        }
    }
    else {
        std::cout << "B³¹d sk³adni polecenia wyznacznika.\n";
    }
}


