#include "program.h"

program::program(){
    //create main function
    //load standard lib
    current_function = -1;
    new_function();
}

void program::push_instruction(int i){
    list[current_function].push_back(i);
}

int program::get_position(){
    return list[current_function].size()-1;
}

int program::get_variable(string n){
    //loop through variables backwards
    //making sure the most local variable gets in first.
    for(int i=variables.size()-1; i>=0; i--){
        if(n==variables[i]){
            return i;
        }
    }
    return -1;
}

int program::assign_variable(string n){
    int i = get_variable(n);
    if(i==-1){
        LOG_DEBUG("Assigning new var "<<n);
        variables.push_back(n);
        return (variables.size()-1);
    }
    LOG_DEBUG("var "<<n<<" found earlier");
    return i;
}

int program::force_variable(string n){
    LOG_DEBUG("Force assigning new var "<<n);
    variables.push_back(n);
    return (variables.size()-1);
}

int program::new_scope(){
    LOG_DEBUG("new scope");
    return variables.size();
}

void program::pop_scope(int n){
    LOG_DEBUG("end scope");
    for(int i=variables.size()-1; i>=n; i--){
        variables[i]="/"; //FIXME: this is just hackish
    }
}
int program::new_function(){
    vector <int> v;
    list.push_back(v);
    call_stack.push_back(current_function);
    current_function=list.size()-1;
    return current_function;
}

void program::pop_function(){
    current_function = call_stack.back();
    call_stack.pop_back();
}

vector< vector<int> > program::get_list(){
    return list;
}
