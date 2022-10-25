#include "kdtree.hpp"
#include <iostream>
#include <string>
using namespace std;

typedef std::tuple<int,int,int> my_key;
typedef string my_value;
typedef std::pair<my_key,my_value> element;

element make_element(int a, int b, int c,string d){
    return make_pair(make_tuple(a,b,c),d);
}

int main(){

    vector<element> v;
    v.push_back(make_element(-1,2,0,"VE281"));
    v.push_back(make_element(0,0,0,"VE280"));
    v.push_back(make_element(1,-1,0,"VE482"));
    v.push_back(make_element(0,0,0,"VE282"));
    v.push_back(make_element(0,0,0,"VE370"));
    v.push_back(make_element(1,-1,1,"VE283"));
    v.push_back(make_element(0,0,-1,"VE284"));
    v.push_back(make_element(0,-1,0,"VE285"));

    KDTree<std::tuple<int,int,int>,string> kdTree(v);
    cout << "The treesize of kdTree is: " << kdTree.size() << endl;
    KDTree<std::tuple<int,int,int>,string> kdTree2 = kdTree;
    cout << "The treesize of kdTree2 is: " << kdTree2.size() << endl;
    //kdTree2.insert(make_tuple(0,0,0),"VE483");
    //cout << "After inserting... \nThe treesize of kdTree2 is: " << kdTree2.size() << endl;
    //kdTree2.insert(make_tuple(-1,2,-4),"VE477");
    //cout << "After inserting... \nThe treesize of kdTree2 is: " << kdTree2.size() << endl;
    
    
    //kdTree2.erase(make_pair(0,0));
    //cout << "After erasing... \nThe treesize of kdTree2 is: " << kdTree2.size() << endl;
    //kdTree2.erase(make_pair(3,6));
    //cout << "After erasing... \nThe treesize of kdTree2 is: " << kdTree2.size() << endl;
    for (auto &item : kdTree2){
        cout << item.second << endl;
    }
    //cout << "Maximum in dim 1: " << (kdTree2.findMax<1>())->second << endl;
    //cout << "Maximum in dim 0: " << (kdTree2.findMax<0>())->second << endl;
    //cout << "find (-1,2,-4)?: " << (kdTree2.find(make_tuple(-1,2,-4))->second) << endl;
    //kdTree2.erase(make_tuple(-1,2,-4));
    cout << "The result of range search is : \n";
    vector<my_value> result = *(kdTree2.Range_Search(make_tuple(0,0,0),1));
    for (auto it = result.begin(); it < result.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}
