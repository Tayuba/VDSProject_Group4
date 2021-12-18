//
// Created by ludwig on 22.11.16.
#include "Tests.h"

namespace ClassProject{

    TEST(uniqueTableSizeTest, ChecksSizeOfTable) {
        Manager *m = new Manager();
        EXPECT_EQ(m->uniqueTableSize(), 2);
    }
    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
