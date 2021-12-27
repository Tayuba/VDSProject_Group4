#include "Manager.h"
#include <iterator>
#include <algorithm>

    size_t ClassProject::Manager::uniqueTableSize() {
        return ClassProject::Manager::unique_table.size();
}

    ClassProject::BDD_ID ClassProject::Manager::createVar(const std::string &label) {
        bool varExists = false;
        size_t sizeOfTable = uniqueTableSize();
        for (int i = 0; i < ClassProject::Manager::unique_table.size(); i++) {
            if (ClassProject::Manager::unique_table[i].label == label) {
                varExists = true;
                return ClassProject::Manager::unique_table[i].node_id;
            }
        }
        if (varExists == false) {
            Manager::unique_table.push_back(ClassProject::Manager::BDDnode{sizeOfTable, label, 1, 0, sizeOfTable});
            return ClassProject::Manager::unique_table[sizeOfTable].node_id;
        }

        else {
            return 0;
        }
}
    const ClassProject::BDD_ID &ClassProject::Manager::False(){
        static const BDD_ID FalseID = ClassProject::Manager::unique_table[0].node_id;
        return FalseID;
}

    const ClassProject::BDD_ID &ClassProject::Manager::True(){
        static const BDD_ID TrueID = ClassProject::Manager::unique_table[1].node_id;
        return TrueID;
}

    ClassProject::BDD_ID ClassProject::Manager::topVar(BDD_ID f) {
        return ClassProject::Manager::unique_table[f].top;
}
    ClassProject::BDD_ID ClassProject::Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){

        std::set<BDD_ID> topVariables;
        BDD_ID topVariable;
        BDD_ID highSuccessor;
        BDD_ID lowSuccessor;
        BDDnode newNode;
        size_t tableSize = uniqueTableSize();
        BDDnode existingNode;
        bool nodeExists = false;

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
        else{
            topVariables={topVar(i), topVar(t), topVar(e)};
            topVariables.erase(0);
            topVariables.erase(1);
            topVariable = *(--topVariables.rend());

            highSuccessor=ite(coFactorTrue(i,topVariable), coFactorTrue(t,topVariable), coFactorTrue(e,topVariable));
            lowSuccessor=ite(coFactorFalse(i,topVariable), coFactorFalse(t,topVariable), coFactorFalse(e,topVariable));

            if(highSuccessor==lowSuccessor)
                return highSuccessor;

            newNode = {tableSize,"",highSuccessor,lowSuccessor,topVariable};

            for(int j=0; j<tableSize; j++){
                existingNode = ClassProject::Manager::unique_table[j];
                if(existingNode.high==newNode.high && existingNode.low==newNode.low && existingNode.top==newNode.top)
                    nodeExists = true;
            }
            if(!nodeExists)
                ClassProject::Manager::unique_table.push_back(newNode);

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
        if(unique_table[x].label !="False" && unique_table[x].label !="True" && !unique_table[x].label.empty())
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
            F = coFactorTrue(unique_table[f].low, x);
            T = coFactorTrue(unique_table[f].high, x);

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
        BDD_ID negB = neg(b);
        return ite(a, negB, b);
}
    ClassProject::BDD_ID ClassProject::Manager::nand2(BDD_ID a, BDD_ID b){
        BDD_ID And = and2(a, b);
        BDD_ID nand = neg(And);
        return nand;
}
    ClassProject::BDD_ID ClassProject::Manager::nor2(BDD_ID a, BDD_ID b){
        BDD_ID Or = or2(a, b);
        BDD_ID nor = neg(Or);
        return nor;
}
    ClassProject::BDD_ID ClassProject::Manager::xnor2(BDD_ID a, BDD_ID b){
        BDD_ID Xor = xor2(a, b);
        BDD_ID xnor = neg(Xor);
        return xnor;

}