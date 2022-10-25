#include <iostream>
using std::cin;
using std::cout;
int max2(int a, int b){
    return (a>b)?a:b;
}
int max4(int a,int b, int c,int d){
    return max2(a,max2(b,max2(c,d)));
}
int main(){
    // two paths are considered simultaneously, one at (i, j), the other at (k, l)
    // integers stored in integer[n][n]
    int n;
    cin >> n;
    int dp[10][10][10][10] = {0};
    int integers[10][10] = {0};
    int x, y ,val;
    // read all the inputs
    while (true){
            cin >> x >> y >> val;
            if (x==0 && y ==0 && val==0) break;
            integers[x][y]=val;
        }
    
    dp[1][1][1][1] = integers[1][1]; // start point
    
    // start dp
    
    /* modify code within this part */
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                for (int l = 1; l <= n; l++){
                    dp[i][j][k][l] = max4(dp[i-1][j][k-1][l], dp[i][j-1][k-1][l],
                                         dp[i-1][j][k][l-1], dp[i][j-1][k][l-1])
                                         + integers[i][j] + integers[k][l];
                    if(i==k&&j==l) dp[i][j][k][l]-=integers[i][j];
                }                         
                                         
    /* modify code within this part */
    
    cout << dp[n][n][n][n];
    
}