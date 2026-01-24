#include <bits/stdc++.h>
using namespace std;
int label = 0;

void gen_start_code()
{
    ofstream asmfile;
    asmfile.open("code.asm", ios::app);
    string code = "\
.MODEL SMALL\n\
\n\
.STACK 1000H\n\
\n\
.DATA\n\
\n\
NUMBER DB '00000$'\n";
    asmfile << code;
}

string gen_new_line_code(){
    string code = "\n\
new_line proc\n\
    push ax\n\
    push dx\n\
    mov ah,2\n\
    mov dl,0Dh\n\
    int 21h\n\
    mov ah,2\n\
    mov dl,0Ah\n\
    int 21h\n\
    pop dx\n\
    pop ax\n\
    ret\n\
    new_line endp\n";
    return code;
}

string gen_print_output_code(){
    string code = "\
print_output proc  ;print what is in ax\n\
    push ax\n\
    push bx\n\
    push cx\n\
    push dx\n\
    push si\n\
    lea si,number\n\
    mov bx,10\n\
    add si,4\n\
    cmp ax,0\n\
    jnge negate\n\
    print:\n\
    xor dx,dx\n\
    div bx\n\
    mov [si],dl\n\
    add [si],'0'\n\
    dec si\n\
    cmp ax,0\n\
    jne print\n\
    inc si\n\
    lea dx,si\n\
    mov ah,9\n\
    int 21h\n\
    pop si\n\
    pop dx\n\
    pop cx\n\
    pop bx\n\
    pop ax\n\
    ret\n\
    negate:\n\
    push ax\n\
    mov ah,2\n\
    mov dl,'-'\n\
    int 21h\n\
    pop ax\n\
    neg ax\n\
    jmp print\n\
    print_output endp\n\n";
    return code;
}


void gen_global_variable(string var_name, int array_size){
    ofstream asmfile;
    asmfile.open("code.asm", ios::app);

    string code;
    if(array_size > 0){
        code="\
"+var_name+" DW "+to_string(array_size)+" DUP(0) "+"\n";
    }
    else{
        code="\
"+var_name+" DW 0"+"\n";
    }
    asmfile<<code;
}

void gen_func_start_code(string func_name){
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\n" + func_name + " PROC\n";
    if(func_name == "main"){
        code+= "\
    MOV AX, @DATA\n\
    MOV DS, AX\n";
    }
    else{
        code+="\
    PUSH BP\n";
    }
    temp_file<<code;
}

void gen_func_end_code(string func_name, int arg_size){
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code;
    int pop_size = arg_size * 2;
    if(func_name == "main"){
        code = "\
    MOV AX, 4CH\n\
    INT 21H\n";
    }
    else{
        code = "\
    POP BP\n\
    RET " + to_string(pop_size) + "\n";
    }
    code += func_name+" ENDP\n";
    temp_file<<code;
}

void gen_mov(string reg1, string reg2)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    MOV " + reg1 +
                  ", " + reg2 + "\n";
    temp_file<<code;
}

void gen_mov(string reg1, int val)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    MOV " + reg1 +
                  ", " + to_string(val) + "\n";
    temp_file<<code;
}

void gen_push(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    PUSH " + reg + "\n";
    temp_file << code;
}

void gen_pop(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    POP " + reg + "\n";
    temp_file << code;
}

void gen_call(string func_name)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    CALL " + func_name +
                  "\n";
    temp_file << code;
}

void gen_add(string reg1, string reg2)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    ADD " + reg1 +
                  ", " + reg2 + "\n";
    temp_file << code;
}

void gen_add(string reg, int val)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    ADD " + reg + ", " +
                  to_string(val) + "\n";
    temp_file << code;
}

void gen_sub(string reg1, string reg2)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    SUB " + reg1 +
                  ", " + reg2 + "\n";
    temp_file << code;
}

void gen_sub(string reg, int val)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    SUB " + reg + ", " +
                  to_string(val) + "\n";
    temp_file << code;
}

void gen_xchg(string reg1, string reg2)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    XCHG " + reg1 +
                  ", " + reg2 + "\n";
    temp_file << code;
}

void gen_imul(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    IMUL " + reg +
                  "\n";
    temp_file << code;
}

void gen_idiv(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    IDIV " + reg +
                  "\n";
    temp_file << code;
}

void gen_xor(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    XOR " + reg +
                 " , " + reg + "\n";
    temp_file << code;
}

void gen_and(string reg1, string reg2)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    AND " + reg1 +
                  ", " + reg2 + "\n";
    temp_file << code;
}

void gen_or(string reg1, string reg2)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    OR " + reg1 +
                  ", " + reg2 + "\n";
    temp_file << code;
}

void gen_not(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    NOT " + reg + "\n";
    temp_file << code;
}

void gen_inc(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    INC " + reg + "\n";
    temp_file << code;
}

void gen_dec(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    DEC " + reg + "\n";
    temp_file << code;
}

void gen_cmp(string reg1, string reg2)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    CMP " + reg1 +
                  ", " + reg2 + "\n";
    temp_file << code;
}

void gen_cmp(string reg1, int val)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    CMP " + reg1 +
                  ", " + to_string(val) + "\n";
    temp_file << code;
}

void gen_neg(string reg)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = "\
    NEG " + reg + "\n";
    temp_file << code;
}

string get_newlabel()
{
    return "L" + to_string(label++);
}

void gen_label(string lbl)
{
    ofstream temp_file;
    temp_file.open("code.asm",ios::app);
    string code = lbl + ":\n";
    temp_file << code;
}

void gen_end_code(bool is_print){
    ofstream asmfile;
    asmfile.open("code.asm", ios::app);
    string code;
    if(is_print){
        code= gen_new_line_code()+ "\n"+gen_print_output_code() + "END MAIN\n";
    }
    else{
        code = "END MAIN\n";
    }
    asmfile << code;
}

void peephole_optimization(string src_name, string dst_name){
    ifstream infile;
    infile.open(src_name);
    ofstream out;
    out.open(dst_name, ios::app);
    vector<string> all_line;
    string line;

    while(getline(infile, line)){
        all_line.push_back(line);
    }

    for(int k=0; k<2; k++){
        for(int i=0; i<all_line.size(); i++){
            line = all_line[i];
            line.erase(0, line.find_first_not_of(" \t"));

            string op = line.substr(0, line.find(" "));

            if(op == "PUSH" && i<all_line.size()-1){
                string next_line = all_line[i+1];
                next_line.erase(0, next_line.find_first_not_of(" \t"));
                string next_op = next_line.substr(0, next_line.find(" "));

                if(next_op == "POP"){
                    string reg = line.substr(line.find(" ") + 1);
                    string next_reg = next_line.substr(next_line.find(" ") + 1);
                    if(reg == next_reg){
                        all_line.erase(all_line.begin()+i+1);
                        all_line.erase(all_line.begin()+i);
                        i--;
                        continue;
                    }
                }
            }

            if(op == "MOV" && i<all_line.size()-1){
                string next_line = all_line[i+1];
                next_line.erase(0, next_line.find_first_not_of(" \t"));
                string next_op = next_line.substr(0, next_line.find(" "));
                if(next_op == "MOV"){
                    string reg1 = line.substr(line.find(" ") + 1, line.find(",") - line.find(" ") - 1);
                    string reg2 = line.substr(line.find(",") + 2);
                    string next_reg1 = next_line.substr(next_line.find(" ") + 1, next_line.find(",") - next_line.find(" ") - 1);
                    string next_reg2 = next_line.substr(next_line.find(",") + 2);

                    if(reg1==next_reg2 && reg2==next_reg1){
                        all_line.erase(all_line.begin()+i+1);
                        continue;
                    }
                }
            }

            if(op == "MOV" && i<all_line.size()-1){
                    string reg1 = line.substr(line.find(" ") + 1, line.find(",") - line.find(" ") - 1);
                    string reg2 = line.substr(line.find(",") + 2);

                    if(reg1==reg2){
                        all_line.erase(all_line.begin()+i);
                        i--;
                        continue;
                    }
                
            }

            if(op == "ADD"){
                string reg2 = line.substr(line.find(",") + 2);
                if(reg2=="0"){
                    all_line.erase(all_line.begin()+i);
                    i--;
                    continue;
                }
            }
        }
    }

    for(auto l : all_line){
        out<<l<<endl;
    }
    out.close();
}
