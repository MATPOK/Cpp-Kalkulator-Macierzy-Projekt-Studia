#include "Macierz.h"
#include <iomanip>
#include <iostream>

using namespace std;

Macierz::Macierz(int wym, char nazwa):wymiar(wym), nazwa(nazwa)
{
	tablica = new double[wym * wym];
	Zeros();
}



Macierz::Macierz(const Macierz & wzor) : wymiar(wzor.zWymiar()) {
	tablica = new double[wymiar * wymiar];
	for (int i = 0; i < wymiar * wymiar; ++i) {
		tablica[i] = wzor.zTablice()[i];
	}
}


Macierz::~Macierz()
{
	delete [] tablica;
}

Macierz::Macierz()
{
	wymiar = 0;
	tablica = new double[0];
	nazwa = ' ';
}

const int Macierz::zWymiar() const
{
	return wymiar;
}

double* Macierz::zTablice() const
{
	return tablica;
}

const double& Macierz::zWartosc(int w, int k) const {
	return tablica[w * wymiar + k];
}


void Macierz::UstawWartosc(int w, int k, double nowa)
{
	tablica[w * wymiar + k] = nowa;
}

const void Macierz::Wypisz() const {
	const int szerokosc = 8; 
	const int precyzja = 3; 

	std::cout << "Macierz " <<nazwa<<"\n";
	for (int i = 0; i < wymiar; i++) {
		std::cout << "|"; 
		for (int j = 0; j < wymiar; j++) {
			std::cout << std::setw(szerokosc) << std::fixed << std::setprecision(precyzja)
				<< zWartosc(i, j); 
		}
		std::cout << " |\n"; 
	}
}


void Macierz::Wpisz()
{
	double* tab = zTablice();
	double a;
	for (int i = 0; i < wymiar * wymiar; i++) {
		cin >> a;
		tab[i] = a;
	}
}

void Macierz::Zeros()
{
	for (int i = 0; i < wymiar; i++) {
		for (int j = 0; j < wymiar; j++) {
			UstawWartosc(i, j, 0.0);
		}
	}
}

bool Macierz::RowneWymiary(const Macierz& A) const
{
	if (wymiar == A.zWymiar()) {
		return true;
	}
	else
		return false;
}

void Macierz::ZmienNazwe(char nowa)
{
	nazwa = nowa;
}


void Macierz::Trasponuj()
{
	double pom;
	for (int i = 0; i < wymiar; i++) {
		for (int j = i+1; j < wymiar; j++) {
			pom = zWartosc(i, j);
			UstawWartosc(i, j, zWartosc(j, i));
			UstawWartosc(j, i, pom);
		}
	}
}

void Macierz::Dodaj(Macierz& A)
{
	if (RowneWymiary(A)) {
		for (int i = 0; i < wymiar; i++) {
			for (int j = 0; j < wymiar; j++) {
				UstawWartosc(i, j, zWartosc(i, j) + A.zWartosc(i, j));
			}
		}
	}
	else
		cout << "Rozne wymiary macierzy!\n";
}

Macierz Macierz::operator+(const Macierz& A) const {
	if (!RowneWymiary(A)) {
		throw std::invalid_argument("Rozne wymiary macierzy!");
	}

	Macierz wynik(wymiar,'W');
	for (int i = 0; i < wymiar; i++) {
		for (int j = 0; j < wymiar; j++) {
			wynik.UstawWartosc(i, j, A.zWartosc(i, j) + zWartosc(i, j));
		}
	}
	return wynik;
}

Macierz Macierz::operator-(const Macierz& A) const
{
	if (!RowneWymiary(A)) {
		throw std::invalid_argument("Rozne wymiary macierzy!");
	}

	Macierz wynik(wymiar, 'W');
	for (int i = 0; i < wymiar; i++) {
		for (int j = 0; j < wymiar; j++) {
			wynik.UstawWartosc(i, j, A.zWartosc(i, j) - zWartosc(i, j));
		}
	}
	return wynik;
}


void Macierz::Odejmij(Macierz& A)
{
	if (RowneWymiary(A)) {
		for (int i = 0; i < wymiar; i++) {
			for (int j = 0; j < wymiar; j++) {
				UstawWartosc(i, j, zWartosc(i, j) - A.zWartosc(i, j));
			}
		}
	}
	else
		cout << "Rozne wymiary macierzy!\n";
}



Macierz& Macierz::operator=(const Macierz& A) {
	if (this != &A) { 
		if (wymiar != A.wymiar) {
			delete[] tablica; 
			wymiar = A.wymiar;
			tablica = new double[wymiar * wymiar]; 
		}
		for (int i = 0; i < wymiar * wymiar; ++i) {
			tablica[i] = A.tablica[i];
		}
	}
	return *this;
}

void Macierz::MnozenieStala(double a)
{
	for (int i = 0; i < wymiar; i++) {
		for (int j = 0; j < wymiar; j++) {
			UstawWartosc(i, j, zWartosc(i, j)*a);
		}
	}
}

bool Macierz::CzyRowne(Macierz& A) const
{
	if (RowneWymiary(A)) {
		for (int i = 0; i < wymiar; i++) {
			for (int j = 0; j < wymiar; j++) {
				if (zWartosc(i, j) == A.zWartosc(i, j)) {
					return true;
				}
				else
					return false;
			}
		}
	}
	
	return false;
}

Macierz Macierz::Mnozenie(const Macierz& A) const
{
	Macierz wynik(A.zWymiar(), 'W');
	if (RowneWymiary(A)) {
		for (int i = 0; i < wymiar; i++) {
			for (int j = 0; j < wymiar; j++) {
				for (int z = 0; z < wymiar; z++) {
					wynik.zTablice()[i * wymiar + j] += tablica[i * wymiar + z] * A.zTablice()[z * wymiar + j];
				}
			}
		}
	}
	else {
		throw std::runtime_error("Rozne wymiary macierzy!");
	}

	return wynik;
}

Macierz Macierz::Odwrotna() const{
	double det = Det(); 
	if (det == 0) {
		cout << "Macierz nieodwracalna (wyznacznik = 0)!";
		throw std::runtime_error("Macierz nie jest odwracalna (wyznacznik = 0).");
	}

	Macierz wynik(wymiar,'W');
	for (int i = 0; i < wymiar; i++) {
		for (int j = 0; j < wymiar; j++) {
			
			Macierz submat(wymiar - 1,'W');
			for (int row = 0, subRow = 0; row < wymiar; row++) {
				if (row == i) continue; 
				for (int col = 0, subCol = 0; col < wymiar; col++) {
					if (col == j) continue; 
					submat.UstawWartosc(subRow, subCol, zWartosc(row, col));
					subCol++;
				}
				subRow++;
			}
			double dopelnienie = submat.Det() * ((i + j) % 2 == 0 ? 1 : -1);
			wynik.UstawWartosc(j, i, dopelnienie); 
		}
	}

	wynik.MnozenieStala(1.0 / det);
	return wynik;
}

Macierz Macierz::Dzielenie(const Macierz& A) const
{
	Macierz A_odwrotna = A.Odwrotna();
	Macierz wynik(*this);
	wynik.Mnozenie(A_odwrotna);
	return wynik;
}

Macierz Macierz::operator/(const Macierz& A) const
{
	return Dzielenie(A);
}

Macierz Macierz::operator*(const Macierz& A) const
{
	return Mnozenie(A);
}


double Macierz::Det() const
{
	if (wymiar == 1) {
		return zWartosc(0, 0);
	}
	double det = 0.0;
	Macierz submat(wymiar - 1,'W');
	for (int i = 0; i < wymiar; i++) {
		for (int j = 1; j < wymiar; j++) {
			int submatCol = 0;
			for (int k = 0; k < wymiar; k++) {
				if (k != i) {
					submat.UstawWartosc(j - 1, submatCol, zWartosc(j, k));
					submatCol++;
				}
			}
		}
		det += (i % 2 == 0 ? 1 : -1) * zWartosc(0, i) * submat.Det();
	}
	return det;
}

void Macierz::Przypisz(const Macierz& A) {
	if (wymiar != A.wymiar) {  
		delete[] tablica;
		wymiar = A.wymiar;
		tablica = new double[wymiar * wymiar];
	}
	for (int i = 0; i < wymiar; ++i) {
		for (int j = 0; j < wymiar; j++) {
			UstawWartosc(i,j,A.zWartosc(i,j));
		}
		
	}
}

std::ostream& operator<<(std::ostream& wy, const Macierz& A)
{
	A.Wypisz();
	return wy;
}

std::istream& operator>>(std::istream& we, Macierz& A)
{
	A.Wpisz();
	return we;
}
