//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"


namespace ClassProject {


//    TEST(ReachabilityInterface_Constructor, Check_UniqueTableSize) {
//        Reachability m(2);
//        EXPECT_EQ(m.uniqueTableSize(), 6);
//    }

//    TEST(ReachabilityInterface_Constructor, Check_Initializations) {
//        Reachability m(0);
//        EXPECT_EQ(m.uniqueTableSize(), 2);
//    }

    TEST(ReachabilityInterface_Constructor, Check_Initializations) {
        Reachability m(2);
       // EXPECT_EQ(m.uniqueTableSize(), 6);
        //unique table elements
        EXPECT_EQ(m.unique_table[2].label, "s0");
        EXPECT_EQ(m.unique_table[3].label, "s1");
        EXPECT_EQ(m.unique_table[4].label, "s'0");
        EXPECT_EQ(m.unique_table[5].label, "s'1");
        //init states
        EXPECT_EQ(m.initial_states[0], 0);
        EXPECT_EQ(m.initial_states[1], 0);
        //current states
        EXPECT_EQ(m.current_states[0], 2);
        EXPECT_EQ(m.current_states[1], 3);
        //next states
        EXPECT_EQ(m.next_states[0], 4);
        EXPECT_EQ(m.next_states[1], 5);
    }



    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}