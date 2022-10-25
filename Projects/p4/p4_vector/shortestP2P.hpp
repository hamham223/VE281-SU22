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

typedef struct _Node
{
    unsigned int next;
    int weight;
}node;


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
    
    //vector<vector<int>> u; // adjacent matrix
    vector<list<node>> from;
    vector<list<node>> to;
    void initialize_adjacent_matrix(unsigned int num);
    
    bool if_valid_graph();
    
    bool floyd();

    bool update(unsigned int start, unsigned int end, int weight);
};

void ShortestP2P::readGraph(){
    int vertices_num;
    cin >> vertices_num;
    int edges_num;
    cin >> edges_num;

    this->initialize_adjacent_matrix((unsigned)vertices_num);
    unsigned int start=0,end=0;
    int weight=0;
    for (int i = 0; i< edges_num; i++){
        cin >> start >> end >> weight;
        if (start==end) {
            if (weight<0) invalid_graph_error();
            continue;
        }
        from[end].push_back({start,weight});
        to[start].push_back({end,weight});
    }
    if (!floyd()) invalid_graph_error();
}

void ShortestP2P::distance(unsigned int A, unsigned int B){
    for (auto it = to[A].begin(); it!=to[A].end();it++){
        if (it->next==B) {cout << it->weight << endl;return;}
    }
    cout << "INF" << endl;
}

bool ShortestP2P::if_valid_graph(){
    return true;
}
void ShortestP2P::initialize_adjacent_matrix(unsigned int num){
    from.resize(num);
    to.resize(num);
    for (unsigned int i =0; i < num; i++){
        from[i].push_back({i,0});
        to[i].push_back({i,0});
    }
    //for (unsigned int i = 0; i < num; i++){
    //    u[i].resize(num);
    //    for (unsigned int j = 0; j < num; j++){
    //        u[i][j]=(i==j)?0:MYINF;
    //    }
    //}
}
bool ShortestP2P::floyd(){
    unsigned int i,j;
    for (unsigned int k = 0; k < from.size(); k++){
        for (auto it1 = from[k].begin(); it1 != from[k].end(); it1++){
            i = it1->next;
            for (auto it2 = to[k].begin(); it2 != to[k].end(); it2++){
                j = it2->next;
                if (!update(i,j,it1->weight+it2->weight)) return false;
            }
        }
    }
    return true;
}

bool ShortestP2P::update(unsigned int start, unsigned int end, int weight){
    if (start == end) {
        return (weight>=0);
    }
    bool flag = false;
    auto it = to[start].begin();
    for (; it!=to[start].end(); it++){
        if (it->next == end) {
            it->weight = (weight<it->weight)?weight:it->weight;
            flag = true; 
            break;
        }
    }
    if (!flag){
        from[start].push_back({end,weight});
        to[end].push_back({start,weight});
    }
    else {
        for (it = from[end].begin(); it!=from[end].end(); it++){
            if (it->next == start) { 
                it->weight = (weight<it->weight)?weight:it->weight;
                break;
            }
        } 
    }
    return true;
}

#endif //SHORTESTP2P_HPP