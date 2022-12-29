#ifndef LAB23SEM_HASH_H
#define LAB23SEM_HASH_H
#include <list>
#include <functional>
#include <iostream>
#include <iterator>
#include <exception>
using namespace std;
template <typename K,typename V>
class Node{
private:
    K key;
    V value;
    //Node<K, V>* next;
public:
    Node(){
        key = 0;
        value = 0;
        //next = nullptr;
    }
    Node(const K& k,const V& v) {
        key = k;
        value = v;
        //next = nullptr;
    }
    bool check(const K& k){
        if (key == k){
            return true;
        }
        else{
            return false;
        }
    }
    V Get_Element(){
        return value;
    }
    K Get_Key(){
        return key;
    }
};
template <typename Tkey,typename Tvalue>
class hash_table{
public:
    list<Node<Tkey, Tvalue>>** arr;
    int capacity;
    int number;
    const float rehash_factor = 0.7;
    int hash_function(Tkey key){
        return key % capacity;
    }
public:
    hash_table() {
        capacity = 8;
        number = 0;
        arr = new list<Node<Tkey, Tvalue>>* [capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = nullptr;
        }
    }
    hash_table(int cap){
        capacity = cap;
        number = 0;
        arr = new list<Node<Tkey, Tvalue>>* [capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = nullptr;
        }
    }
    /*hash_table(Tkey key, Tvalue value){
        capacity = 8;
        number = 0;
        arr = new list<Node<Tkey, Tvalue>>* [capacity];
        for (int i = 0; i < capacity; i++) {
            if(i == hash_function2(key)){
                arr[i]->insert(key, value);
            }
            else {
                arr[i] = nullptr;
            }
        }
    }*/
    ~hash_table(){
        for(int i = 0; i < capacity; i++){
            if(arr[i]){
                delete arr[i];
            }
        }
        delete[] arr;
    }
    void insert(const Tkey& key, const Tvalue& value){
        //cout<< number<<" "<< capacity<<" \n";
        number++;
        if(capacity*rehash_factor < number){
            rehash();
        }
        int num = hash_function(key);
        list<Node<Tkey, Tvalue>>* current = arr[num];
        if(current != nullptr){
            auto* newNode = new Node<Tkey, Tvalue>(key, value);
            current->push_back(*newNode);
        }
        else{
            auto* newNode = new Node<Tkey, Tvalue>(key, value);
            current = new list<Node<Tkey, Tvalue>>;
            current->push_back(*newNode);
            //copy(current->begin(), current->end(), ostream_iterator<int>(cout," "));
            //cout<<current->begin()->value<<" "<<num<<"\n";
            arr[num] = current;
        }
    }
    Tvalue operator[](Tkey){

    }
    bool is_find(const Tkey& key){
        int num = hash_function(key);
        list<Node<Tkey, Tvalue>>* current = arr[num];
        if(current == nullptr){
            //cout<<"no element"<<"\n";
            return false;
        }
        else{
            for(auto iter = current->begin(); iter!= current->end(); iter++){
                if(iter->check(key)){
                    //cout<<"your element is "<< iter->Get_Element()<<"\n";
                    return true;
                }
            }
            //cout<<"the last added element is "<< current->back().value<<"\n";
            //cout<<"no element";
            return false;
        }
    }
    Tvalue find_by_the_key(const Tkey& key){
        int num = hash_function(key);
        list<Node<Tkey, Tvalue>>* current = arr[num];
        if(current == nullptr){
            throw "no element";
        }
        else{
            for(auto iter = current->begin(); iter!= current->end(); iter++){
                if(iter->check(key)){
                    return iter->Get_Element();
                }
            }
            //cout<<"the last added element is "<< current->back().value<<"\n";

            throw "no element";
        }
    }
    void erase (const Tkey& key){
        int num = hash_function(key);
        list<Node<Tkey, Tvalue>>* current = arr[num];
        if (current == nullptr){
            cout<<"key doesn't find";
            return;
        }
        else{
            for(auto iter = current->begin(); iter != current->end(); iter++){
                if(iter->check(key)){
                    current->erase(iter);
                    if(current->begin() == current->end()){
                        //delete current;
                        //current->clear();//= nullptr;
                        arr[num] = nullptr;
                    }
                    return;
                }
            }
            cout<<"key doesn't find";
            return;
        }
    }
    int Get_Size(){
        return capacity;
    }
    void rehash(){
        int previous_size = capacity;
        capacity = capacity*2;
        auto** new_arr = new list<Node<Tkey, Tvalue>>* [capacity];
        for(int i = 0; i < capacity; i++){
            new_arr[i] = nullptr;
        }
        swap(arr, new_arr);
        for(int i = 0; i < previous_size; i++){
            list<Node<Tkey, Tvalue>>* current = new_arr[i];
            if(current != nullptr) {
                for (auto iter = current->begin(); iter != current->end(); iter++) {
                    //arr[hash_function(iter->Get_Key())];
                    this->insert(iter->Get_Key(), iter->Get_Element());
                    number--;
                }
            }
        }
        for(int i = 0; i < previous_size; i++){
            delete(new_arr[i]);
        }
    delete[](new_arr);
    }
};

template <typename Tkey, typename Tvalue>
ostream& operator << (ostream &os, const hash_table<Tkey, Tvalue> &table) {
    for(int i = 0; i < table.capacity; i++){
        if (table.arr[i] != nullptr){
            list<Node<Tkey, Tvalue>>* param = table.arr[i];
            for(auto iter = param->begin(); iter != param->end(); iter++){
                os<< iter->Get_Element()<<"|"<<iter->Get_Key()<<" ";
            }
            //copy(param->begin(), param->end(), ostream_iterator<Node<Tkey, Tvalue>>(os," "));
        }
        else{
            os<<"None ";
        }
        os<<"\n";
    }
    return os;
};
#endif //LAB23SEM_HASH_H