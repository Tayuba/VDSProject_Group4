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

        BDD_ID f = m-> and2(m->and2(id3, id4),m->or2(id1, id2));


        std::cout<< m->u_Table[f].high << std::endl<< m->u_Table[f].low<<std::endl;


        return 0;
    }


