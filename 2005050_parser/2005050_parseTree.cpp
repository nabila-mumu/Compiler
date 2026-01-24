#include<bits/stdc++.h>

using namespace std;

class ParseTreeNode{
    int start_line;
    int end_line;
    string data_type;
    string rule;
    vector<ParseTreeNode*> child_list;

public:
    ParseTreeNode(){
        start_line = 0; 
        end_line = 0;
        data_type = "NULL";
        rule = "";
    }

    ParseTreeNode(int sl, int el, string r){
        start_line = sl;
        end_line = el;
        rule = r;
    }

    int get_start_line(){
        return start_line;
    }

    int get_end_line(){
        return end_line;
    }

    string get_data_type(){
        return data_type;
    }

    string get_rule(){
        return rule;
    }

    vector<ParseTreeNode*> get_child_list(){
        return child_list;
    }

    void set_start_line(int st_line){
        start_line = st_line;
    }

    void set_end_line(int e_line){
        end_line = e_line;
    }

    void set_data_type(string d_type){
        data_type = d_type;
    }

    void set_rule(string r){
        rule = r;
    }

    void add_child(ParseTreeNode* pt_node){
        child_list.push_back(pt_node);
    }

    void set_child_list(vector<ParseTreeNode*> c_list){
        child_list = c_list;
    }

    void print_tree(ParseTreeNode* root, int depth){
        ofstream outputFile;
        outputFile.open("parsetree.txt", ios::app);

        if(root == nullptr) return;
        for(int i=0; i<depth; i++){
            outputFile<<" ";
        }

        if(root->child_list.size() == 0){
            outputFile<< root->get_rule()<< "\t<Line: " <<root->get_start_line()<< ">" <<endl;
        }
        else{
            outputFile<< root->get_rule()<< "\t<Line: " <<root->get_start_line()<< "-" <<root->get_end_line() << ">" <<endl;
        }
        for(auto c: root->get_child_list()){
            print_tree(c, depth+1);
        }
    }
};