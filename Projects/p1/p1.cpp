//#include "sort.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

struct pt{
    int x;
    int y;
};

bool operator==(pt p1,pt p2){
    return (p1.x ==p2.x && p1.y == p2.y);
}

bool if_lower(pt p1,pt p2){
    //EFFECTS: return true, if p1 is at the left bottom side of p2
    return (p1.y<p2.y || (p1.y==p2.y && p1.x < p2.x));
}

bool if_far(pt p0,pt p1,pt p2){
    //REQUIRES: p0,p1,p2 to be colinear, p0 is the left bottom point
    //EFFECTS: return true is p2 is far away from p0 than p1
    int d1 = p1.x-p0.x;
    int d2 = p2.x-p0.x;
    int d3 = p1.y-p0.y;
    int d4 = p2.y-p0.y;
    return (d4>d3 || ((d4==d3) && d2>d1));
    //false if d2<d1 or d2 == d1
}

ll ccw(pt p1, pt p2, pt p3){
    ll x1 = (ll)p1.x; ll y1 = (ll)p1.y;
    ll x2 = (ll)p2.x; ll y2 = (ll)p2.y;
    ll x3 = (ll)p3.x; ll y3 = (ll)p3.y;
    return  (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
}


struct CompareLess {
    pt _p0;
    bool operator()(const pt &lp, const pt &rp) const {
        // the farthest ones are kept in the bottom
        return (ccw(_p0,lp,rp)>0 || (ccw(_p0,lp,rp)==0 && if_far(_p0,lp,rp)));
    }
};

pt find_p0(const vector<pt>& X){
    pt p=X[0];
    for (auto i = X.begin()+1; i != X.end(); i++){
        if (if_lower(*i, p)) p =*i;
    }
    return p;
}

void input_X(vector<pt>& X, int N){
    int tmp1, tmp2; //for input
    pt tmp3;
    for (int i = 0; i < N; i++){
        cin >> tmp1 >> tmp2;
        tmp3.x=tmp1; tmp3.y = tmp2;
        X.push_back(tmp3);
    }
}

void remove_duplicates(vector<pt>& X,pt p0){
    // Remove all the colinear points, only keep the farest ones
    if (X.size()<=1) return;
    auto it=X.begin();
    while (it!= X.end()-1){
        if (ccw(p0,*it,*(it+1))==0) X.erase(it);
        else it++;
    }
}

template<typename T>
T next_to_top(vector<T> S){
    //REQUIRES: S.size() > 1
    //EFFECTS: return the next to top element of a vector
    return *(S.end()-2);
}

void solve_convex_hull(vector<pt>& S,vector<pt>& X){
    // main solver 
    for (auto i = X.begin() ; i != X.end(); i++){
        while (S.size()>1 && ccw(next_to_top(S),S.back(),*i)<=0){
            S.pop_back();
        }
         S.push_back(*i);
    }
}   

void print_result(vector<pt>& S,pt p0){
    cout << p0.x << " " << p0.y << endl;
    for (auto i = S.begin(); i != S.end(); i++){
        cout << (*i).x << " " << (*i).y << endl;
    }
}


void remove_p0(vector<pt> & X,pt p0){
    auto i = X.begin();
    while (i!=X.end()){
        if (*i == p0) X.erase(i);
        else i++;
    }
}
int main(){
    int N; cin >> N;
    if (N==0) return 0; //boudary case
    //
    vector<pt> X;
    input_X(X,N);//input
    
    pt p0 = find_p0(X); 

    CompareLess comp;
    comp._p0 = p0;

    remove_p0(X,p0);
    
    sort(X.begin(),X.end(),comp);
    

    remove_duplicates(X,p0);

    vector<pt> S;
    S.push_back(p0);
    solve_convex_hull(S,X);
    remove_p0(S,p0);
    sort(S.begin(),S.end(),comp);
    print_result(S,p0);
    return 0;
}