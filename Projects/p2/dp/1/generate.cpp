#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;

std::random_device r;
std::default_random_engine e1(r());
std::uniform_int_distribution<int> uniform_dist(-100000,100000);
std::normal_distribution<> normal_dist{0.5,0.2};

void random_insert(ofstream &out,int num){
    int key, value;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1); value = uniform_dist(e1);
        out << key << " " << value << endl;
    }
}

void random_access(ofstream &out,int num){
    int key;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1);
        out << key << endl;
    }
}



void random_find(ofstream & out,int num){
    int key;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1);
        out << key << endl;
    }
}

void random_erase(ofstream & out,int num){
    int key;
    for (int i = 0; i<num;i++){
        key = uniform_dist(e1);
        out << key << endl;
    }
}


int main(){
    ofstream out;
    out.open("list");
    for (int i = 0; i < 10; i++){
        random_insert(out,1000);
        random_access(out,1000);
        random_erase(out,1000);
        random_find(out,1000);
    }
    out.close();
}