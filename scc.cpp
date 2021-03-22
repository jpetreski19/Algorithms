/**
 *  Implementation of Kosaraju's algorithm for finding
 *  all strongly connected components of a graph.
 *  
 *  Time complexity: O(V + E)
 *    V - number of vertices
 *    E - number of edges
 *
 *  22/03/2021 - Jovan Petreski
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:

  int num_nodes;                  // Number of vertices

  vector<bool> visited;           // Used to perform DFS traversal.
                                  // visited[i] = true if i has been visited/discovered.

  vector<vector<int>> neighbour;  // The graph (adjacency list representation).

  vector<vector<int>> reversed;   // The reversed graph (all edges are flipped).

  stack<int> stack_t;             // Used to keep order of visited vertices
                                  // when traversing the graph.

  /**
   *  Traverses the graph and gets order of visited
   *  vertices in a stack. The vertex from which
   *  the algorithm starts is the front of the stack.
   *
   *  Param: curr - the index of the current node being explored.
   */
  void get_order(int curr);

  /**
   *  Performs a simple DFS traversal over the
   *  reversed graph (directions of edges in the
   *  initial graph are flipped).
   *
   *  Param: curr - the index of the current node being explored.
   */
  void dfs(int curr);

public:

  /**
   *  Initialises vector sizes and sets
   *  all entries to false for visited.
   */
  Graph(int num_nodes);

  /**
   *  Helper method - adds an edge between
   *  nodes x and y.
   */
  void add_edge(int x, int y);

  /**
   *  Returns the number of strongly connected components
   *  of tha graph. A SCC is a subset V' of the set of vertices V,
   *  such that there is a path between each pair of nodes.
   */
  int get_num_scc();

  /**
   *  A method that checks if all vertices in the graph
   *  form a SCC.
   *  Returns if the number of SCC is 1. False otherwise.
   */
  bool all_pairs_reachable();

};


/**
 *  Driver program to test above class.
 */
int main() {
  ios::sync_with_stdio(false);

  int nodes, edges;
  cin >> nodes >> edges;
  Graph g(nodes);

  int x, y;
  for (int i = 0; i < edges; i++) {
    cin >> x >> y;
    g.add_edge(x, y);
  }

  cout << g.all_pairs_reachable() << endl;

  return 0;
}



/** 
 *  Class methods implementations: 
 */

Graph::Graph(int num_nodes) {
  this->num_nodes = num_nodes;
  neighbour.resize(num_nodes);
  reversed.resize(num_nodes);
  visited.resize(num_nodes, false);
}

void Graph::add_edge(int x, int y) {
  neighbour[x].push_back(y);
  reversed[y].push_back(x);   // Flipped direction
}

void Graph::get_order(int curr) {
  visited[curr] = true;

  for (int i = 0; i < (int)neighbour[curr].size(); i++) {
    int next = neighbour[curr][i];
    if (!visited[next]) {
      get_order(next);
    }
  }

  stack_t.push(curr); // Get order by adding the nodes explored
                      // earlier later to the stack.
}

void Graph::dfs(int curr) {
  visited[curr] = true;

  for (int i = 0; i < (int)reversed[curr].size(); i++) {
    int next = reversed[curr][i];
    if (!visited[next]) {
      dfs(next);
    }
  }
}

int Graph::get_num_scc() {
  for (int i = 0; i < num_nodes; i++) {
    if (!visited[i]) {
      // New graph component (graph is a forest)
      get_order(i);
    }
  }

  // Reset entries of visited
  fill(visited.begin(), visited.end(), false);
  int num_scc = 0;

  while (!stack_t.empty()) {
    int curr = stack_t.top();
    stack_t.pop();

    if (!visited[curr]) {
      // New scc
      num_scc++;
      dfs(curr);
    }
  }

  return num_scc;
}

bool Graph::all_pairs_reachable() {
  return get_num_scc() == 1;
}


