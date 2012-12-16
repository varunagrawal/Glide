/***************************
	Author: Varun Agrawal
	Prog: Encode.cpp

	This program reads a text file consisting of the mnemonics 
	and prints it out in the specified file so that it can be hardcoded
	as an array in the Assembler program.
***************************/

#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char** argv)
{
    fstream in, out;
    in.open(argv[1], fstream::in);
    out.open(argv[2], fstream::out);

    string s;

    while(true){

        if(in.eof())
            break;

        in >> s;

        out << "\"" << s << "\"" << ", ";

    }

    return 0;

}
