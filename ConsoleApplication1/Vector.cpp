#include "Vector.h"
#include <iostream>
#include<cmath>
#include <iomanip>

using namespace std;

// Konstruktor domyœlny
Vector::Vector() : nazwa(' '), wartosci{ 0.0, 0.0 } {}

// Konstruktor kopiuj¹cy
Vector::Vector(const Vector& vector) : nazwa(vector.nazwa) {
    wartosci[0] = vector.wartosci[0];
    wartosci[1] = vector.wartosci[1];
}

// Konstruktor z parametrami
Vector::Vector(char nazwa, double w1, double w2) : nazwa(nazwa) {
    wartosci[0] = w1;
    wartosci[1] = w2;
}

// Destruktor
Vector::~Vector() {}

// Metoda do pobierania wartoœci
const double* Vector::zWartosci() const {
    return wartosci;
}

// Metoda do ustawiania wartoœci
void Vector::uWartosci(double w1, double w2) {
    wartosci[0] = w1;
    wartosci[1] = w2;
}

void Vector::Wypisz() const
{
	/////////////////////////////////////////////////////mozliwosc zmiany sposobu wyswietlania macierzy/////////////////////////////////////////////
	const int precyzja = 3;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "Wektor " << nazwa << "\n";
	cout << "[ ";
	cout << fixed << setprecision(precyzja)
		<< wartosci[0] << " ";
    cout << fixed << setprecision(precyzja)
        << wartosci[1];
    cout << " ]\n";
}

const double Vector::dlugoscWektora() const
{
    return sqrt(wartosci[0] * wartosci[0] + wartosci[1] * wartosci[1]);
}

const double Vector::iloczynSkalarny(const Vector& w) const
{
    return (wartosci[0] * w.wartosci[0] + wartosci[1] * w.wartosci[1]);
}
