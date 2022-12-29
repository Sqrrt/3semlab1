#ifndef INC_3LAB3SEM_GRAPH_H
#define INC_3LAB3SEM_GRAPH_H
//#include <map>
#include <iostream>
#include "../lab23sem/hash.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <exception>
#include <stack>
using namespace std;

template<typename T1, typename T2>
class Pair {
public:
    T1 value_1;
    T2 value_2;
    Pair<T1, T2>() {
        value_1 = T1();
        value_2 = T2();
    }
    Pair<T1, T2>(T1 arg_1, T2 arg_2) {
        value_1 = arg_1;
        value_2 = arg_2;
    }
    T1 GetFirst() {
        return value_1;
    }
    T2 GetSecond() {
        return value_2;
    }
    bool operator==(const Pair<T1, T2>& p) {
        if (value_1 == p.value_1 && value_2 == p.value_2) return true;
        else return false;
    }
    int operator%(int size){
        return (value_1*10 + value_2) % size;
    }
    Pair<T1, T2>&operator=(const Pair<T1, T2>& p) {
        this->value_1 = p.value_1;
        this->value_2 = p.value_2;
        return *this;
    }
    bool operator!=(const Pair<T1, T2>& p) {
        if (value_1 != p.value_1 || value_2 != p.value_2) return true;
        else return false;
    }
    Pair swaps(){
        return Pair<T2,T1>(value_2, value_1);
    }
};
template<typename Tindex, typename Tvalue>
class Matrix{
private:
    hash_table<Pair<Tindex,Tindex>, Tvalue>* matrix;
public:
    Matrix<Tindex, Tvalue>(){
        matrix =new hash_table<Pair<Tindex, Tindex>, Tvalue>;
    }
    Matrix<Tindex,Tvalue>(Pair<Tindex, Tindex> pair, Tvalue value){
        matrix =new hash_table<Pair<Tindex, Tindex>, Tvalue>(pair, value);
    }
    int GetSize(){
        return matrix->Get_Size();
    }
    void insert(Pair<Tindex, Tindex> pair, Tvalue value){
        matrix->insert(pair, value);
    }
    void erase(Pair<Tindex, Tindex> pair){
        if(matrix->is_find(pair)){
            matrix->erase(pair);
        }
    }
    Tvalue find(Pair<Tindex, Tindex> pair){
        return matrix->find_by_the_key(pair);
    }
};
template <typename T>
class Graph{
private:
    template<typename Td>
    class Edge {
    public:
        Td start;
        Td finish;
        int distance;
        Edge(Td start_vertex, Td finish_vertex, int distance1) {
            start = start_vertex;
            finish = finish_vertex;
            distance = distance1;
        }
        friend ostream& operator<< (ostream &out, const Edge<Td> &edge) {
            out << "[ " << edge.start << " -> " << edge.finish << " : " << edge.distance << " ]";
            return out;
        }
    };
    Matrix<T, int>* graph;
    int number_of_ver;
    vector<T> vec;
    int min(int a, int b){
        if(a > b){
            return b;
        }
        return a;
    }
    int index(T ver){
        for(int i = 0; i < number_of_ver; i++){
            if(vec[i] == ver) {
                return i;
            }
        }
        return -1;
    }
public:
    Graph() {
        graph =new Matrix<int, T>;
        number_of_ver = 0;
    }
    int GetNumber() {
        return number_of_ver;
    }
    void insert_edge(T first, T second, int distance) {
        Pair<T, T> p = Pair<T,T>(first, second);
        graph->erase(Pair<T,T>(first, second));
        graph->insert(p, distance);
    }
    int find_distance(T first, T second){
        return graph->find(Pair<T,T>(first, second));
    }
    void delete_edge(T first, T second){
        Pair<T, T> p = Pair<T,T>(first, second);
        graph->erase(p);
        graph->insert(p,10000);
    }
    void insert_ver(T ver) {
        number_of_ver++;
        vec.push_back(ver);
        Pair<T, T> p = Pair<T,T>(ver, ver);
        graph->insert(p, 10000);
        for(int i = 0; i < number_of_ver; i++){
            insert_edge(ver, vec[i], 10000);
            insert_edge(vec[i],ver, 10000);
        }
    }
    void delete_ver(T ver) {
        for (int i = 0; i < number_of_ver; i++) {
            if (graph->find(Pair<T, T>(ver, vec[i]))) {
                delete_edge(ver, vec[i]);
            }
        }
        for (int i = 0; i < number_of_ver; i++) {
            if (graph->find(Pair<T, T>(vec[i], ver))) {
                delete_edge(vec[i], ver);
            }
        }
        number_of_ver--;
        graph->erase(Pair<T, T>(ver, ver));
        //auto iter = remove(vec.begin(), vec.end(), ver);
        //vec.erase(iter, vec.end());
        auto it = find(vec.begin(), vec.end(), ver);
        if(it != vec.end()){
            vec.erase(it);
        }
    }
    void print(){
        for(int i = 0; i < number_of_ver; i++){
            for(int j = 0; j < number_of_ver; j++) {
                cout<<vec[j]<<"->"<<vec[i]<<" = "<< find_distance(vec[j], vec[i])<<" | ";
            }
            cout<<"\n";
        }
    }
    bool is_edge(T start, T finish){
        if(!finish){
            return false;
        }
        if(find_distance(start, finish) != 10000){
            return true;
        }
        else{
            return false;
        }
    }
    vector<T> number_vertexes_into(T item){
        vector<T> result;
        for(auto iter = vec.begin(); iter != vec.end(); iter++){
            if(find_distance(iter, item) != 10000){
                result.push_back(item);
            }
        }
        return result;
    }
    void vspom_func_for_sort(bool visited[],T v, stack<T>& st){
        visited[v - 1] = true;
        for(auto it = vec.begin(); it != vec.end(); it++){
            if(!visited[*it]){
                if(find_distance(v, *it) != 10000){
                    vspom_func_for_sort(visited, *it, st);
                }
            }
        }
        st.push(v);
    }
    stack<T> top_sort(){
        stack<T> result;
        vector<stack<T>> last;
        bool *visited = new bool[number_of_ver];
        for(int i = 0; i < number_of_ver; i++){
            visited[i] = false;
        }
        for(int j = 0; j < number_of_ver; j++) {
            if (!visited[j]) {
                vspom_func_for_sort(visited, vec[j], result);
            }
            last.push_back(result);
        }
        int max = 0;
        int b = 0;
        for(int i = 0; i < last.size(); i++){
            if(last[i].size() > max){
                b = i;
                max = last[i].size();
            }
        }
        return last[b];
    }
    void DFS(T v, bool& param, int visited[]){
        //int* visited = new int[number_of_ver];
        visited[v - 1] = 1;
        for(auto it = vec.begin(); it !=  vec.end(); it++){
            if(find_distance(v,*it) != 10000) {
                //cout<<v<<" "<< *it <<" "<< find_distance(v,*it)<<"\n";
                if (visited[*it] == 0) {
                    DFS(vec[*(it--)], param, visited);
                }
                if (vec[*it] != vec[v-1]) {
                    if (visited[*it] == 1) {
                        //cout << vec[*it]<<" "<< vec[v]<<" ";
                        param = true;
                        break;
                    }
                }
            }
        }
        visited[v - 1] = 2;
    }
    bool is_cycle_here(){
        int* visited = new int[number_of_ver];
        for(int i = 0; i < number_of_ver; i++){
            visited[i] = 0;
        }
        bool param = false;
        T v = vec[0];
        DFS(v, param, visited);
        return param;
    }
    int dexter(T start, T finish) {
        if(start == finish){
            return 0;
        }
        vector<T> vector_of_vertexes(number_of_ver);
        vector<int> vector_of_weights(number_of_ver);
        vector<T> vector = vec;
        for(int j = 0; j < vec.size(); j++){
            vector_of_weights[j]= 10000;
            if(vec[j] == start){
                vector_of_vertexes[j] =start;
                vector_of_weights[j]= 0;
            }
        }
        int current_distance = 0;
        int count = 0;
        while(count != number_of_ver){
            count++;
            for(int i = 0; i < vector.size(); i++){
                if(is_edge(start, vector[i])){
                    if(!vector_of_vertexes[i]){
                        vector_of_vertexes[i] = vector[i];
                        vector_of_weights[i] = current_distance + find_distance(start, vector[i]);
                    }
                    else{
                        if(vector_of_weights[i] > current_distance + find_distance(start, vector[i])){
                            vector_of_weights[i] = current_distance + find_distance(start, vector[i]);
                        }
                    }
                }
            }
            int min = 10000;
            int count2 = -1;
            for(int k = 0; k < number_of_ver; k++){
                if(vector_of_weights[k]){
                    if(vector_of_weights[k] < min){
                        min = vector_of_weights[k];
                        count2 = k;
                    }
                }
                /*
                if(vspom_vec[k] == start){
                    vspom_vec[k] = NULL;
                }*/
            }
            if(count2 < 0) {
                return -1;
            }
            current_distance = vector_of_weights[count2];
            start = vector_of_vertexes[count2];
        }
        //search_of_finish_vertex
        for(int l = 0; l < number_of_ver; l++){
            if(vector_of_vertexes[l] == finish){
                return(vector_of_weights[l]);
            }
        }
        return 10000;
    }
    int worshell_floyd(T start, T finish){
        vector<int> result(number_of_ver);
        for(int l = 0; l < result.size(); l++){
            result[l] = 10000;
            if(vec[l] == start){
                result[l] = 0;
            }
        }
        vector<int> labels;
        for(int uwu = 1; uwu <= number_of_ver - 1; uwu++){
            for(int o_o = 0; o_o < number_of_ver; o_o++){
                for(int lol = 0; lol < number_of_ver; lol++){
                    labels.push_back(result[lol]+find_distance(vec[lol], vec[o_o]));
                }
                /*for(auto iter = labels.begin(); iter != labels.end(); iter++){
                    cout<<*iter<<" ";
                }
                cout<<"\n";*/
                result[o_o] = min(result[o_o], *min_element(labels.begin(), labels.end()));
                //cout<< result[o_o]<<" \n";
                labels.clear();
            }
        }
        for(int p = 0; p < number_of_ver; p++){
            if(vec[p] == finish){
                return result[p];
            }
        }
        return 10000;
    }
    int bellman_ford(T start, T end){
        vector<int> result(number_of_ver);
        for(int i = 0; i < number_of_ver; i++){
            result[i] = 10000;
            if(vec[i] == start){
                result[i] = 0;
            }
        }
        vector<Edge<T>> e_vector;
        for(int i = 0; i < number_of_ver; i++){
            for(int j = 0; j < number_of_ver; j++){
                if(find_distance(vec[i], vec[j]) < 10000){
                    Edge<T> edge(vec[i], vec[j], find_distance(vec[i], vec[j]));
                    e_vector.push_back(edge);
                }
            }
        }
        int a = 0;
        int b = 0;
        for(int i = 0; i < e_vector.size() - 1; ++i){
            for(int j = 0; j < number_of_ver; ++j){
                if(result[index(e_vector[j].start)] < 10000){
                    a = index(e_vector[j].finish);
                    b = index(e_vector[j].start);
                    result[a] = min(result[a],result[b]+ e_vector[j].distance);
                }
            }
        }
        for(int p = 0; p < number_of_ver; p++){
            if(vec[p] == end){
                return result[p];
            }
        }
        return 10000;
    }
};
#endif //INC_3LAB3SEM_GRAPH_H
