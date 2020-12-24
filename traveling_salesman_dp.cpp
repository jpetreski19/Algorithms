#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
const int max_size = 10;
const int max_set = (1 << 10);
const int source = 0; // Here the starting point is set to be always 0

int shops; // Number of shops to visit
int shortest_route = INT_MAX; // Length of the shortest route
int last_position;

int dist[max_size + 1][max_size + 1];
// distance[a][b] = shortest path from a to be or vice versa (the roads are bidirectional)

int result[max_set][max_size + 1];
// result[a][b] = the shortest route to visit shop indexed b with previously visited shops indexed exactly the same as the bits turned on in a
// E.g. if a = 1100010 and b = 4, result[a][b] = shortes route to visit the 4th shop after visiting 1st, 2nd and 6th shop

int previous[max_set][max_size + 1];
// previous[a] = the index of the previous shop

vector<int> order;


/* =============================================== Solution ============================================================== */


int solve(void)
{
    // Traveling salesman problem - solved in bottom up manner, dynamic programming
    // Time complexity - O(n^2 * 2^n), where n == shops

    for (int i = 1; i < (1 << shops); i++)
    {
        for (int j = 0; j < shops; j++) // j is the index of the shop we are at the moment
        {
            if (result[i][j] == INT_MAX) { // We cannot continue from a shop that has not been previously reached
                continue;
            }

            for (int k = 1; k < shops; k++) {   // k is the index of the next shop we are about to visit
                if ( (i & ( 1 << k )) != 0 ) {   // Check if we have computed same set
                    continue;
                }

                int new_pattern = ( i | ( 1 << k ) );
                // Add the new vertex in the bit set if we haven't checked before (the index of the lately visited city is turned on)

                // Update to current minimum if needed
                if (result[new_pattern][k] > result[i][j] + dist[j][k])
                {
                    result[new_pattern][k] = result[i][j] + dist[j][k];

                    // Set j as the previous visited shop so later the order can be easily restored
                    previous[new_pattern][k] = j;
                }
            }
        }
    }

    // Get the result
    for (int i = 1; i < shops; i++)
    {
        // Since we have computed the shortest route till every point with all the
        // vertices included in the bit set, search for the shortest distance from
        // any of the ending points to the source

        if (result[ (1 << shops) - 1 ][i] <= 0) {   // Check if a path exists from last end point until the source
            continue;
        }

        // Get minimum
        if (result[ (1 << shops) - 1 ][i] + dist[i][source] < shortest_route)
        {
            shortest_route = result[ (1 << shops) - 1 ][i] + dist[i][source];
            last_position = i;
        }
    }

    return shortest_route;
}


/* ============================================== Backtracking ======================================================= */


void get_order(int current, int pattern)
{
    if (current == 0) {
        return;
    }
    order.push_back(current);

    int new_pattern = ( pattern & ( ~ (1 << current) ) );
    get_order( previous[pattern][current], new_pattern );

    return;
}


/* ============================================== Initialization ====================================================== */


void init(void)
{
    // Initialize

    for (int i = 1; i <= (1 << shops) - 1; i++) {
        for (int j = 0; j <= shops; j++) {
            result[i][j] = INT_MAX;
            previous[i][j] = j;
        }
    }

    result[1][0] = 0; // We start from this point (100000...0, 0)

    return;
}


/* =============================================== Main function ===================================================== */


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    // Input
    cin >> shops;

    // Input
    for (int i = 0; i < shops; i++) {
        for (int j = 0; j < shops; j++) {
            cin >> dist[i][j];
        }
    }

    init();

    // Output
    cout << solve() << endl;

    order.push_back(0);
    get_order( last_position, (1 << shops) - 1);

    order.push_back(0);
    reverse(order.begin(), order.end());

    for (int i = 0; i < (int)order.size(); i++) {
        cout << order[i] << " ";
    }
    return 0;
}