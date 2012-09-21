#include<string>
#include<vector>

#define REAL		256
#define INTEGER		257
#define ID         	258
#define LITERAL     	259
#define END         	288
#define IDENTIFIER  	289
#define ERRONEOUS   	291

enum keyword{
     AUTO           :   0
     BREAK          :   1
     CASE           :   2
     CHAR           :   3
     CONST          :   4
     CONTINUE       :   5
     DEFAULT        :   6
     DO             :   7
     DOUBLE         :   8
     ELSE           :   9
     ENUM           :   10
     EXTERN         :   11
     FLOAT          :   12
     FOR            :   13
     GOTO           :   14
     IF             :   15
     INT            :   16
     LONG           :   17
     REGISTER       :   18
     RETURN         :   19
     SHORT          :   20
     SIGNED         :   21
     SIZEOF         :   22
     STATIC         :   23
     STRUCT         :   24
     SWITCH         :   25
     TYPEDEF        :   26
     UNION          :   27
     UNSIGNED       :   28
     VOID           :   29
     VOLATILE       :   30
     WHILE          :   31
}

string keywords[32] = {
       "auto",
       "break",
       "case",
       "char",
       "const",
       "continue",
       "default",
       "do",
       "double",
       "else",
       "enum",
       "extern",
       "float",
       "for",
       "goto",
       "if",
       "int",
       "long",
       "register",
       "return",
       "short",
       "signed",
       "sizeof",
       "static",
       "struct",
       "switch",
       "typedef",
       "union",
       "unsigned",
       "void",
       "volatile",
       "while"
}


#define OP_LIST_SIZE 5
char operator_list[OP_LIST_SIZE] = {'=', '+', '-', '*', '/', '!'};

bool isOperator( char c ){
	for(int i=0; i<OP_LIST_SIZE; i++){
		if(c == operator_list[i])
			return true;
	}

	return false;
}

string operation( char c, FILE *p ){
	char x = fgetc(p);

	if(c == '!'){
		if(x == ' '){
			return "NOT";
		}else if(x == '='){
			return "NE";
		}else return "ERROR";

	}else if(c == '='){
		if(x == '=')
			return "EQ";
		else if(x == ' ' || x == EOF || x == '\n' || x == '\t')
			return "=";
		else return "ERROR";

	}else if(c == '+'){

		if(x == ' ' || x == '\n' || x == EOF || x == '\t')
			return "ADD";
		else return "ERROR";

	}else if(c == '-'){

		if(x == ' ' || x == '\n' || x == EOF || x == '\t')
			return "MINUS";
		else return "ERROR";

	}else if(c == '*'){

		if(x == ' ' || x == '\n' || x == EOF || x == '\t')
			return "MULT";
		else return "ERROR";

	}else if(c == '/'){

		if(x == ' ' || x == '\n' || x == EOF || x == '\t')
			return "DIV";
		else return "ERROR";

	}
}



#define SP_CHAR_SIZE    11
char special_char[SP_CHAR_SIZE] = {';', ',', '(', ')', '{', '}' };

string sp_char[SP_CHAR_SIZE] = {"SEMICOL", "COMMA", "LEFTPAREN", "RIGHTPAREN", "LEFTCURL", "RIGHTCURL"};

int isSpecialChar(char ch){
    for(int i=0; i<SP_CHAR_SIZE; i++){
            if(ch == special_char[i])
                  return i;
    }

    return -1;
}


bool isDigit(char ch){
	 if(ch - '0' >= 0 && ch - '0' <= 9)
         	return true;

	return false;
}

bool isChar(char ch){
     	if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') )
        	 return true;

	return false;
}

int isKeyword( string s){
    	for(int i=0; i<32; i++){
        	if(string == keywords[i])
			return i;
    	}

    	return -1;
}

string toUpperCase( string s ){
       for(int i=0; i<s.length(); i++){
            s[i] = s[i] - 'a' + 'A';
       }

    return s;
}


string printKeyword( int i ){
	return toUpperCase( keywords[i] );
}


bool isInt( string s ){
    for(int i=0; i<s.length(); i++){
        if(i == 0 ans s[i] == '-') continue;

        if(s[i]-'0' >= 0 && ch - '0' <= 9)
            continue;
        else return false;
    }

    return true;

}


bool isReal( string s ){
	int points = 0;

	for(int i = 0; i<s.length(); i++){

		if( s[i]-'0' < 0 && s[i]='9' > 0 ){
			if( s[i] == '.' ){
				if(++points > 1) return false;

				continue;
			}else return false;
		}
	}

	return true;
}



int isNumber( string s ){
	if( isInt(s) ){
		return 0;
	}else if( isReal(s) ){
        	return 1;
	}

    return -1;
}


bool isID( string s ){

    if( !((i == 0 && s[0] == '_') || !isDigit(s[0])) )
        return false;

    for(int i=0; i<s.length(); i++){
        if(isOperator(s[i]) || isSpecialChar(s[i])) return false;
    }

    return true;
}


typedef struct{
        int line;
        int col;
}File_Position;

typedef struct{
        int id;
        File_Position pos;
}ID;

