/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "2005050.y"

#include<bits/stdc++.h>

#include "2005050_parseTree.cpp"
#include "2005050_symbolTable.cpp"
#include "2005050_icg.cpp"
//#define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;
extern int line_count;
extern int error_count;
extern bool func_or_loop;

ofstream logfile;
ofstream parsetreefile;
ofstream asmfile;

bool after_calc=false;
bool from_func = false;

SymbolTable *table;
vector<SymbolInfo*> var_decl_list;
vector<string> global;
vector< pair<string, string> > param_list;
vector< pair<string, int> > sp_map;
vector<string> func_var_list;
int sub_from_sp = 0;

void yyerror(char *s){
	printf("%s\n",s);
}

void generate_assembly(ParseTreeNode* ptnode){
    if(ptnode->get_rule()=="start : program"){
        //generate_assembly(ptnode->child_list[0]);
        ifstream tempfile;
        tempfile.open("tempfile.txt");
        ofstream asmfile;
        asmfile.open("code.asm",ios::app);
        gen_start_code();

        //global variable
        vector<SymbolInfo*> all_of_global_scope = table->global_var_list();
        vector<SymbolInfo*> global_vars;
        for(SymbolInfo* s : all_of_global_scope){
            if(s->getType() == "INT"){
                gen_global_variable(s->getName(),s->array_size);
                global.push_back(s->getName());
            }
        }
        //////////////////////////////////////////////////////////////////////

        //generate_assembly(ptnode->child_list[0]);
        asmfile<<"\n.CODE"<<endl;
        //tempfile.seekg(0, ios::beg);
		string line;

        // while(getline(tempfile, line))
		// {
		// 	//asmfile << line + (jumping_label[lineno] == ""?"":" "+jumping_label[lineno]) << endl;
		// 	//lineno++;
        //     asmfile<<line<<endl;
		// }
        generate_assembly(ptnode->child_list[0]);
		gen_end_code(true);
    }
    else if(ptnode->get_rule()=="program : program unit"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="program : unit"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="unit : var_declaration"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="unit : func_declaration"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="unit : func_definition"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="func_definition : type_specifier ID LPAREN RPAREN compound_statement"){
        //ofstream out;
        //out.open("tempfile.txt",ios::app);
        generate_assembly(ptnode->child_list[0]);
        generate_assembly(ptnode->child_list[1]);
        generate_assembly(ptnode->child_list[2]);
        generate_assembly(ptnode->child_list[3]);
        string func_name = ptnode->get_name();
        gen_func_start_code(func_name);
        generate_assembly(ptnode->child_list[4]);
       // out<<"after generate"<<endl;
        gen_func_end_code(func_name, 0);
    }
    else if(ptnode->get_rule()=="parameter_list : parameter_list COMMA type_specifier ID"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="parameter_list : parameter_list COMMA type_specifier"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="parameter_list : type_specifier ID"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="parameter_list : type_specifier"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="compound_statement : LCURL statements RCURL"){
        generate_assembly(ptnode->child_list[1]);
        gen_add("SP",sub_from_sp);
        sub_from_sp = 0;
        sp_map.clear();
    }
    else if(ptnode->get_rule()=="compound_statement : LCURL RCURL"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="var_declaration : type_specifier declaration_list SEMICOLON"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="type_specifier : INT"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="type_specifier : FLOAT"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="type_specifier : VOID"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="declaration_list : declaration_list COMMA ID"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="declaration_list : ID"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="declaration_list : ID LTHIRD CONST_INT RTHIRD"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statements : statement"){
        generate_assembly(ptnode->child_list[0]);
        
    }
    else if(ptnode->get_rule()=="statements : statements statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statement : var_declaration"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        for(string s : ptnode->child_list[0]->var_list){
            sub_from_sp +=2;
            gen_sub("SP",2);
            sp_map.push_back(make_pair(s,sub_from_sp));
        }
    }
    else if(ptnode->get_rule()=="statement : expression_statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statement : compound_statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statement : IF LPAREN expression RPAREN statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statement : IF LPAREN expression RPAREN statement ELSE statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statement : WHILE LPAREN expression RPAREN statement"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="statement : PRINTLN LPAREN ID RPAREN SEMICOLON"){
        gen_label(get_newlabel());
        int pt=0;
        for(int i=0; i<sp_map.size(); i++){
            if(ptnode->child_list[2]->get_name()==sp_map[i].first){
                pt=sp_map[i].second;
                break;
            }
        }
        if(pt==0) gen_mov("AX",ptnode->child_list[2]->get_name());
        else gen_mov("AX","[BP-"+to_string(pt)+"]");
        gen_call("print_output");
        gen_call("new_line");
        // for(ParseTreeNode* child : ptnode->child_list){
        //     generate_assembly(child);
        // }
    }
    else if(ptnode->get_rule()=="statement : RETURN expression SEMICOLON"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        if(after_calc){                //if after_calc true then the return value in AX
            after_calc = false;
        }
        else{
            bool got = false;
            for(string g : global){
                if(g==ptnode->child_list[1]->get_name()){
                    gen_mov("AX",g);
                    got = true;
                    break;
                }
            }
            int pt=0;
            for(int i=0; i<sp_map.size(); i++){
                if(ptnode->child_list[1]->get_name() == sp_map[i].first){
                    pt = sp_map[i].second;
                    got = true;
                    break;
                }
            }
            if(pt!=0) gen_mov("AX", "[BP-"+to_string(pt)+"]");
            if(!got) gen_mov("AX",ptnode->child_list[1]->get_value());  //for const int
        }
    }
    else if(ptnode->get_rule()=="expression_statement : SEMICOLON"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="expression_statement : expression SEMICOLON"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="variable : ID"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="variable : ID LTHIRD expression RTHIRD"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="expression : logic_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        ptnode->set_value(ptnode->child_list[0]->get_value());
        ptnode->set_name(ptnode->child_list[0]->get_name());
    }
    else if(ptnode->get_rule()=="expression : variable ASSIGNOP logic_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        if(!after_calc && !from_func) {
            gen_mov("AX", ptnode->child_list[2]->get_value());
        }
        else if(from_func){
            gen_mov("AX", "AX");
        }
        else{
            gen_pop("AX");
            after_calc = false;
        }
        int pt=0;
        for(int i=0; i<sp_map.size(); i++){
            if(ptnode->child_list[0]->get_name() == sp_map[i].first){
                pt = sp_map[i].second;
                break;
            }
        }
        if(pt==0) gen_mov(ptnode->child_list[0]->get_name(), "AX");
        else gen_mov("[BP-"+to_string(pt)+"]", "AX");
        //gen_push("AX");
    }
    else if(ptnode->get_rule()=="logic_expression : rel_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        ptnode->set_name(ptnode->child_list[0]->get_name());
    }
    else if(ptnode->get_rule()=="logic_expression : rel_expression LOGICOP rel_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="rel_expression : simple_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        ptnode->set_name(ptnode->child_list[0]->get_name());
    }
    else if(ptnode->get_rule()=="rel_expression : simple_expression RELOP simple_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="simple_expression : term"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        ptnode->set_name(ptnode->child_list[0]->get_name());
        //gen_push("AX");

    }
    else if(ptnode->get_rule()=="simple_expression : simple_expression ADDOP term"){
        gen_label(get_newlabel());
        generate_assembly(ptnode->child_list[0]);
        //gen_push("AX");
        if(!after_calc){
            int pt=0;
            for(int i=0; i<sp_map.size(); i++){
                if(ptnode->child_list[0]->get_name() == sp_map[i].first){
                    pt = sp_map[i].second;
                    break;
                }
            }
            if(pt == 0) gen_mov("AX",ptnode->child_list[0]->get_name());
            else gen_mov("AX","[BP-"+to_string(pt)+"]");
        } 
        else gen_pop("AX");
        gen_mov("BX","AX");
        generate_assembly(ptnode->child_list[2]);
        //gen_pop("BX");

        int pt=0;
        for(int i=0; i<sp_map.size(); i++){
            if(ptnode->child_list[2]->get_name() == sp_map[i].first){
                pt = sp_map[i].second;
                break;
            }
        }
        if(pt == 0) gen_mov("AX",ptnode->child_list[2]->get_name());
        else gen_mov("AX","[BP-"+to_string(pt)+"]");
        //gen_mov("AX",ptnode->child_list[2]->get_name());

        if(ptnode->child_list[1]->get_name()=="+"){
            gen_xchg("AX","BX");
            gen_add("AX","BX");
        } 
        else if(ptnode->child_list[1]->get_name()=="-") {
            gen_xchg("AX","BX");
            gen_sub("AX","BX");
        }
        gen_push("AX");
        after_calc = true;
    }
    else if(ptnode->get_rule()=="term : unary_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        ptnode->set_name(ptnode->child_list[0]->get_name());
       //gen_mov("AX",ptnode->child_list[0]->get_name());
    }
    else if(ptnode->get_rule()=="term : term MULOP unary_expression"){
        gen_label(get_newlabel());
        generate_assembly(ptnode->child_list[0]);
        //gen_push("AX");
        if(!after_calc) {
            int pt=0;
            for(int i=0; i<sp_map.size(); i++){
                if(ptnode->child_list[0]->get_name() == sp_map[i].first){
                    pt = sp_map[i].second;
                    break;
                }
            }
            if(pt == 0) gen_mov("AX",ptnode->child_list[0]->get_name());
            else gen_mov("AX","[BP-"+to_string(pt)+"]");
        }
        else gen_pop("AX");
        gen_mov("BX","AX");
        generate_assembly(ptnode->child_list[2]);
        //gen_pop("BX");

        int pt=0;
        for(int i=0; i<sp_map.size(); i++){
            if(ptnode->child_list[2]->get_name() == sp_map[i].first){
                pt = sp_map[i].second;
                break;
            }
        }
        if(pt == 0) gen_mov("AX",ptnode->child_list[2]->get_name());
        else gen_mov("AX","[BP-"+to_string(pt)+"]");

        if(ptnode->child_list[1]->get_name()=="*"){
            gen_xchg("AX","BX");
            gen_xor("DX");
            gen_imul("BX");
            gen_push("AX");
        } 
        else if(ptnode->child_list[1]->get_name()=="/") {
            gen_xchg("AX","BX");
            gen_xor("DX");
            gen_idiv("BX");
            gen_push("AX");
        }
        else if(ptnode->child_list[1]->get_name()=="%") {
            gen_xchg("AX","BX");
            gen_xor("DX");
            gen_idiv("BX");
            gen_push("DX");
        }
        //gen_push("AX");
        after_calc = true;
    }
    else if(ptnode->get_rule()=="unary_expression : ADDOP unary_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="unary_expression : NOT unary_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="unary_expression : factor"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        ptnode->set_name(ptnode->child_list[0]->get_name());
    }
    else if(ptnode->get_rule()=="factor : variable"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        ptnode->set_name(ptnode->child_list[0]->get_name());
    }
    else if(ptnode->get_rule()=="factor : ID LPAREN argument_list RPAREN"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        gen_call(ptnode->child_list[0]->get_name());
        from_func = true;
    }
    else if(ptnode->get_rule()=="factor : LPAREN expression RPAREN"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="factor : CONST_INT"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="factor : CONST_FLOAT"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="factor : variable INCOP"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        for(auto g: global){
            if(g == ptnode->child_list[0]->get_name()){
                gen_mov("AX",g);
                gen_inc("AX");
                gen_mov(g, "AX");
                break;
            }
        }
        for(auto s : sp_map){
            if(s.first == ptnode->child_list[0]->get_name()){
                int pt = s.second;
                gen_mov("AX","[BP-"+to_string(pt)+"]");
                gen_inc("AX");
                gen_mov("[BP-"+to_string(pt)+"]", "AX");
            }
        }
    }
    else if(ptnode->get_rule()=="factor : variable DECOP"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
        for(auto g: global){
            if(g == ptnode->child_list[0]->get_name()){
                gen_mov("AX",g);
                gen_dec("AX");
                gen_mov(g, "AX");
                break;
            }
        }
        for(auto s : sp_map){
            if(s.first == ptnode->child_list[0]->get_name()){
                int pt = s.second;
                gen_mov("AX","[BP-"+to_string(pt)+"]");
                gen_dec("AX");
                gen_mov("[BP-"+to_string(pt)+"]", "AX");
            }
        }
    }
    else if(ptnode->get_rule()=="argument_list : arguments"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="argument_list : "){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="arguments : arguments COMMA logic_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
    else if(ptnode->get_rule()=="arguments : logic_expression"){
        for(ParseTreeNode* child : ptnode->child_list){
            generate_assembly(child);
        }
    }
}


#line 652 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    VOID = 259,                    /* VOID  */
    INT = 260,                     /* INT  */
    FLOAT = 261,                   /* FLOAT  */
    CONST_INT = 262,               /* CONST_INT  */
    CONST_FLOAT = 263,             /* CONST_FLOAT  */
    LTHIRD = 264,                  /* LTHIRD  */
    RTHIRD = 265,                  /* RTHIRD  */
    LPAREN = 266,                  /* LPAREN  */
    RPAREN = 267,                  /* RPAREN  */
    LCURL = 268,                   /* LCURL  */
    RCURL = 269,                   /* RCURL  */
    SEMICOLON = 270,               /* SEMICOLON  */
    COMMA = 271,                   /* COMMA  */
    FOR = 272,                     /* FOR  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    WHILE = 275,                   /* WHILE  */
    PRINTLN = 276,                 /* PRINTLN  */
    RETURN = 277,                  /* RETURN  */
    ASSIGNOP = 278,                /* ASSIGNOP  */
    NOT = 279,                     /* NOT  */
    INCOP = 280,                   /* INCOP  */
    DECOP = 281,                   /* DECOP  */
    LOGICOP = 282,                 /* LOGICOP  */
    RELOP = 283,                   /* RELOP  */
    ADDOP = 284,                   /* ADDOP  */
    MULOP = 285                    /* MULOP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define VOID 259
#define INT 260
#define FLOAT 261
#define CONST_INT 262
#define CONST_FLOAT 263
#define LTHIRD 264
#define RTHIRD 265
#define LPAREN 266
#define RPAREN 267
#define LCURL 268
#define RCURL 269
#define SEMICOLON 270
#define COMMA 271
#define FOR 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define PRINTLN 276
#define RETURN 277
#define ASSIGNOP 278
#define NOT 279
#define INCOP 280
#define DECOP 281
#define LOGICOP 282
#define RELOP 283
#define ADDOP 284
#define MULOP 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 582 "2005050.y"

    SymbolInfo* symbol_info;
    ParseTreeNode* pt_node;

#line 770 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_VOID = 4,                       /* VOID  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_CONST_INT = 7,                  /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 8,                /* CONST_FLOAT  */
  YYSYMBOL_LTHIRD = 9,                     /* LTHIRD  */
  YYSYMBOL_RTHIRD = 10,                    /* RTHIRD  */
  YYSYMBOL_LPAREN = 11,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 12,                    /* RPAREN  */
  YYSYMBOL_LCURL = 13,                     /* LCURL  */
  YYSYMBOL_RCURL = 14,                     /* RCURL  */
  YYSYMBOL_SEMICOLON = 15,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 16,                     /* COMMA  */
  YYSYMBOL_FOR = 17,                       /* FOR  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_PRINTLN = 21,                   /* PRINTLN  */
  YYSYMBOL_RETURN = 22,                    /* RETURN  */
  YYSYMBOL_ASSIGNOP = 23,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_INCOP = 25,                     /* INCOP  */
  YYSYMBOL_DECOP = 26,                     /* DECOP  */
  YYSYMBOL_LOGICOP = 27,                   /* LOGICOP  */
  YYSYMBOL_RELOP = 28,                     /* RELOP  */
  YYSYMBOL_ADDOP = 29,                     /* ADDOP  */
  YYSYMBOL_MULOP = 30,                     /* MULOP  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_start = 32,                     /* start  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_unit = 34,                      /* unit  */
  YYSYMBOL_func_declaration = 35,          /* func_declaration  */
  YYSYMBOL_func_definition = 36,           /* func_definition  */
  YYSYMBOL_parameter_list = 37,            /* parameter_list  */
  YYSYMBOL_compound_statement = 38,        /* compound_statement  */
  YYSYMBOL_var_declaration = 39,           /* var_declaration  */
  YYSYMBOL_type_specifier = 40,            /* type_specifier  */
  YYSYMBOL_declaration_list = 41,          /* declaration_list  */
  YYSYMBOL_statements = 42,                /* statements  */
  YYSYMBOL_statement = 43,                 /* statement  */
  YYSYMBOL_expression_statement = 44,      /* expression_statement  */
  YYSYMBOL_variable = 45,                  /* variable  */
  YYSYMBOL_expression = 46,                /* expression  */
  YYSYMBOL_logic_expression = 47,          /* logic_expression  */
  YYSYMBOL_rel_expression = 48,            /* rel_expression  */
  YYSYMBOL_simple_expression = 49,         /* simple_expression  */
  YYSYMBOL_term = 50,                      /* term  */
  YYSYMBOL_unary_expression = 51,          /* unary_expression  */
  YYSYMBOL_factor = 52,                    /* factor  */
  YYSYMBOL_argument_list = 53,             /* argument_list  */
  YYSYMBOL_arguments = 54                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   171

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   602,   602,   615,   626,   636,   645,   654,   664,   690,
     713,   748,   772,   789,   803,   816,   827,   843,   855,   879,
     889,   899,   910,   925,   950,   960,   982,   989,   999,  1006,
    1013,  1020,  1042,  1060,  1083,  1101,  1122,  1136,  1144,  1155,
    1164,  1181,  1188,  1201,  1209,  1222,  1230,  1243,  1251,  1267,
    1275,  1288,  1299,  1309,  1318,  1325,  1343,  1356,  1365,  1373,
    1383,  1394,  1401,  1409,  1421
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "VOID", "INT",
  "FLOAT", "CONST_INT", "CONST_FLOAT", "LTHIRD", "RTHIRD", "LPAREN",
  "RPAREN", "LCURL", "RCURL", "SEMICOLON", "COMMA", "FOR", "IF", "ELSE",
  "WHILE", "PRINTLN", "RETURN", "ASSIGNOP", "NOT", "INCOP", "DECOP",
  "LOGICOP", "RELOP", "ADDOP", "MULOP", "$accept", "start", "program",
  "unit", "func_declaration", "func_definition", "parameter_list",
  "compound_statement", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-59)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      49,   -59,   -59,   -59,    29,    49,   -59,   -59,   -59,   -59,
      13,   -59,   -59,    16,    46,    32,     6,   -59,    41,    39,
      43,     5,    54,    56,   -59,    68,   -59,   -59,    51,    49,
     -59,    62,    69,   -59,   -59,   142,   -59,   -59,    66,    73,
      76,    80,   142,   142,   142,   -59,   -59,   101,    95,   -59,
     -59,    25,    90,   -59,    84,    65,    77,   -59,   -59,   -59,
     -59,   111,   108,   142,   142,   109,    23,   142,   142,   117,
     107,    70,   -59,   -59,   114,   -59,   -59,   142,   -59,   -59,
     -59,   142,   142,   142,   142,   -59,   -59,   121,   -59,   120,
     118,   -59,    23,   124,   126,   129,   -59,   -59,   -59,   119,
      77,   -59,   -59,   -59,   142,   142,   122,   122,   132,   -59,
     140,   135,   -59,   -59,   122,   122,   -59,   -59
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    21,    19,    20,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    24,     0,     0,     0,    18,     0,     0,
       0,     0,    15,    22,    25,     0,     9,    11,     0,     0,
      14,     0,    39,    57,    58,     0,    17,    37,     0,     0,
       0,     0,     0,     0,     0,    30,    28,     0,     0,    26,
      29,    54,     0,    41,    43,    45,    47,    49,    53,     8,
      10,    13,     0,     0,    62,     0,     0,     0,     0,     0,
       0,    54,    52,    51,    24,    16,    27,     0,    59,    60,
      38,     0,     0,     0,     0,    12,    23,     0,    64,     0,
      61,    56,     0,     0,     0,     0,    36,    42,    44,    46,
      48,    50,    40,    55,     0,     0,     0,     0,     0,    63,
       0,    32,    34,    35,     0,     0,    31,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   -59,   150,   -59,   -59,   -59,    -6,    15,     8,
     -59,   -59,   -47,   -57,   -41,   -35,   -58,    75,    78,    74,
     -39,   -59,   -59,   -59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    21,    45,    46,    47,
      14,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    89,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      65,    76,    71,    71,    72,    73,    88,    70,    10,    92,
       1,     2,     3,    10,    27,     9,    13,    28,    20,    97,
       9,    29,    60,    71,    22,    15,    32,    16,    87,    11,
      33,    34,    93,    94,    35,   105,    71,    61,    37,    19,
      71,    71,    71,    71,    23,   101,   109,    43,    77,    24,
      78,    79,    44,     1,     2,     3,    25,    30,    26,   111,
     112,    17,    18,    71,    25,    31,    59,   116,   117,    62,
     110,    32,     1,     2,     3,    33,    34,    66,    63,    35,
      64,    25,    36,    37,    67,    38,    39,    68,    40,    41,
      42,    69,    43,    82,    83,    78,    79,    44,    32,     1,
       2,     3,    33,    34,    74,    80,    35,    84,    25,    75,
      37,    81,    38,    39,    85,    40,    41,    42,    86,    43,
      95,    91,    96,    15,    44,    32,     1,     2,     3,    33,
      34,   102,   103,    35,   104,    25,   106,    37,   107,    38,
      39,   108,    40,    41,    42,    32,    43,   113,    83,    33,
      34,    44,   114,    35,   115,    12,    98,   100,     0,     0,
      99,     0,     0,     0,     0,     0,    43,     0,     0,     0,
       0,    44
};

static const yytype_int8 yycheck[] =
{
      35,    48,    43,    44,    43,    44,    64,    42,     0,    66,
       4,     5,     6,     5,    20,     0,     3,    12,    12,    77,
       5,    16,    28,    64,    16,     9,     3,    11,    63,     0,
       7,     8,    67,    68,    11,    92,    77,    29,    15,     7,
      81,    82,    83,    84,     3,    84,   104,    24,    23,    10,
      25,    26,    29,     4,     5,     6,    13,     3,    15,   106,
     107,    15,    16,   104,    13,     9,    15,   114,   115,     7,
     105,     3,     4,     5,     6,     7,     8,    11,     9,    11,
      11,    13,    14,    15,    11,    17,    18,    11,    20,    21,
      22,    11,    24,    28,    29,    25,    26,    29,     3,     4,
       5,     6,     7,     8,     3,    15,    11,    30,    13,    14,
      15,    27,    17,    18,     3,    20,    21,    22,    10,    24,
       3,    12,    15,     9,    29,     3,     4,     5,     6,     7,
       8,    10,    12,    11,    16,    13,    12,    15,    12,    17,
      18,    12,    20,    21,    22,     3,    24,    15,    29,     7,
       8,    29,    12,    11,    19,     5,    81,    83,    -1,    -1,
      82,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,    32,    33,    34,    35,    36,    39,
      40,     0,    34,     3,    41,     9,    11,    15,    16,     7,
      12,    37,    40,     3,    10,    13,    15,    38,    12,    16,
       3,     9,     3,     7,     8,    11,    14,    15,    17,    18,
      20,    21,    22,    24,    29,    38,    39,    40,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    15,
      38,    40,     7,     9,    11,    46,    11,    11,    11,    11,
      46,    45,    51,    51,     3,    14,    43,    23,    25,    26,
      15,    27,    28,    29,    30,     3,    10,    46,    47,    53,
      54,    12,    44,    46,    46,     3,    15,    47,    48,    49,
      50,    51,    10,    12,    16,    44,    12,    12,    12,    47,
      46,    43,    43,    15,    12,    19,    43,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    35,    35,
      36,    36,    37,    37,    37,    37,    38,    38,    39,    40,
      40,    40,    41,    41,    41,    41,    42,    42,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    44,    44,    45,
      45,    46,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    51,    52,    52,    52,    52,    52,    52,
      52,    53,    53,    54,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     3,     2,     3,     1,
       1,     1,     3,     6,     1,     4,     1,     2,     1,     1,
       1,     7,     5,     7,     5,     5,     3,     1,     2,     1,
       4,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     2,     2,     1,     1,     4,     3,     1,     1,     2,
       2,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 602 "2005050.y"
                {
        logfile<<"start : program"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line((yyvsp[0].pt_node)->get_start_line());
        ptnode->set_end_line((yyvsp[0].pt_node)->get_end_line());
        ptnode->set_rule("start : program");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;

        (yyval.pt_node)->print_tree((yyval.pt_node),0);
        generate_assembly((yyval.pt_node));
    }
#line 1901 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 615 "2005050.y"
                       {
        logfile<<"program : program unit"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line((yyvsp[-1].pt_node)->get_start_line());
        ptnode->set_end_line((yyvsp[0].pt_node)->get_end_line());
        ptnode->set_rule("program : program unit");
        //$1->add_child($2);
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 1917 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 626 "2005050.y"
               {
            logfile<<"program : unit"<<endl;
            ParseTreeNode* ptnode = new ParseTreeNode();
            ptnode->set_start_line((yyvsp[0].pt_node)->get_start_line());
            ptnode->set_end_line((yyvsp[0].pt_node)->get_end_line());
            ptnode->set_rule("program : unit");
            ptnode->add_child((yyvsp[0].pt_node));
            (yyval.pt_node) = ptnode;
        }
#line 1931 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 636 "2005050.y"
                       {
        logfile<<"unit : var_declaration"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line((yyvsp[0].pt_node)->get_start_line());
        ptnode->set_end_line((yyvsp[0].pt_node)->get_end_line());
        ptnode->set_rule("unit : var_declaration");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 1945 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 645 "2005050.y"
                        {
        logfile<<"unit : func_declaration"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line((yyvsp[0].pt_node)->get_start_line());
        ptnode->set_end_line((yyvsp[0].pt_node)->get_end_line());
        ptnode->set_rule("unit : func_declaration");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 1959 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 654 "2005050.y"
                       {
        logfile<<"unit : func_definition"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line((yyvsp[0].pt_node)->get_start_line());
        ptnode->set_end_line((yyvsp[0].pt_node)->get_end_line());
        ptnode->set_rule("unit : func_definition");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 1973 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 664 "2005050.y"
                                                                            {
        logfile<<"func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON"<<endl;
        
        SymbolInfo* si = new SymbolInfo((yyvsp[-4].symbol_info)->getName(), "FUNCTION", (yyvsp[-5].pt_node)->get_data_type());
        si->func_parameter_list = param_list;
        param_list.clear();
        table->insert_into_st(si);

        ParseTreeNode* node_semicolon = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "SEMICOLON : ;");
        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child(node_semicolon);
        //$4->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($4);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[-4].symbol_info)->line_no, "ID : "+(yyvsp[-4].symbol_info)->getName());
        //node_id->add_child(node_lparen);
        //$1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-5].pt_node)->get_start_line(), (yyvsp[-1].symbol_info)->line_no, "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
        ptnode->add_child((yyvsp[-5].pt_node));
        ptnode->add_child(node_id);
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_rparen);
        ptnode->add_child(node_semicolon);
        (yyval.pt_node) = ptnode;
    }
#line 2004 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 690 "2005050.y"
                                                             {
        logfile<<"func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON"<<endl;

        SymbolInfo* si = new SymbolInfo((yyvsp[-3].symbol_info)->getName(), "FUNCTION", (yyvsp[-4].pt_node)->get_data_type());
        table->insert_into_st(si);

        ParseTreeNode* node_semicolon = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "SEMICOLON : ;");
        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child(node_semicolon);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child(node_rparen);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "ID : "+(yyvsp[-3].symbol_info)->getName());
        //node_id->add_child(node_lparen);
        //$1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-4].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
        ptnode->add_child((yyvsp[-4].pt_node));
        ptnode->add_child(node_id);
        ptnode->add_child(node_lparen);
        ptnode->add_child(node_rparen);
        ptnode->add_child(node_semicolon);
        (yyval.pt_node) = ptnode;
    }
#line 2031 "y.tab.c"
    break;

  case 10: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement  */
#line 713 "2005050.y"
                                                                                    {
        logfile<<"func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement"<<endl;
 
        SymbolInfo* si = new SymbolInfo((yyvsp[-4].symbol_info)->getName(), "FUNCTION", (yyvsp[-5].pt_node)->get_data_type());
        si->func_parameter_list = param_list;
        table->insert_into_st(si);
        table->enterScope();
        func_or_loop = true;
        for(auto p: param_list){
            SymbolInfo* sp = new SymbolInfo(p.first, p.second);
            table->insert_into_st(sp);
        }
        for(auto p: param_list){
            (yyvsp[-2].pt_node)->func_param_list.push_back(p.first);
        }
        param_list.clear();

        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child($6);
        //$4->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($4);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[-4].symbol_info)->line_no, "ID : "+(yyvsp[-4].symbol_info)->getName());
        //node_id->add_child(node_lparen);
        //$1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-5].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
        ptnode->set_name((yyvsp[-4].symbol_info)->getName());
        ptnode->add_child((yyvsp[-5].pt_node));
        ptnode->add_child(node_id);
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_rparen);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2071 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 748 "2005050.y"
                                                                     {
        logfile<<"func_definition : type_specifier ID LPAREN RPAREN compound_statement"<<endl;

        SymbolInfo* si = new SymbolInfo((yyvsp[-3].symbol_info)->getName(), "FUNCTION", (yyvsp[-4].pt_node)->get_data_type());
        //si->func_return_type = $1->get_data_type();
        table->insert_into_st(si);

        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child($5);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child(node_rparen);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "ID : "+(yyvsp[-3].symbol_info)->getName());
        //node_id->add_child(node_lparen);
        //$1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-4].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
        ptnode->set_name((yyvsp[-3].symbol_info)->getName());
        ptnode->add_child((yyvsp[-4].pt_node));
        ptnode->add_child(node_id);
        ptnode->add_child(node_lparen);
        ptnode->add_child(node_rparen);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2099 "y.tab.c"
    break;

  case 12: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 772 "2005050.y"
                                                        {
        logfile<<"parameter_list : parameter_list COMMA type_specifier ID"<<endl;

        param_list.push_back(make_pair((yyvsp[0].symbol_info)->getName(),(yyvsp[-1].pt_node)->get_data_type()));

        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "ID : "+(yyvsp[0].symbol_info)->getName());
        //$3->add_child(node_id);
        ParseTreeNode* node_comma = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "COMMA : ,");
        //node_comma->add_child($3);
        //$1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-3].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "parameter_list : parameter_list COMMA type_specifier ID");
        ptnode->add_child((yyvsp[-3].pt_node));
        ptnode->add_child(node_comma);
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_id);
        (yyval.pt_node) = ptnode;
    }
#line 2121 "y.tab.c"
    break;

  case 13: /* parameter_list: parameter_list COMMA type_specifier  */
#line 789 "2005050.y"
                                                     {
        logfile<<"parameter_list : parameter_list COMMA type_specifier"<<endl;

        param_list.push_back(make_pair("",(yyvsp[0].pt_node)->get_data_type()));

        ParseTreeNode* node_comma = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "COMMA : comma");
        //node_comma->add_child($3);
        //$1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "parameter_list : parameter_list COMMA type_specifier");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_comma);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2140 "y.tab.c"
    break;

  case 14: /* parameter_list: type_specifier ID  */
#line 803 "2005050.y"
                                   {
        logfile<<"parameter_list : type_specifier ID"<<endl;

        param_list.clear();
        param_list.push_back(make_pair((yyvsp[0].symbol_info)->getName(),(yyvsp[-1].pt_node)->get_data_type()));

        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "ID : "+(yyvsp[0].symbol_info)->getName());
        //$1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "parameter_list : type_specifier ID");
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_id);
        (yyval.pt_node) = ptnode;
    }
#line 2158 "y.tab.c"
    break;

  case 15: /* parameter_list: type_specifier  */
#line 816 "2005050.y"
                                {
        logfile<<"parameter_list : type_specifier"<<endl;

        param_list.clear();
        param_list.push_back(make_pair("",(yyvsp[0].pt_node)->get_data_type()));

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "parameter_list : type_specifier");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2173 "y.tab.c"
    break;

  case 16: /* compound_statement: LCURL statements RCURL  */
#line 827 "2005050.y"
                                            {
        logfile<<"compound_statement : LCURL statements RCURL"<<endl;

        table->print_all_scopeTable();
        table->exitScope();

        ParseTreeNode* node_rcurl = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "RCURL : }");
        //$2->add_child(node_rcurl);
        ParseTreeNode* node_lcurl = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LCURL : {");
        //node_lcurl->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "compound_statement : LCURL statements RCURL");
        ptnode->add_child(node_lcurl);
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_rcurl);
        (yyval.pt_node) = ptnode;
    }
#line 2194 "y.tab.c"
    break;

  case 17: /* compound_statement: LCURL RCURL  */
#line 843 "2005050.y"
                                 {
        logfile<<"compound_statement : LCURL RCURL"<<endl;

        ParseTreeNode* node_rcurl = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "RCURL : }");
        ParseTreeNode* node_lcurl = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "LCURL : {");
        //node_lcurl->add_child(node_rcurl);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "compound_statement : LCURL RCURL");
        ptnode->add_child(node_lcurl);
        ptnode->add_child(node_rcurl);
        (yyval.pt_node) = ptnode;
    }
#line 2210 "y.tab.c"
    break;

  case 18: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 855 "2005050.y"
                                                            {
        logfile<<"var_declaration : type_specifier declaration_list SEMICOLON"<<endl;
        vector<string> v_list;
        for(auto s: var_decl_list){
            SymbolInfo* si = new SymbolInfo(s->getName(), (yyvsp[-2].pt_node)->get_data_type());
            v_list.push_back(s->getName());
            table->insert_into_st(si);
        }
        var_decl_list.clear();

        ParseTreeNode* node_semicolon = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "SEMICOLON : ;");
        //$2->set_data_type($1->get_data_type());
        //$2->add_child(node_semicolon);
        //$1->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "var_declaration : type_specifier declaration_list SEMICOLON");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_semicolon);
        ptnode->set_data_type((yyvsp[-2].pt_node)->get_data_type());
        ptnode->var_list = v_list;
        (yyval.pt_node) = ptnode;
        //table->print_all_scopeTable();
    }
#line 2238 "y.tab.c"
    break;

  case 19: /* type_specifier: INT  */
#line 879 "2005050.y"
                      {
        logfile<<"type_specifier : INT"<<endl;
        
        ParseTreeNode* node_int = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "INT : int");
        node_int->set_data_type("INT");
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "type_specifier : INT");
        ptnode->set_data_type("INT");
        ptnode->add_child(node_int);
        (yyval.pt_node) = ptnode;
    }
#line 2253 "y.tab.c"
    break;

  case 20: /* type_specifier: FLOAT  */
#line 889 "2005050.y"
                       {
        logfile<<"type_specifier : FLOAT"<<endl; 
       
        ParseTreeNode* node_float = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "FLOAT : float");
        node_float->set_data_type("FLOAT");
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "type_specifier : FLOAT");
        ptnode->set_data_type("FLOAT");
        ptnode->add_child(node_float);
        (yyval.pt_node) = ptnode;
    }
#line 2268 "y.tab.c"
    break;

  case 21: /* type_specifier: VOID  */
#line 899 "2005050.y"
                       {
        logfile<<"type_specifier : VOID"<<endl;
          
        ParseTreeNode* node_void = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "VOID : void");
        node_void->set_data_type("VOID");
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "type_specifier : VOID");
        ptnode->set_data_type("VOID");
        ptnode->add_child(node_void);
        (yyval.pt_node) = ptnode;   
    }
#line 2283 "y.tab.c"
    break;

  case 22: /* declaration_list: declaration_list COMMA ID  */
#line 910 "2005050.y"
                                             {
        logfile<<"declaration_list : declaration_list COMMA ID "<<endl;
        var_decl_list.push_back((yyvsp[0].symbol_info));

        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "ID : "+(yyvsp[0].symbol_info)->getName());
        ParseTreeNode* node_comma = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "COMMA : ,");
        //node_comma->add_child(node_id);
        //$1->add_child(node_comma);

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "declaration_list : declaration_list COMMA ID");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_comma);
        ptnode->add_child(node_id);
        (yyval.pt_node) = ptnode;
    }
#line 2303 "y.tab.c"
    break;

  case 23: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 925 "2005050.y"
                                                                     {
        logfile<<"declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD"<<endl;
        SymbolInfo* s = (yyvsp[-3].symbol_info);
        s->array_size = stoi((yyvsp[-1].symbol_info)->getName());
        var_decl_list.push_back(s);

        ParseTreeNode* node_rthird = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "RSQUARE : ]");
        ParseTreeNode* node_const_int = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "CONST_INT : "+(yyvsp[-1].symbol_info)->getName());
        //node_const_int->add_child(node_rthird);
        ParseTreeNode* node_lthird = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LSQUARE : [");
        //node_lthird->add_child(node_const_int);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "ID : "+(yyvsp[-3].symbol_info)->getName());
        //node_id->add_child(node_lthird);
        ParseTreeNode* node_comma = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[-4].symbol_info)->line_no, "COMMA : ,");
        //node_comma->add_child(node_id);
        //$1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-5].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
        ptnode->add_child((yyvsp[-5].pt_node));
        ptnode->add_child(node_comma);
        ptnode->add_child(node_id);
        ptnode->add_child(node_lthird);
        ptnode->add_child(node_const_int);
        ptnode->add_child(node_rthird);
        (yyval.pt_node) = ptnode;
    }
#line 2333 "y.tab.c"
    break;

  case 24: /* declaration_list: ID  */
#line 950 "2005050.y"
                       {
        logfile<<"declaration_list : ID"<<endl;
        var_decl_list.clear();
        var_decl_list.push_back((yyvsp[0].symbol_info));

        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "ID : "+(yyvsp[0].symbol_info)->getName());
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "declaration_list : ID");
        ptnode->add_child(node_id);
        (yyval.pt_node) = ptnode;
    }
#line 2348 "y.tab.c"
    break;

  case 25: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 960 "2005050.y"
                                              {
        logfile<<"declaration_list : ID LTHIRD CONST_INT RTHIRD"<<endl;
        SymbolInfo* s = (yyvsp[-3].symbol_info);
        s->array_size = stoi((yyvsp[-1].symbol_info)->getName());
        var_decl_list.clear();
        var_decl_list.push_back(s);
        
        ParseTreeNode* node_rthird = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "RSQUARE : ]");
        ParseTreeNode* node_const_int = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "CONST_INT : "+(yyvsp[-1].symbol_info)->getName());
        //node_const_int->add_child(node_rthird);
        ParseTreeNode* node_lthird = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LSQUARE : [");
        //node_lthird->add_child(node_const_int);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "ID : "+(yyvsp[-3].symbol_info)->getName());
        //node_id->add_child(node_lthird);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "declaration_list : ID LTHIRD CONST_INT RTHIRD");
        ptnode->add_child(node_id);
        ptnode->add_child(node_lthird);
        ptnode->add_child(node_const_int);
        ptnode->add_child(node_rthird);
        (yyval.pt_node) = ptnode;
    }
#line 2374 "y.tab.c"
    break;

  case 26: /* statements: statement  */
#line 982 "2005050.y"
                       {
        logfile<<"statements : statement"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "statements : statement");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2386 "y.tab.c"
    break;

  case 27: /* statements: statements statement  */
#line 989 "2005050.y"
                                  {
        logfile<<"statements : statements statement"<<endl;

        //$1->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "statements : statements statement");
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2400 "y.tab.c"
    break;

  case 28: /* statement: var_declaration  */
#line 999 "2005050.y"
                            {
        logfile<<"statement : var_declaration"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "statement : var_declaration");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2412 "y.tab.c"
    break;

  case 29: /* statement: expression_statement  */
#line 1006 "2005050.y"
                                 {
        logfile<<"statement : expression_statement"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "statement : expression_statement");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2424 "y.tab.c"
    break;

  case 30: /* statement: compound_statement  */
#line 1013 "2005050.y"
                               {
        logfile<<"statement : compound_statement"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "statement : compound_statement");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2436 "y.tab.c"
    break;

  case 31: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 1020 "2005050.y"
                                                                                             {
        logfile<<"statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child($7);
        //$5->add_child(node_rparen);
        //$4->add_child($5);
        //$3->add_child($4);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-5].symbol_info)->line_no, (yyvsp[-5].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($3);
        ParseTreeNode* node_for = new ParseTreeNode((yyvsp[-6].symbol_info)->line_no, (yyvsp[-6].symbol_info)->line_no, "FOR : for");
        //node_for->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-6].symbol_info)->line_no, (yyvsp[0].pt_node)->get_end_line(), "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
        ptnode->add_child(node_for);
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-4].pt_node));
        ptnode->add_child((yyvsp[-3].pt_node));
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_rparen);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2463 "y.tab.c"
    break;

  case 32: /* statement: IF LPAREN expression RPAREN statement  */
#line 1042 "2005050.y"
                                                  {
        logfile<<"statement : IF LPAREN expression RPAREN statement"<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child($5);
        //$3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($3); 
        ParseTreeNode* node_if = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[-4].symbol_info)->line_no, "IF : if");
        //node_if->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[0].pt_node)->get_end_line(), "statement : IF LPAREN expression RPAREN statement");
        ptnode->add_child(node_if);
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_rparen);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2486 "y.tab.c"
    break;

  case 33: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 1060 "2005050.y"
                                                                 {
        logfile<<"statement : IF LPAREN expression RPAREN statement ELSE statement"<<endl;

        ParseTreeNode* node_else = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "ELSE : else");
        //node_else->add_child($7);
        //$5->add_child(node_else);
        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child($5);
        //$3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-5].symbol_info)->line_no, (yyvsp[-5].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($3); 
        ParseTreeNode* node_if = new ParseTreeNode((yyvsp[-6].symbol_info)->line_no, (yyvsp[-6].symbol_info)->line_no, "IF : if");
        //node_if->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-6].symbol_info)->line_no, (yyvsp[0].pt_node)->get_end_line(), "statement : IF LPAREN expression RPAREN statement ELSE statement");
        ptnode->add_child(node_if);
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-4].pt_node));
        ptnode->add_child(node_rparen);
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_else);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2514 "y.tab.c"
    break;

  case 34: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 1083 "2005050.y"
                                                     {
        logfile<<"statement : WHILE LPAREN expression RPAREN statement"<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child($5);
        //$3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($3); 
        ParseTreeNode* node_while = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[-4].symbol_info)->line_no, "WHILE : while");
        //node_while->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[0].pt_node)->get_end_line(), "statement : WHILE LPAREN expression RPAREN statement");
        ptnode->add_child(node_while);
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_rparen);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2537 "y.tab.c"
    break;

  case 35: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 1101 "2005050.y"
                                               {
        logfile<<"statement : PRINTLN LPAREN ID RPAREN SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "SEMICOLON : ;");
        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RPAREN : )");
        //node_rparen->add_child(node_semicolon);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "ID : "+(yyvsp[-2].symbol_info)->getName());
        node_id->set_name((yyvsp[-2].symbol_info)->getName());
        //node_id->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child(node_id); 
        ParseTreeNode* node_println = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[-4].symbol_info)->line_no, "PRINTLN : println");
        //node_println->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-4].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
        ptnode->add_child(node_println);
        ptnode->add_child(node_lparen);
        ptnode->add_child(node_id);
        ptnode->add_child(node_rparen);
        ptnode->add_child(node_semicolon);
        (yyval.pt_node) = ptnode;
    }
#line 2563 "y.tab.c"
    break;

  case 36: /* statement: RETURN expression SEMICOLON  */
#line 1122 "2005050.y"
                                        {
        logfile<<"statement : RETURN expression SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "SEMICOLON : ;");
        //$2->add_child(node_semicolon);
        ParseTreeNode* node_return = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "RETURN : return");
        //node_return->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "statement : RETURN expression SEMICOLON");
        ptnode->add_child(node_return);
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_semicolon);
        (yyval.pt_node) = ptnode;
    }
#line 2581 "y.tab.c"
    break;

  case 37: /* expression_statement: SEMICOLON  */
#line 1136 "2005050.y"
                                 {
        logfile<<"expression_statement : SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "SEMICOLON : ;");
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "expression_statement : SEMICOLON");
        ptnode->add_child(node_semicolon);
        (yyval.pt_node) = ptnode;
    }
#line 2594 "y.tab.c"
    break;

  case 38: /* expression_statement: expression SEMICOLON  */
#line 1144 "2005050.y"
                                            {
        logfile<<"expression_statement : expression SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "SEMICOLON : ;");
        //$1->add_child(node_semicolon);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "expression_statement : expression SEMICOLON");
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_semicolon);
        (yyval.pt_node) = ptnode;
    }
#line 2609 "y.tab.c"
    break;

  case 39: /* variable: ID  */
#line 1155 "2005050.y"
              {
        logfile<<"variable : ID "<<endl;

        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "ID : "+(yyvsp[0].symbol_info)->getName());
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "variable : ID");
        ptnode->set_name((yyvsp[0].symbol_info)->getName());
        ptnode->add_child(node_id);
        (yyval.pt_node) = ptnode;
    }
#line 2623 "y.tab.c"
    break;

  case 40: /* variable: ID LTHIRD expression RTHIRD  */
#line 1164 "2005050.y"
                                       {
        logfile<<"variable : ID LTHIRD expression RTHIRD"<<endl;

        ParseTreeNode* node_rthird = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "RSQUARE : ]");
        //$3->add_child(node_rthird);
        ParseTreeNode* node_lthird = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LSQUARE : [");
        //node_lthird->add_child($3);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "ID : "+(yyvsp[-3].symbol_info)->getName());
        //node_id->add_child(node_lthird);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "variable : ID LTHIRD expression RTHIRD");
        ptnode->add_child(node_id);
        ptnode->add_child(node_lthird);
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_rthird);
        (yyval.pt_node) = ptnode;
    }
#line 2644 "y.tab.c"
    break;

  case 41: /* expression: logic_expression  */
#line 1181 "2005050.y"
                              {
        logfile<<"expression : logic_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "expression : logic_expression");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2656 "y.tab.c"
    break;

  case 42: /* expression: variable ASSIGNOP logic_expression  */
#line 1188 "2005050.y"
                                                {
        logfile<<"expression : variable ASSIGNOP logic_expression"<<endl;

        ParseTreeNode* node_assignop = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "ASSIGNOP : =");
        //node_assignop->add_child($3);
        //$1->add_child(node_assignop);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "expression : variable ASSIGNOP logic_expression");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_assignop);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2673 "y.tab.c"
    break;

  case 43: /* logic_expression: rel_expression  */
#line 1201 "2005050.y"
                                  {
        logfile<<"logic_expression : rel_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "logic_expression : rel_expression");
        ptnode->add_child((yyvsp[0].pt_node));
        ptnode->set_value((yyvsp[0].pt_node)->get_value());
        (yyval.pt_node) = ptnode;
    }
#line 2686 "y.tab.c"
    break;

  case 44: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 1209 "2005050.y"
                                                         {
        logfile<<"logic_expression : rel_expression LOGICOP rel_expression"<<endl;

        ParseTreeNode* node_logicop = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "LOGICOP : "+(yyvsp[-1].symbol_info)->getName());
        //node_logicop->add_child($3);
        //$1->add_child(node_logicop);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "logic_expression : rel_expression LOGICOP rel_expression");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_logicop);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2703 "y.tab.c"
    break;

  case 45: /* rel_expression: simple_expression  */
#line 1222 "2005050.y"
                                   {
        logfile<<"rel_expression : simple_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "rel_expression : simple_expression");
        ptnode->add_child((yyvsp[0].pt_node));
        ptnode->set_value((yyvsp[0].pt_node)->get_value());
        (yyval.pt_node) = ptnode;
    }
#line 2716 "y.tab.c"
    break;

  case 46: /* rel_expression: simple_expression RELOP simple_expression  */
#line 1230 "2005050.y"
                                                           {
        logfile<<"rel_expression : simple_expression RELOP simple_expression"<<endl;

        ParseTreeNode* node_relop = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "RELOP : "+(yyvsp[-1].symbol_info)->getName());
        //node_relop->add_child($3);
        //$1->add_child(node_relop);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "rel_expression : simple_expression RELOP simple_expression");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_relop);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;      
    }
#line 2733 "y.tab.c"
    break;

  case 47: /* simple_expression: term  */
#line 1243 "2005050.y"
                         {
        logfile<<"simple_expression : term"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "simple_expression : term");
        ptnode->add_child((yyvsp[0].pt_node));
        ptnode->set_value((yyvsp[0].pt_node)->get_value());
        (yyval.pt_node) = ptnode;
    }
#line 2746 "y.tab.c"
    break;

  case 48: /* simple_expression: simple_expression ADDOP term  */
#line 1251 "2005050.y"
                                                 {
        logfile<<"simple_expression : simple_expression ADDOP term"<<endl;

        ParseTreeNode* node_addop = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "ADDOP : "+(yyvsp[-1].symbol_info)->getName());
        node_addop->set_name((yyvsp[-1].symbol_info)->getName());
        //node_addop->add_child($3);
        //$1->add_child(node_addop);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "simple_expression : simple_expression ADDOP term");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_addop);
        ptnode->add_child((yyvsp[0].pt_node));
        if((yyvsp[-1].symbol_info)->getName()=="+") ptnode->set_value((yyvsp[-2].pt_node)->get_value()+(yyvsp[0].pt_node)->get_value());
        else if((yyvsp[-1].symbol_info)->getName()=="-") ptnode->set_value((yyvsp[-2].pt_node)->get_value()-(yyvsp[0].pt_node)->get_value());
        (yyval.pt_node) = ptnode;
    }
#line 2766 "y.tab.c"
    break;

  case 49: /* term: unary_expression  */
#line 1267 "2005050.y"
                        {
        logfile<<"term : unary_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "term : unary_expression");
        ptnode->add_child((yyvsp[0].pt_node));
        ptnode->set_value((yyvsp[0].pt_node)->get_value());
        (yyval.pt_node) = ptnode;
    }
#line 2779 "y.tab.c"
    break;

  case 50: /* term: term MULOP unary_expression  */
#line 1275 "2005050.y"
                                   {
        logfile<<"term : term MULOP unary_expression"<<endl;

        ParseTreeNode* node_mulop = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "MULOP : "+(yyvsp[-1].symbol_info)->getName());
        node_mulop->set_name((yyvsp[-1].symbol_info)->getName());
        //$1->add_child(node_mulop);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "term : term MULOP unary_expression");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_mulop);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2796 "y.tab.c"
    break;

  case 51: /* unary_expression: ADDOP unary_expression  */
#line 1288 "2005050.y"
                                          {
        logfile<<"unary_expression : ADDOP unary_expression"<<endl;

        ParseTreeNode* node_addop = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "ADDOP : "+(yyvsp[-1].symbol_info)->getName());
        node_addop->set_name((yyvsp[-1].symbol_info)->getName());
        //node_addop->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[0].pt_node)->get_end_line(), "unary_expression : ADDOP unary_expression");
        ptnode->add_child(node_addop);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2812 "y.tab.c"
    break;

  case 52: /* unary_expression: NOT unary_expression  */
#line 1299 "2005050.y"
                                        {
        logfile<<"unary_expression : NOT unary_expression"<<endl;

        ParseTreeNode* node_not = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "NOT : "+(yyvsp[-1].symbol_info)->getName());
        //node_not->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[0].pt_node)->get_end_line(), "unary_expression : NOT unary_expression");
        ptnode->add_child(node_not);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2827 "y.tab.c"
    break;

  case 53: /* unary_expression: factor  */
#line 1309 "2005050.y"
                          {
        logfile<<"unary_expression : factor"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "unary_expression : factor");
        ptnode->add_child((yyvsp[0].pt_node));
        ptnode->set_value((yyvsp[0].pt_node)->get_value());
        (yyval.pt_node) = ptnode;
    }
#line 2840 "y.tab.c"
    break;

  case 54: /* factor: variable  */
#line 1318 "2005050.y"
                  {
        logfile<<"factor : variable "<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "factor : variable");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2852 "y.tab.c"
    break;

  case 55: /* factor: ID LPAREN argument_list RPAREN  */
#line 1325 "2005050.y"
                                        {
        logfile<<"factor : ID LPAREN argument_list RPAREN"<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "RPAREN : )");
        //$3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($3);
        ParseTreeNode* node_id = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[-3].symbol_info)->line_no, "ID : "+(yyvsp[-3].symbol_info)->getName());
        node_id->set_name((yyvsp[-3].symbol_info)->getName());
        //node_id->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-3].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "factor : ID LPAREN argument_list RPAREN");
        ptnode->add_child(node_id);
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_rparen);
        (yyval.pt_node) = ptnode;

    }
#line 2875 "y.tab.c"
    break;

  case 56: /* factor: LPAREN expression RPAREN  */
#line 1343 "2005050.y"
                                  {
        logfile<<"factor : LPAREN expression RPAREN"<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "RPAREN : )");
        //$2->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[-2].symbol_info)->line_no, "LPAREN : (");
        //node_lparen->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "factor : LPAREN expression RPAREN");
        ptnode->add_child(node_lparen);
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_rparen);
        (yyval.pt_node) = ptnode;
    }
#line 2893 "y.tab.c"
    break;

  case 57: /* factor: CONST_INT  */
#line 1356 "2005050.y"
                   {
        logfile<<"factor : CONST_INT"<<endl;

        ParseTreeNode* node_const_int = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "CONST_INT : "+(yyvsp[0].symbol_info)->getName());
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "factor : CONST_INT");
        ptnode->add_child(node_const_int);
        ptnode->set_value(stoi((yyvsp[0].symbol_info)->getName()));
        (yyval.pt_node) = ptnode;
    }
#line 2907 "y.tab.c"
    break;

  case 58: /* factor: CONST_FLOAT  */
#line 1365 "2005050.y"
                     {
        logfile<<"factor : CONST_FLOAT"<<endl;

        ParseTreeNode* node_const_float = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "CONST_FLOAT : "+(yyvsp[0].symbol_info)->getName());
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "factor : CONST_FLOAT");
        ptnode->add_child(node_const_float);
        (yyval.pt_node) = ptnode;
    }
#line 2920 "y.tab.c"
    break;

  case 59: /* factor: variable INCOP  */
#line 1373 "2005050.y"
                        {
        logfile<<"factor : variable INCOP"<<endl;

        ParseTreeNode* node_incop = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "INCOP : ++");
        //$1->add_child(node_incop);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "factor : variable INCOP");
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_incop);
        (yyval.pt_node) = ptnode;
    }
#line 2935 "y.tab.c"
    break;

  case 60: /* factor: variable DECOP  */
#line 1383 "2005050.y"
                        {
        logfile<<"factor : variable DECOP"<<endl;

        ParseTreeNode* node_decop = new ParseTreeNode((yyvsp[0].symbol_info)->line_no, (yyvsp[0].symbol_info)->line_no, "DECOP : --");
        //$1->add_child(node_decop);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-1].pt_node)->get_start_line(), (yyvsp[0].symbol_info)->line_no, "factor : variable DECOP");
        ptnode->add_child((yyvsp[-1].pt_node));
        ptnode->add_child(node_decop);
        (yyval.pt_node) = ptnode;
    }
#line 2950 "y.tab.c"
    break;

  case 61: /* argument_list: arguments  */
#line 1394 "2005050.y"
                          {
        logfile<<"argument_list : arguments"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "argument_list : arguments");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2962 "y.tab.c"
    break;

  case 62: /* argument_list: %empty  */
#line 1401 "2005050.y"
                {
        logfile<<"argument_list : "<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_rule("argument_list : ");
        //ptnode->add_child($1);
        (yyval.pt_node) = ptnode;
    }
#line 2974 "y.tab.c"
    break;

  case 63: /* arguments: arguments COMMA logic_expression  */
#line 1409 "2005050.y"
                                             {
        logfile<<"arguments : arguments COMMA logic_expression"<<endl;

        ParseTreeNode* node_comma = new ParseTreeNode((yyvsp[-1].symbol_info)->line_no, (yyvsp[-1].symbol_info)->line_no, "COMMA : ,");
        //node_comma->add_child($3);
        //$1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[-2].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "arguments : arguments COMMA logic_expression");
        ptnode->add_child((yyvsp[-2].pt_node));
        ptnode->add_child(node_comma);
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 2991 "y.tab.c"
    break;

  case 64: /* arguments: logic_expression  */
#line 1421 "2005050.y"
                             {
        logfile<<"arguments : logic_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode((yyvsp[0].pt_node)->get_start_line(), (yyvsp[0].pt_node)->get_end_line(), "arguments : logic_expression");
        ptnode->add_child((yyvsp[0].pt_node));
        (yyval.pt_node) = ptnode;
    }
#line 3003 "y.tab.c"
    break;


#line 3007 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1430 "2005050.y"

int main(int argc,char *argv[])
{
    FILE* fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
    table = new SymbolTable(11);

    logfile.open("log.txt",ios::app);
    parsetreefile.open("parsetree.txt",ios::app);
    asmfile.open("code.asm", ios::app);
    
	yyin=fp;
	yyparse();

    table->print_all_scopeTable();
    logfile<<"Total Lines: "<<line_count<<endl;
    logfile<<"Total Errors: "<<error_count<<endl;
	fclose(fp);
    peephole_optimization("code.asm", "optimized_code.asm");
    logfile.close();
    parsetreefile.close();
    asmfile.close();
	return 0;
}
