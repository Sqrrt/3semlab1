#ifndef INC_3LAB3SEM_GRAPH_H
#define INC_3LAB3SEM_GRAPH_H
#include <iostream>
#include "../lab23sem/hash.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <stack>
#include <unordered_map>
#include <typeinfo>
#include <list>
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
        return ((int)value_1*10 + (int)value_2) % size;
        //return (value_1.length()*10 + value_2.length()) % size;
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
    Tvalue find_special(Tindex i1, Tindex i2){
        Pair<Tindex, Tindex> pair(i1, i2);
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
    vector<T> vec; // vector of all vertexes
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

    //graph realization
    Graph() {
        graph =new Matrix<T, int>;
        number_of_ver = 0;
    }
    int GetNumber() {
        return number_of_ver;
    }
    void insert_edge(const T& first,const T& second, int distance) {
        Pair<T, T> p = Pair<T,T>(first, second);
        graph->erase(Pair<T,T>(first, second));
        graph->insert(p, distance);
    }
    int find_distance(const T& first,const T& second){
        return graph->find(Pair<T,T>(first, second));
    }
    void delete_edge(const T& first,const T& second){
        Pair<T, T> p = Pair<T,T>(first, second);
        graph->erase(p);
        graph->insert(p,10000);
    }
    void insert_ver(const T& ver) {
        number_of_ver++;
        vec.push_back(ver);
        Pair<T, T> p = Pair<T,T>(ver, ver);
        graph->insert(p, 10000);
        for(int i = 0; i < number_of_ver; i++){
            insert_edge(ver, vec[i], 10000);
            insert_edge(vec[i],ver, 10000);
        }
    }
    void delete_ver(const T& ver) {
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
    bool is_edge(const T& start,const T& finish){
        if(!finish || !start){
            return false;
        }
        if(find_distance(start, finish) < 10000){
            return true;
        }
        else{
            return false;
        }
    }

    //different functions for finding distance
    bool is_no_positive_cycle_in_graph(){
        for(int i = 0; i < vec.size(); i++){
            if(worshell_floyd(vec[i]) < 0){
                return false;
            }
        }
        return true;
    }
    //extratask
    unordered_map<T, int> deixtra(T start, T finish){//новый дейкстра, немного красивее предыдущего
        vector<T> temp = vec;
        vector<int> vspom(vec.size()); // вектор, говорящий о том, была посещена вершина или нет
        unordered_map<T, int> weights; // хэш таблица, хранящая веса (двумя векторами как было раньше не получилось)
        T start2 = start;
        for(int i = 0; i < vec.size(); i++){
            //cout<< vec[i]<<" ";
            if(vec[i] == start2){
                weights[vec[i]] = 0;
                vspom[i] = 2;
            }
            else {
                weights[vec[i]] = 10000;
                vspom[i] = 1;
            }
        }
        int count = 0;
        int x = 0;
        // сам алгоритм
        while(count < 10001) {
            for (int i = 0; i < temp.size(); i++) {
                if (weights[temp[i]] > count) {
                    if (is_edge(start2, temp[i])) {
                        weights[temp[i]] = min(weights[temp[i]], weights[start2] + find_distance(start2, temp[i]));
                    }
                }
            }
            int d = 10001;
            int m = 10000;
            for (int i = 0; i < temp.size(); i++) {
                if (vspom[i] == 1 && weights[temp[i]] >= count && weights[temp[i]] < d) {
                    d = weights[temp[i]];
                    m = i;
                }
            }
            count = d;
            if(m < 10000) {
                start2 = temp[m];
                vspom[m] = 2;
            }
        }
        return weights;
    }
    //Для нахождения обратного пути, так как имеем дело с матрицей расстояний, можем в любое время рассмотреть ребро ab любых вершин.
    //Если текущий вес в точности равен весу смежной вершины плюс вес направленного ребра, то эта вершина часть кратчайшего пути, иначе
    //был бы знак меньше. Далее заменяем вершину на finish и повторяем циклом. Сложность вроде невысокая, максимум O(VE).
    vector<T> path_finding(T start, T finish){
        unordered_map<T, int> weights = deixtra(start, finish);
        vector<T> result;
        int count = weights[finish];
        int x = 0;
        while(count != 0 && x < vec.size()+2) {
            if(x == vec.size() + 1){
                throw invalid_argument("no path");
            }
            for (int i = 0; i < vec.size(); i++) {
                if (is_edge(vec[i], finish)) {
                    if (weights[vec[i]] == weights[finish] - find_distance(vec[i], finish)) {
                        result.push_back(vec[i]);
                        finish = vec[i];
                        count = weights[vec[i]];
                    }
                }
            }
            x++;
        }
        //cout<< "\n";
        reverse(result.begin(), result.end());
        return result;
    }

    //algorithms returns shortest distance
    int dexter(T start, T finish){
        unordered_map<T, int> weights = deixtra(start, finish);
        for(int i = 1; i < vec.size(); i++){
            if(vec[i] == finish){
                return weights[vec[i]];
            }
        }
        return -1;
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
        for(int i = 0; i < number_of_ver - 1; ++i){
            for(int j = 0; j < e_vector.size(); ++j){
                if(result[index(vec[i])] < 10000){
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
        //cout<<"\n";
        return 10000;
    }

    //search and top sort
    vector<T> DFS(unordered_map<T, int>& pairs, vector<T>& result,const T& v){
        pairs[v] = 1;
        for(int j = 0; j < number_of_ver; j++){
            if(find_distance(v, vec[j]) != 10000){
                if(pairs[vec[j]] == 0){
                    result = DFS(pairs, result, vec[j]);
                }
            }
        }
        if(pairs[v] == 1){
            pairs[v] = 2;
            result.push_back(v);
        }
        return result;
    }
    vector<T> doDFS(T v){
        unordered_map<T, int> pairs;
        vector<T> result;
        for(int i = 0; i < number_of_ver; i++){
            pairs[vec[i]] = 0;
        }
        result = DFS(pairs,result,v);
        reverse(result.begin(), result.end());
        return result;
    }
    vector<T> top_sort(){
        unordered_map<T, int> pairs;
        vector<T> result;
        for(int i = 0; i < number_of_ver; i++){
            pairs[vec[i]] = 0;
        }
        for(int i = 0; i < vec.size(); i++){
            if(pairs[vec[i]] == 0){
                DFS(pairs,result, vec[i]);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
#endif //INC_3LAB3SEM_GRAPH_H
