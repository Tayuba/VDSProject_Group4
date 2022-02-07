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
//void ClassProject::Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) {
//
//
//}
