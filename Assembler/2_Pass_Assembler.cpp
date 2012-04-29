/*
*    2 Pass Assembler Program.
*    Creates Symbol table on the first pass.
*    Generates 8085 based Machine code on Second Pass.
*
*    Author: Varun Agrawal
*    Date:23/04/2012
*
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<string>
#include<fstream>

#include "2_Pass_Assembler.h"
#include "Generate.h"


using namespace std;


ifstream in;
ofstream out;



vector<string> tokenize(string line){              //Tokenizes the words in a line of Assembly code

    vector<string> vs;
    vs.clear();

    int start = 0;

    for(int i=0; i<line.length(); i++){

        while( line[i] == ' ' || line[i] == ',' || line[i] == ':' ){
                i++;
        }
        start = i;

        while( line[i] != ' ' && line[i] != ',' && line[i] != ':' ){
                i++;
                if(i >= line.length()){
                    break;
                }
        }

        vs.push_back( line.substr(start, i-start) );

    }

    return vs;

}



vector< vector<string> > firstPass(){           // 1st Pass of Assembler

    int lineNo = 0;
    string line;
    vector<string> vs;

    vector< vector<string> > assembly;
    assembly.clear();

    while(true){

        if(in.eof())
            break;

        getline(in, line);

        vs = tokenize(line);
        assembly.push_back(vs);

        for(int i=0; i < vs.size(); i++){
            if( checkHex(vs[i]) )
                continue;

            if(checkMnem(vs[i]))
                continue;

            if(checkReg(vs[i]))
                continue;

            if(checkSymbol(vs[i]))
                continue;

            if(i == 0){
                addToSymTab(vs[i], lineNo);
                continue;
            }

        }

        lineNo++ ;


    }

    assembly.pop_back();

    cout << "1st Pass done" << endl;


    return assembly;

}



vector< vector<string> > secondPass(vector< vector<string> > assembly){             // 2nd Pass of Assembler

    vector< vector<string> > machine;
    machine.clear();

    machine = createMachineCode( assembly );

    cout << "2nd Pass Done" << endl;

    return machine;
}



void tester(){
    string s = "";
    int line = 1;
    cout << "This is the tester loop.\nInput Assembly lines and it will generate equivalent Machine code.\nType \"exit\" to quit.\n" << endl;

    vector<string> assembly, machine;
    vector<string> vs;

    while(s != "exit"){
        getline(cin, s);

        vs = tokenize(s);
        machine = machineCode(vs);

        for(int i=0; i<machine.size(); i++){
            cout << machine[i] << endl;
        }

        line++;
    }

}



int main(int argc, char** argv)
{

    if(argc < 3){
        printf("Incorrect Number of Parameters\n");
        return 0;
    }

    vector< vector<string> > assembly, machine;

    in.open(argv[1], ifstream::in);
    out.open(argv[2], ifstream::out);


    assembly = firstPass();
    machine = secondPass(assembly);


    for(long i=0; i<machine.size(); i++){
        for(long j=0; j<machine[i].size(); j++){
            out << machine[i][j] << endl;
        }
    }

    cout << "Machine Code generated!" << endl;

    in.close();
    out.close();


 //  tester();         // Comment rest of main and uncomment this function to get a REPL for Assembly code!

	return 0;
}
