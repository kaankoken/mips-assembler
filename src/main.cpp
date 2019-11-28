#include <iostream>
#include "ErrorHandling.h"
#include <fstream>
#include <filesystem>

class Main : ErrorHandling {
    public:
        Main() { ErrorHandling(); }
        ~Main() {}
        
        char menu() {
            std::string menuOption;

            std::cout << "(1) Interactive Mode" <<  std::endl;
            std::cout << "(2) Batch Mode" << std::endl;
            std::cout << "(3) Exit" << std::endl;

            std::cout << "Your Choice: ";
            std::cin >> menuOption;
            
            bool option = optionChecker(menuOption);
            if (option == false) {
                std::cout << "You have enter wrong input" << std::endl;
                std::cout << "Input should not be empty or multi value";
                return NULL;
            }
            return menuOption.at(0);
        }

        void readFile(std::string fileName) {
            bool isExist = std::filesystem::exists(fileName);
            if (isExist) {
                std::fstream file(fileName);
                if (file.is_open()) {
                    std::string line;
                    while (getline(file, line)) {
                        std::cout << line << std::endl;
                        // get the new codes from file and process it
                    }
                    file.close();
                }
            }
        }

};

int main(int argc, char **argv) {
    Main assembler;
    char menuOption;
    
    std::string fileName = "./test1.txt";
    assembler.readFile(fileName);
    std::cout << "Welcome to the MIPS ASSEMBLER" << std::endl;

    do {
        menuOption = assembler.menu();
        switch (menuOption) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            default:
                std::cout << "\nWrong Option!!!" << std::endl;
                break;
        }
    } while (menuOption != '3');
    
    return 0;
}
