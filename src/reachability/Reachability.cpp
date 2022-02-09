//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#include "Reachability.h"

const std::vector<ClassProject::BDD_ID> &ClassProject::Reachability::getStates() const{

        return current_states;
}

void ClassProject::Reachability::setInitState(const std::vector<bool> &stateVector){
    if(stateVector.size()!=initial_states.size()){
        throw std::runtime_error("Size does not match with number of state bits");
    }
    else{
        for(int i=0; i<stateVector.size();i++){
            if(stateVector[i])
                initial_states[i]=true;
            else
                initial_states[i]=false;
        }
    }

    char_function = compute_characteristic_function();

}

ClassProject::BDD_ID ClassProject::Reachability::compute_transition_relation() {

    int next_states_size = next_states.size();
    transition_relation = 1;
    BDD_ID xnor;

    for(int i=0; i<next_states_size;i++){
        xnor = Manager::xnor2(next_states[i],transition_functions[i]);
        transition_relation = Manager::and2(xnor,transition_relation);
    }

    return transition_relation;
}

ClassProject::BDD_ID ClassProject::Reachability::compute_characteristic_function(){

    int current_states_size = current_states.size();
    char_function = 1;
    BDD_ID xnor_1;

    for(int i=0; i<current_states_size;i++){
        xnor_1 = Manager::xnor2(current_states[i],initial_states[i]);
        char_function = Manager::and2(xnor_1,char_function);
    }

    return char_function;

}
void ClassProject::Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) {

    if(transitionFunctions.size()!=current_states.size())
        throw std::runtime_error("The number of given transition functions does not match the number of state bits");

    for(unsigned long transitionFunction : transitionFunctions){
        if(transitionFunction >= Manager::uniqueTableSize())
            throw std::runtime_error("Unknown ID");
    }

    for(int i=0; i<transitionFunctions.size();i++){
        transition_functions[i] = transitionFunctions[i];
    }

    transition_relation = compute_transition_relation();
}

ClassProject::BDD_ID ClassProject::Reachability::symb_compute_reachable_states(){
    BDD_ID cr_it, cr, temp1, temp2, temp3, temp4,temp5;

    cr_it = char_function;

    do{
        cr = cr_it;
        temp1 = Manager::and2(cr, transition_relation);

        for(int i=current_states.size()-1; i>=0;i--){
            temp2 = Manager::or2(coFactorTrue(temp1, current_states[i]),coFactorFalse(temp1,current_states[i]));
            temp1 = temp2;
        }

        temp3 = 1;
        BDD_ID xnor_1;
        for(int i=0; i<current_states.size();i++){
            xnor_1 = Manager::xnor2(current_states[i],next_states[i]);
            temp3 = Manager::and2(xnor_1,temp3);
        }
        temp4 = Manager::and2(temp3,temp2);

        for(int i=next_states.size()-1; i>=0;i--){
            temp5 = Manager::or2(coFactorTrue(temp4, next_states[i]),coFactorFalse(temp4,next_states[i]));
            temp4 = temp5;
        }

        cr_it = Manager::or2(cr,temp5);

    }  while(cr!=cr_it);

    return cr;
}
