#include <iostream>
#include "hash.h"
#include <gtest/gtest.h>
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    cout << "Hello, World!\n";
    return RUN_ALL_TESTS();
}
/*
int main() {
    hash_table<int, int> table;
    table.insert(1,2);
    table.insert(3,7);
    table.insert(5,5);
    table.insert(13,98);
    //table.erase(5);
    table.insert(21,111);
    table.erase(13);
    //table.is_find(5);
    //table.rehash();
    cout<<table;
    return 0;
}*/
void menu(){

}