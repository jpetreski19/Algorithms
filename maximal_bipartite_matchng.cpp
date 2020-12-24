/**
 *  A solution to a problem from national competition that involves
 *  maximal bipartite matching.
 */

#include <bits/stdc++.h>
 
typedef long long ll;
using namespace std;
const int max_size = 150;
 
ll N, len[max_size + 1], match[max_size + 1];
bool adj[max_size + 1][max_size + 1];
bool vis[max_size + 1];
 
// ===================== Maximal bipartite matching =========================== //
 
// Ford-Fulkerson max flow algorithm implementation
// Time complexity : O (V x E)
 
inline bool bpm(ll u) {
    // DFS based function that tries all
    // possibilities to match the current item
 
    for (ll v = 0; v < N; v++) {
        // Check if there is an edge between u and v and if v is matched
        if (!adj[u][v] or vis[v]) {
            continue;
        }
        vis[v] = true;
 
        // If "v" has not been previously matched OR previously
        // matched vertex has an alternate matching vertex available
        if (match[v] < 0 or bpm(match[v])) {
            // Update "v"'s partner
            match[v] = u;
            return true;
        }
    }
 
    return false;
}
 
inline ll max_bpm() {
    // Returns the maximum number of pairings
 
    // Initialize as unmatched ( -1 ).
    fill(match, match + N + 1, -1);
    ll res = 0;
 
    for (ll i = 0; i < N; i++) {
        // Initialize as unvisited
        fill(vis, vis + N + 1, false);
 
        if (bpm(i)) {
            res++;
        }
    }
 
    return res;
}
 
// ================================ Task ===================================== //
 
inline bool possible(ll X, ll Y) {
    // Check if right triangle can be formed
    ll res = (X * X) + (Y * Y);
 
    if (sqrt(res) == round(sqrt(res))) {
        return true;
    } else {
        return false;
    }
}
 
inline bool GCD(ll X, ll Y) {
    // Check if the greatest common divisor is 1
    // i.e. there is no common divisor
 
    if (Y > X) {
        swap(X, Y);
    }
 
    if (X % Y == 0) {
        return false;
    }
    else if (X % Y == 1) {
        return true;
    } else {
        GCD(Y, X % Y);
    }
}
 
inline void create_graph() {
    // Check if the lengths satisfy the given conditions
    // If true, then add an edge between them
 
    for (ll i = 0; i < N - 1; i++) {
        // Avoid overlapping; the cases with the previous elements have already been checked
        for (ll j = i + 1; j < N; j++) {
            // If the length is the same, then skip the iteration
            if (len[i] == len[j]) {
                continue;
            }
 
            if (GCD(len[i], len[j]) and possible(len[i], len[j])) {
                adj[i][j] = true; // Add edge
                adj[j][i] = true; // Add edge
            }
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false); // Optimize input
    cin.tie(0); cout.tie(0); // Optimize input and output
 
    // Input
    cin >> N;
    for (ll i = 0; i < N; i++) {
        cin >> len[i];
    }
 
    // Create an adjacency matrix -> 1 means an edge exists
    create_graph();
 
    // Compute output
    cout << max_bpm() << endl;
    return 0;
}