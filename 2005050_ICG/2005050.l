%option noyywrap 
%{
#include<bits/stdc++.h>
#include "2005050_symbolTable.cpp"
#include "2005050_parseTree.cpp"
#include "y.tab.h"

using namespace std;


extern YYSTYPE yylval;
extern SymbolTable *table;
extern ofstream logfile;
void yyerror(char *);

int line_count=1;
int error_count = 0;
bool func_or_loop = false;

SymbolTable* s_table;

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z_]
DIGIT [0-9]
NEWLINE \n
ID {LETTER}({LETTER}|{DIGIT})*
INT {DIGIT}+
FLOAT {DIGIT}+(\.{DIGIT}+)?(E[+|-]?{DIGIT}+)?

%%

{NEWLINE} {line_count++;}	
{WHITESPACE} {}

"if"	{
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <IF> Lexeme "<<yytext<<" found"<<endl;
	return IF;
	}
"else"	{
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <ELSE> Lexeme "<<yytext<<" found"<<endl;
	return ELSE;
	}
"for"   {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	table->enterScope();
	func_or_loop = true;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <FOR> Lexeme "<<yytext<<" found"<<endl;
	return FOR;
	}
"while" {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <WHILE> Lexeme "<<yytext<<" found"<<endl;
	return WHILE;
	}

"int"  {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <INT> Lexeme "<<yytext<<" found"<<endl;
	return INT;
	}

"float"  {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <FLOAT> Lexeme "<<yytext<<" found"<<endl;
	return FLOAT;
	}

"void"  {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <VOID> Lexeme "<<yytext<<" found"<<endl;
	return VOID;
	}
"return"  {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <RETURN> Lexeme "<<yytext<<" found"<<endl;
	return RETURN;
	}

"println"	{
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
    logfile<<"Line# "<<line_count<<": Token <PRINTLN> Lexeme "<<yytext<<" found"<<endl;
	return PRINTLN;}

"+"|"-"	    {
	            SymbolInfo* s = new SymbolInfo(yytext, "ADDOP");
				s->line_no = line_count;
				yylval.symbol_info = s;
				logfile<<"Line# "<<line_count<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<endl;
			    return ADDOP;
	    	}

"*"     | 
"/"     | 
"%"     {
	        SymbolInfo* s= new  SymbolInfo(yytext, "MULOP");
			s->line_no = line_count;
			yylval.symbol_info=s;
			logfile<<"Line# "<<line_count<<": Token <MULOP> Lexeme "<<yytext<<" found"<<endl;
			return MULOP;
        }	

"++"    {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <INCOP> Lexeme "<<yytext<<" found"<<endl;
	return INCOP;
	}
"--"    {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <DECOP> Lexeme "<<yytext<<" found"<<endl;
	return DECOP;
	}

"<"|"<="|">"|">="|"=="|"!="    {
			SymbolInfo* s= new  SymbolInfo(yytext, "RELOP");
			s->line_no = line_count;
			yylval.symbol_info = s;
			logfile<<"Line# "<<line_count<<": Token <RELOP> Lexeme "<<yytext<<" found"<<endl;
			return RELOP;
        }

"="     { 
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<endl;
	return ASSIGNOP;
	}

"&&"|"||"   {
			SymbolInfo* s= new  SymbolInfo(yytext, "LOGICOP");
			s->line_no = line_count;
			yylval.symbol_info = s;
			logfile<<"Line# "<<line_count<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<endl;
			return LOGICOP;
        }

"!"	    { 
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <NOT> Lexeme "<<yytext<<" found"<<endl;
	return NOT; 
	}		
"("     { 
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<endl;
	return LPAREN; 
	}
")"     {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<endl;
	return RPAREN; }

"{"     {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	if(func_or_loop == false) table->enterScope();
	else func_or_loop = false;
	logfile<<"Line# "<<line_count<<": Token <LCURL> Lexeme "<<yytext<<" found"<<endl;
	return LCURL;
	    }	

"}"     {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <RCURL> Lexeme "<<yytext<<" found"<<endl;
	return RCURL;
		}			

"["     {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <LSQUARE> Lexeme "<<yytext<<" found"<<endl;
	return LTHIRD;
	}		
"]"     {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <RSQUARE> Lexeme "<<yytext<<" found"<<endl;
	return RTHIRD;
	}
","     {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <COMMA> Lexeme "<<yytext<<" found"<<endl;
	return COMMA;
	}			
";"     {
	SymbolInfo* s = new SymbolInfo(yytext, "token");
	s->line_no = line_count;
	yylval.symbol_info = s;
	logfile<<"Line# "<<line_count<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<endl;
	return SEMICOLON;
	}	

{INT} 	{
			SymbolInfo *s= new  SymbolInfo(yytext, "CONST_INT");
			s->line_no = line_count;
			yylval.symbol_info = s;
			logfile<<"Line# "<<line_count<<": Token <CONST_INT> Lexeme "<<yytext<<" found"<<endl;
			return CONST_INT;
		}

{ID}    {			
			SymbolInfo* s= new SymbolInfo(yytext, "ID");
			s->line_no = line_count;
			yylval.symbol_info = s;
			logfile<<"Line# "<<line_count<<": Token <ID> Lexeme "<<yytext<<" found"<<endl;			
			return ID;
        }	

{FLOAT}     {
	            SymbolInfo *s= new  SymbolInfo(yytext, "CONST_FLOAT");
				s->line_no = line_count;
				yylval.symbol_info = s;
				logfile<<"Line# "<<line_count<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found"<<endl;
				return CONST_FLOAT;
			}	

%%

