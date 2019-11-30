#pragma once

class BitConverter {
    private:
        int jTypeAreaLen;
        int rTypeAreaLen[5];
        int iTypeAreaLen[3];
    
    public:
        BitConverter();
        ~BitConverter();
        
        void DecToHex();
        void DecToBin();
        void BinToHex();
        void BinToDec();
        void HexToDec();
        void HexToBin();
}