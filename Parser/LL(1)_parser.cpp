#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<cmath>
#include<stack>

typedef long long LL;

#define FOR(i, a, b) 	for(int i=a; i<b; i++)
#define REP(i, a) 	FOR(i, 0, a)
#define RFOR(i, a, b) 	for(int i=a-1; i>=b; i--)
#define RREP(i, a)	RFOR(i, a, 0)
#define PB(x)		push_back(x)
#define PP()		pop_back()
#define SZ		size()
#define LEN		length()

using namespace std;

#define NO_NT 5
#define NO_TERM 6

vector< vector< vector<string> > > parse_table;
stack<string> st;
string term[NO_TERM] = {"id", "+", "*", "(", ")", "$"};
string NT[NO_NT] = {"E", "E'", "T", "T'", "F"};


void init(){
    parse_table.clear();

    parse_table.resize(NO_NT);
    REP(i, NO_NT){
        parse_table[i].resize(NO_TERM);
    }

    parse_table[0][0].push_back("T");
    parse_table[0][0].push_back("E'");

    parse_table[0][3].push_back("T");
    parse_table[0][3].push_back("E'");

    parse_table[1][1].push_back("+");
    parse_table[1][1].push_back("T");
    parse_table[1][1].push_back("E'");

    parse_table[1][4].push_back("");

    parse_table[1][5].push_back("");

    parse_table[2][0].push_back("F");
    parse_table[2][0].push_back("T'");

    parse_table[2][3].push_back("F");
    parse_table[2][3].push_back("T'");

    parse_table[3][1].push_back("");

    parse_table[3][2].push_back("*");
    parse_table[3][2].push_back("F");
    parse_table[3][2].push_back("T'");

    parse_table[3][4].push_back("");

    parse_table[3][5].push_back("");

    parse_table[4][0].push_back("id");

    parse_table[4][3].push_back("(");
    parse_table[4][3].push_back("E");
    parse_table[4][3].push_back(")");

}


string getTok(string in, int it){
    string str;
    bool found = false;

    REP(i, in.length()){
            str = in.substr(it, i);
            REP(j, NO_TERM){
                if(str == term[j]){
                    return str;
                }
            }

    }

    cout << "Invalid Input!" << endl;

    exit(1);

}

int getIdent(vector<string> vs, int ind){

    REP(i, NO_TERM){
        if(vs[ind] == term[i])
            return i;
    }

}


int getNT(string s){
    REP(i, NO_NT){
        if(s == NT[i])
            return i;
    }

    return -1;

}



string parse(vector<string> input, stack<string> &st){

    int k, l;
    int it = 0;

    //cout << st.top() << " --> ";

    while(st.top() != "$"){

        if(st.top() == ""){
            st.pop();
        }else if(st.top() == input[it]){
            st.pop();

            if(input[it] != "$"){
                it++;
            }
        }

        k = getNT(st.top());
        l = getIdent(input, it);

        if(k < 0) continue;

        cout << st.top() << " --> ";

        if(parse_table[k][l].size() == 0){
            return "Rejected";

        }else{

            st.pop();

            RREP(i, parse_table[k][l].size()){
                st.push(parse_table[k][l][i]);
            }

        }

        REP(i, parse_table[k][l].size()){
            cout << parse_table[k][l][i] << " ";
        }
        cout << endl;

    }

    if(input[it] == "$")
        return "Accepted";
    else
        return "Rejected";
}



int main()
{
    init();

    cout << "Initialized" <<endl;

    string in;
    cin >> in;

    vector<string> input;
    input.clear();

    int cnt = 0;
    for(int i=0; i<in.length(); i++){
        input.push_back(getTok(in, i));
        i += input[cnt].length()-1;
        cnt++;
    }

    input.push_back("$");
    st.push("$");
    st.push("E");

    string result = parse(input, st);

    cout << result << endl;
	return 0;
}
