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

int program::get_virtual(string n){
    //return standardlib::check(n);
    if(n=="say"){
        return 0;
    }
    return -1;
}

int program::get_variable(string n){
    //just loop through varibles fuck hash tables
    for(int i=0; i<variables.size(); i++){
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
