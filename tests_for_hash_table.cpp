#include "hash.h"
#include "gtest/gtest.h"
#include <iostream>
TEST(hash_table, input){
    hash_table<int, string> table;
    table.insert(15, "vanya");
    table.insert(398, "kostas");
    table.insert(2, "ksysha");
    EXPECT_EQ(table.find_by_the_key(2), "ksysha");
    EXPECT_EQ(table.find_by_the_key(15), "vanya");
    EXPECT_EQ(table.find_by_the_key(398), "kostas");
}
TEST(hash_table, delete){
    hash_table<int, int> table(16);
    table.insert(1,11);
    table.insert(2,9);
    table.insert(3, 15);
    table.insert(4,10);
    table.insert(5,119);
    table.insert(6, 115);
    table.insert(14,116);
    EXPECT_EQ(table.find_by_the_key(2), 9);
    EXPECT_EQ(table.find_by_the_key(6), 115);
    table.erase(6);
    ASSERT_ANY_THROW(table.find_by_the_key(6));
    table.insert(6, -1);
    EXPECT_EQ(table.find_by_the_key(6), -1);
}
TEST(hash_table, rehash){
    hash_table<int, int> table(8);
    table.insert(1,11);
    table.insert(2,9);
    table.insert(3, 15);
    table.insert(4,10);
    table.insert(5,119);
    EXPECT_EQ(table.Get_Size(),8);
    table.insert(6, 115);
    EXPECT_EQ(table.Get_Size(),16);
    table.insert(14,116);
    table.insert(10,116);
    table.insert(11,116);
    EXPECT_EQ(table.Get_Size(),16);
}