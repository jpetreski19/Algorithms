/**
 *  A solution to the problem:
 *  Given a sting with lower case alphabet letters (maximum size = 200k). Find the minimum number of swaps
 *  to convert the string to palindrome (if possible).
 *  If the string cannot be converted, return -1.
 *
 *  Required time complexity: O(N).
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <climits>
#include <cmath>
#include <map>
 
#define pb push_back
#define mp make_pair
 
#define endl "\n"
#define all(v) (v).begin(), (v).end()
 
using namespace std;
const int MAX_SIZE = 200005;
 
int length;
string input;       // Input string
string palindrome;  // The palindrome 
 
int result;             // Minimum number of swaps
map<int, int> letter;   // letter[a] = number of letters a
 
int part[MAX_SIZE];         // Holds the indes of the char at position i
int frequency[MAX_SIZE];    // Number of chars in the string of type i


/** 
 *  Check whether the string can be converted to palindrome.
 *  That is even number of all the characters.
 */
bool can_convert(string s) {
 
    // Count the number of appearences of each letter
    for (int i = 0; i < (int)s.length(); i++) {
        letter[(int)(s[i] - 'a')]++;
    }
 
    // If the length is even number, there should be even
    // number of letters for every letter type
    if ((int)s.length() % 2 == 0) {
        for (int i = 0; i < 26; i++) {
 
            // Letter that appears odd number of times,
            // so this string cannot be converted
            if (letter[i] % 2 == 1) {
                return false;
            }
        }

        return true;
    }
 
    // In case our string's length is an odd number,
    // There should be exactly one letter that appears odd number of times
    else {
        bool odd_found = false;
        for (int i = 0; i < 26; i++) {
 
            // If a letter that appears odd number of times is encountered
            if (letter[i] % 2 == 1) {
 
                // This happens for the first time, so it is fine
                if (odd_found == false) {
                    odd_found = true;
                    continue;
                }
 
                // We have multiple letters that appear odd number of times
                // so this string cannot be converted into palindrome
                else {
                    return false;
                }
            }
        }

        return true;
    }
}


/**
 *  Return the number of swaps needed to convert the 
 *  right part of the strng into the reversed left part.
 */
int count_swaps(string s1, string s2) {
 
    // A two pointer algorithm to transform s1 into s2
    // by only swapping two adjacent characters
    int num_swaps = 0;
    int i = 0, j = 0;   // Two pointers
 
    while (i < (int)s1.size()) {
        j = i;
 
        // Go until char s2[i] is not found in s1
        while (s1[j] != s2[i]) {
            j++;
        }
 
        // Swap all the chars in between
        while (i < j) {
 
            // Swap two adjacent characters
            swap(s1[j], s1[j - 1]);
            j--;
            num_swaps++;    // Update result
        }

        i++;
    }

    return num_swaps;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    // Input
    cin >> length >> input;
 
    // First, we should separate the letters that should belong to
    // the left and the right part of the string. This can be simply done
    // by keeping track of how many letters we have encountered so far.
    // We store the index of the part the ith letter belongs to in the
    // array part (part[a] = index of the part of the string letter a belongs to).
    // If the length is even number, we have 2 part. Otherwise, there are 3 (for the
    // middle letter). Then we calculate the number of swaps needed to transfer each
    // letter to the part it belongs to. For that, we simply iterate through the
    // part array and increment the result if we have encountered an element whose
    // part index is greater than the current. Once that is done, we can calculate
    // the number of swaps needed to transform the right part of the string into
    // the reversed left part.
 
    if (can_convert(input)) {
 
        // If we have even length, we have no middle letter
        if (length % 2 == 0) {
            for (int i = 0; i < length; i++) {
                int c = (int)(input[i] - 'a');
                frequency[c]++;
 
                // Check the number of times we have encountered letter c
                if (frequency[c] <= letter[c] / 2) {
                    part[i] = 1;
                } else {
                    part[i] = 3;
                }
            }
 
            // Iterate through the part array and calculate the
            // number of swaps needed to transfer each element into
            // the right part
            for (int i = 1; i <= 3; i++) {
 
                // We do not have middle part if our string's length is even number
                if (i == 2) {
                    continue;
                }
                int greater = 0;    // Number of elements that should
                                    // go to the right
                for (int j = 0; j < length; j++) {
 
                    // Another element in a different part discovered
                    if (part[j] > i) {
                        greater++;
                    }
 
                    // Update the result and the output string
                    if (part[j] == i) {
                        result += greater;
                        palindrome += input[j];
                    }
                }
            }
 
            string inverted_left = "";
            string right_part = "";
 
            // Get the inverted left part and the right part
            for (int i = length / 2 - 1, j = length / 2; i >= 0 and j < length; i--, j++) {
                inverted_left += palindrome[i];
                right_part += palindrome[j];
            }
 
            result += count_swaps(right_part, inverted_left);
        }
 
        // Length is odd number, we have middle part
        else {
            for (int i = 0; i < length; i++) {
                int c = (int)(input[i] - 'a');
                frequency[c]++;
 
                // If this is not the letter that appears odd number
                // of times, do the normal procedure
                if (letter[c] % 2 == 0) {
                    if (frequency[c] <= letter[c] / 2) {
                        part[i] = 1;
                    } else {
                        part[i] = 3;
                    }
                } 
 
                // Otherwise, check whether we are at that particular letter
                // and assign the part index to 2
                else {
                    if (frequency[c] == (letter[c] / 2) + 1) {  // The middle letter
                        part[i] = 2;
                    } else {
                        if (frequency[c] <= letter[c] / 2) { // The rest of the letters
                            part[i] = 1;
                        } else {
                            part[i] = 3;
                        }
                    }
                }
            }
 
            // Iterate and update the result the same way as previously
            // but this time include the middle part in the search
            for (int i = 1; i <= 3; i++) {
                int greater = 0;
                for (int j = 0; j < length; j++) {
                    if (part[j] > i) {       // Element that should be on the right
                        greater++;
                    }
                    if (part[j] == i) {     // Update result
                        result += greater;
                        palindrome += input[j];
                    }
                }
            }
 
            string inverted_left = "";
            string right_part = "";
 
            // Get the left and right part
            for (int i = length / 2 - 1, j = length / 2 + 1; i >= 0 and j < length; i--, j++) {
                inverted_left += palindrome[i];
                right_part += palindrome[j];
            }
 
            result += count_swaps(right_part, inverted_left);
        }
 
        // Print the result
        cout << result << endl;
    } 
 
    // A palindrome cannot be constructed
    else {
        cout << "-1" << endl;
    }
    return 0;
}