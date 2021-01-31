#include <iostream>

using namespace std;

int max_subarray(int arr[], int size) {
  int starting_idx = 0;
  int ending_idx = 0;

  int max_so_far = 0;
  int max_ending_here = 0;

  for (int i = 0; i < size; i++) {
    /**
     *  2 cases: either the max subarray starts at
     *  index i, or it started before and element at 
     *  position i is just another element being part of it.
     */

    if (arr[i] > max_ending_here + arr[i]) {
      // Case 1
      // The subarray up to this point contains negative numbers

      max_ending_here = arr[i];
      starting_idx = i;

    } else {
      // Case 2
      max_ending_here += arr[i];
    }

    if (max_so_far < max_ending_here) {
      // Update result so far

      max_so_far = max_ending_here;
      ending_idx = i;
    }
  }

  return max_so_far;
}

int main() {
  int n;
  cin >> n;

  int arr[n + 1];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  cout << max_subarray(arr, n) << endl;
  return 0;
}