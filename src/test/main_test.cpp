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
    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
