#include <iostream>
#include "graph.h"
#include <gtest/gtest.h>
int main() {
    Graph<int> graph;
    graph.insert_ver(1);
    graph.insert_ver(2);
    graph.insert_ver(3);
    graph.insert_ver(4);
    //graph.insert_edge(1,3,11);
    graph.insert_edge(3,2,3);
    graph.insert_edge(2,1,2);
    graph.insert_edge(3,1,8);
    graph.insert_edge(4,1,2);
    graph.insert_edge(4,2,8);
    graph.insert_edge(4,3,8);
    graph.insert_edge(3,4,8);
    //graph.insert_edge(4,2,11);
    //graph.delete_edge(2,3);
    //graph.delete_ver(2);
    graph.print();
    bool k = graph.is_cycle_here();
    if(k){
        cout<<"f";
    }
    stack<int> res = graph.top_sort();
    while(!res.empty()){
        cout<< res.top()<<" ";
        res.pop();
    }
    //graph.print();

}
/*
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
