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
                initial_states[i]=1;
            else
                initial_states[i]=0;
        }
    }

}

ClassProject::BDD_ID ClassProject::Reachability::compute_transition_relation() {

    int next_states_size = next_states.size();
    BDD_ID transition_relation = 1;
    BDD_ID xnor;

    for(int i=0; i<next_states_size;i++){
        xnor = Manager::xnor2(next_states[i],transition_functions[i]);
        transition_relation = Manager::and2(xnor,transition_relation);
    }

    return transition_relation;
}

ClassProject::BDD_ID ClassProject::Reachability::compute_characteristic_function(){

    int current_states_size = current_states.size();
    BDD_ID char_function = 1;
    BDD_ID xnor_1;

    for(int i=0; i<current_states_size;i++){
        xnor_1 = Manager::xnor2(current_states[i],initial_states[i]);
        char_function = Manager::and2(xnor_1,char_function);
    }

    return char_function;

}
//void ClassProject::Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) {
//
//
//}
