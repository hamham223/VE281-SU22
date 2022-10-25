#include <random>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
int main(){
    srand((unsigned)time(NULL));
    int N = (rand()%2000000+5);
    int x,y;
    //std::default_random_engine generator;
    //double seed = 3.0;
    //std::gamma_distribution<double> distribution(double(1.0/seed),double(2.0/seed));
    cout << N << endl;
    for (int  i = 0; i < N; i++){
        x = (rand()%N+1)*(rand()%3-1);
        y = (rand()%N+1)*(rand()%3-1);
        cout << x << " " << y << endl;
    }
    return 0;
}
