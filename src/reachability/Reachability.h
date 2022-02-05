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

    public: struct state{
        BDD_ID state_id;
        std::string state_label;
        BDD_ID value;

    };

    public:
        Reachability(unsigned int stateSize) : ReachabilityInterface(stateSize){
            if(stateSize==0){
                throw std::runtime_error("Invalid size");
            }
            else {
                std::vector<state> state_variables;
                std::vector<BDD_ID> transition_functions;
                BDD_ID id1, id2;
                state s;
                for (int i = 0; i <= stateSize; i++) {
                    id1 = Manager::createVar("s" + std::to_string(i));
                    s = {id1, "s" + std::to_string(i), 0};
                    state_variables.push_back(s);
                    transition_functions.push_back(0);

                }
                for (int j = stateSize + 1; j <= 2 * stateSize; j++) {
                    id2 = Manager::createVar("s'" + std::to_string(j));
                    s = {id2, "s'" + std::to_string(j), 0};
                    state_variables.push_back(s);

                }
            }
    }

        void setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) = 0;

    };

}
#endif
