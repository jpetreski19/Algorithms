/**
 *	Solution of a task using segment tree.
 *
 *	The task:
 *	Given an array of N (1 <= N <= 100 000) of K distinct integers (1 <= K <= 50).
 *	M (1 <= M <= 100 000) queries need to be performed of type:
 *		1. 1 x y - update element at position x to value y.
 *		2. 2	 - return the length of the smallest window that contains 
 *				   all distinct integers at least once.
 */

#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <utility>

using namespace std;

int N;	// Array size
int K;	// Distinct numbers in the array
int M;	// Number of queries


class Node {
private:
	int leftmost;
	int rightmost;
	int result;

	Node* right_child;
	Node* left_child;

	int min_pos[52];	// Leftmost positions of each element type
	int max_pos[52];	// Rightmost positions of each element type

	// min_pos[a] - index of the leftmost element of type a in this range
	// max_pos[b] - index of the rightmost element of type b in this range


	/**
	 *	Calculates result and the min_pos and max_pos arrays for the current node
	 *	based on the min_pos of the left child and max_pos of right child.
	 *
	 *	The shortest segment we are looking for is either 
	 *	completely within the range of one of the two children
	 *	(left and right), or it spreads accross the ranges covered
	 *	by both of them.
	 *	In the latter case, the rightmost elements of each type
	 *	in the range of the left child and the leftmost elements 
	 *	of each type in the range of the right child should be considered.
	 *	Once this array is computed, it is sorted and two pointers
	 *	is applied to find smallest window containing all element types.
	 */
	void recalc() {
		result = min(left_child->result, right_child->result);

		if (result == K) {
			/* 
			 *	Result in one of the children is already smallest possible,
			 *	so there is no point calculating the "middle" result 
			 *	because it won't be any better.
			 */

			for (int i = 1; i <= K; i++) {
				min_pos[i] = min(left_child->min_pos[i], right_child->min_pos[i]);
				max_pos[i] = max(left_child->max_pos[i], right_child->max_pos[i]);
			}

			return;
		}
		// There is room for improvement otherwise


		vector<pair<int, int> > inner;	// Holds the leftmost and rightmost
										// positions of each element type
										// in this range (first = pos, second = type).

		for (int i = 1; i <= K; i++) {
			// Build the case where the shortest segment is accross both children

			if (left_child->max_pos[i] != -1) {
				inner.push_back(make_pair(left_child->max_pos[i], i));
			}
			if (right_child->min_pos[i] != INT_MAX) {
				inner.push_back(make_pair(right_child->min_pos[i], i));
			}

			/* 
			 *	The leftmost positions of each element type are in the left subtree
			 *	(and some in the right, which are not present at all in the left).
			 *	Converesely, rightmost positions are in the right subtree.
			 */
			min_pos[i] = min(left_child->min_pos[i], right_child->min_pos[i]);
			max_pos[i] = max(left_child->max_pos[i], right_child->max_pos[i]);
		}


		
		sort(inner.begin(), inner.end());	// Sort the elements by their position 
											// in the array (first element in pair).

		vector<int> count(K + 1, 0);		// count[x] - holds the number of times element
											// of type x is contained in the window so far.

						// i - right pointer
		int j = 0;		// Left pointer
		int found = 0;

		// Two pointers:
		for (int i = 0; i < (int)inner.size(); i++) {
			if (count[inner[i].second] == 0) {
				found++;	// Just found element of this type
			}
			count[inner[i].second]++;

			if (found == K) {
				/* 
				 *	Desirable window found - trying to minimize it.
				 *	While there is still at least 1 element
				 *	of each type, remove the leftmost (pointed by j).
				 */
				while (count[inner[j].second] > 1 and j < i) {
					count[inner[j].second]--;
					j++;
				}
				result = min(result, inner[i].first - inner[j].first + 1);

				if (result == K) {
					// Can't get better than this
					return;
				}
			}
		}
	}


public:
	/**
	 *	Constructor - builds the segment tree.
	 */
	Node (int left, int right, int array[]) {
		leftmost = left;
		rightmost = right;
		result = INT_MAX;

		if (left == right) {
			// Leaf node

			left_child = nullptr;
			right_child = nullptr;

			for (int i = 1; i <= K; i++) {
				min_pos[i] = INT_MAX;
				max_pos[i] = -1;
			}
			
			// Only one position covered in this range
			min_pos[array[left]] = left;
			max_pos[array[left]] = left;
		} else {
			// Internal node

			int mid = left + (right - left) / 2;	// Avoids overflow
			left_child = new Node(left, mid, array);
			right_child = new Node(mid + 1, right, array);

			recalc();
		}
	}


	/**
	 *	Updates a single point in the array.
	 */
	void update(int index, int new_val, int array[]) {
		if (leftmost == rightmost) {
			// Reset values - needed to recalculate
			min_pos[array[index]] = INT_MAX;
			max_pos[array[index]] = -1;
			
			array[index] = new_val; // Array should be updated too
									// (needed for updates in the future)

			// Set new values
			min_pos[new_val] = index;
			max_pos[new_val] = index;

			return;
		}

		if (index <= left_child->rightmost) {
			left_child->update(index, new_val, array);
		} else {
			right_child->update(index, new_val, array);
		}

		recalc();
	}


	// ==================== Helper functions =========================


	static int min(int a, int b) {
		return (a < b) ? a : b;
	}

	static int max(int a, int b) {
		return (a > b) ? a : b;
	}

	int get_result(Node* x) {
		return (x == nullptr) ? INT_MAX : x->result;
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	// Input
	cin >> N >> K >> M;

	int array[N + 5];
	for (int i = 0; i < N; i++) {
		cin >> array[i];
	}

	/*
	 *	Creates an instance of the root of the segment tree
	 *	and builds the rest of the tree recursively.
	 */
	Node* root = new Node(0, N - 1, array);


	// Queries
	int q_type, x, y;	// Query description
	for (int i = 0; i < M; i++) {
		/*
		 *	2 types of queries:
		 *	1 x y - update the element at position x to have the value y.
		 *	2 	  - perform a query on the whole array.
		 */

		cin >> q_type;
		if (q_type == 1) {
			cin >> x >> y;

			if (array[x - 1] == y) {
				continue;
			}
			if (x < 0 or x > N) {
				cout << "Invalid index." << endl;
				continue;
			}

			root->update(x - 1, y, array);
		} else if (q_type == 2) {
			int res = root->get_result(root);

			if (res == INT_MAX) {
				cout << "-1" << endl;
			} else {
				cout << res << endl;
			}
		} else {
			cout << "Invalid query type." << endl;
		}
	}

	return 0;
}