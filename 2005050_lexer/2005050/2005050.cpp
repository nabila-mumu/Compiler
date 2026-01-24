#include<bits/stdc++.h>

using namespace std;

class SymbolInfo
{
private:
    string Name;
    string Type;
public:
    SymbolInfo* Next;

    SymbolInfo(string name, string type)
    {
        Name = name;
        Type = type;
        Next = NULL;
    }

    ~SymbolInfo()
    {
        delete Next;
    }

    string getName()
    {
        return Name;
    }

    string getType()
    {
        return Type;
    }
};

unsigned long long sdbmHash(string Name)
{
    unsigned long long hash = 0;
    const char* str = Name.c_str();

    // Perform the hash calculation
    while (*str)
    {
        // Equivalent to: hash = 65599 * hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

class ScopeTable
{
private:
    string id;
    unsigned long long total_buckets;

public:
    int current_Id;
    int current_position;

    ScopeTable* parentScope;
    SymbolInfo** hash_table;

    //constructor
    ScopeTable(int n)
    {
        total_buckets = static_cast<unsigned long long> (n);
        hash_table = new SymbolInfo* [total_buckets];
        for(unsigned long long i=0; i<total_buckets; i++)
        {
            hash_table[i] = nullptr;
        }
        current_Id = 1;
    }

    //destructor
    ~ScopeTable()
    {
        //deallocate memory for each SymbolInfo of each linked list
        for(unsigned long long i=0; i<total_buckets; i++)
        {
            SymbolInfo* current = hash_table[i];

            while(current != nullptr)
            {
                SymbolInfo* next = current->Next;
                delete current;
                current = next;
            }
        }

        //deallocate the whole table
        delete[] hash_table;
    }

    string getId()
    {
        return id;
    }

    void setId(string i)
    {
        id = i;
    }

    unsigned long long hash_function(string Name)
    {
        return sdbmHash(Name)%total_buckets;
    }


    bool insertEntry(string name, string type)
    {
        current_position = 1;
        SymbolInfo* s = new SymbolInfo(name, type);
        unsigned long long i= hash_function(name);

        SymbolInfo* current = hash_table[i];

        if(current == nullptr)
        {
            hash_table[i] = s;
            s->Next = nullptr;
            return true;
        }

        else
        {
            while(current->Next!=nullptr)
            {
                if(current->getName()== name) return false;
                else
                {
                    current_position++;
                    current = current->Next;
                }
            }
            if(current->getName() == name) return false;
            else
            {
                current_position++;
                current->Next = s;
                s->Next = nullptr;
                return true;
            }
        }

    }

    SymbolInfo* lookUp(string name)
    {
        /*ofstream outputFile;
        outputFile.open("output.txt", ios::app);*/

        current_position = 1;
        unsigned long long i= hash_function(name);
        SymbolInfo* current= hash_table[i];

        while(current!=nullptr)
        {
            if(current->getName()==name)
            {
                break;
            }
            else
            {
                current_position++;
                current = current->Next;
            }
        }
        return current;

    }

    bool deleteEntry(string name)
    {
        /*ofstream outputFile;
        outputFile.open("output.txt", ios::app);*/

        unsigned long long i= hash_function(name);
        current_position = 1;

        SymbolInfo* current = hash_table[i];
        SymbolInfo* previous = nullptr;

        while(current != nullptr)
        {
            if(current->getName()==name)
            {
                if(previous == nullptr)
                {
                    hash_table[i] = current->Next;
                }
                else
                {
                    previous->Next = current->Next;
                }
                current->Next = nullptr;
                delete current;
                return true;
            }
            previous = current;
            current = current->Next;
            current_position++;

        }
        return false;

    }


    void print()
    {
        ofstream outputFile;
        outputFile.open("2005050_log.txt", ios::app);

        outputFile<<"	ScopeTable# "<<id<<endl;
        for(unsigned long long i=0; i<total_buckets; i++)
        {
            outputFile<<"	"<<i+1;
            if(hash_table[i] == nullptr)
            {
                outputFile<<'\n';
                continue;
            }
            else
            {
                outputFile<<" --> ";
                SymbolInfo* current = hash_table[i];
                while(current->Next != nullptr)
                {
                    outputFile<<"("<<current->getName()<<","<<current->getType()<<")"<<" --> ";
                    current = current->Next;
                }
                outputFile<<"("<<current->getName()<<","<<current->getType()<<")";
                outputFile<<'\n';
            }
        }
    }
};


class SymbolTable
{
public:
    int total_buckets;
    ScopeTable* current_scopetable;

    SymbolTable(int n)
    {
        total_buckets = n;
        current_scopetable = new ScopeTable(total_buckets);
        current_scopetable->setId("1");
        current_scopetable->parentScope = nullptr;
    }

    ~SymbolTable()
    {
        while(current_scopetable!= nullptr)
        {
            ScopeTable* temp = current_scopetable;
            current_scopetable = current_scopetable->parentScope;
            delete temp;
        }
    }

    bool enterScope()
    {
        ScopeTable* new_scopeTable = new ScopeTable(total_buckets);
        new_scopeTable->parentScope = current_scopetable;
        string str = current_scopetable->getId()+"."+to_string(current_scopetable->current_Id);
        new_scopeTable->setId(str);
        current_scopetable = new_scopeTable;
        return true;
    }

    bool exitScope()
    {
        if ( current_scopetable->parentScope == nullptr )
        {
            return false;
        }
        else  if(current_scopetable->parentScope->parentScope == nullptr )
        {
            ScopeTable* temp = current_scopetable;
            current_scopetable = current_scopetable->parentScope;
            current_scopetable->current_Id++;
            temp= nullptr;
            delete temp;
            return true;

        }
        else
        {
            ScopeTable* temp = current_scopetable;
            current_scopetable = current_scopetable->parentScope;
            current_scopetable->current_Id++;

            delete temp;
            return true;
        }

    }

    bool insert_into_st(string name, string type)
    {

        bool inserted = current_scopetable->insertEntry(name, type);
        return inserted;
    }

    bool remove_from_st(string name)
    {

        bool removed = current_scopetable->deleteEntry(name);
        return removed;
    }

    /*SymbolInfo* lookUp_in_st(string name)
    {
        ofstream outputFile;
        outputFile.open("output.txt", ios::app);

        ScopeTable* stack_top = current_scopetable;
        SymbolInfo* found;
        while(stack_top!=nullptr)
        {
            found = stack_top->lookUp(name);
            if(found == nullptr)
            {
                stack_top = stack_top ->parentScope;
            }
            else
            {
                break;
            }
        }

        if(found == nullptr) outputFile<<"	'"<<name<<"' not found in any of the ScopeTables"<<endl;
        return found;
    }
    */

    void print_current_scopeTable()
    {
        current_scopetable->print();
    }

    void print_all_scopeTable()
    {
        ScopeTable* stack_top = current_scopetable;

        while(stack_top!= nullptr)
        {
            stack_top->print();
            stack_top = stack_top->parentScope;
        }
    }
};
