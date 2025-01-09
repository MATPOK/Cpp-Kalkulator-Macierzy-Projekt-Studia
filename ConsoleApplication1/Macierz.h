#pragma once
#include <iostream>
#include <iomanip>

class Macierz {

private:
   int wymiar;    
   double *wartosci;
   char nazwa;

public:
    Macierz(int wymiar, char nazwa);
    Macierz(const Macierz& wzor);
    Macierz();
    ~Macierz();
    

    const int zWymiar() const;
    double* zWszystkieWartosci() const;
    const double& zWartosc(int w, int k) const;


    const void Wypisz() const;
    void Wpisz();
    
    
    void ZmienNazwe(char nowa);
    void UstawWartosc(int w, int k, double nowa);
    void Trasponuj();
    void Zeros();
    double Det() const;
    void Przypisz(const Macierz& A);
    void Dodaj(Macierz& A);
    bool RowneWymiary(const Macierz& A) const;
    void MnozenieStala(double a);
    bool CzyRowne(Macierz& A) const;
    Macierz Mnozenie(const Macierz& A) const;
    Macierz Odwrotna() const;
    Macierz Dzielenie(const Macierz& A) const;
    void Odejmij(Macierz& A);
    
    
    Macierz& operator=(const Macierz& A);
    Macierz operator+(const Macierz& A) const;
    Macierz operator-(const Macierz& A) const;
    Macierz operator/(const Macierz& A) const;
    Macierz operator*(const Macierz& A) const;

    friend std::ostream& operator<<(std::ostream& wy, const Macierz& A);
    friend std::istream& operator>>(std::istream& we, Macierz& A);
};



//Za³o¿enia projektu do poprawy////
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




////dorzucic wieksze operacje
///swoja klasa do wyrazen regularnych
///mnozenie stala
/// ///przede wszytkim swoje wyrazenie
/// 
/// //jak sie nie uda to na wektorach dzialania iloczyn skalarny itp