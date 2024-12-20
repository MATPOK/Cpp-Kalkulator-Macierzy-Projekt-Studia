#include "Macierz.h"
#include "Interpreter.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    Interpreter interpreter;
    std::string input;

    std::cout << "Wpisz 'exit', aby zakończyć program.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        interpreter.Interpretuj(input);
    }

    return 0;
    
    
   
    
    

  
}
