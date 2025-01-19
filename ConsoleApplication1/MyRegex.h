#pragma once
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

class MyRegex
{
private:
	string ciag;
	int dlugosc;
	string zapisane[10] = {"","", "", "", "", "", "", "", "", ""};
	int iloscZapisanych = 1;
private:
	void uCiag(string& wzor);
	void uDlugosc(int& wzor);

	//string zCiag() const;
public:
	void wZapisane() const;
	
	string All();
	string Spacja();
	string Operator();
	string Wyrazenie();
	bool Cokolwiek(const string& szukane);
	string DowolnyZnak(char znak);
	string Pomiedzy(char z1, char z2);
	string PomiedzyDoPrzypisywania(char z1, char z2);
	//string Find() const;
	
	string Liczba();

	void Nadpisz(string wyrazenie);
public:
	string* Analizuj(const string& input, string wyrazenie);
	string zZapisane(int indeks) const;
};

