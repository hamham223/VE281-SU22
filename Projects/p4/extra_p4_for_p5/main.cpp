#include "shortestP2P.hpp"

using namespace std;

int main () {
	ShortestP2P a;
	int vertex_number = 4;
	vector<vector<int> *> edges;
	vector<int> * e1=new vector<int>{0,1,5};
	vector<int> * e2=new vector<int>{1,2,1};
	vector<int> * e3=new vector<int>{2,3,4};
	vector<int> * e4=new vector<int>{3,1,6};
	edges.push_back(e1); edges.push_back(e2); edges.push_back(e3); edges.push_back(e4);
	//a.readGraph();
	a.setGraph(vertex_number,&edges);
	int A, B;

	cin >> A;
	do {
		cin >> B;
		vector<int> * path;
		path = a.distance(A, B);
		for (auto it= path->begin(); it < path->end(); it++){
			cout << *it << " ";
		}
		cout << endl;
		cin >> A;
	} while (A >= 0);
	delete e1; delete e2; delete e3; delete e4;

	return 0;
}
