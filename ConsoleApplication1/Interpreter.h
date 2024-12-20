#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <map>
#include "Macierz.h"

class Interpreter
{
    std::map<std::string, Macierz> macierze;
    void przetworzPrzypisanie(const std::string& input);
    void utworzMacierz(const std::string& nazwa, const std::string& dane);
    void wykonajOperacje(const std::string& nazwa, const std::string& wyrazenie);
    Macierz wykonajDzialanie(const Macierz& m1, const std::string& operacja, const Macierz& m2);
    void przetworzTranspozycje(const std::string& input);
    void przetworzWyznacznik(const std::string& input);
    void przetworzWyswietlanie(const std::string& input);

public:
    void interpretuj(const std::string& input);


};

