#include "sort.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class myint{
    protected:
        int val;
        int ord;
    public:
        myint();
        myint(int v,int o);
        void print();
        bool operator<(const myint& y) const;
        myint& operator=(const myint& y);
};
myint::myint(int v,int o):val(v),ord(o) {}
myint::myint():val(0),ord(0) {}
void myint::print(){
    cout << val << " " << ord << endl;
}
bool myint::operator<(const myint& y) const{
    return (this->val<y.val);
}
myint & myint::operator= (const myint& y){
    if (this != &y) {this->val = y.val;this->ord = y.ord;}
    return *this;
}
template<typename T>
bool compare_less(const T &lhs, const T &rhs) {
    return lhs < rhs;
}
void generate(vector<myint>& a){
    srand((unsigned)time(NULL));
    int count = rand()%300+50;
    int val = 0; 
    int exist[101]={0};
    for (int i = 0; i < count; i++){
        val = rand()%80+1;
        exist[val]++;
        a.push_back({val,exist[val]});
    }
}
int main(){
    vector<myint> a;
    generate(a);
    //a.push_back({46,1});
    //a.push_back({52,1});
    //a.push_back({45,1});
    //a.push_back({80,1});
    //a.push_back({4,1});
    cout << "Before sorting........" << endl;
    for (auto i=a.begin();i!=a.end();i++) {
        (*i).print();
    }

    cout << "After sorting........." << endl;
    quick_sort_extra(a,compare_less<myint>);
    for (auto i=a.begin();i!=a.end();i++) {
        (*i).print();
    }
    return 0;
}