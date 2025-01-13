#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <map>
#include "Macierz.h"
#include "Vector.h"

class Interpreter
{

    //zbior wszystkich macierzy do wykonywania operacji po kluczach
    std::map<std::string, Macierz> macierze;
    std::map<std::string, Vector> vectors;

    void PrzetworzPrzypisanie(const std::string& input);
    void UtworzMacierz(const std::string& nazwa, const std::string& dane);
    void WykonajOperacje(const std::string& nazwa, const std::string& wyrazenie);
    Macierz WykonajDzialanie(const Macierz& m1, const std::string& operacja, const Macierz& m2);
    void PrzetworzTranspozycje(const std::string& input);
    void PrzetworzWyznacznik(const std::string& input);
    void PrzetworzWyswietlanie(const std::string& input);
    void PrzetworzDlugoscWektora(const std::string& input);
    void PrzetworzIloczynSkalarny(const std::string& input);
    //void PrzetworzMnozenieStala(const std::string& input);

public:
    void Interpretuj(const std::string& input);
};

