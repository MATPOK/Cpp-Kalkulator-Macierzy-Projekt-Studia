#include "Macierz.h"
#include "Interpreter.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    Interpreter interpreter;
    string input;

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
