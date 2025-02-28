#include "Manager.h"
#include <algorithm>
#include "iostream"


size_t ClassProject::Manager::uniqueTableSize() {
    return ClassProject::Manager::unique_table.size();
}

ClassProject::BDD_ID ClassProject::Manager::createVar(const std::string &label) {
    size_t sizeOfTable = uniqueTableSize();
    for(const auto& i : unique_table) {
        if (i.label == label) {
            return i.node_id;
        }
    }
    Manager::unique_table.push_back(ClassProject::Manager::BDDnode{sizeOfTable, label, 1, 0, sizeOfTable});
    return ClassProject::Manager::unique_table[sizeOfTable].node_id;

}

const ClassProject::BDD_ID &ClassProject::Manager::False(){
    static const BDD_ID FalseID = unique_table[0].node_id;
    return FalseID;
}


const ClassProject::BDD_ID &ClassProject::Manager::True(){
    static const BDD_ID TrueID = unique_table[1].node_id;
    return TrueID;
}


ClassProject::BDD_ID ClassProject::Manager::topVar(BDD_ID f) {
    return unique_table[f].top;
}

void ClassProject::Manager::update_computed_table(const BDD_ID i,const BDD_ID t, const BDD_ID e, BDD_ID &node_id){
    computed_table.insert({{i, t, e},{node_id}});

}

bool ClassProject::Manager::get_computed_table(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID &nodeID) {

    auto found = computed_table.find({i, t, e});

    if(found != computed_table.end()) {
        nodeID = found->second;
        return true;
    }
    return false;
}


ClassProject::BDD_ID ClassProject::Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){

    BDD_ID nodeID;

    //terminal cases
    if (i == True()) {
        return t;
    }
    else if (i == False()) {
        return e;
    }
    else if(t == e) {
        return t;
    }
    else if(t == True() && e == False()) {
        return i;
    }

    else if(get_computed_table(i,t,e, nodeID))
    {
        return nodeID;
    }

    else{
        std::set<BDD_ID> topVariables = {topVar(i), topVar(t), topVar(e)};
        topVariables.erase(0);
        topVariables.erase(1);
        BDD_ID topVariable = *(--topVariables.rend());

        BDD_ID highSuccessor=ite(coFactorTrue(i,topVariable), coFactorTrue(t,topVariable), coFactorTrue(e,topVariable));
        BDD_ID lowSuccessor=ite(coFactorFalse(i,topVariable), coFactorFalse(t,topVariable), coFactorFalse(e,topVariable));

        if(highSuccessor==lowSuccessor) {
            computed_table[{i, t, e}] = highSuccessor;
            return highSuccessor;
        }
        size_t tableSize = uniqueTableSize();
        BDDnode newNode = { tableSize,"",highSuccessor,lowSuccessor,topVariable};


        auto alreadyIn = inverse_table.find({highSuccessor, lowSuccessor, topVariable});

        if(alreadyIn != inverse_table.end()) {
            nodeID = alreadyIn->second;
            return nodeID;
        }

        inverse_table.insert({{highSuccessor, lowSuccessor, topVariable},{tableSize}});

        ClassProject::Manager::unique_table.push_back(newNode);
        update_computed_table(i,t,e,tableSize);
        return newNode.node_id;


    }
}



bool ClassProject::Manager::isConstant(BDD_ID f){
    if(f==0 || f==1)
        return true;
    else
        return false;
}

bool ClassProject::Manager::isVariable(BDD_ID x){
    if(unique_table[x].top !=0 && unique_table[x].top !=1 && !unique_table[x].label.empty())
        return true;
    else
        return false;

}

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    BDD_ID F, T;


    if (isConstant(f) || isConstant(x) || ClassProject::Manager::unique_table[f].top > x)
        return f;
    if(topVar(f)==x)
        return unique_table[f].high;
    else {
        F = coFactorTrue(unique_table[f].low, x);
        T = coFactorTrue(unique_table[f].high, x);

        return ite(topVar(f), T, F);
    }
}

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    BDD_ID F, T;

    if (isConstant(f) || isConstant(x) || ClassProject::Manager::unique_table[f].top > x)
        return f;
    if(topVar(f)==x)
        return unique_table[f].low;
    else {
        F = coFactorFalse(unique_table[f].low, x);
        T = coFactorFalse(unique_table[f].high, x);

        return ite(topVar(f), T, F);
    }
}

ClassProject::BDD_ID ClassProject::Manager:: coFactorTrue(BDD_ID f){

    return ClassProject::Manager::unique_table[f].high;


}
ClassProject::BDD_ID ClassProject::Manager:: coFactorFalse(BDD_ID f){

    return ClassProject::Manager::unique_table[f].low;


}
ClassProject::BDD_ID ClassProject::Manager::neg(BDD_ID a) {

    return ite(a, 0, 1);
}
ClassProject::BDD_ID ClassProject::Manager::and2(BDD_ID a, BDD_ID b){

    return ite(a, b, 0);
}
ClassProject::BDD_ID ClassProject::Manager::or2(BDD_ID a, BDD_ID b){

    return ite(a, 1, b);
}

ClassProject::BDD_ID ClassProject::Manager::xor2(BDD_ID a, BDD_ID b){

    return ite(a, neg(b), b);
}
ClassProject::BDD_ID ClassProject::Manager::nand2(BDD_ID a, BDD_ID b){
//    return ite(a, n)
    return neg(and2(a, b));

}
ClassProject::BDD_ID ClassProject::Manager::nor2(BDD_ID a, BDD_ID b){
    return neg(or2(a, b));
}
ClassProject::BDD_ID ClassProject::Manager::xnor2(BDD_ID a, BDD_ID b){
    return neg(xor2(a, b));
}

std::string ClassProject::Manager::getTopVarName(const BDD_ID &root) {
    BDD_ID topVariable = topVar(root);
    return ClassProject::Manager::unique_table[topVariable].label;

}
void ClassProject::Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    nodes_of_root.insert(root);
    if(root > 1) {
        findNodes(coFactorTrue(root), nodes_of_root);
        findNodes(coFactorFalse(root), nodes_of_root);
    }

}

void ClassProject::Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
    std::set<BDD_ID> nodes;
    findNodes(root, nodes);
    nodes.erase(1);
    nodes.erase(0);
    for(auto x: nodes){
        vars_of_root.insert(topVar(x));

    }


}

