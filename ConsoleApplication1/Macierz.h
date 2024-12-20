#pragma once
#include <iostream>
#include <iomanip>


class Macierz {
private:
   int wymiar;
   double *tablica;
   char nazwa;
public:
    Macierz(int wymiar, char nazwa);
    Macierz(const Macierz& wzor);
    ~Macierz();
    Macierz();

    const int zWymiar() const;
    double* zTablice() const;
    const double& zWartosc(int w, int k) const;

    void UstawWartosc(int w, int k, double nowa);
    const void Wypisz() const;
    void Wpisz();
    void Zeros();
    bool RowneWymiary(const Macierz& A) const;
    void ZmienNazwe(char nowa);
  

    void Trasponuj();
    void Dodaj(Macierz& A);
    Macierz operator+(const Macierz& A) const;
    Macierz operator-(const Macierz& A) const;
    void Odejmij(Macierz& A);
    Macierz& operator=(const Macierz& A);
    void MnozenieStala(double a);
    bool CzyRowne(Macierz& A) const;
    Macierz Mnozenie(const Macierz& A) const;
    Macierz Odwrotna() const;
    Macierz Dzielenie(const Macierz& A) const;
    Macierz operator/(const Macierz& A) const;
    Macierz operator*(const Macierz& A) const;
    double Det() const;
    void Przypisz(const Macierz& A);

    friend std::ostream& operator<<(std::ostream& wy, const Macierz& A);
    friend std::istream& operator>>(std::istream& we, Macierz& A);
};

// Consola:
// A = [1 3; 5 6]
// C = A + B;
// C = A / B;
// B = [0 -1; 7 6]
// 
// Kod
// Macierz A(2), B(2), C(2)
// C = A + B;
// // C = A / B;
// cout << C;
// cout << A.Dodaj(B)