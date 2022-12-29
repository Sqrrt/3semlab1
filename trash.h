//
// Created by olegg on 29.12.2022.
//

/*#ifndef INC_3LAB3SEM_TRASH_H
#define INC_3LAB3SEM_TRASH_H
void vspom_func_for_sort(Pair<T, int>* pair, stack<T>* st){
        if(pair->GetSecond() == 1){
            throw "graph has cycle";
        }
        if(pair->GetSecond() == 0){
            pair->value_2 = 1;
            for(int i = 0; i < number_of_ver; ++i){
                if(find_distance(pair->GetFirst(), vec[i]) != 10000){
                    auto* pair2 = new Pair<T, int>(vec[i], 0);
                    vspom_func_for_sort(pair2, st);
                }
            }
            pair->value_2 = 2;
            st->push(pair->GetFirst());
        }
    }
    stack<T> DFS(){
        stack<T> result;
        vector<int> visited_vector(number_of_ver);
        vector<Pair<T, int>> vector(number_of_ver);
        for(int i = 0; i < number_of_ver; i++){
            Pair<T, int> pair(vec[i], 0);
            vector[i] = pair;
            visited_vector[i] = 0;
        }
        for(int j = 0; j < number_of_ver; j++){
            if(vector[j].GetSecond() == 0) {
                vspom_func_for_sort(&vector[j], &result);
            }
        }
        return result;
    }
#endif //INC_3LAB3SEM_TRASH_H
*/