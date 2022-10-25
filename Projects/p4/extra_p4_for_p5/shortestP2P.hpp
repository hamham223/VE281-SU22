#include<iostream>
#include<list>
#include<vector>
#include<climits>

#define INF INT_MAX
#define MYINF 715827882

inline int MIN(int a, int b) {return (a<b)?a:b;}
using namespace std;
typedef struct _Node
{
    int to;
    int weight;
}node;

class ShortestP2P {
public:
    ShortestP2P() {}

    /**
     * read the graph from a vector, the graph is connected and you don't need to consider negative edges.
     *
     * @param vertex_number: the number of vertices in the graph
     * @param edges: a vector representing the edges in the undirected graph,
     *               each element of it is a vector containing three integers,
     *               the first two integers are the two vertices of an edge,
     *               the third integer is the length of the edge
     */
    void setGraph(int vertex_number, vector<vector<int> *> *edges) {
        //TODO: implement this function
        size = (unsigned) vertex_number;
        
        int start = 0; int end = 0; int weight = 0;
        a.resize((unsigned)vertex_number);
        for (auto it = edges->begin(); it < edges->end(); it++){
            start = (*(*it))[0]; end = (*(*it))[1]; weight = (*(*it))[2];
            a[(unsigned)start].push_back({end,weight});
            a[(unsigned)end].push_back({start,weight});
        }

    }

    /**
     * input: two vertices A and B
     * @param A
     * @param B
     * @return a vector, which contains all the vertices in the shortest path (including A and B)
     */
    vector<int> *distance(unsigned int A, unsigned int B) {
        spfa(A);
        A2B_path.clear();
        int cur = B;
        while (cur !=-1 ){
            A2B_path.push_back(cur);
            cur = path[(unsigned)cur];
        }
        return &A2B_path;
    };


private:
    // internal data and functions.
    
    unsigned int size = 0;
    vector<list<node>> a; // adjacent list
    vector<int> d; // distance
    list<unsigned int> q;//queue
    vector<int> cnt;//number of times of inque
    vector<bool> exist;//if in queue
    vector<int> path; 
    vector<int> A2B_path;
    bool spfa(unsigned int begin); // false if invalidness detected
};

bool ShortestP2P::spfa(unsigned int begin){
    d.assign(a.size(),MYINF);
    q.assign(1,begin);//queue
    cnt.assign(a.size(),0);//number of times of inque
    exist.assign(a.size(),false);//if in queue
    path.assign(a.size(),-1); // -1 means unknown
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
                path[i->to] = first;
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