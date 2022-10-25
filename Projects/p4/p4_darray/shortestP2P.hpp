#ifndef shortestP2P_HPP
#define shortestP2P_HPP

#include<iostream>
//#include<list>
//#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX
#define MYINF 715827882
// comment the below line to use SPFA


using namespace std;

class ShortestP2P {
  public:
      ShortestP2P() {}

      /* Read the graph from stdin
       * The input has the following format:
       *
       * Firstline: 1 unsigned int, the total number of verticies, X.
       * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
       * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
       *
       * Example:
       * 4
       * 4
       * 0 1 5
       * 1 2 -1
       * 2 3 4
       * 3 1 6
       * 
       * 
       * 
       *
       * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
       * 
       * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
       * cout << "Invalid graph. Exiting." << endl;
       *
       * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
       */
      void readGraph();

      /* Input: 2 vertices A and B
       * Output: distance between them.
       * cout << dist << endl;
       *
       * When the A and B are not connected print INF:
       * cout << "INF" << endl;
       */
      void distance(unsigned int A, unsigned int B);

      ~ShortestP2P(){
        for (unsigned int i = 0; i < size; i++){
            delete[] u[i];
        }
        if (u) delete[] u;
      }
  private:
    // internal data and functions.

    
    void invalid_graph_error() {cout << "Invalid graph. Exiting." << endl;exit(0);}
    void print(int dis) {
        if (dis!=MYINF) cout << dis << endl;
        else cout << "INF" << endl; 
    }
    int** u= nullptr; // adjacent matrix
    unsigned int size = 0;
    void initialize_adjacent_matrix();
    bool if_valid_graph();
    bool floyd();
};


void ShortestP2P::readGraph(){
    int vertices_num;
    cin >> vertices_num;
    int edges_num;
    cin >> edges_num;
    size = vertices_num;
    if (vertices_num==0) return;
    u = new int*[size];
    this->initialize_adjacent_matrix();
    int start=0,end=0,weight=0;
    for (int i = 0; i< edges_num; i++){
        cin >> start >> end >> weight;
        if (start < 0 || end < 0) invalid_graph_error();
        if (start==end){
            if (weight<0) invalid_graph_error();
            continue;
        }
        u[start][end]=weight;
    }
    if (!floyd() || !if_valid_graph()) invalid_graph_error();
}

void ShortestP2P::distance(unsigned int A, unsigned int B){
    print(u[A][B]);
}


bool ShortestP2P::if_valid_graph(){
    for (unsigned int i = 0; i < size; i++){
        if (u[i][i]<0) return false;
    }
    return true;
}
void ShortestP2P::initialize_adjacent_matrix(){
    for (unsigned int i = 0; i < size; i++){
        u[i] = new int[size];
        for (unsigned int j = 0; j < size; j++){
            u[i][j]=(i==j)?0:MYINF;
        }
    }
}
bool ShortestP2P::floyd(){
    for (unsigned int k = 0; k < size; k++){
        for (unsigned int i = 0; i < size; i++){
            for (unsigned int j = 0; j < size; j++){
                u[i][j] = (u[i][k]+u[k][j]<u[i][j])?u[i][k]+u[k][j]:u[i][j];
            }
            if (u[i][i]<0) return false;
        }
    }
    return true;
}

#endif //SHORTESTP2P_HPP