#include<cstdio>
#include<cstdlib>
#include<iostream>

#include "lex.h"

FILE *fp, *out ;
char l;
int ind;
string lexeme = 'l';

void skip_blanks(){
    while( (l = fgetc(fp)) != NULL ){
        if( l == EOF )
            return END;

        if( l == ' ' || l == '\n' || l == '\t')
            continue;
        else{
            fseek(fp, -1, SEEK_CUR);
            return;
        }
    }
}

string Lex(){
       if( skip_blanks() == END ){
            fclose(fp);
            fclose(out);
            exit(0);
        }

        l = fgetc(fp);

        if( (ind = isSpecialChar(l)) > 0){
            fprintf(out, "%s ", sp_char[ind]);

        }else if(isDigit(l)){
		lexeme.assign(1, l);

		while(true){
			l = fgetc(fp);
			if( l == ' ' || l == EOF || l == '\n' || l == '\t') break;
			lexeme.append(1, l);
		}

		if(isOperator(l)){
			operation(l, fp);
		}

		if( isNumber(lexeme) < 0 ){
			fprintf(out, "%s ", "ERROR");
		}
		else{
			fprintf(out, "%s ", lexeme);
		}

	}else if(isChar(l)){
		lexeme.assign(1, l);

        while(true){
			l = fgetc(fp);
			if( l == ' ' || l == EOF || l == '\n' || l == '\t') break;
			lexeme.append(1, l);
		}

		if( (ind = isKeyword(lexeme)) > 0 ){
            fprintf(out, "%s", toUpperCase(keywords[ind]) );
		}else
	}
}


int main( int argc, char** argv ){

    *fp = fopen(argv[1], "r");
    *out = fopen("lex.txt", "w+");



}
