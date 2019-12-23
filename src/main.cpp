#include <iostream>
#include "ErrorHandling.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>

#include "SyntaxChecker.h"
#include "BitConverter.h"
#include "Instructions/Pseudo.h"
#include "Instructions/RType.h"
#include "Instructions/IType.h"
#include "Instructions/JType.h"

class Main : ErrorHandling, RType, IType, JType{
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

        //Reads the instructions from file if file exists, if it doesn't exist then it gives error
        std::vector<std::string> readFile(std::string fileName) const {
            bool isExist = std::filesystem::exists(fileName);
            std::vector<std::string> instructionSet;

            if (isExist) {
                std::fstream file(fileName);
                if (file.is_open()) {
                    std::string line;
                    while (getline(file, line))
                        instructionSet.push_back(line);
                    file.close();
                }
            }
            else
                std::cout << "File does not Exist!!!" << std::endl;
            return instructionSet;
        }

        //Writes the output of assembler
        void writeFile(std::vector<std::string> instructionSet){
            std::ofstream outfile ("output.obj");
            std::vector<std::string>::iterator it = instructionSet.begin();

            while(it != instructionSet.end()){
                outfile << *it << std::endl;
                it++;
            }

            outfile.close();
        }

        //Finds the 'label:' part inside instructions for jump operation to jump that instruction
        std::pair<std::map<std::string, int>, std::vector<int>> labelAndPcCounter(std::vector<std::string> instructionSet) {
            int pc = 80001000;

            std::vector<int> pcCounter;
            std::map<std::string, int> labels;
        
            std::vector<std::string>::iterator it = instructionSet.begin();

            while(it != instructionSet.end()) {
                pcCounter.push_back(pc);

                if (it->find(':') != std::string::npos) {
                    labels.insert(labels.begin(), {it->substr(0, it->find(':') + 1), pc});
                }
                pc += 4;
                it++;
            }
            
            return std::make_pair(labels, pcCounter);;
        }

        //Shows the instructions
        void displayInstructions(std::vector<std::string> instructionSet) {
            std::vector<std::string>::iterator it = instructionSet.begin();

            while(it != instructionSet.end()) {
                std::cout << *it << std::endl;
                it++;
            }
        }

        std::vector<std::string> splitInst(std::string instruction) const {
            size_t pos = 0;
            std::vector<std::string> token;
            std::string delimeter = ",";

            while((pos = instruction.find(delimeter)) != std::string::npos) {
                token.push_back(instruction.substr(0, pos));
                instruction.erase(0, pos + delimeter.length());
            }
            token.push_back(instruction);
            return token;
        }

        //Reads the instructions from file if file exists, if it doesn't exist then it gives error
        void lookupTable(std::string fileName) {
            std::vector<std::string> instructionSet = readFile(fileName);

            std::vector<std::string>::iterator it = instructionSet.begin() + 1;
            std::vector<std::string> temp = splitInst(*it);

            while(it != instructionSet.end()) {
                if (temp.at(0) == "rtype") {
                    RType::setter(temp);
                }
                else if (temp.at(0) == "itype"){
                }
                else{
                }
                it++;
            }
        }
};

//Main function of the assembler
int main(int argc, char **argv) {
    std::vector<std:: string> instructionSet;
    char menuOption;
    
    Main assembler;
    SyntaxChecker syntax;
    BitConverter converter;
    Pseudo pseudo;
    std::pair<std::map<std::string, int>, std::vector<int>> labelsAndPc;
    std::vector<std::vector<std::string>> instructions;
    std::vector<std::string> result;

    std::string fileName = "lookupTable";
    assembler.lookupTable(fileName);

    std::cout << "Welcome to the MIPS ASSEMBLER" << std::endl;
    std::cout << "Made By Kaan Taha Köken & Ege Seçkin" << std::endl << std::endl;;
    
    
    //Selects the correct menu option according to input comes from user
    do {
        menuOption = assembler.menu();
        switch (menuOption) {
            //Takes input manually from terminal
            case '1': {
                int numbOfInst;
                std::cout << "\nHow many lines of code will be entered" << std::endl;
                std::cout << "Answer: ";
                std::cin >> numbOfInst;
                std::string temp;
                while(numbOfInst > 0 && std::getline(std::cin, temp)) {
                    if (temp.compare("")) {
                        instructionSet.push_back(temp);
                        numbOfInst--;
                    }
                }
                break;
            }
            //Takes input from a file
            case '2':
                std::cout << "\nEnter a file name: ";
                std::cin >> fileName;
                instructionSet = assembler.readFile(fileName);
                break;
            //Closes assembler
            case '3':
                std::cout << "\nGood Bye!!!" << std::endl;
                break;
            //If wrong input is entered by user it displays an error message
            default:
                std::cout << "\nWrong Option!!!" << std::endl;
                break;
        }
        //converts the pseudo instructions to equivalent versions
        instructionSet = pseudo.convertInstructions(instructionSet);
        //Finds out where label starts from
        labelsAndPc = assembler.labelAndPcCounter(instructionSet);
        std::vector<std::string>::iterator it = instructionSet.begin();
        int size = 0;

        while (size < instructionSet.size() && it != instructionSet.end()) {
            instructions.push_back(syntax.checkSyntax(*it));
            size++;
            it++;
        }

        std::vector<std::vector<std::string>>::iterator instIterator = instructions.begin();
        std::vector<int>::iterator pcIterator = labelsAndPc.second.begin();
       
        while (instIterator != instructions.end()) {
            std::string type;
            if (instIterator->at(0)[instIterator->at(0).size() - 1] == ':')
                type = instIterator->at(1);
            else
                type = instIterator->at(0);

            result.push_back(converter.DecToBin(syntax.checkInstType(type), *instIterator, labelsAndPc.first, *pcIterator));
            instIterator++;
            pcIterator++;
        }
        /**If user selects option 1 then output prints on terminal 
        *however if user selects option 2 the result prints on output file
        **/
        result = converter.BinToHex(result);
        if (menuOption == '1')
            assembler.displayInstructions(result);
        else if (menuOption == '2')
            assembler.writeFile(result);
        
        result.clear();
        labelsAndPc.first.clear();
        labelsAndPc.second.clear();
        instructions.clear();
        instructionSet.clear();
    } while (menuOption != '3');
    
    return 0;
}
