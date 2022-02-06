//
// Created by ludwig on 27.11.18
// Refactored by deutschmann on 19.04.21
//

#ifndef VDSPROJECT_REACHABILITY_H
#define VDSPROJECT_REACHABILITY_H

#include "ReachabilityInterface.h"
#include <vector>

namespace ClassProject {

    class Reachability : public ReachabilityInterface {

    public:
        struct state{
        BDD_ID state_id;
        std::string state_label;
        BDD_ID value;

    };
        std::vector<state> current_states;
        std::vector<state> next_states;
        std::vector<BDD_ID> transition_functions;
        std::vector<state> initial_states;


    public:
        explicit Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize){
            if(stateSize==0){
                throw std::runtime_error("Invalid size");
            }
            else {

                BDD_ID id1, id2;
                state s;
                for (int i = 0; i <= stateSize; i++) {
                    id1 = Manager::createVar("s" + std::to_string(i));
                    s = {id1, "s" + std::to_string(i), 0};
                    current_states.push_back(s);
                    transition_functions.push_back(0);

                }
                for (unsigned int j = stateSize + 1; j <= 2 * stateSize; j++) {
                    id2 = Manager::createVar("s'" + std::to_string(j));
                    s = {id2, "s'" + std::to_string(j), 0};
                    next_states.push_back(s);

                }
            }
    }

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions);
        const std::vector<BDD_ID> &getStates() const;
        bool isReachable(const std::vector<bool> &stateVector);
        void setInitState(const std::vector<bool> &stateVector);
        BDD_ID compute_transition_relation();
        BDD_ID compute_characteristic_function(std::vector<BDD_ID> stateVariables);



    };

}
#endif
