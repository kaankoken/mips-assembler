#include "BitConverter.h"

BitConverter::BitConverter() {}
BitConverter::~BitConverter() {}

//Converts decimal to binary
std::string BitConverter::DecToBin(std::string instType, std::vector<std::string>inst,
  std::map<std::string, int> label, int pcCounter) {
    std::string result;
    int rs = 0, rt = 0, rd = 0, shamt = 0, func = 0, imm = 0;

    //Checks whether the given instruction is Rtype or not
    if (std::strcmp(instType.c_str(), "RType") == 0) {
        std::tuple instructions = RType::findInst(inst.at(0));
        
        std::string instOrder = std::get<2>(instructions);
       
        //Converts opcode into binary
        result.append(BitConverter::bin(6, std::get<0>(instructions)));
        
        //Converts registers into binary
        std::vector<std::string>::iterator it = inst.begin() + 1;
        while (!instOrder.empty()) {
            std::string temp = splitOrder(&instOrder);
            if (std::strcmp(temp.c_str(), "rd") == 0)
                rd = Registers::findInst(*it);
            else if (std::strcmp(temp.c_str(), "rs") == 0)
                rs = Registers::findInst(*it);
            else if (std::strcmp(temp.c_str(), "rt") == 0)
                rt = Registers::findInst(*it);
            else {
                if (it->find("0x") == std::string::npos)
                    shamt = std::stoi(*it, 0, 10);
                else {
                    size_t pos = it->find("0x");
                    it->erase(it->begin(), it->begin() + pos + 2);
                    shamt = std::stoi(*it, 0, 16);
                }
            }
            it++;
        }

        if (shamt > 31) {
            std::cout << "Shamt value is bigger than 5 bits" << std::endl;
            exit(1);
        }
        if (shamt < 0) {
            std::cout << "Shamt value cannot be negative" << std::endl;
            exit(1);
        }

        //func
        func = std::get<1>(instructions);
        //Adds finished conversions into result
        result.append(BitConverter::bin(5, rs));
        result.append(BitConverter::bin(5, rt));
        result.append(BitConverter::bin(5, rd));
        result.append(BitConverter::bin(5, shamt));
        result.append(BitConverter::bin(6, func));
    }
    //Checks whether the given instruciton is Itype or not
    else if (std::strcmp(instType.c_str(), "IType") == 0) {
        std::tuple instructions = IType::findInst(inst.at(0));
        std::string instOrder = std::get<1>(instructions);

        //Converts opcode into binary
        result.append(BitConverter::bin(6, std::get<0>(instructions)));
        
        //Converts registers into binary
        std::vector<std::string>::iterator it = inst.begin() + 1;
        std::map<std::string, int>::iterator mapIterator;
        while (!instOrder.empty()) {
            std::string temp = splitOrder(&instOrder);
            if (std::strcmp(temp.c_str(), "rs") == 0)
                rs = Registers::findInst(*it);
            else if (std::strcmp(temp.c_str(), "rt") == 0)
                rt = Registers::findInst(*it);
            else {
                if (label.size() > 0) {
                    if (label.find(*it + ":") != label.end()) {
                        mapIterator = label.find(*it + ":");
                        int diff = mapIterator->second - pcCounter - 4;
                        diff /= 4;
                        *it = std::to_string(diff);
                    }
                }
                if (it->find("0x") == std::string::npos)
                    imm = std::stoi(*it, 0, 10);
                else {
                    size_t pos = it->find("0x");
                    it->erase(it->begin(), it->begin() + pos + 2);
                    imm = std::stoi(*it, 0, 16);
                }
            }
            it++;
        }

        if (imm > 32767 || imm < -32768) {
            std::cout << "Immediate value is bigger than 16 bits" << std::endl;
            exit(1);
        }

        //Adds finished conversions into result
        result.append(BitConverter::bin(5, rs));
        result.append(BitConverter::bin(5, rt));
        result.append(BitConverter::bin(16, imm));
    }

    //If the given instruction is not R-Type or I-type then it is J-Type
    else {
        std::tuple instructions = JType::findInst(inst.at(0));
        //Converts opcode into binary
        result.append(BitConverter::bin(6, std::get<0>(instructions)));

        std::vector<std::string>::iterator it = inst.begin() + 1;

        //When it finds ':' inside given instrucitons it jumps to that label and converts that instruciton
        std::map<std::string, int>::iterator mapIterator = label.find(*it + ":");
        std::string addr = BitConverter::bin(32, mapIterator->second);
        
        addr = addr.substr(4, 26);
        result.append(addr);

    }
    return result;
}

//Converts integer to binary
std::string BitConverter::bin(int size, int inst) {
    unsigned i;
    int temp = inst; 
    std::string result;
    if (inst < 0)
        temp *= -1;

    for (i = 1 << size - 1; i > 0; i = i / 2) 
        (temp & i)? result.append("1") : result.append("0");
    
    if (inst < 0) {
        for (i = result.length() - 1; i >= 0; i--)
            if (result[i] == '1')
                break;
        for (int k = i - 1; k >= 0; k--) {
            if (result[k] == '1') 
               result[k] = '0'; 
            else
                result[k] = '1'; 
        }
    }
    return result;
} 

//split order for rs rt rd instructions
std::string BitConverter::splitOrder(std::string *instOrder) {
    size_t pos = 0;
    std::string token, delimeter = " ";
    
    pos = instOrder->find(delimeter);

    if (instOrder->find(delimeter) != std::string::npos)
        token = instOrder->substr(0, pos);
    else {
        token.assign(*instOrder);
        instOrder->erase(0, instOrder->length());
    }
    instOrder->erase(0, pos + 1);
    return token;
}

//Converts from binary to hexadecimal
std::vector<std::string> BitConverter::BinToHex(std::vector<std::string> binInst) {
    std::map<std::string, char> lookUpTable;
    std::vector<std::string>::iterator it = binInst.begin();
    std::vector<std::string> result;

    lookUpTable.insert({"0000", '0'});
    lookUpTable.insert({"0001", '1'});
    lookUpTable.insert({"0010", '2'});
    lookUpTable.insert({"0011", '3'});
    lookUpTable.insert({"0100", '4'});
    lookUpTable.insert({"0101", '5'});
    lookUpTable.insert({"0110", '6'});
    lookUpTable.insert({"0111", '7'});
    lookUpTable.insert({"1000", '8'});
    lookUpTable.insert({"1001", '9'});
    lookUpTable.insert({"1010", 'A'});
    lookUpTable.insert({"1011", 'B'});
    lookUpTable.insert({"1100", 'C'});
    lookUpTable.insert({"1101", 'D'});
    lookUpTable.insert({"1110", 'E'});
    lookUpTable.insert({"1111", 'F'});
    
    while (it != binInst.end()) {
        int splitter = 0;
        std::string key;
        std::string temp = "0x";
        do {
            key = it->substr(splitter, 4);
            if (splitter < 32) {
                std::map<std::string, char>::iterator mapIterator = lookUpTable.find(key);
                temp = temp + mapIterator->second;
            }
            splitter += 4;
        } while (key.compare(""));
        result.push_back(temp);
        it++;
    }

    return result;
}