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
