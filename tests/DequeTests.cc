#include <gtest/gtest.h>
#include <ThreadSafeDeque.h>
#include <iostream>

// Demonstrate some basic assertions.
TEST(BasicTests, TestingSizeFunction) {
    TSDeque<int> tsDeque{};
    for(int i=0; i<50; i++)
        tsDeque.push(i);
    
    for(int i=0; i<50; i++){
        tsDeque.pop();
        ASSERT_EQ(tsDeque.size(), 49-i);
    }
}

TEST(BasicTests, TestingSizeFunctionRvalues) {
    TSDeque<int> tsDeque{};
    tsDeque.push(1);
    tsDeque.push(2);
    tsDeque.push(3);
    ASSERT_EQ(tsDeque.size() , 3);
    ASSERT_EQ(*(tsDeque.pop()) , 1);
    ASSERT_EQ(*(tsDeque.pop()) , 2);
    ASSERT_EQ(*(tsDeque.pop()) , 3);
}


TEST(BasicTests, EmptyQueueTest) {
    int counter = 0;    
    TSDeque<int> tsDeque{};
    std::shared_ptr<int> temp = tsDeque.pop();
    if(temp == nullptr)
        ASSERT_EQ(1,1);    
    else
        ASSERT_EQ(1,0);    

}




