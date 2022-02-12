//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"


namespace ClassProject {


    TEST(ReachabilityInterface_Constructor, Check_RuntimeErr_0) {
        EXPECT_ANY_THROW(Reachability m(0));
    }
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
    TEST(IsReachable, Check_RuntimeErr_DiffSize) {
        Reachability m(2);
        EXPECT_ANY_THROW(m.isReachable({0,0,1,1}));

    }
//    TEST(IsReachable, Check_reachability) {
//        Reachability m(2);
//
//        EXPECT_EQ(m.isReachable({0,0}), true);
//        EXPECT_EQ(m.isReachable({1,1}), true);
//        EXPECT_EQ(m.isReachable({1,0}), false);
//        EXPECT_EQ(m.isReachable({0,1}), false);
//    }

    TEST(SetInitState, Check_RuntimeErr_DiffSize) {
        Reachability m(2);
        std::vector<bool> myVec = {1,0,0,1,1};
        EXPECT_ANY_THROW(m.setInitState(myVec));
    }

    TEST(SetInitState, Check_InitState) {
        Reachability m(5);
        std::vector<bool> myVec = {1, 0, 0, 1, 1};
        m.setInitState(myVec);

        EXPECT_TRUE(m.initial_states[0]);
        EXPECT_FALSE(m.initial_states[1]);
        EXPECT_FALSE(m.initial_states[2]);
        EXPECT_TRUE(m.initial_states[3]);
        EXPECT_TRUE(m.initial_states[4]);
    }


    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}