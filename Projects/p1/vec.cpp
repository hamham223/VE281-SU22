#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector<int> a(10);
    auto size1 = distance(a.begin(),a.end());
    vector<int> b(size1);
    cout << b.size() << endl;
    return 0;
}