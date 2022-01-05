//
// Created by ludwig on 22.11.16.

#include "Tests.h"

namespace ClassProject{
    TEST(uniqueTableSizeTest, ChecksSizeOfTable) {
        Manager *m = new Manager();
        EXPECT_EQ(m->uniqueTableSize(), 2);
    }
    TEST(createVarTest, CheckIDOfVar){
        Manager *m = new Manager();
        EXPECT_EQ(m->createVar("a"), 2);
    }
    TEST(ReturnFalseTest, ReturnFalseID){
        Manager *m = new Manager();
        EXPECT_EQ(m->False(), 0);
    }
    TEST(ReturnTrueTest, ReturnTrueID){
        Manager *m = new Manager();
        EXPECT_EQ(m->True(), 1);
    }
    TEST(TopVarTest, ReturnTopVarID){
        Manager *m = new Manager();
        EXPECT_EQ(m->topVar(0), 0);
    }
    TEST(ITETest, ITETest){
        Manager *m = new Manager();
        BDD_ID id1 = m->createVar("a");
        BDD_ID id2 = m->createVar("b");
        EXPECT_EQ(m->ite(id1,id2,0), 4);
    }
    TEST(isConstantTest, isConstantTest){
        Manager *m = new Manager();
        EXPECT_EQ(m->isConstant(0), true);
    }
    TEST(isVariableTest, isVariableTest){
        Manager *m = new Manager();
        BDD_ID id1 = m->createVar("a");
        EXPECT_EQ(m->isVariable(id1), true);
    }
    TEST(coFactorTrueTest, coFactorTrueTest){
        Manager *m = new Manager();
        BDD_ID f1 = m->createVar("a");
        BDD_ID x = m->createVar("b");
        BDD_ID f = m->isConstant(1);
        EXPECT_EQ(m->coFactorTrue(f1, x), f1);
        EXPECT_EQ(m->coFactorTrue(f, x), f);
    }
    TEST(coFactorFalseTest, coFactorFalseTest){
        Manager *m = new Manager();
        BDD_ID f1 = m->createVar("a");
        BDD_ID x = m->createVar("b");
        BDD_ID f = m->isConstant(0);
        EXPECT_EQ(m->coFactorFalse(f1, x), f1);
        EXPECT_EQ(m->coFactorFalse(f, x), f);
    }
    TEST(coFactorTrue1Test, coFactorTrue1Test){
        Manager *m = new Manager();
        BDD_ID f = m->createVar("a");
        EXPECT_EQ(m->coFactorTrue(f), 1);
    }
    TEST(coFactorFalse1Test, coFactorFalse1Test){
        Manager *m = new Manager();
        BDD_ID f = m->createVar("a");
        EXPECT_EQ(m->coFactorFalse(f), 0);
    }
    TEST(negTestTrue, negTestTrue){
        Manager *m = new Manager();
        EXPECT_EQ(m->neg(0), 1);
    }

    TEST(negTestFalse, negTestFalse){
        Manager *m = new Manager();
        EXPECT_EQ(m->neg(1), 0);
    }

    TEST(and2TestFalse, and2TestFalse){
        Manager *m = new Manager();
        EXPECT_EQ(m->and2(1, 0), 0);
    }

    TEST(and2TestTrue, and2TestTrue){
        Manager *m = new Manager();
        EXPECT_EQ(m->and2(1, 1), 1);
    }

    TEST(or2TestFalse, or2TestFalse){
        Manager *m = new Manager();
        EXPECT_EQ(m->or2(0, 0), 0);
    }

    TEST(or2TestTrue, or2TestTrue){
        Manager *m = new Manager();
        EXPECT_EQ(m->or2(1, 0), 1);
    }

    TEST(xor2TestFalse, xor2TestFalse){
        Manager *m = new Manager();
        EXPECT_EQ(m->xor2(1, 1), 0);
    }

    TEST(xor2TestTrue, xor2TestTrue){
        Manager *m = new Manager();
        EXPECT_EQ(m->xor2(1, 0), 1);
    }

    TEST(nand2TestTrue, nand2TestTrue){
        Manager *m = new Manager();
        EXPECT_EQ(m->nand2(0, 0),1);
    }
    TEST(nand2TestFalse, nand2TestFalse){
        Manager *m = new Manager();
        EXPECT_EQ(m->nand2(1, 1),0);
    }

    TEST(nor2TestTrue, nor2TestTrue){
        Manager *m = new Manager();
        EXPECT_EQ(m->nor2(0, 0),1);
    }
    TEST(nor2TestFalse, nor2TestFalse){
        Manager *m = new Manager();
        EXPECT_EQ(m->nor2(1, 1),0);
    }

    TEST(xnor2TestFalse, xnor2TestFalse){
        Manager *m = new Manager();
        EXPECT_EQ(m->xnor2(1, 0),0);
    }

    TEST(xnor2TestTrue, xnor2TestTrue){
        Manager *m = new Manager();
        EXPECT_EQ(m->xnor2(1, 1),1);
    }

    TEST(getTopVarNameTest, ReturnLabel){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        EXPECT_EQ(m->getTopVarName(2),"a");
    }


    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
