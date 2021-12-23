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
            ClassProject::Manager::unique_table.push_back(ClassProject::Manager::BDDnode {sizeOfTable,label,1,0,sizeOfTable});
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

}

    bool ClassProject::Manager::isConstant(BDD_ID f){
        return false;
}
