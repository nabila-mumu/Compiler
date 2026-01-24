#include<bits/stdc++.h>
#include "2005050_classes.cpp"

using namespace std;

int main()
{
    ifstream infile;
    infile.open("input.txt");

    ofstream outputFile;
    outputFile.open("output.txt", ios::app);
    string line;
    int total_buckets;
    int cmd_no=0;

    infile>>total_buckets;
    SymbolTable* sTable = new SymbolTable(total_buckets);
    getline(infile, line);
    while(getline(infile, line))
    {
        cmd_no++;
        outputFile<<"Cmd "<<cmd_no<<": "<<line<<endl;

        stringstream str(line);
        string strArray[10];

        int count = 0;
        while(str >> strArray[count] )
        {
            count++;
        }
        char c = strArray[0].at(0);
        switch(c)
        {
        case 'I':
            if(count!=3) outputFile<<"	Wrong number of arguments for the command I"<<endl;
            else
            {
                bool inserted = sTable->insert_into_st(strArray[1], strArray[2]);
                if(!inserted)
                {
                    outputFile<<"	'"<<strArray[1]<<"' already exists in the current ScopeTable# "<<sTable->current_scopetable->getId()<<endl;
                }
            }
            break;

        case 'D':
            if(count!=2) outputFile<<"	Wrong number of arguments for the command D"<<endl;
            else
            {
                bool deleted = sTable->remove_from_st(strArray[1]);
                if(!deleted)
                {
                    outputFile<<"	Not found in the current ScopeTable# "<<sTable->current_scopetable->getId()<<endl;
                }
            }
            break;

        case 'E':
            if(count!=1) outputFile<<"	Wrong number of arguments for the command E"<<endl;
            else sTable->exitScope();
            break;

        case 'S':
            if(count!=1) outputFile<<"	Wrong number of arguments for the command S"<<endl;
            else sTable->enterScope();
            break;

        case 'P':
            if(count!=2) outputFile<<"	Wrong number of arguments for the command P"<<endl;
            else
            {
                if(strArray[1] == "A") sTable->print_all_scopeTable();
                else if(strArray[1] == "C") sTable->print_current_scopeTable();
                else outputFile<<"	Invalid argument for the command P"<<endl;
            }
            break;

        case 'L':
            if(count!=2) outputFile<<"	Wrong number of arguments for the command L"<<endl;
            else sTable->lookUp_in_st(strArray[1]);
            break;

        case 'Q':
            if(count!=1) outputFile<<"	Wrong number of arguments for the command Q"<<endl;
            else delete sTable;
            break;
        }

    }

    infile.close();
    return 0;
}
