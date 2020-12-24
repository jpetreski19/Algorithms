#include <iostream>
#include <algorithm>

#define endl "\n"

using namespace std;

int partition(int arr[], int low, int high) {

	int pivot = arr[high];	// Set pivot to be the rightmost element
	int smaller_id = (low - 1);	// Index of smaller element

	for (int i = low; i < high; i++) {
		if (arr[i] < pivot) {
			smaller_id++;
			swap(arr[i], arr[smaller_id]);
		}
	}

	// The correct position of the pivot is smaller_id + 1
	swap(arr[smaller_id + 1], arr[high]);
	return smaller_id + 1;
}

void quick_sort(int arr[], int low, int high) {
	if (low < high) {

		int pivot_id = partition(arr, low, high);

		quick_sort(arr, low, pivot_id - 1);
		quick_sort(arr, pivot_id + 1, high);
	}
}

int main() {
	ios::sync_with_stdio(false);

	int size;
	cin >> size;

	int arr[size + 1];
	for (int i = 0; i < size; i++) {
		cin >> arr[i];
	}

	quick_sort(arr, 0, size - 1);

	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}