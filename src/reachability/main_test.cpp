//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"


namespace ClassProject {


    TEST(ReachabilityInterface_Constructor, Check_Initializations) {
        Reachability m(2);
        EXPECT_EQ(m.uniqueTableSize(), 6);
    }



    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}