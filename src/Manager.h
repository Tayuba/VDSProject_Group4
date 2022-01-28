// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include "unordered_map"

namespace ClassProject {

    class Manager : public ManagerInterface {

        struct bDDHasher{
            size_t operator() (const std::array<BDD_ID,3> &a) const{
                size_t h = 0;

                for(auto e: a){
                    h ^= std::hash<BDD_ID>{}(e) + 0x9e3779b9 + (h << 6) + (h >> 2);
                }
                return h;
            }
        };

    public:

        struct BDDnode {
            BDD_ID node_id;
            std::string label;
            BDD_ID high;
            BDD_ID low;
            BDD_ID top;
        };


        std::vector<BDDnode> unique_table;
//        std::unordered_map<std::string, BDD_ID>computed_table;
        std::unordered_map<std::array<BDD_ID,3>, BDD_ID, bDDHasher> computed_table;
        std::unordered_map<std::array<BDD_ID,3>, BDD_ID, bDDHasher> inverse_table;
//        std::unordered_map<std::array<BDD_ID,3>, BDD_ID, bDDHasher> l_Table;
        std::unordered_map<BDD_ID, std::string> l_Table;
//        std::unordered_map<std::string, BDD_ID> inverse_table;

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
        std::string getTopVarName(const BDD_ID &root);
        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);
        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);
        void update_computed_table(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID &node_id);
        bool get_computed_table(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID &nodeID);



    public:  Manager(){

            BDDnode F = {0,"False",0,0,0};
            BDDnode T = {1,"True",1,1,1};



            unique_table.push_back(F);
            unique_table.push_back(T);

        }
        virtual    ~Manager(){
            unique_table.erase(unique_table.begin());
        }

    };

}

#endif