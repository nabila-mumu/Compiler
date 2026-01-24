%option noyywrap

%x MYSTATE COMMENT

%{
#include<bits/stdc++.h>

using namespace std;

%}
WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z_]
DIGIT [0-9]
NEWLINE \n
ID {LETTER}({LETTER}|{DIGIT})*
ESCAPE \\
EXCEPTION ['n"t\afrbv0]
CHAR \'.\'
SPEC_CHAR \'{ESCAPE}{EXCEPTION}\'
STRING ({WHITESPACE}|{LETTER}|{DIGIT}|({ESCAPE}{EXCEPTION}))*
MUL_STRING {STRING}({ESCAPE}{NEWLINE}{STRING})+

%%

[ \t\n]+ {}
<MYSTATE>[ \t\n]+ {}

\"  {
            BEGIN MYSTATE; 
		    printf("MYSTATE started at %s\n",yytext);   
	}

"//"  {
        BEGIN COMMENT;
        cout<<"comment stated"<<endl;
} 
<COMMENT>{ESCAPE}{NEWLINE} {}
<COMMENT>{NEWLINE} {
        BEGIN INITIAL;
        cout<<"exiting comment"<<endl;
}   

<MYSTATE>\" {
            printf("ending mystate at %s\n",yytext); 
			BEGIN INITIAL;
            }    

<MYSTATE>{STRING} 	{
                    string str;
					printf("In mystate %s found\n",yytext);
                    str = yytext;
                    cout<<str<<endl;
                    size_t found = str.find("\\t");
                    if(found!= string::npos){
                        str.replace(found, 2, 1,'\t');
                        cout<<"yes"<<endl;
                    }
                    else{
                        cout<<"no"<<endl;
                    }
                    cout<<str<<endl;
				    }

<MYSTATE>{MUL_STRING} {
                    string str;
					printf("In mystate %s found\n",yytext);
                    str = yytext;
                    size_t found = str.find("\\\n");
                    while(found!=string::npos){
                        str.replace(found, 2, 1,'\t');
                        found = str.find("\\\n",found+1);
                        cout<<"yes"<<endl;
                    }
                    cout<<str<<endl;
}    

<COMMENT>{STRING} {
        string str= yytext;
        cout<<str<<endl;
}
<COMMENT>{MUL_STRING} {
        string str = yytext;
        cout<<str<<endl;
}

{ID} 	{
			printf("In initial State %s found\n",yytext);
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
	
	yyin= fin;
	yylex();
	fclose(yyin);
	return 0;
}