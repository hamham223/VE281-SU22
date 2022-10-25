#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>
#include <stdlib.h>
#include <functional>


template<typename T, typename Compare>
void bubble_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    for (auto i = vector.begin() ; i != vector.end(); ++i){
        bool flag = true;
        for (auto j = vector.end()-1 ; j != vector.begin() ;j-- ){
            if (comp(*j,*(j-1))) {
                std::iter_swap(j,j-1);
                flag = false;
            }
        }
        if (flag) break;
    }
}

template<typename T, typename Compare>
void insertion_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    if (vector.size()<=1) return;
    auto j =vector.begin();
    T temp;
    for (auto i = vector.begin()+1 ; i != vector.end(); ++i){
        temp = *i;
        for ( j = i ; j != vector.begin(); j--){
            if (comp(temp,*(j-1))) 
                *(j) = *(j-1); 
            else 
                break;
        }
        *j = temp;
    }
}

template<typename T, typename Compare>
void selection_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    T min;
    auto k = vector.begin();
    for (auto i = vector.begin() ; i != vector.end(); ++i){
        min = *i; k = i;
        for (auto j = i+1 ; j != vector.end(); j++){
            if (comp(*j,min)) {
                min = *j; k=j;
            }
        }
        std::iter_swap(i,k);
    }
}

template<typename T, typename Compare>
void merge(T left, T mid  ,T right, //std::vector<typename T::value_type> &vector, 
            Compare comp = std::less<typename T::value_type>()){
    std::vector<typename T::value_type> sorted_vec;
    auto i = left; auto j = mid;
    while (i!= mid && j!=right){
        if (!comp(*j,*i)) {sorted_vec.push_back(*i);i++;}
        else {sorted_vec.push_back(*j);j++;}
    }
    while (i!=mid) {sorted_vec.push_back(*i);i++;}
    while (j!=right) {sorted_vec.push_back(*j);j++;}
    for (auto i = left, j = sorted_vec.begin(); i!= right; i++, j++) *i =*j;
    return;
}

template<typename T, typename Compare>
void merge_sort_helper( T left , T right, 
                         Compare comp = std::less<typename T::value_type>() ){
    // *(right - 1) represents the last element
    auto size = std::distance(left, right);
    if (size<=1) return;
    auto mid = left + size/2;
    merge_sort_helper(left,mid,comp);
    merge_sort_helper(mid,right,comp);
    merge(left,mid,right,comp);
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    merge_sort_helper(vector.begin(),vector.end(),comp);
}

template<typename T,typename Compare>
T partition_extra(T left, T right, Compare comp = std::less<typename T::value_type>()){
    auto size = std::distance(left,right);
    std::vector<typename T::value_type> parted_vec(size);
    auto pivot = std::next(right,-1);
    auto parted_vec_left = parted_vec.begin();
    auto parted_vec_right = parted_vec.end()-1;
    auto i = left;
    while ( i!=pivot) {
        if (comp(*i,*pivot)) {*parted_vec_left=*i;parted_vec_left++;}
        else {*parted_vec_right=*i;parted_vec_right--;}
        i++;
    }
    *parted_vec_left = *pivot;
    for (auto i = left, j = parted_vec.begin(); i!= right; i++, j++) *i =*j;
    return left+std::distance(parted_vec.begin(),parted_vec_left);
}

template<typename T, typename Compare>
void quick_sort_extra_helper(T left,T right, Compare comp = std::less<typename T::value_type>()){
    auto size = std::distance(left, right);
    if (size<=1) return;
    auto pivot = partition_extra(left,right,comp);
    quick_sort_extra_helper(left,pivot,comp);
    quick_sort_extra_helper(pivot+1,right,comp);
}

template<typename T, typename Compare>
void quick_sort_extra(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    quick_sort_extra_helper(vector.begin(),vector.end(),comp);
}

template<typename T, typename Compare>
T partition_inplace(T left, T right,Compare comp = std::less<typename T::value_type>() ){
    auto size = std::distance(left, right);
    auto pivot = std::next(right, -1);
    if (size == 2 && comp(*pivot , *left)) {
        std::iter_swap(left, pivot);
        return pivot;
    }
    auto mid = left; auto i = left;
    while (i!=right){
        if (comp(*i , *pivot)){
            std::iter_swap(mid,i);
            mid++;
        }
        i++;
    }
    std::iter_swap(mid,pivot);
    return mid;
}

template<typename T, typename Compare>
void quick_sort_helper(T left,T right, Compare comp = std::less<typename T::value_type>()){
    auto size = std::distance(left, right);
    if (size<=1) return;
    auto pivot = partition_inplace(left,right,comp);
    quick_sort_helper(left,pivot,comp);
    quick_sort_helper(pivot+1,right,comp);
}

template<typename T, typename Compare>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    quick_sort_helper(vector.begin(),vector.end(),comp);
}

#endif //VE281P1_SORT_HPP