#include "program.h"

void program::push_instruction(int i){
    list.push_back(i);
};

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

vector<int> program::get_list(){
    return list;
}
