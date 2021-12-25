// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>

namespace ClassProject {

    class Manager : public ManagerInterface {
    public:

        struct BDDnode {
            BDD_ID node_id;
            std::string label;
            BDD_ID high;
            BDD_ID low;
            BDD_ID top;
        };

        std::vector<BDDnode> unique_table;

        size_t uniqueTableSize();
        BDD_ID createVar(const std::string &label);
        const BDD_ID &True();
        const BDD_ID &False();
        BDD_ID topVar(BDD_ID f);
        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);
        bool isConstant(BDD_ID f);
        bool isVariable(BDD_ID x);
        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);
        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);
        BDD_ID coFactorTrue(BDD_ID f);
        BDD_ID coFactorFalse(BDD_ID f);
        BDD_ID neg(BDD_ID a);
        BDD_ID and2(BDD_ID a, BDD_ID b);
        BDD_ID or2(BDD_ID a, BDD_ID b);
        BDD_ID xor2(BDD_ID a, BDD_ID b);
        BDD_ID nand2(BDD_ID a, BDD_ID b);
        BDD_ID nor2(BDD_ID a, BDD_ID b);
        BDD_ID xnor2(BDD_ID a, BDD_ID b);

    public:  Manager(){

            BDDnode F = {0,"False",0,0,0};
            BDDnode T = {1,"True",1,1,1};



            unique_table.push_back(F);
            unique_table.push_back(T);

        }

    };

}
#endif
