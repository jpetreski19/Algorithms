#include <algorithm>
#include <iostream>

#define endl "\n"

using namespace std;

int n;
int A[100];

void print_array() {
	for (int i = 0; i < n; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

int main() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}

	cout << "----------------------------" << endl;

	int current = 0;
	for (int i = 1; i < n; i++) {
		current = A[i];
		int j = i - 1;

		while ( (j >= 0) and (A[j] > current) ) {
			A[j + 1] = A[j];
			j--;
		}

		A[j + 1] = current;
		print_array();
	}

	return 0;
}