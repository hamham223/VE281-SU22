#include "hashtable.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

std::random_device r;
std::default_random_engine e1(r());
std::uniform_int_distribution<int> uniform_dist(-100000,100000);
std::normal_distribution<> normal_dist{0.5,0.2};

void print_Hash_Table(HashTable<int,int> &a){
    cout << "============ Resulting HashTable ============" << endl;
    auto it = a.begin();
    for (size_t i = 0; i < a.bucketSize(); i++){
        printf("%6ld |",i);
        while (it!=a.end() && (it->first % a.bucketSize() == i) ){
            printf(" {%d, %d}",it->first,it->second);
            it++;
        }
        printf("\n");
    }
    
}

inline void erase_message(bool flag,int key){
    if (flag) printf("erase %d suceessfully!\n",key);
    else printf("%d does not exist!\n",key);
}

void random_erase(HashTable<int,int> & a,int num,ifstream & in){
    int key;in >> key;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1);
        erase_message(a.erase(key),key);
    }
}

void random_insert(HashTable<int,int> & a,int num,ifstream & in){
    int key, value;
    in >> key >> value;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1); value = uniform_dist(e1);
        a.insert(key,value);
    }
}

void random_access(HashTable<int,int> & a,int num,ifstream & in){
    int key;in >> key;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1);
        printf("Access value %d at key %d\n",a[key],key);
    }
}

inline void find_message(bool flag,int key){
    if (flag) printf("Key %d found!\n",key);
    else printf("Key %d not found!\n",key);
}

void random_find(HashTable<int,int> & a,int num,ifstream & in){
    int key; in >> key;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1);
        find_message(a.contains(key),key);
    }
}

int main(){
    HashTable<int,int> a;
    HashTable<int,int> b;
    ifstream in;
    in.open("list");
    auto start = std::chrono::steady_clock::now();
    a.setMaxLoadFactor((double)(normal_dist(e1)));
    for (int i = 0; i < 10; i++){
        random_insert(a,1000,in);
        random_access(a,1000,in);
        random_erase(a,1000,in);
        random_find(a,1000,in);
    }
    b = a;
    print_Hash_Table(b);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end-start);
    ofstream out;
    out.open("time");
    out << "elapsed time: " << elapsed_seconds.count() << "s\n";
    out.close();
    in.close();
    return 0;
}