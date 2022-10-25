#ifndef shortestP2P_HPP
#define shortestP2P_HPP

#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX
#define MYINF 715827882
// comment the below line to use SPFA
//#define FLOYD_ALGORITHM 
#ifndef FLOYD_ALGORITHM
typedef struct _Node
{
    unsigned int to;
    int weight;
}node;
#endif

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

  private:
    // internal data and functions.

    
    void invalid_graph_error() {cout << "Invalid graph. Exiting." << endl;exit(0);}
    void print(int dis) {
        if (dis!=MYINF) cout << dis << endl;
        else cout << "INF" << endl; 
    }
    #ifdef FLOYD_ALGORITHM
        vector<vector<int>> u; // adjacent matrix
        void initialize_adjacent_matrix(unsigned int num);
        bool if_valid_graph();
        bool floyd();
    #else
        vector<list<node>> a; // adjacent list
        vector<int> d; // distance
        list<unsigned int> q;//queue
        vector<int> cnt;//number of times of inque
        vector<bool> exist;//if in queue
        bool spfa(unsigned begin); // false if invalidness detected
    #endif
};

void ShortestP2P::readGraph(){
    int vertices_num;
    cin >> vertices_num;
    int edges_num;
    cin >> edges_num;
    #ifdef FLOYD_ALGORITHM
        this->initialize_adjacent_matrix((unsigned)vertices_num);
        int start=0,end=0,weight=0;
        for (int i = 0; i< edges_num; i++){
            cin >> start >> end >> weight;
            if ((start==end && weight<0) || start < 0 || end < 0) invalid_graph_error();
            u[(unsigned)start][(unsigned)end]=weight;
        }
        if (!floyd() || !if_valid_graph()) invalid_graph_error();
    #else
        node tmp; int start = 0;
        a.resize((unsigned)vertices_num);
        d.resize((unsigned)vertices_num);
        cerr << "Number of vertices: " << vertices_num << endl;
        for (unsigned int i = 0; i< (unsigned)edges_num; i++){
            cin >> start >> tmp.to >> tmp.weight;
            if (((unsigned)start==tmp.to && tmp.weight<0) || start < 0) invalid_graph_error();
            a[(unsigned)start].push_back(tmp);
        }
    #endif
}

void ShortestP2P::distance(unsigned int A, unsigned int B){
    #ifdef FLOYD_ALGORITHM
        print(u[A][B]);
    #else
        cerr << "Query: " << A << " to " << B << endl;
        spfa(A);
        print(d[B]);
    #endif
}


#ifdef FLOYD_ALGORITHM
bool ShortestP2P::if_valid_graph(){
    for (unsigned int i = 0; i < u.size(); i++){
        if (u[i][i]<0) return false;
    }
    return true;
}
void ShortestP2P::initialize_adjacent_matrix(unsigned int num){
    u.resize(num);
    for (unsigned int i = 0; i < num; i++){
        u[i].resize(num);
        for (unsigned int j = 0; j < num; j++){
            u[i][j]=(i==j)?0:MYINF;
        }
    }
}
bool ShortestP2P::floyd(){
    for (unsigned int k = 0; k < u.size(); k++){
        for (unsigned int i = 0; i < u.size(); i++){
            for (unsigned int j = 0; j < u.size(); j++){
                u[i][j] = (u[i][k]+u[k][j]<u[i][j])?u[i][k]+u[k][j]:u[i][j];
            }
            if (u[i][i]<0) return false;
        }
    }
    return true;
}
#else

bool ShortestP2P::spfa(unsigned int begin){
    d.assign(a.size(),MYINF);
    q.assign(1,begin);//queue
    cnt.assign(a.size(),0);//number of times of inque
    exist.assign(a.size(),false);//if in queue
    d[begin]=0;
    cnt[begin]=1;
    exist[begin]=true;//first element in the que
    while(!q.empty()){
        const unsigned int first=q.front();
        q.pop_front();
        exist[first]=false;//deque
        for(auto i=a[first].begin(); i!=a[first].end(); i++)
            if (d[i->to]>d[first]+i->weight){ // update and inque
                d[i->to] = d[first]+i->weight;
                if (!exist[i->to]){
                    exist[i->to] = true;
                    if (++cnt[i->to]==(int)a.size()) return false;// negative cycle
                    if (!q.empty() && d[i->to]<d[q.front()]) q.push_front(i->to);
                    else q.push_back(i->to);
                }
            }
    }
    return true;
}
#endif
#endif //SHORTESTP2P_HPP