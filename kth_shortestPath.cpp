#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

#define pb push_back
#define endl '\n'

using namespace std;
const int MAX_SIZE = 3005;
const int K = 5;


/** In this implementation of the shortest path
 *	with cost <= K, I search for the path only up
 *	to the 5th shortest one, just to experiment.
 *	To make the solution more general, one could 
 *	first check if a path with cost <= K exists, 
 *	and then update the index of the shotest path
 *	that is supposed to be the last one. This would
 *	however increase the time complexity.
 */

struct edge {
	int neightbour;
	int dist, cost;

	edge() {}

	edge(int neightbour, int dist, int cost) {
		this -> neightbour = neightbour;
		this -> dist = dist;
		this -> cost = cost;
	}
};

struct node {
	int x;
	int dist, cost;

	node() {}

	node(int x, int dist, int cost) {
		this -> x = x;
		this -> dist = dist;
		this -> cost = cost;
	}

	/**	Sort the edges increasingly.
	 */
	bool operator <(const node &a) const {
		return dist > a.dist;
	}
};


vector<edge> adj[MAX_SIZE];
priority_queue<node> Q;

/** dist[i][j] - length of the jth shortest path to i
 * 	cost[i][j] - cost of the jth shortest path to i
 */
vector<int> dist[MAX_SIZE];
vector<int> cost[MAX_SIZE];


int solve(int nodes, int edges, int budget) {

	node curr;
	Q.push(node(0, 0, 0));

	while (!Q.empty()) {
		curr = Q.top();
		Q.pop();

		if (curr.cost > budget)
			continue;
        if (dist[curr.x].size() >= K)
            continue;

		dist[curr.x].pb(curr.dist);
		cost[curr.x].pb(curr.cost);

		for (int i = 0; i < (int)adj[curr.x].size(); i++) {

			if (curr.cost + adj[curr.x][i].cost > budget)
				continue;
			if (dist[adj[curr.x][i].neightbour].size() == K) 
                continue;

			Q.push(node(adj[curr.x][i].neightbour, 
					curr.dist + adj[curr.x][i].dist,
					curr.cost + adj[curr.x][i].cost));
		}
	}

	int res = INT_MAX;
	for (int i = 0; i < (int)dist[nodes - 1].size(); i++) {
		if (cost[nodes - 1][i] <= budget) {
            res = min(res, dist[nodes - 1][i]);
        }
	}

	// No path with cost <= K found
	if (res == INT_MAX)
		res = -1;
	return res;
}


int main() {
	ios::sync_with_stdio(false);

	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int nodes, edges, budget;
	cin >> budget >> nodes >> edges;

	for (int i = 0; i < edges; i++) {

		/**	u - from
		 *	v - to
		 *	d - distance (or time)
		 *	c - cost
		 */
		int u, v, d, c;
		cin >> u >> v >> d >> c;

		// 0-based indexing
		u--;
		v--;

		adj[u].pb(edge(v, d, c));
		adj[v].pb(edge(u, d, c));
	}

	cout << solve(nodes, edges, budget) << endl;
	return 0;
}