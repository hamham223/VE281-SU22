#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isMatch(string s, string p) {
        auto matches = [&] (int i, int j){
            if (i==0) return false;
            if (j==0) return false;
            if (p[j-1]=='.') return true;
            return (s[i-1]==p[j-1]);
        };
        int m = s.size(); int n = p.size();
        bool ** f = new bool*[m+1];
        for (int i = 0; i <= m; i++) f[i] = new bool[n+1]{0};
        f[0][0] = true;
        for (int i = 0; i <= m ; ++i){
            for (int j = 1; j <=n ; ++j){
                if (i < j) {f[i][j] = false;continue;}
                if (p[j-1]=='*'){
                    f[i][j] = (f[i-1][j-1] && matches(i,j-1));
                }
                else {
                    f[i][j] = (f[i-1][j-1] && matches(i,j));
                }
            }
        }
        bool result = f[m][n];
        for (int i = 0; i <= m; i++) delete[] f[i];
        delete[] f;
        return result;
    }
};

int main(){
    Solution a;
    cout << "result is " << a.isMatch("aa","a*") << endl; 
    return 0;
}