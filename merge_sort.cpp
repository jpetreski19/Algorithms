#include <iostream>
#include <algorithm>
  
typedef long long ll;
using namespace std;
const int MAX_SIZE = 100005;
  
void merge(int arr[], int temp[], int left, int middle, int right) {  
  int i = left;
  int j = middle;
  int k = left;
  
  while (i < middle and j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k] = arr[i++];
    } else {
      temp[k] = arr[j++];
    }
    k++;
  }
  while (i < middle) {
    temp[k++] = arr[i++];
  }
  while (j <= right) {
    temp[k++] = arr[j++];
  }
  for (i = left; i <= right; i++) {
    arr[i] = temp[i];
  }
}
  
void mergeSort(int arr[], int temp[], int left, int right) {
  int middle;
  
  if (left < right) {
    middle = left + (right - left) / 2;
    mergeSort(arr, temp, left, middle);
    mergeSort(arr, temp, middle + 1, right);
    merge(arr, temp, left, middle + 1, right);
  }
}
  
int main() {
  ios::sync_with_stdio(false);
  
  int n;
  cin >> n;
 
  int arr[n + 5];
  int temp[n + 5];
 
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  mergeSort(arr, temp, 0, n - 1);
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}