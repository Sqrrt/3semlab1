#include "gtest/gtest.h"
#include <iostream>
#include "graph.h"

TEST(graph, insert){
    Graph<int> graph;
    graph.insert_ver(1);
    graph.insert_ver(2);
    graph.insert_ver(3);
    graph.insert_edge(2,3,5);
    graph.insert_edge(3,2,1);
    graph.insert_edge(1,2,3);
    EXPECT_EQ(5, graph.find_distance(2,3));
    EXPECT_EQ(10000, graph.find_distance(1,3));
}
TEST(graph, delete_all){
    Graph<int> graph;
    graph.insert_ver(1);
    graph.insert_ver(2);
    graph.insert_ver(3);
    graph.insert_ver(4);
    graph.insert_edge(2,3,5);
    graph.insert_edge(3,2,1);
    graph.insert_edge(1,2,3);
    graph.insert_edge(1,4,12);
    graph.insert_edge(4,3,19);
    EXPECT_EQ(5, graph.find_distance(2,3));
    graph.delete_edge(2,3);
    EXPECT_EQ(10000, graph.find_distance(2,3));
    graph.delete_edge(1,2);
    EXPECT_EQ(10000, graph.find_distance(1,2));
    graph.insert_edge(1,2,4);
    EXPECT_EQ(4, graph.find_distance(1,2));
}
TEST(graph, different_distances){
    Graph<int> graph;
    graph.insert_ver(1);
    graph.insert_ver(2);
    graph.insert_ver(3);
    graph.insert_edge(1,2,2);
    graph.insert_edge(2,1,3);
    graph.insert_edge(3,2,8);
    graph.insert_edge(2,3,8);
    EXPECT_EQ(10,graph.bellman_ford(1,3));
    EXPECT_EQ(10,graph.worshell_floyd(1,3));
    EXPECT_EQ(10,graph.dexter(1,3));
    graph.insert_edge(1,3,9);
    EXPECT_EQ(9,graph.bellman_ford(1,3));
    EXPECT_EQ(9,graph.worshell_floyd(1,3));
    EXPECT_EQ(9,graph.dexter(1,3));
    graph.delete_edge(2,3);
    graph.delete_edge(1,3);
    graph.insert_edge(1,3,11);
    EXPECT_EQ(11,graph.bellman_ford(1,3));
    EXPECT_EQ(11,graph.worshell_floyd(1,3));
    EXPECT_EQ(11,graph.dexter(1,3));
}
TEST(graph, sort){
    Graph<int> graph;
    graph.insert_ver(5);
    graph.insert_ver(4);
    graph.insert_ver(3);
    graph.insert_ver(2);
    graph.insert_ver(1);
    graph.insert_edge(2,3,3);
    graph.insert_edge(1,3,8);
    graph.insert_edge(1,4,2);
    graph.insert_edge(2,4,8);
    graph.insert_edge(3,4,8);
    graph.insert_edge(3,5,8);
    graph.insert_edge(5,4,8);
    graph.insert_edge(4,3,8);
    graph.print();
    vector<int> result = graph.top_sort();
    for(int i = 0; i < 5; i++){
        cout<< result[i];
    }
    for(int i = 2; i < 5; i++) {
        ASSERT_NE(result[i], 1);
        ASSERT_NE(result[i],2);
    }
    graph.insert_edge(1,2,1);
    vector<int> result2 = graph.top_sort();
    EXPECT_EQ(1, result2[0]);
    EXPECT_EQ(2, result2[1]);
    graph.delete_edge(1,2);
    graph.insert_edge(2,1,11);
    vector<int> result3 = graph.top_sort();
    EXPECT_EQ(2, result3[0]);
    EXPECT_EQ(1, result3[1]);
    cout<<"\n";
    //ASSERT_ANY_THROW(graph.top_sort());
}
TEST (graph, path_find){//этот тест для нахождения пути
    Graph<int> graph;
    graph.insert_ver(1);
    graph.insert_ver(2);
    graph.insert_ver(3);
    graph.insert_ver(4);
    graph.insert_ver(5);
    graph.insert_ver(6);
    graph.insert_ver(7);
    graph.insert_ver(8);
    graph.insert_ver(9);
    graph.insert_edge(1, 2, 3);
    graph.insert_edge(1, 3, 5);
    graph.insert_edge(2, 3, 1);
    graph.insert_edge(2, 4, 5);
    graph.insert_edge(2, 5, 5);
    graph.insert_edge(3, 5, 3);
    graph.insert_edge(3, 6, 6);
    graph.insert_edge(4, 7, 8);
    graph.insert_edge(5, 7, 1);
    graph.insert_edge(6, 8, 10);
    graph.insert_edge(7, 9, 1);
    graph.insert_edge(8, 9, 1);
    vector<int> v = {1,2,3,5,7};
    EXPECT_EQ(graph.path_finding(1,9), v);
    vector<int> v2 = {1,2,3,6};
    EXPECT_EQ(graph.path_finding(1,8), v2);
    v.pop_back();
    EXPECT_EQ(graph.path_finding(1,7), v);
    v2.pop_back();
    EXPECT_EQ(graph.path_finding(1,6), v2);
    vector<int> v3 = {1,2};
    EXPECT_EQ(graph.path_finding(1,3), v3);
    EXPECT_ANY_THROW(graph.path_finding(5,2));
}
/*
TEST(graph, insert){
    Graph<string> graph;
    graph.insert_ver("a");
    graph.insert_ver("b");
    graph.insert_ver("c");
    graph.insert_edge("b","c",5);
    graph.insert_edge("c","b",1);
    graph.insert_edge("a","b",3);
    EXPECT_EQ(5, graph.find_distance("b","c"));
}*/
