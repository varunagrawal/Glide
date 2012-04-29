/*
    Header file for 2 Pass Assembler.
    Contains Generic helper functions for use throughout the program.

    Author: Varun Agrawal.
*/

#ifndef _PASS_ASSEMBLER_INCLUDED
#define _PASS_ASSEMBLER_INCLUDED



#include<vector>
#include<string>


#define OPS 80
#define REGS 10

std::string reg[REGS]   = { "A", "B", "C", "D", "E", "H", "L", "M", "SP", "PSW"};

std::string mnem[OPS]   = { "ACI", "ADC", "ADD", "ADI", "ANA", "ANI", "CALL", "CC", "CM", "CMA", "CMC", "CMP", "CNC",
                            "CNZ", "CP", "CPE", "CPI", "CPO", "CZ", "DAA", "DAD", "DCR", "DCX", "DI", "EI", "HLT", "IN",
                            "INR", "INX", "JMP", "JC", "JM", "JNC", "JNZ", "JP", "JPE", "JPO", "JZ", "LDA", "LDAX", "LHLD",
                            "LXI", "MOV", "MVI", "NOP", "ORA", "ORI", "OUT", "PCHL", "POP", "PUSH", "RAL", "RAR", "RET",
                            "RC", "RIM", "RM", "RNC", "RNZ", "RP", "RPE", "RPO", "RZ", "RLC", "RRC", "RST", "SBB", "SBI",
                            "SHLD", "SIM", "SPHL", "STA", "STAX", "STC", "SUB", "SUI", "XCHG", "XRA", "XRI", "XTHL"};


char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

typedef struct SYMBOL{
    std::string symbol;
    int address;
}Symbol;

std::vector<Symbol> symtab;



bool checkHex(std::string n){

    bool hexa = true;

    for(int i=0; i<n.length(); i++){
        for(int j=0; j < 16; j++){
            //std::cout << n[i] << " " << hex[j] << std::endl;
            if(n[i] == hex[j]){
                hexa = true;
                break;
            }else
                hexa = false;
        }

        if(!hexa)
            break;
    }

    return hexa;
}



bool checkReg(std::string s){
    for(int i=0; i<REGS; i++){
        if(s == reg[i])
            return true;
    }

    return false;
}


/********Function To check Mnemonics***********/
bool checkMnem(std::string m){

    if(m == ":")
        return true;

    for(int i=0; i < OPS; i++){
        if(m == mnem[i])
            return true;        //Return true if word is a mnemonic stored in mnem
    }

    return false;               //return false if word is not a mnemonic
}


/*******************/



/*********Function to check for user symbols and to generate the address of the symbol**********/
bool checkSymbol(std::string s){
    for(int i=0; i<symtab.size(); i++){
        if(s == symtab[i].symbol){
            return true;
        }
    }

    return false;                 //Return false if word is not already in symbol table
}

int getSymAddr(std::string s){

    for(int i=0; i<symtab.size(); i++){
        if(s == symtab[i].symbol){
            return symtab[i].address;

        }
    }

    return -1;                  //Return -1 if word does not exist in symbol table
}
/*******************/



/*********Function to add entry to Symbol Table**********/
void addToSymTab(std::string s, int lineNo){

    if(s[s.length()-1] == ':')
        s = s.substr(0, s.length()-2);

    Symbol t;

    t.symbol = s;
    t.address = lineNo;

    symtab.push_back(t);

}
/*******************/


#endif // 2_PASS_ASSEMBLER_INCLUDED
