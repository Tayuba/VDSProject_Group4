//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"


namespace ClassProject {

    TEST(ReachabilityInterface_Constructor, Check_Unique_Table_Elements) {
        Reachability m(2);
        EXPECT_EQ(m.unique_table[2].label, "s0");
        EXPECT_EQ(m.unique_table[3].label, "s1");
        EXPECT_EQ(m.unique_table[4].label, "s'0");
        EXPECT_EQ(m.unique_table[5].label, "s'1");
    }
    TEST(ReachabilityInterface_Constructor, Check_Init_States) {
        Reachability m(2);
        EXPECT_EQ(m.initial_states[0], 0);
        EXPECT_EQ(m.initial_states[1], 0);
    }

    TEST(ReachabilityInterface_Constructor, Check_Current_States) {
        Reachability m(2);
        EXPECT_EQ(m.current_states[0], 2);
        EXPECT_EQ(m.current_states[1], 3);
    }

    TEST(ReachabilityInterface_Constructor, Check_Next_States) {
        Reachability m(2);
        EXPECT_EQ(m.next_states[0], 4);
        EXPECT_EQ(m.next_states[1], 5);
    }

    TEST(GetStates_return, Check_whole_states) {
        Reachability m(5);
        EXPECT_EQ(m.getStates()[0], 2);
        EXPECT_EQ(m.getStates()[1], 3);
        EXPECT_EQ(m.getStates()[2], 4);
        EXPECT_EQ(m.getStates()[3], 5);
        EXPECT_EQ(m.getStates()[4], 6);
    }





    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}