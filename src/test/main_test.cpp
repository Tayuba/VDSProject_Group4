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
    TEST(negTest, negTest){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        EXPECT_EQ(m->neg(a), 3);
    }
    TEST(and2Test, and2Test){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        BDD_ID b = m->createVar("b");
        EXPECT_EQ(m->and2(a, b), 4);
    }
    TEST(or2Test, or2Test){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        BDD_ID b = m->createVar("b");
        EXPECT_EQ(m->or2(a, b), 4);
    }
    TEST(xor2Test, xor2Test){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        BDD_ID b = m->createVar("b");
        EXPECT_EQ(m->xor2(a, b), 5);
    }
    TEST(nand2Test, nand2Test){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        BDD_ID b = m->createVar("b");
        EXPECT_EQ(m->nand2(a, b),5);
    }
    TEST(nor2Test, nor2Test){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        BDD_ID b = m->createVar("b");
        EXPECT_EQ(m->nor2(a, b),5);
    }
    TEST(xnor2Test, xnor2Test){
        Manager *m = new Manager();
        BDD_ID a = m->createVar("a");
        BDD_ID b = m->createVar("b");
        EXPECT_EQ(m->xnor2(a, b),6);
    }
    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
