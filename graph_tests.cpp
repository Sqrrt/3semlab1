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
    graph.insert_ver(1);
    graph.insert_ver(2);
    graph.insert_ver(3);
    graph.insert_ver(4);
    graph.insert_edge(2,3,3);
    graph.insert_edge(1,2,2);
    graph.insert_edge(1,3,8);
    graph.insert_edge(1,4,2);
    graph.insert_edge(2,4,8);
    graph.insert_edge(3,4,8);
    stack<int> res = graph.top_sort();
    int i = 1;
    while(!res.empty()){
        EXPECT_EQ(res.top(), i);
        res.pop();
        i++;
    }
    graph.insert_edge(4,2,1);
    //ASSERT_ANY_THROW(graph.top_sort());
}