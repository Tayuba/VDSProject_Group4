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

ClassProject::BDD_ID ClassProject::Reachability::compute_transition_relation(std::vector<BDD_ID>& nextStates, std::vector<BDD_ID>& transitionFunctions) {
    BDD_ID T = 1;

    for(int i=0; i<nextStates.size();i++){
        BDD_ID xnor = Manager::xnor2(nextStates[i],transitionFunctions[i]);
        T = Manager::and2(xnor,T);
    }

    return T;
}

ClassProject::BDD_ID ClassProject::Reachability::compute_characteristic_function(std::vector<BDD_ID> currentStates, std::vector<bool> initialStates){

    BDD_ID Cs = 1;

    for(int i=0; i<currentStates.size();i++){
        BDD_ID xnor_1 = Manager::xnor2(currentStates[i],initialStates[i]);
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
    BDD_ID img, Cr,img2,temp2, temp3;

    do{
        Cr = Cr_it;
        BDD_ID temp1 = Manager::and2(Cr, T);
//step 7
        for(int i=current_states.size()-1; i>=0;i--){
            img = Manager::or2(coFactorTrue(temp1, current_states[i]),coFactorFalse(temp1,current_states[i]));
            temp1 = img;
        }
//step 8
        temp2 = 1;
        BDD_ID xnor_1;
        for(int i=0; i<current_states.size();i++){
            xnor_1 = Manager::xnor2(current_states[i],next_states[i]);
            temp2 = Manager::and2(xnor_1,temp2);
        }
        temp3 = Manager::and2(temp2,img);

        for(int i=next_states.size()-1; i>=0;i--){
            img2 = Manager::or2(coFactorTrue(temp3, next_states[i]),coFactorFalse(temp3, next_states[i]));
            temp3 = img2;
        }
        //step 9
        Cr_it = Manager::or2(Cr,img2);

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

            if (isR <= 1)
                return true;

            else
                return false;
        }
    }


}