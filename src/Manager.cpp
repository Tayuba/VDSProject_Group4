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
        static const BDD_ID FalseID = 1;
        return FalseID;
}