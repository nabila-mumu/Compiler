%option noyywrap

%{
#include<bits/stdc++.h>
#include "2005050_symbolTable.cpp"

using namespace std; 

int line_count=1;

ofstream logout;
ofstream tokenout;
SymbolTable* s_table;

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n

%%

{NEWLINE} {line_count++;}

"if"	{
            tokenout<<"<IF, "<<yytext<<">"<<endl;
            logout<<"Line no "<<line_count<<": TOKEN <IF> Lexeme "<<yytext<<" found\n";
			//bool x= s_table->insert_into_st("IF","if");
			//if(x==true) s_table->print_all_scopeTable("log.txt"); 
		}
		
"else"	{
            tokenout<<"<ELSE, "<<yytext<<">"<<endl;
            logout<<"Line no "<<line_count<<": TOKEN <ELSE> Lexeme "<<yytext<<" found\n";
			//bool x= s_table->insert_into_st("ELSE","else");
			//if(x==true) s_table->print_all_scopeTable("log.txt"); 
		}

"+"|"-"		{
            tokenout<<"<ADDOP, "<<yytext<<">"<<endl;
            logout<<"Line no "<<line_count<<": TOKEN <ADDOP> Lexeme "<<yytext<<" found\n";
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}
		
{DIGIT}+ 	{
                tokenout<<"<CONST_INT, "<<yytext<<">"<<endl;
                logout<<"Line no "<<line_count<<": TOKEN <CONST_INT> Lexeme "<<yytext<<" found\n";
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
			

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		cout<<"Please provide input file name and try again\n";
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		cout<<"Cannot open specified file\n";
		return 0;
	}
	
    logout.open("log.txt", ios::app);
    tokenout.open("token.txt", ios::app);
	s_table = new SymbolTable(10);

	yyin= fin;
	yylex();
	fclose(yyin);
    logout.close();
    tokenout.close();
	return 0;
}