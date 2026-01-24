%{
#include<bits/stdc++.h>

#include "2005050_parseTree.cpp"
#include "2005050_symbolTable.cpp"
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
ofstream errorfile;

SymbolTable *table;
vector<SymbolInfo*> var_decl_list;
vector< pair<string, string> > param_list;

void yyerror(char *s){
	printf("%s\n",s);
}

%}

%union{
    SymbolInfo* symbol_info;
    ParseTreeNode* pt_node;
}

%token<symbol_info> ID VOID INT FLOAT CONST_INT CONST_FLOAT LTHIRD RTHIRD LPAREN RPAREN LCURL RCURL SEMICOLON COMMA FOR IF ELSE WHILE PRINTLN RETURN ASSIGNOP NOT INCOP DECOP
%token TOO_MANY_DECIMAL ILL_FORMED_NUMBER INVALID_ID
%type<pt_node> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments

%right  ASSIGNOP
%left <symbol_info> LOGICOP
%left  <symbol_info> RELOP
%left  <symbol_info> ADDOP
%left  <symbol_info> MULOP
%right  NOT
%right  INCOP DECOP

%nonassoc ELSE

%%

start : program {
        logfile<<"start : program"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line($1->get_start_line());
        ptnode->set_end_line($1->get_end_line());
        ptnode->set_rule("start : program");
        ptnode->add_child($1);
        $$ = ptnode;

        $$->print_tree($$,0);
    }
      ;
program : program unit {
        logfile<<"program : program unit"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line($1->get_start_line());
        ptnode->set_end_line($2->get_end_line());
        ptnode->set_rule("program : program unit");
        $1->add_child($2);
        ptnode->add_child($1);
        $$ = ptnode;
    }
        | unit {
            logfile<<"program : unit"<<endl;
            ParseTreeNode* ptnode = new ParseTreeNode();
            ptnode->set_start_line($1->get_start_line());
            ptnode->set_end_line($1->get_end_line());
            ptnode->set_rule("program : unit");
            ptnode->add_child($1);
            $$ = ptnode;
        }
        ;
unit : var_declaration {
        logfile<<"unit : var_declaration"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line($1->get_start_line());
        ptnode->set_end_line($1->get_end_line());
        ptnode->set_rule("unit : var_declaration");
        ptnode->add_child($1);
        $$ = ptnode;
    }
     | func_declaration {
        logfile<<"unit : func_declaration"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line($1->get_start_line());
        ptnode->set_end_line($1->get_end_line());
        ptnode->set_rule("unit : func_declaration");
        ptnode->add_child($1);
        $$ = ptnode;
    }
     | func_definition {
        logfile<<"unit : func_definition"<<endl;
        ParseTreeNode* ptnode = new ParseTreeNode();
        ptnode->set_start_line($1->get_start_line());
        ptnode->set_end_line($1->get_end_line());
        ptnode->set_rule("unit : func_definition");
        ptnode->add_child($1);
        $$ = ptnode;
    }
     ;
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {
        logfile<<"func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON"<<endl;
        
        SymbolInfo* si = new SymbolInfo($2->getName(), "FUNCTION", $1->get_data_type());
        si->func_parameter_list = param_list;
        param_list.clear();
        table->insert_into_st(si);

        ParseTreeNode* node_semicolon = new ParseTreeNode($6->line_no, $6->line_no, "SEMICOLON : ;");
        ParseTreeNode* node_rparen = new ParseTreeNode($5->line_no, $5->line_no, "RPAREN : )");
        node_rparen->add_child(node_semicolon);
        $4->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($3->line_no, $3->line_no, "LPAREN : (");
        node_lparen->add_child($4);
        ParseTreeNode* node_id = new ParseTreeNode($2->line_no, $2->line_no, "ID : "+$2->getName());
        node_id->add_child(node_lparen);
        $1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $5->line_no, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                 | type_specifier ID LPAREN RPAREN SEMICOLON {
        logfile<<"func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON"<<endl;

        SymbolInfo* si = new SymbolInfo($2->getName(), "FUNCTION", $1->get_data_type());
        table->insert_into_st(si);

        ParseTreeNode* node_semicolon = new ParseTreeNode($5->line_no, $5->line_no, "SEMICOLON : ;");
        ParseTreeNode* node_rparen = new ParseTreeNode($4->line_no, $4->line_no, "RPAREN : )");
        node_rparen->add_child(node_semicolon);
        ParseTreeNode* node_lparen = new ParseTreeNode($3->line_no, $3->line_no, "LPAREN : (");
        node_lparen->add_child(node_rparen);
        ParseTreeNode* node_id = new ParseTreeNode($2->line_no, $2->line_no, "ID : "+$2->getName());
        node_id->add_child(node_lparen);
        $1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $5->line_no, "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                 ;
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement {
        logfile<<"func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement"<<endl;
 
        SymbolInfo* si = new SymbolInfo($2->getName(), "FUNCTION", $1->get_data_type());
        si->func_parameter_list = param_list;
        table->insert_into_st(si);
        table->enterScope();
        func_or_loop = true;
        for(auto p: param_list){
            SymbolInfo* sp = new SymbolInfo(p.first, p.second);
            table->insert_into_st(sp);
        }
        param_list.clear();

        ParseTreeNode* node_rparen = new ParseTreeNode($5->line_no, $5->line_no, "RPAREN : )");
        node_rparen->add_child($6);
        $4->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($3->line_no, $3->line_no, "LPAREN : (");
        node_lparen->add_child($4);
        ParseTreeNode* node_id = new ParseTreeNode($2->line_no, $2->line_no, "ID : "+$2->getName());
        node_id->add_child(node_lparen);
        $1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $6->get_end_line(), "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                | type_specifier ID LPAREN RPAREN compound_statement {
        logfile<<"func_definition : type_specifier ID LPAREN RPAREN compound_statement"<<endl;

        SymbolInfo* si = new SymbolInfo($2->getName(), "FUNCTION", $1->get_data_type());
        //si->func_return_type = $1->get_data_type();
        table->insert_into_st(si);

        ParseTreeNode* node_rparen = new ParseTreeNode($4->line_no, $4->line_no, "RPAREN : )");
        node_rparen->add_child($5);
        ParseTreeNode* node_lparen = new ParseTreeNode($3->line_no, $3->line_no, "LPAREN : (");
        node_lparen->add_child(node_rparen);
        ParseTreeNode* node_id = new ParseTreeNode($2->line_no, $2->line_no, "ID : "+$2->getName());
        node_id->add_child(node_lparen);
        $1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $5->get_end_line(), "func_definition : type_specifier ID LPAREN RPAREN compound_statement");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                ;
parameter_list : parameter_list COMMA type_specifier ID {
        logfile<<"parameter_list : parameter_list COMMA type_specifier ID"<<endl;

        param_list.push_back(make_pair($4->getName(),$3->get_data_type()));

        ParseTreeNode* node_id = new ParseTreeNode($4->line_no, $4->line_no, "ID : "+$4->getName());
        $3->add_child(node_id);
        ParseTreeNode* node_comma = new ParseTreeNode($2->line_no, $2->line_no, "COMMA : ,");
        node_comma->add_child($3);
        $1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $4->line_no, "parameter_list : parameter_list COMMA type_specifier ID");
        ptnode->add_child($1);
        $$ = ptnode;
    }
               | parameter_list COMMA type_specifier {
        logfile<<"parameter_list : parameter_list COMMA type_specifier"<<endl;

        param_list.push_back(make_pair("",$3->get_data_type()));

        ParseTreeNode* node_comma = new ParseTreeNode($2->line_no, $2->line_no, "COMMA : comma");
        node_comma->add_child($3);
        $1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->get_end_line(), "parameter_list : parameter_list COMMA type_specifier");
        ptnode->add_child($1);
        $$ = ptnode;
    }
               | type_specifier ID {
        logfile<<"parameter_list : type_specifier ID"<<endl;

        param_list.clear();
        param_list.push_back(make_pair($2->getName(),$1->get_data_type()));

        ParseTreeNode* node_id = new ParseTreeNode($2->line_no, $2->line_no, "ID : "+$2->getName());
        $1->add_child(node_id);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $2->line_no, "parameter_list : type_specifier ID");
        ptnode->add_child($1);
        $$ = ptnode;
    }
               | type_specifier {
        logfile<<"parameter_list : type_specifier"<<endl;

        param_list.clear();
        param_list.push_back(make_pair("",$1->get_data_type()));

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "parameter_list : type_specifier");
        ptnode->add_child($1);
        $$ = ptnode;
    }
               ;
compound_statement : LCURL statements RCURL {
        logfile<<"compound_statement : LCURL statements RCURL"<<endl;

        table->print_all_scopeTable();
        table->exitScope();
        ParseTreeNode* node_rcurl = new ParseTreeNode($3->line_no, $3->line_no, "RCURL : }");
        $2->add_child(node_rcurl);
        ParseTreeNode* node_lcurl = new ParseTreeNode($1->line_no, $1->line_no, "LCURL : {");
        node_lcurl->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $3->line_no, "compound_statement : LCURL statements RCURL");
        ptnode->add_child(node_lcurl);
        $$ = ptnode;
    }
                   | LCURL RCURL {
        logfile<<"compound_statement : LCURL RCURL"<<endl;

        ParseTreeNode* node_rcurl = new ParseTreeNode($2->line_no, $2->line_no, "RCURL : }");
        ParseTreeNode* node_lcurl = new ParseTreeNode($1->line_no, $1->line_no, "LCURL : {");
        node_lcurl->add_child(node_rcurl);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $2->line_no, "compound_statement : LCURL RCURL");
        ptnode->add_child(node_lcurl);
        $$ = ptnode;
    }
                   ;
var_declaration : type_specifier declaration_list SEMICOLON {
        logfile<<"var_declaration : type_specifier declaration_list SEMICOLON"<<endl;
        for(auto s: var_decl_list){
            SymbolInfo* si = new SymbolInfo(s->getName(), $1->get_data_type());
            table->insert_into_st(si);
        }
        var_decl_list.clear();
        ParseTreeNode* node_semicolon = new ParseTreeNode($3->line_no, $3->line_no, "SEMICOLON : ;");
        $2->set_data_type($1->get_data_type());
        $2->add_child(node_semicolon);
        $1->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->line_no, "var_declaration : type_specifier declaration_list SEMICOLON");
        ptnode->add_child($1);
        ptnode->set_data_type($1->get_data_type());
        $$ = ptnode;
        //table->print_all_scopeTable();
    }
                ;
type_specifier : INT  {
        logfile<<"type_specifier : INT"<<endl;
        
        ParseTreeNode* node_int = new ParseTreeNode($1->line_no, $1->line_no, "INT : int");
        node_int->set_data_type("INT");
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "type_specifier : INT");
        ptnode->set_data_type("INT");
        ptnode->add_child(node_int);
        $$ = ptnode;
    }
               | FLOAT {
        logfile<<"type_specifier : FLOAT"<<endl; 
       
        ParseTreeNode* node_float = new ParseTreeNode($1->line_no, $1->line_no, "FLOAT : float");
        node_float->set_data_type("FLOAT");
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "type_specifier : FLOAT");
        ptnode->set_data_type("FLOAT");
        ptnode->add_child(node_float);
        $$ = ptnode;
    }
               | VOID  {
        logfile<<"type_specifier : VOID"<<endl;
          
        ParseTreeNode* node_void = new ParseTreeNode($1->line_no, $1->line_no, "VOID : void");
        node_void->set_data_type("VOID");
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "type_specifier : VOID");
        ptnode->set_data_type("VOID");
        ptnode->add_child(node_void);
        $$ = ptnode;   
    }
               ;
declaration_list : declaration_list COMMA ID {
        logfile<<"declaration_list : declaration_list COMMA ID "<<endl;
        var_decl_list.push_back($3);

        ParseTreeNode* node_id = new ParseTreeNode($3->line_no, $3->line_no, "ID : "+$3->getName());
        ParseTreeNode* node_comma = new ParseTreeNode($2->line_no, $2->line_no, "COMMA : ,");
        node_comma->add_child(node_id);
        $1->add_child(node_comma);

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->line_no, "declaration_list : declaration_list COMMA ID");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
        logfile<<"declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD"<<endl;
        SymbolInfo* s = $3;
        s->array_size = stoi($5->getName());
        var_decl_list.push_back(s);

        ParseTreeNode* node_rthird = new ParseTreeNode($6->line_no, $6->line_no, "RSQUARE : ]");
        ParseTreeNode* node_const_int = new ParseTreeNode($5->line_no, $5->line_no, "CONST_INT : "+$5->getName());
        node_const_int->add_child(node_rthird);
        ParseTreeNode* node_lthird = new ParseTreeNode($4->line_no, $4->line_no, "LSQUARE : [");
        node_lthird->add_child(node_const_int);
        ParseTreeNode* node_id = new ParseTreeNode($3->line_no, $3->line_no, "ID : "+$3->getName());
        node_id->add_child(node_lthird);
        ParseTreeNode* node_comma = new ParseTreeNode($2->line_no, $2->line_no, "COMMA : ,");
        node_comma->add_child(node_id);
        $1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $6->line_no, "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                 | ID  {
        logfile<<"declaration_list : ID"<<endl;
        var_decl_list.clear();
        var_decl_list.push_back($1);

        ParseTreeNode* node_id = new ParseTreeNode($1->line_no, $1->line_no, "ID : "+$1->getName());
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "declaration_list : ID");
        ptnode->add_child(node_id);
        $$ = ptnode;
    }
                 | ID LTHIRD CONST_INT RTHIRD {
        logfile<<"declaration_list : ID LTHIRD CONST_INT RTHIRD"<<endl;
        SymbolInfo* s = $1;
        s->array_size = stoi($3->getName());
        var_decl_list.clear();
        var_decl_list.push_back(s);
        
        ParseTreeNode* node_rthird = new ParseTreeNode($4->line_no, $4->line_no, "RSQUARE : ]");
        ParseTreeNode* node_const_int = new ParseTreeNode($3->line_no, $3->line_no, "CONST_INT : "+$3->getName());
        node_const_int->add_child(node_rthird);
        ParseTreeNode* node_lthird = new ParseTreeNode($2->line_no, $2->line_no, "LSQUARE : [");
        node_lthird->add_child(node_const_int);
        ParseTreeNode* node_id = new ParseTreeNode($1->line_no, $1->line_no, "ID : "+$1->getName());
        node_id->add_child(node_lthird);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $4->line_no, "declaration_list : ID LTHIRD CONST_INT RTHIRD");
        ptnode->add_child(node_id);
        $$ = ptnode;
    }
                 ;
statements : statement {
        logfile<<"statements : statement"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "statements : statement");
        ptnode->add_child($1);
        $$ = ptnode;
    }
           | statements statement {
        logfile<<"statements : statements statement"<<endl;

        $1->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $2->get_end_line(), "statements : statements statement");
        ptnode->add_child($1);
        $$ = ptnode;
    }
           ;
statement : var_declaration {
        logfile<<"statement : var_declaration"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "statement : var_declaration");
        ptnode->add_child($1);
        $$ = ptnode;
    }
          | expression_statement {
        logfile<<"statement : expression_statement"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "statement : expression_statement");
        ptnode->add_child($1);
        $$ = ptnode;
    }
          | compound_statement {
        logfile<<"statement : compound_statement"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "statement : compound_statement");
        ptnode->add_child($1);
        $$ = ptnode;
    }
          | FOR LPAREN expression_statement expression_statement expression RPAREN statement {
        logfile<<"statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode($6->line_no, $6->line_no, "RPAREN : )");
        node_rparen->add_child($7);
        $5->add_child(node_rparen);
        $4->add_child($5);
        $3->add_child($4);
        ParseTreeNode* node_lparen = new ParseTreeNode($2->line_no, $2->line_no, "LPAREN : (");
        node_lparen->add_child($3);
        ParseTreeNode* node_for = new ParseTreeNode($1->line_no, $1->line_no, "FOR : for");
        node_for->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $7->get_end_line(), "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
        ptnode->add_child(node_for);
        $$ = ptnode;
    }
          | IF LPAREN expression RPAREN statement {
        logfile<<"statement : IF LPAREN expression RPAREN statement"<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode($4->line_no, $4->line_no, "RPAREN : )");
        node_rparen->add_child($5);
        $3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($2->line_no, $2->line_no, "LPAREN : (");
        node_lparen->add_child($3); 
        ParseTreeNode* node_if = new ParseTreeNode($1->line_no, $1->line_no, "IF : if");
        node_if->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $5->get_end_line(), "statement : IF LPAREN expression RPAREN statement");
        ptnode->add_child(node_if);
        $$ = ptnode;
    }
          | IF LPAREN expression RPAREN statement ELSE statement {
        logfile<<"statement : IF LPAREN expression RPAREN statement ELSE statement"<<endl;

        ParseTreeNode* node_else = new ParseTreeNode($6->line_no, $6->line_no, "ELSE : else");
        node_else->add_child($7);
        $5->add_child(node_else);
        ParseTreeNode* node_rparen = new ParseTreeNode($4->line_no, $4->line_no, "RPAREN : )");
        node_rparen->add_child($5);
        $3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($2->line_no, $2->line_no, "LPAREN : (");
        node_lparen->add_child($3); 
        ParseTreeNode* node_if = new ParseTreeNode($1->line_no, $1->line_no, "IF : if");
        node_if->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $7->get_end_line(), "statement : IF LPAREN expression RPAREN statement ELSE statement");
        ptnode->add_child(node_if);
        $$ = ptnode;
    }
          | WHILE LPAREN expression RPAREN statement {
        logfile<<"statement : WHILE LPAREN expression RPAREN statement"<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode($4->line_no, $4->line_no, "RPAREN : )");
        node_rparen->add_child($5);
        $3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($2->line_no, $2->line_no, "LPAREN : (");
        node_lparen->add_child($3); 
        ParseTreeNode* node_while = new ParseTreeNode($1->line_no, $1->line_no, "WHILE : while");
        node_while->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $5->get_end_line(), "statement : WHILE LPAREN expression RPAREN statement");
        ptnode->add_child(node_while);
        $$ = ptnode;
    }
          | PRINTLN LPAREN ID RPAREN SEMICOLON {
        logfile<<"statement : PRINTLN LPAREN ID RPAREN SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode($5->line_no, $5->line_no, "SEMICOLON : ;");
        ParseTreeNode* node_rparen = new ParseTreeNode($4->line_no, $4->line_no, "RPAREN : )");
        node_rparen->add_child(node_semicolon);
        ParseTreeNode* node_id = new ParseTreeNode($3->line_no, $3->line_no, "ID : "+$3->getName());
        node_id->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($2->line_no, $2->line_no, "LPAREN : (");
        node_lparen->add_child(node_id); 
        ParseTreeNode* node_println = new ParseTreeNode($1->line_no, $1->line_no, "PRINTLN : println");
        node_println->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $5->line_no, "statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
        ptnode->add_child(node_println);
        $$ = ptnode;
    }
          | RETURN expression SEMICOLON {
        logfile<<"statement : RETURN expression SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode($3->line_no, $3->line_no, "SEMICOLON : ;");
        $2->add_child(node_semicolon);
        ParseTreeNode* node_return = new ParseTreeNode($1->line_no, $1->line_no, "RETURN : return");
        node_return->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $3->line_no, "statement : RETURN expression SEMICOLON");
        ptnode->add_child(node_return);
        $$ = ptnode;
    }
          ;
expression_statement : SEMICOLON {
        logfile<<"expression_statement : SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode($1->line_no, $1->line_no, "SEMICOLON : ;");
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "expression_statement : SEMICOLON");
        ptnode->add_child(node_semicolon);
        $$ = ptnode;
    }
                     | expression SEMICOLON {
        logfile<<"expression_statement : expression SEMICOLON"<<endl;

        ParseTreeNode* node_semicolon = new ParseTreeNode($2->line_no, $2->line_no, "SEMICOLON : ;");
        $1->add_child(node_semicolon);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $2->line_no, "expression_statement : expression SEMICOLON");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                     ;
variable : ID {
        logfile<<"variable : ID "<<endl;

        if($1->array_size!=-1){
            errorfile<<"Line# "<<$1->line_no<<": '"<<$1->getName()<<" is an array"<<endl;
        }
        SymbolInfo* inserted = table->lookUp_in_st($1->getName());
        if(inserted == nullptr){
            errorfile<<"Line# "<<$1->line_no<<": Undeclared variable '"<<$1->getName()<<"'"<<endl;
        }

        ParseTreeNode* node_id = new ParseTreeNode($1->line_no, $1->line_no, "ID : "+$1->getName());
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "variable : ID");
        ptnode->add_child(node_id);
        $$ = ptnode;
    }
         | ID LTHIRD expression RTHIRD {
        logfile<<"variable : ID LTHIRD expression RTHIRD"<<endl;

        if($1->array_size==-1){
            errorfile<<"Line# "<<$1->line_no<<": '"<<$1->getName()<<" is not an array"<<endl;
        }
        SymbolInfo* inserted = table->lookUp_in_st($1->getName());
        if(inserted == nullptr){
            errorfile<<"Line# "<<$1->line_no<<": Undeclared variable '"<<$1->getName()<<"'"<<endl;
        }

        ParseTreeNode* node_rthird = new ParseTreeNode($4->line_no, $4->line_no, "RSQUARE : ]");
        $3->add_child(node_rthird);
        ParseTreeNode* node_lthird = new ParseTreeNode($2->line_no, $2->line_no, "LSQUARE : [");
        node_lthird->add_child($3);
        ParseTreeNode* node_id = new ParseTreeNode($1->line_no, $1->line_no, "ID : "+$1->getName());
        node_id->add_child(node_lthird);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $4->line_no, "variable : ID LTHIRD expression RTHIRD");
        ptnode->add_child(node_id);
        $$ = ptnode;
    }
         ;
expression : logic_expression {
        logfile<<"expression : logic_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "expression : logic_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
           | variable ASSIGNOP logic_expression {
        logfile<<"expression : variable ASSIGNOP logic_expression"<<endl;

        ParseTreeNode* node_assignop = new ParseTreeNode($2->line_no, $2->line_no, "ASSIGNOP : =");
        node_assignop->add_child($3);
        $1->add_child(node_assignop);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->get_end_line(), "expression : variable ASSIGNOP logic_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
           ;
logic_expression : rel_expression {
        logfile<<"logic_expression : rel_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "logic_expression : rel_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                 | rel_expression LOGICOP rel_expression {
        logfile<<"logic_expression : rel_expression LOGICOP rel_expression"<<endl;

        ParseTreeNode* node_logicop = new ParseTreeNode($2->line_no, $2->line_no, "LOGICOP : "+$2->getName());
        node_logicop->add_child($3);
        $1->add_child(node_logicop);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->get_end_line(), "logic_expression : rel_expression LOGICOP rel_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                 ;
rel_expression : simple_expression {
        logfile<<"rel_expression : simple_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "rel_expression : simple_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
               | simple_expression RELOP simple_expression {
        logfile<<"rel_expression : simple_expression RELOP simple_expression"<<endl;

        ParseTreeNode* node_relop = new ParseTreeNode($2->line_no, $2->line_no, "RELOP : "+$2->getName());
        node_relop->add_child($3);
        $1->add_child(node_relop);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->get_end_line(), "rel_expression : simple_expression RELOP simple_expression");
        ptnode->add_child($1);
        $$ = ptnode;      
    }
               ;
simple_expression : term {
        logfile<<"simple_expression : term"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "simple_expression : term");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                  | simple_expression ADDOP term {
        logfile<<"simple_expression : simple_expression ADDOP term"<<endl;

        ParseTreeNode* node_addop = new ParseTreeNode($2->line_no, $2->line_no, "ADDOP : "+$2->getName());
        node_addop->add_child($3);
        $1->add_child(node_addop);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->get_end_line(), "simple_expression : simple_expression ADDOP term");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                  ;
term : unary_expression {
        logfile<<"term : unary_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "term : unary_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
     | term MULOP unary_expression {
        logfile<<"term : term MULOP unary_expression"<<endl;

        ParseTreeNode* node_mulop = new ParseTreeNode($2->line_no, $2->line_no, "MULOP : "+$2->getName());
        node_mulop->add_child($3);
        $1->add_child(node_mulop);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->get_end_line(), "term : term MULOP unary_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
     ;
unary_expression : ADDOP unary_expression {
        logfile<<"unary_expression : ADDOP unary_expression"<<endl;

        ParseTreeNode* node_addop = new ParseTreeNode($1->line_no, $1->line_no, "ADDOP : "+$1->getName());
        node_addop->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $2->get_end_line(), "unary_expression : ADDOP unary_expression");
        ptnode->add_child(node_addop);
        $$ = ptnode;
    }
                 | NOT unary_expression {
        logfile<<"unary_expression : NOT unary_expression"<<endl;

        ParseTreeNode* node_not = new ParseTreeNode($1->line_no, $1->line_no, "NOT : "+$1->getName());
        node_not->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $2->get_end_line(), "unary_expression : NOT unary_expression");
        ptnode->add_child(node_not);
        $$ = ptnode;
    }
                 | factor {
        logfile<<"unary_expression : factor"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "unary_expression : factor");
        ptnode->add_child($1);
        $$ = ptnode;
    }
                 ;
factor : variable {
        logfile<<"factor : variable "<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "factor : variable");
        ptnode->add_child($1);
        $$ = ptnode;
    }
       | ID LPAREN argument_list RPAREN {
        logfile<<"factor : ID LPAREN argument_list RPAREN"<<endl;

        if($1->getType()!= "FUNCTION"){
            errorfile<<"Line# "<<$1->line_no<<": '"<<$1->getName()<<"' is not a function"<<endl;
        }

        ParseTreeNode* node_rparen = new ParseTreeNode($4->line_no, $4->line_no, "RPAREN : )");
        $3->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($2->line_no, $2->line_no, "LPAREN : (");
        node_lparen->add_child($3);
        ParseTreeNode* node_id = new ParseTreeNode($1->line_no, $1->line_no, "ID : "+$1->getName());
        node_id->add_child(node_lparen);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $4->line_no, "factor : ID LPAREN argument_list RPAREN");
        ptnode->add_child(node_id);
        $$ = ptnode;

    }
       | LPAREN expression RPAREN {
        logfile<<"factor : LPAREN expression RPAREN"<<endl;

        ParseTreeNode* node_rparen = new ParseTreeNode($3->line_no, $3->line_no, "RPAREN : )");
        $2->add_child(node_rparen);
        ParseTreeNode* node_lparen = new ParseTreeNode($1->line_no, $1->line_no, "LPAREN : (");
        node_lparen->add_child($2);
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $3->line_no, "factor : LPAREN expression RPAREN");
        ptnode->add_child(node_lparen);
        $$ = ptnode;
    }
       | CONST_INT {
        logfile<<"factor : CONST_INT"<<endl;

        ParseTreeNode* node_const_int = new ParseTreeNode($1->line_no, $1->line_no, "CONST_INT : "+$1->getName());
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "factor : CONST_INT");
        ptnode->add_child(node_const_int);
        $$ = ptnode;
    }
       | CONST_FLOAT {
        logfile<<"factor : CONST_FLOAT"<<endl;

        ParseTreeNode* node_const_float = new ParseTreeNode($1->line_no, $1->line_no, "CONST_FLOAT : "+$1->getName());
        ParseTreeNode* ptnode = new ParseTreeNode($1->line_no, $1->line_no, "factor : CONST_FLOAT");
        ptnode->add_child(node_const_float);
        $$ = ptnode;
    }
       | variable INCOP {
        logfile<<"factor : variable INCOP"<<endl;

        ParseTreeNode* node_incop = new ParseTreeNode($2->line_no, $2->line_no, "INCOP : ++");
        $1->add_child(node_incop);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $2->line_no, "factor : variable INCOP");
        ptnode->add_child($1);
        $$ = ptnode;
    }
       | variable DECOP {
        logfile<<"factor : variable DECOP"<<endl;

        ParseTreeNode* node_decop = new ParseTreeNode($2->line_no, $2->line_no, "DECOP : --");
        $1->add_child(node_decop);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $2->line_no, "factor : variable DECOP");
        ptnode->add_child($1);
        $$ = ptnode;
    }
       ;
argument_list : arguments {
        logfile<<"argument_list : arguments"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "argument_list : arguments");
        ptnode->add_child($1);
        $$ = ptnode;
    }
              | {
        logfile<<"argument_list : "<<endl;
    }
              ;
arguments : arguments COMMA logic_expression {
        logfile<<"arguments : arguments COMMA logic_expression"<<endl;

        ParseTreeNode* node_comma = new ParseTreeNode($2->line_no, $2->line_no, "COMMA : ,");
        node_comma->add_child($3);
        $1->add_child(node_comma);
        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $3->get_end_line(), "arguments : arguments COMMA logic_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
          | logic_expression {
        logfile<<"arguments : logic_expression"<<endl;

        ParseTreeNode* ptnode = new ParseTreeNode($1->get_start_line(), $1->get_end_line(), "arguments : logic_expression");
        ptnode->add_child($1);
        $$ = ptnode;
    }
          ;

%%
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
    errorfile.open("error.txt", ios::app);
    
	yyin=fp;
	yyparse();

    table->print_all_scopeTable();
    logfile<<"Total Lines: "<<line_count<<endl;
    logfile<<"Total Errors: "<<error_count<<endl;
	fclose(fp);
    logfile.close();
    parsetreefile.close();
    errorfile.close();
	return 0;
}