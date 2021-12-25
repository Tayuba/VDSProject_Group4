#include "Manager.h"

    size_t ClassProject::Manager::uniqueTableSize() {
        return ClassProject::Manager::unique_table.size();
}

    ClassProject::BDD_ID ClassProject::Manager::createVar(const std::string &label) {
        bool varExists=false;
        size_t sizeOfTable = uniqueTableSize();
        for(int i=0; i< ClassProject::Manager::unique_table.size(); i++) {
            if (ClassProject::Manager::unique_table[i].label == label) {
                varExists = true;
                return ClassProject::Manager::unique_table[i].node_id;
            }
        }
        if(varExists==false){
            Manager::unique_table.push_back(ClassProject::Manager::BDDnode {sizeOfTable,label,1,0,sizeOfTable});
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
        //terminal cases
        if (i == True()) return t;
        if (i == False()) return e;
        if(t == e) return t;
        if(t == True() && e == False()) return i;

        BDD_ID topVariable = topVar(i);
        return 10;
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

        if (isConstant(f) || ClassProject::Manager::unique_table[f].top > x)
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

        if (isConstant(f) || ClassProject::Manager::unique_table[f].top > x)
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