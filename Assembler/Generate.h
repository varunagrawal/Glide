/*
    Generate.h Header file.
    Contains necessary functions to calulate opcodes for Assembly statements.
    Performs lookup in opcodeTab table to find appropriate opcode for a mnemonic.

    Code also handles Mnemonics where Data and Addresses are involved.

    Author: Varun Agrawal.
*/


#ifndef GENERATE_H_INCLUDED
#define GENERATE_H_INCLUDED

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<iomanip>
#include<algorithm>


#include "2_Pass_Assembler.h"


void errMsg(int line){
    std::cout << "Unrecognized Syntax at line:" << line << std::endl;
    exit(1);
}


std::string opcodeTab[16][16] = {
    "NOP",      "LXI B D16",  "STAX B",   "INX B",   "INR B",   "DCR B",   "MVI B D8", "RLC", "DSUB",    "DAD B",  "LDAX B",   "DCX B",  "INR C", "DCR C", "MVI C D8", "RRC",
    "ARHL",     "LXI D D16",  "STAX D",   "INX D",   "INR D",   "DCR D",   "MVI D D8", "RAL", "RDEL",    "DAD D",  "LDAX D",   "DCX D",  "INR E", "DCR E", "MVI E D8", "RAR",
    "RIM",      "LXI H D16",  "SHLD D16", "INX H",   "INR H",   "DCR H",   "MVI H D8", "DAA", "LDHI D8", "DAD H",  "LHLD D16", "DCX H",  "INR L", "DCR L", "MVI L D8", "CMA",
    "SIM",      "LXI SP D16", "STA D16",  "INX SP",  "INR M",   "DCR M",   "MVI M D8", "STC", "LDSI D8", "DAD SP", "LDA D16",  "DCX SP", "INR A", "DCR A", "MVI A D8", "CMC",
    "MOV B B",  "MOV B C",    "MOV B D",  "MOV B E", "MOV B H", "MOV B L", "MOV B M", "MOV B A", "MOV C B", "MOV C C", "MOV C D", "MOV C E", "MOV C H", "MOV C L", "MOV C M", "MOV C A",
    "MOV D B",  "MOV D C",    "MOV D D",  "MOV D E", "MOV D H", "MOV D L", "MOV D M", "MOV D A", "MOV E B", "MOV E C", "MOV E D", "MOV E E", "MOV E H", "MOV E L", "MOV E M", "MOV E A",
    "MOV H B",  "MOV H C",    "MOV H D",  "MOV H E", "MOV H H", "MOV H L", "MOV H M", "MOV H A", "MOV L B", "MOV L C", "MOV L D", "MOV L E", "MOV L H", "MOV L L", "MOV L M", "MOV L A",
    "MOV M B",  "MOV M C",    "MOV M D",  "MOV M E", "MOV M H", "MOV M L", "HLT",     "MOV M A", "MOV A B", "MOV A C", "MOV A D", "MOV A E", "MOV A H", "MOV A L", "MOV A M", "MOV A A",
    "ADD B",    "ADD C", "ADD D", "ADD E", "ADD H", "ADD L", "ADD M", "ADD A", "ADC B", "ADC C", "ADC D", "ADC E", "ADC H", "ADC L", "ADC M", "ADC A",
    "SUB B",    "SUB C", "SUB D", "SUB E", "SUB H", "SUB L", "SUB M", "SUB A", "SBB B", "SBB C", "SBB D", "SBB E", "SBB H", "SBB L", "SBB M", "SBB A",
    "ANA B",    "ANA C", "ANA D", "ANA E", "ANA H", "ANA L", "ANA M", "ANA A", "XRA B", "XRA C", "XRA D", "XRA E", "XRA H", "XRA L", "XRA M", "XRA A",
    "ORA B",    "ORA C", "ORA D", "ORA E", "ORA H", "ORA L", "ORA M", "ORA A", "CMP B", "CMP C", "CMP D", "CMP E", "CMP H", "CMP L", "CMP M", "CMP A",
    "RNZ",      "POP B",    "JNZ D16", "JMP D16",   "CNZ D16", "PUSH B",   "ADI D8", "RST 0", "RZ",  "RET",  "JZ D16",  "RSTV",  "CZ D16",  "CALL D16", "ACI D8", "RST 1",
    "RNC",      "POP D",    "JNC D16", "OUT D8",    "CNC D16", "PUSH D",   "SUI D8", "RST 2", "RC",  "SHLX", "JC D16",  "IN D8", "CC D16",  "JNK D16",  "SBI D8", "RST 3",
    "RPO",      "POP H",    "JPO D16", "XTHL",      "CPO D16", "PUSH H",   "ANI D8", "RST 4", "RPE", "PCHL", "JPE D16", "XCHG",  "CPE D16", "LHLX",     "XRI D8", "RST 5",
    "RP",       "POP PSW",  "JP D16",  "DI",        "CP D16",  "PUSH PSW", "ORI D8", "RST 6", "RM",  "SPHL", "JM D16",  "EI",    "CM D16",  "JK D16",   "CPI D8", "RST 7"

};


std::string hexify(int x){    //Generates Hex values string for integer

    switch(x){
        case 0:
            return "0";
            break;
        case 1:
            return "1";
            break;
        case 2:
            return "2";
            break;
        case 3:
            return "3";
            break;
        case 4:
            return "4";
            break;
        case 5:
            return "5";
            break;
        case 6:
            return "6";
            break;
        case 7:
            return "7";
            break;
        case 8:
            return "8";
            break;
        case 9:
            return "9";
            break;
        case 10:
            return "A";
            break;
        case 11:
            return "B";
            break;
        case 12:
            return "C";
            break;
        case 13:
            return "D";
            break;
        case 14:
            return "E";
            break;
        case 15:
            return "F";
            break;

    }
}


std::string getHex(int num){
    std::stringstream ss;
    ss.clear();

    ss << std::setfill('0') << std::setw(4) << std::hex << num;

    std::string s = ss.str();

    //std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    for(int i=0; i<s.size(); i++){
        s[i] = std::toupper(s[i]);
    }

    return s;
}



std::vector<std::string> machineCode( std::vector<std::string> vs){          //Main function to generate the opcodes for the mnemonics.

    int i = 0;
    std::string m = "", d8 = "D8", d16 = "D16", symbol;
    bool b16 = false, b8 = false;;

    std::vector<std::string> mach;

    mach.clear();

    i = 0;                                      //Keeps track of whether there is a label or no.

    if(checkSymbol(vs[i])){
        i = 1;                                  //This means that there is a label in the code
    }else if(!checkMnem(vs[i])){
        printf("Invalid Symbol\n");
    }


// These are mnemonics that have 16 bit addresses or 8 bit data respectively.
// LXI SHLD STA LDA (JMP JNZ JNC JPO JP JZ JC JPE JM JNK JK) (CALL CNZ CNC CPO CP CZ CC CPE CM)
// OUT IN ADI ACI SUI SBI ANI ORI XRI CPI LDHI LDSI  MVI

    if(vs[i] == "LXI" || vs[i] == "SHLD" || vs[i] == "STA" || vs[i] == "LDA" || vs[i] == "JMP" || vs[i] == "JNZ" || vs[i] == "JNC" || vs[i] == "JPO" || vs[i] == "JP" || vs[i] == "JZ" || vs[i] == "JC" || vs[i] == "JPE" || vs[i] == "JM" || vs[i] == "JNK" || vs[i] == "JK" || vs[i] == "CALL" || vs[i] == "CNZ" || vs[i] == "CNC" || vs[i] == "CPO" || vs[i] == "CP" || vs[i] == "CZ" || vs[i] == "CC" || vs[i] == "CPE" || vs[i] == "CM"){

        for(int j=i; j<vs.size()-1; j++){
            m = m + vs[j] + " ";
        }
        m += d16;
        b16 = true;

    }else if(vs[i] == "OUT" || vs[i] == "IN" || vs[i] == "ADI" || vs[i] == "ACI" || vs[i] == "SUI" || vs[i] == "SBI" || vs[i] == "ANI" || vs[i] == "ORI" || vs[i] == "XRI" || vs[i] == "CPI" || vs[i] == "LDHI" || vs[i] == "LDSI" || vs[i] == "MVI"){
        for(int j=i; j<vs.size()-1; j++){
            m = m + vs[j] + " ";
        }
        m += d8;
        b8 = true;

    }else{
            for(int j=i; j<vs.size(); j++){
                m = m + vs[j] + " ";
            }
            m = m.substr(0, m.length()-1);
    }


    bool found = false;
    for(int j=0; j<16 ; j++){
        for(int k=0; k<16; k++){
            if(m == opcodeTab[j][k]){
                std::string s1 = hexify(j);
                std::string s2 = hexify(k);

                mach.push_back(s1+s2);

                found = true;
                break;
            }

            if(found)
                break;
        }
    }

    if(!found){
        std::cout << "Error in Source code! Unidentified synatax" << std::endl;
    }


    if(b16){

        if(checkSymbol( vs[vs.size()-1] )){

            mach.push_back( "" );
            mach.push_back( "" );

        }else if( checkHex(vs[vs.size()-1]) ){
            mach.push_back( vs[vs.size()-1].substr(2, 2) );
            mach.push_back( vs[vs.size()-1].substr(0, 2) );
        }else{
            std::cout << "Error in source!" << std::endl;
            exit(1);
        }

    }else if(b8){

        if( checkHex(vs[vs.size()-1]) ){
            mach.push_back( vs[vs.size()-1] );
        }else{
            std::cout << "Error in source!" << std::endl;
            exit(1);
        }

    }


    return mach;

}


std::vector< std::vector<std::string> > createMachineCode( std::vector< std::vector<std::string> > assem ){

    std::vector< std::vector<std::string> > machine;
    machine.clear();

    for(int i=0; i<assem.size(); i++){
        machine.push_back( machineCode(assem[i]) );
    }

    for(int x=0; x<assem.size(); x++){
        if( checkSymbol(assem[x][assem[x].size()-1]) ){
            int addr = getSymAddr(assem[x][assem[x].size()-1]);

            int count = 1;

                    for(int y=0; y<addr; y++){
                            count += machine[y].size();
                    }

                    std::string offset;
                    offset = getHex(count);

                    machine[x][machine[x].size()-2] = offset.substr(2, 2);
                    machine[x][machine[x].size()-1] = offset.substr(0, 2);

        }
    }

    return machine;

}

#endif // GENERATE_H_INCLUDED
