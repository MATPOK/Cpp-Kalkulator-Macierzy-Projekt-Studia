#pragma once

class Vector
{
private:
    char nazwa;
    double wartosci[2];

public:
    Vector();
    Vector(const Vector& vector);
    Vector(char nazwa, double w1, double w2);
    ~Vector();

    const double* zWartosci() const;
    void uWartosci(double w1, double w2);
    void Wypisz() const;

    const double dlugoscWektora() const;
    const double iloczynSkalarny(const Vector& w) const;
};

