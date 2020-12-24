#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <utility>
#include <vector>
#include <map>
 
typedef long long ll;
using namespace std;
const int MAX_SIZE = 1e5 + 5;
 
int num_elements;
ll element[MAX_SIZE];
ll pref_sum[MAX_SIZE];
 
ll solve(void) {
    map<ll, ll> prev_sum;
    ll result = 0;
    ll sum = 0;
 
    for (int i = 0; i < num_elements; i++) {
        sum += element[i];
        
        if (sum == 0) {
            result++;
        }
        if (prev_sum.find(sum) != prev_sum.end()) {
            result += prev_sum[sum];
            cout << "In if" << endl;
        }
        prev_sum[sum]++;

        cout << sum << " " << result << endl;
    }
    return result;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    cin >> num_elements;
    for (int i = 0; i < num_elements; i++) {
        cin >> element[i];
    }
    cout << solve() << endl;
    return 0;
}