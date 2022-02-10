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

    symb_compute_reachable_states();

}

ClassProject::BDD_ID ClassProject::Reachability::compute_transition_relation(std::vector<BDD_ID>& next_states, std::vector<BDD_ID>& transition_functions) {
    BDD_ID T = 1;

    for(int i=0; i<next_states.size();i++){
        BDD_ID xnor = Manager::xnor2(next_states[i],transition_functions[i]);
        T = Manager::and2(xnor,T);
    }

    return T;
}

ClassProject::BDD_ID ClassProject::Reachability::compute_characteristic_function(std::vector<BDD_ID> current_states, std::vector<bool> initial_states){

    BDD_ID Cs = 1;

    for(int i=0; i<current_states.size();i++){
        BDD_ID xnor_1 = Manager::xnor2(current_states[i],initial_states[i]);
        Cs = Manager::and2(xnor_1,Cs);
    }

    return Cs;

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
    symb_compute_reachable_states();

}

ClassProject::BDD_ID ClassProject::Reachability::symb_compute_reachable_states(){

    BDD_ID T = compute_transition_relation(next_states,transition_functions);
    BDD_ID Cs = compute_characteristic_function(current_states, initial_states);
    BDD_ID Cr_it = Cs;
    BDD_ID Img, temp2, Cr;

    do{
         Cr = Cr_it;
        BDD_ID temp1 = Manager::and2(Cr, T);

        for(unsigned long current_state : current_states){
            Img = Manager::or2(coFactorTrue(temp1, current_state),coFactorFalse(temp1,current_state));
        }

        for(int i = 0; i < next_states.size(); ++i){
          temp2 = Manager::and2(Img, Manager::xnor2(current_states[i], next_states[i]));
        }

        for(unsigned long next_state : next_states){
            Img = Manager::or2(coFactorTrue(temp2, next_state),coFactorFalse(temp1, next_state));
        }
        Cr_it = Manager::or2(Cr,Img);

    }  while(Cr != Cr_it);

    return Cr;
}

bool ClassProject:: Reachability :: isReachable(const std::vector<bool> &stateVector) {
    BDD_ID isR = symb_compute_reachable_states();
    if (stateVector.size() != current_states.size())
        throw std::runtime_error("The number of size does not match the number of state bits");

    else {

        for (int i = 0; i < stateVector.size(); ++i) {

            if (stateVector.at(i)) {
                isR = coFactorTrue(isR, current_states[i]);
            } else {
                isR = coFactorFalse(isR, current_states[i]);
            }

            if (isR <= 1) {
                return true;
            }
        }
    }


}