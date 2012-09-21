#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>

#include "lex.h"
 
#define is_number(ch) 	(ch >= '0' && ch <= '9')
#define is_char(ch) 	((ch >= 'a' && ch <= 'z') || (ch >= 'A' || ch <= 'Z'))

char *file;
ifstream *f;


void skip_blanks(){
	while(f.peek() == ' ') f.get();

	return;
}
int get_number()

void lexA(){

	f.open(file, ifstream::in);
	
	skip_blanks();
	
	char peek = f.peek();

	if( is_number(peek) ){
		get_number(peek);	
	}else if( is_char(peek) ){
		check_keyword(peek);
	}else if( is_special(peek) ){
		handle_special(peek);
	}else{
		get_identifier();
	}
	
}

int main(int argc, char** argv)
{

	if(argc < 2 || argc > 2){ 
		printf("Incorrect number of arguments\n");	
		exit(1);	
	}	

	file = argv[1];	


	string token;
	

	return 0;
}

