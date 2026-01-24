%option noyywrap 
%x STRING_STATE SL_COMMENT ML_COMMENT
%{
#include<bits/stdc++.h>
#include "2005050.cpp"

using namespace std;

int line_count=1;
int error_count = 0;
int warning_count =0;
int tab_count;
int req_tab_count = 0;
int space_count;

ofstream logout;
ofstream tokenout;
SymbolTable* s_table;

%}

INDENTATION ^[ \t]*([ \t]+)
WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z_]
DIGIT [0-9]
NEWLINE \n
ID {LETTER}({LETTER}|{DIGIT})*
INVALID_ID {DIGIT}+{LETTER}+({LETTER}|{DIGIT})*
INT {DIGIT}+
FLOAT {DIGIT}*(\.{DIGIT}+)?(E[+|-]?{DIGIT}+)?
ESCAPE \\
EXCEPTION ['n"t\afrbv0]
CHAR \'{LETTER}\'
SPEC_CHAR \'{ESCAPE}{EXCEPTION}\'
OTHER_CHAR [`~!@#$%^&*\.,-_+=:<>?\{\}\(\)\[\]]
UNRECOGNIZED_CHAR \'.\'
UNRECOGNIZED_CHAR2 \'{ESCAPE}!({EXCEPTION})\'
EMPTY_CHAR \'\'
UNFINISHED_CHAR \'{LETTER}|\'{ESCAPE}{EXCEPTION}|\'
MULTI_CHAR \'{LETTER}{LETTER}+\'|\'({WHITESPACE})?{LETTER}(({WHITESPACE})?{LETTER})+({WHITESPACE})?\'
TOO_MANY_DECIMAL {DIGIT}*\.{DIGIT}*(\.{DIGIT}*)+(E[+|-]?{DIGIT}+)?
ILL_FORMED_NUMBER {DIGIT}*(\.{DIGIT}+)?(E[+|-]?{DIGIT}*(\.{DIGIT}+))
STRING ({WHITESPACE}|{LETTER}|{DIGIT}|({ESCAPE}{EXCEPTION})|{OTHER_CHAR})*
SL_STRING {STRING}\"
INVALID_SL_STRING {STRING}{NEWLINE}|{NEWLINE}
MUL_STRING {STRING}{ESCAPE}({NEWLINE}{STRING}{ESCAPE})*{NEWLINE}{STRING}\"
MUL_COMMENT {STRING}({ESCAPE}{NEWLINE}{STRING})+
INVALID_MUL_STRING {STRING}{ESCAPE}({NEWLINE}{STRING}{ESCAPE})*{NEWLINE}{STRING}
%%

{NEWLINE} {line_count++;}
{INDENTATION} {
	int founded_indentation=yyleng;
	tab_count=0;
	space_count=0;
	for(int i=0; i<founded_indentation; i++){
		if(yytext[i] == '\t'){
			tab_count++;
		}
		else if(yytext[i]= ' '){
			space_count++;
		}
	}
	
	if(space_count==0 && tab_count!=req_tab_count){
		logout<<"Line# "<<line_count<<": warning, "<<req_tab_count<<" of tabs needed but got "<<tab_count<<" tabs."<<endl;
		
		warning_count++;
	}
	else if(space_count>0 ){
		logout<<"Line# "<<line_count<<": Warning, tab requrired but got space."<<endl;
		warning_count++;
	}
}

{WHITESPACE} {}

"if"	{
			tokenout<<"<IF, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <IF> Lexeme "<<yytext<<" found"<<endl;	
}
		
"else"	{
			tokenout<<"<ELSE, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <ELSE> Lexeme "<<yytext<<" found"<<endl;
		}

"for"   {
			tokenout<<"<FOR, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <FOR> Lexeme "<<yytext<<" found"<<endl;
        }

"while" {
	        tokenout<<"WHILE, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <WHILE> Lexeme "<<yytext<<" found"<<endl;
        }

"do"    {
		   tokenout<<"<DO, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <DO> Lexeme "<<yytext<<" found"<<endl; 
}

"break"  {
			tokenout<<"<BREAK, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <BREAK> Lexeme "<<yytext<<" found"<<endl;
}

"int"  {
			tokenout<<"<INT, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <INT> Lexeme "<<yytext<<" found"<<endl;
}

"char"  {
			tokenout<<"<CHAR, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <CHAR> Lexeme "<<yytext<<" found"<<endl;
}

"float"  {
			tokenout<<"<FLOAT, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <FLOAT> Lexeme "<<yytext<<" found"<<endl;
}

"double"  {
			tokenout<<"<DOUBLE, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <DOUBLE> Lexeme "<<yytext<<" found"<<endl;
}

"void"  {
			tokenout<<"<VOID, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <VOID> Lexeme "<<yytext<<" found"<<endl;
}

"return"  {
			tokenout<<"<RETURN, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <RETURN> Lexeme "<<yytext<<" found"<<endl;
}

"switch"  {
			tokenout<<"<SWITCH, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <SWITCH> Lexeme "<<yytext<<" found"<<endl;
}

"case"  {
			tokenout<<"<CASE, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <CASE> Lexeme "<<yytext<<" found"<<endl;
}

"default"  {
			tokenout<<"<DEFAULT, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <DEFAULT> Lexeme "<<yytext<<" found"<<endl;
}

"continue"  {
			tokenout<<"<CONTINUE, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <CONTINUE> Lexeme "<<yytext<<" found"<<endl;
}

"+"|"-"		{
			tokenout<<"<ADDOP, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<endl;
		}

"*"     | 
"/"     | 
"%"     {
			tokenout<<"<MULOP, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <MULOP> Lexeme "<<yytext<<" found"<<endl;
        }	

"++"    | 
"--"    {
			tokenout<<"<INCOP, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <INCOP> Lexeme "<<yytext<<" found"<<endl;      
        }

"<"|"<="|">"|">="|"=="|"!="    {
			tokenout<<"<RELOP, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <RELOP> Lexeme "<<yytext<<" found"<<endl;
        }

"="         {
			tokenout<<"<ASSIGNOP, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<endl;
}

"&&"|"||"    {
			 tokenout<<"<LOGICOP, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<endl;
        }

"&"|"|"|"^"|"<<"|">>" {
			tokenout<<"<BITOP, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <BITOP> Lexeme "<<yytext<<" found"<<endl;
			}

"!"	        {
			tokenout<<"<NOT, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <NOT> Lexeme "<<yytext<<" found"<<endl;
}		

"("         {
			tokenout<<"<LPAREN, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<endl;
}

")"         {
			tokenout<<"<RPAREN, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<endl;
			}

"{"         {
			tokenout<<"<LCURL, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <LCURL> Lexeme "<<yytext<<" found"<<endl;
			s_table->enterScope();
			req_tab_count++;
			}	

"}"         {
			tokenout<<"<RCURL, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <RCURL> Lexeme "<<yytext<<" found"<<endl;
			s_table->exitScope();
			req_tab_count--;
			}			

"["         {
			tokenout<<"<LSQUARE, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <LSQUARE> Lexeme "<<yytext<<" found"<<endl;
            }		

"]"         {
			tokenout<<"<RSQUARE, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <RSQUARE> Lexeme "<<yytext<<" found"<<endl;
			}

","         {
			tokenout<<"<COMMA, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <COMMA> Lexeme "<<yytext<<" found"<<endl;
			}			

";"         {
			tokenout<<"<SEMICOLON, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<endl;
			}	

{INT} 	    {
			tokenout<<"<CONST_INT, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <CONST_INT> Lexeme "<<yytext<<" found"<<endl;
			}

{ID}        {
			tokenout<<"<ID, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <ID> Lexeme "<<yytext<<" found"<<endl;
			//insert in symbol table and print symbol table content(only non empty buckets)
			bool check = s_table->insert_into_st(yytext, "ID");
			if(check == true){
				s_table->print_all_scopeTable();
			}
			else{
				logout<<"	"<<yytext<<" already exists in the current ScopeTable"<<endl;
			}
            }	

{FLOAT}     {
			tokenout<<"<CONST_FLOAT, "<<yytext<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found"<<endl;
			}


<STRING_STATE>[ \t]+ {}

\"  {
            BEGIN STRING_STATE;   
	}

<STRING_STATE><<eof>> {
	logout<<"Error at line# "<<line_count<<": UNFINISHED_STRING \""<<endl;
	BEGIN INITIAL;
}	


<STRING_STATE>{SL_STRING} 	{
                    string str;
                    str = yytext;
			        logout<<"Line# "<<line_count<<": Token <SINGLE LINE STRING> Lexeme \""<<str<<" found"<<endl;
                     size_t found = str.find("\\\'");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\'');
					 	found = str.find("\\'");
					 }
					 found = str.find("\\\"");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\"');
					 	found = str.find("\\\"");
					 }

					 found = str.find("\\n");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\n');
					 	found = str.find("\\n");
					 }
					 found = str.find("\\t");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\t');
					 	found = str.find("\\t");
					 }
					 found = str.find("\\\\");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\\');
					 	found = str.find("\\\\");
					 }
					 found = str.find("\\a");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\a');
					 	found = str.find("\\a");
					 }
					 found = str.find("\\f");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\f');
					 	found = str.find("\\f");
					 }
					 found = str.find("\\r");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\r');
					 	found = str.find("\\r");
					 }
					  found = str.find("\\b");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\b');
					 	found = str.find("\\b");
					 }
					 found = str.find("\\v");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\v');
					 	found = str.find("\\v");
					 }
					//found = str.find("\\0");
                    //str.replace(found, 2, 1,'\0');

					tokenout<<"<SINGLE LINE STRING, "<<str<<">\n";
					BEGIN INITIAL;
				    }

<STRING_STATE>{INVALID_SL_STRING} {
	logout<<"Error at line# "<<line_count<<": UNFINISHED_STRING \""<<yytext;
	line_count++;
	error_count++;
	BEGIN INITIAL;
}		

<STRING_STATE>{INVALID_MUL_STRING} {
	string str;
    str = yytext;
	error_count++;
	size_t found = str.find("\\\n");
                    while(found!=string::npos){
						line_count++;
                        str.replace(found, 2, 1,'\t');
                        found = str.find("\\\n",found+1);
                    }
	logout<<"Error at line# "<<line_count<<": UNFINISHED_STRING \""<<yytext<<endl;
	BEGIN INITIAL;
}

<STRING_STATE>{MUL_STRING} {
                    string str;
                    str = yytext;
					logout<<"Line# "<<line_count<<": Token <MULTI LINE STRING> Lexeme \""<<str<<" found"<<endl;
                    size_t found = str.find("\\\n");
                    while(found!=string::npos){
						line_count++;
                        str.replace(found, 2, 1,'\t');
                        found = str.find("\\\n",found+1);
                    }
					found = str.find("\\\'");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\'');
					 	found = str.find("\\'");
					 }
					 found = str.find("\\\"");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\"');
					 	found = str.find("\\\"");
					 }

					 found = str.find("\\n");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\n');
					 	found = str.find("\\n");
					 }
					 found = str.find("\\t");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\t');
					 	found = str.find("\\t");
					 }
					 found = str.find("\\\\");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\\');
					 	found = str.find("\\\\");
					 }
					 found = str.find("\\a");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\a');
					 	found = str.find("\\a");
					 }
					 found = str.find("\\f");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\f');
					 	found = str.find("\\f");
					 }
					 found = str.find("\\r");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\r');
					 	found = str.find("\\r");
					 }
					  found = str.find("\\b");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\b');
					 	found = str.find("\\b");
					 }
					 found = str.find("\\v");
                     while(found!= string::npos){
                         str.replace(found, 2, 1,'\v');
					 	found = str.find("\\v");
					 }
                    tokenout<<"<MULTI LINE STRING, "<<str<<">\n";
					BEGIN INITIAL;
}



"//"  {
        BEGIN SL_COMMENT;
} 
<SL_COMMENT>{ESCAPE}{NEWLINE} {line_count++;}
<SL_COMMENT>{NEWLINE} {
	    line_count++;
        BEGIN INITIAL;
}
<SL_COMMENT>{STRING} {
        string str= yytext;
		logout<<"Line# "<<line_count<<": Token <SINGLE LINE COMMENT> Lexeme //"<<yytext<<" found"<<endl;;
        
}
<SL_COMMENT>{MUL_COMMENT} {
        string str= yytext;
		logout<<"Line# "<<line_count<<": Token <SINGLE LINE COMMENT> Lexeme //"<<yytext<<" found"<<endl;
	    size_t found = str.find("\\\n");
                    while(found!=string::npos){
						line_count++;
                        found = str.find("\\\n",found+1);
                    }
}

"/*" {
	BEGIN ML_COMMENT;
}

<ML_COMMENT><<EOF>> {
    logout<<"Error at line# "<<line_count<<": UNFINISHED COMMENT "<<endl;
	cout<<"exiting mlc"<<endl;
	error_count++;
	BEGIN INITIAL;	

}

<ML_COMMENT>({STRING}{NEWLINE})*{STRING}!("*/") {
	string str =yytext;
	size_t found = str.find("\n");
                    while(found!=string::npos){
						line_count++;
                        found = str.find("\n",found+1);
                    }
		logout<<"Error at line# "<<line_count<<": UNFINISHED COMMENT /*"<<yytext<<endl;
		error_count++;			
}

<ML_COMMENT>{STRING}"*/" {
        string str= yytext;
		logout<<"Line# "<<line_count<<": Token <MULTI LINE COMMENT> Lexeme /*"<<yytext<<" found"<<endl;
		BEGIN INITIAL;
        
}

<ML_COMMENT>({STRING}{NEWLINE})+{STRING}"*/" {
	string str =yytext;
	logout<<"Line# "<<line_count<<": Token <MULTI LINE COMMENT> Lexeme /*"<<yytext<<" found"<<endl;
	size_t found = str.find("\n");
                    while(found!=string::npos){
						line_count++;
                        found = str.find("\n",found+1);
                    }
		BEGIN INITIAL;
}

<ML_COMMENT>{NEWLINE} {line_count++;}


{CHAR}      {
	        int c = yytext[1];
			char x= (char) c;
			tokenout<<"<CONST_CHAR, "<<x<<">"<<endl;
            logout<<"Line# "<<line_count<<": Token <CONST_CHAR> Lexeme "<<x<<" found"<<endl;
			}

{TOO_MANY_DECIMAL} {
	logout<<"Error at line# "<<line_count<<": TOO_MANY_DECIMAL_POINTS "<<yytext<<endl;
	error_count++;
}			

{ILL_FORMED_NUMBER} {
	logout<<"Error at line# "<<line_count<<": ILLFORMED_NUMBER "<<yytext<<endl;
	error_count++;
}

{INVALID_ID} {
	logout<<"Error at line# "<<line_count<<": INVALID_ID_SUFFIX_NUM_PREFIX "<<yytext<<endl;
	error_count++;
}

{MULTI_CHAR} {
	logout<<"Error at line# "<<line_count<<": MULTICHAR_CONST_CHAR "<<yytext<<endl;
	error_count++;
}			

{EMPTY_CHAR} {
	logout<<"Error at line# "<<line_count<<": EMPTY_CONST_CHAR "<<yytext<<endl;
	error_count++;
}

{UNFINISHED_CHAR} {
	logout<<"Error at line# "<<line_count<<": UNFINISHED_CONST_CHAR "<<yytext<<endl;
	error_count++;
}

{UNRECOGNIZED_CHAR2} {
	int c = yytext[2];
	char x= (char) c;
	logout<<"Error at line# "<<line_count<<": UNRECOGNIZED_CHAR "<<x<<endl;
	error_count++;
}

{UNRECOGNIZED_CHAR} {
	int c = yytext[1];
	char x= (char) c;
	logout<<"Error at line# "<<line_count<<": UNRECOGNIZED_CHAR "<<x<<endl;
	error_count++;
}

[`@#$&*:?] {
	logout<<"Error at line# "<<line_count<<": UNRECOGNIZED_CHAR "<<yytext<<endl;
	error_count++;
}	
			

{SPEC_CHAR}	{
	        int c = yytext[2];
			if(c==39){
			    tokenout<<"<CONST_CHAR, \'>\n";
	            logout<< "Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \' found"<<endl;
			}
			else if(c==34){
				tokenout<<"<CONST_CHAR, \">\n";
	            logout<<"Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \" found"<<endl;
			}
			else if(c==110){
				tokenout<<"<CONST_CHAR, \n>\n";
	            logout<<"Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \n found"<<endl;
			}
			else if(c==116){
				tokenout<<"<CONST_CHAR, \t>\n";
	            logout<<"Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \t found"<<endl;
			}
			else if(c==92){
				tokenout<<"<CONST_CHAR, \\>\n";
	            logout<<"Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \\ found"<<endl;
			}
			else if(c==97){
				tokenout<<"<CONST_CHAR, \a>\n";
	            logout<< "Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \a found"<<endl;
			}
			else if(c==102){
				tokenout<<"<CONST_CHAR, \f>\n";
	            logout<< "Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \f found"<<endl;
			}
			else if(c==114){
				tokenout<<"<CONST_CHAR, \r>\n";
	            logout<< "Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \r found"<<endl;
			}
			else if(c==98){
				tokenout<<"<CONST_CHAR, \b>\n";
	            logout<< "Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \b found"<<endl;
			}
			else if(c==118){
				tokenout<<"<CONST_CHAR, \v>\n";
	            logout<< "Line# "<<line_count<<": Token <CONST_CHAR> Lexeme \v found"<<endl;
			}
			else if(c==48){
				tokenout<<"<CONST_CHAR, null character>\n";
	            logout<< "Line# "<<line_count<<": Token <CONST_CHAR> Lexeme null character found"<<endl;
			}
}	


	

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	s_table = new SymbolTable(10);
	logout.open("2005050_log.txt", ios::app);
    tokenout.open("2005050_token.txt", ios::app);

	yyin= fin;
	yylex();

	s_table->print_all_scopeTable();
	logout<<"Total lines: "<<line_count<<endl;
	logout<<"Total errors: "<<error_count<<endl;
	logout<<"Total warnings: "<<warning_count<<endl;
	fclose(yyin);
    logout.close();
    tokenout.close();
	return 0;
}