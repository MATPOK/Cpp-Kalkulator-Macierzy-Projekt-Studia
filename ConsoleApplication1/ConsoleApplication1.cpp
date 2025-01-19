#include "Macierz.h"
#include "Interpreter.h"
#include "Vector.h"
#include "MyRegex.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    Interpreter interpreter;
    string input;
    cout << "Tworzenie macierzy (tylko kwadratowe) nazwa=[x11 x12;x21 x22]\n"
        << "Tworzenie wektora nazwa=[a1 a2]\n"
        << "Możliwe operacje macierze:\n"
        << "\t1) +-*/ - nazwa = M1 operacja M2\n"
        << "\t2) Transpozycja - transpozycja(M)\n"
        << "\t3) Wyświetlanie - wyswietl(M)\n"
        << "\t4) Wyznacznik - wyznacznik(M)\n"
        << "\t5) Mnozenie przez stałą - mnozeniestala(stala,M)\n"
        << "Możliwe operacje wektory:\n"
        << "\t1) Długość wektora - dlugosc(W)\n"
        << "\t2) Iloczyn skalarny - iloczynskalarny(W1,W2)\n"
        << "\t3) Kąt między wektorami - katwektory(W1,W2)\n"
        << endl;
    cout << "Wpisz 'exit', aby zakończyć program.\n";

    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        interpreter.Interpretuj(input);
    }
    return 0;
    

  
}
   
    

