//
// Created by olegg on 26.12.2022.
//

#ifndef LAB23SEM_TRASH_H
#define LAB23SEM_TRASH_H
/*struct Node {
        Node *next;
        T element;
        K key;
        Node *head;
        Node* insert(T value){
            if
        }
        Node *insert_front(T value, K key) {
            Node *tmp = new Node(value, key);
            if (head == nullptr)
                head = tmp;
            else {
                head->prev = tmp;
                tmp->next = head;
                head = tmp;
            }
            return head;
        }
    };
    T find(K key){
        Node* node = arr[hash<K>(key)%size];
        if(node == nullptr){
            cout<< "no element";
            return nullptr;
        }
        else{
            while(node->next != nullptr){
                node = node->next;
            }
            return node->element;
        }
    }
    void add_elem(T data, K key){
        number++;
        if(capacity/number < 2){
            //Rehash;
        }
        data = arr[hash<K>(key)%size];
    }
    void delete_elem(T data){

    }
    void Rehash(){

    }
    void print_all_elements(const Tkey& key){
        int num = hash_function(key);
        list<Node<Tkey, Tvalue>>* current = arr[num];
        if(current != nullptr){
            copy(current->begin(), current->end(),)
        }
    }
void rehash(){
        int previous_size = capacity;
        capacity = capacity*2;
        auto** new_arr = new list<Node<Tkey, Tvalue>>* [capacity];
        for (int i = 0; i < capacity; i++)
            new_arr[i] = nullptr;
        swap(arr, new_arr);
    }
template <typename K, typename V>
ostream& operator << (ostream&os, const Node<K,V>& node){
    return os<< node.Get_Element()<<"|"<<node.Get_Key<<" ";
}

#include <stdio.h>
#include <vector>
#include <list>
using namespace std;
template <typename K, typename T>
class hash{
private:
    class Element{
        T data;
        K value;
        bool is_used;
        bool is_deleted;
    };
    Element** arr;
    int size;
    int capacity;
    int number;
    //K hashfunction;
public:
    hash(){
        capacity = 8;
        size = 0;
        number = 0;
        //hashfunction = hash_func;
        arr = new Element*[capacity];
        for(int i = 0; i < capacity; i++){
            arr[i] = nullptr;
        }
    }
    ~hash(){
        for(int i = 0; i < capacity; i++){
            if(arr[i]){
                delete arr[i];
            }
        }
        delete[] arr;
    }
    void Resize(){
        int previous_capacity = capacity;
        capacity*=2;
        Element** arr2 = new Element* [capacity];
        for(int i = 0; i < previous_capacity; ++i){
            arr2[i] = nullptr;
        }
        swap(arr, arr2);
    }
    void add_elelement(T value, hashfunction){

    }
    void delete_element(){

    }
    T find_element(){

    }
};

    */
#endif //LAB23SEM_TRASH_H
