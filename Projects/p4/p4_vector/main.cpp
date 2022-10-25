#include "shortestP2P.hpp"

using namespace std;

int main () {
	ShortestP2P a;
	a.readGraph();

	int A, B;

	cin >> A;
	do {
		cin >> B;
		a.distance(A, B);
		cin >> A;
	} while (A >= 0);
	return 0;
}
