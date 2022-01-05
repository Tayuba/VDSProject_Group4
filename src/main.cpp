//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

using namespace ClassProject;

    int main(int argc, char *argv[]) {
        std::cout << "Nothing implemented, yet" << std::endl;
        Manager *m = new Manager();
        BDD_ID id1 = m->createVar("a");
        BDD_ID id2 = m->createVar("b");
        BDD_ID id3 = m->createVar("c");
        BDD_ID id4 = m->createVar("d");

        BDD_ID f = m-> and2(m->and2(4, 5), m->or2(2, 3));


//        Manager::BDDnode lastNode = {f+1, "f", m->unique_table[f].high, m->unique_table[f].low, 2};
//        BDD_ID last = m->uniqueTableSize()-1;
//        std::cout<< m->unique_table[last].high<< std::endl<< m->unique_table[last].low<<std::endl;

//        m->unique_table.push_back(lastNode);
//        std::cout<< m->uniqueTableSize();

        std::cout<< m->unique_table[f].high << std::endl<< m->unique_table[f].low<<std::endl;


//        std::cout<< lastNode.node_id << std::endl;

        return 0;
    }


