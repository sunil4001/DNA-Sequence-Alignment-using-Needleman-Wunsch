#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Scoring system
const int MATCH = 1;
const int MISMATCH = -1;
const int GAP = -2;

// Function to return match/mismatch score
int getScore(char a, char b) {
    return (a == b) ? MATCH : MISMATCH;
}

int main() {
    string seq1, seq2;

    // Input DNA sequences
    cout << "Enter first DNA sequence: ";
    cin >> seq1;
    cout << "Enter second DNA sequence: ";
    cin >> seq2;

    int m = seq1.length();
    int n = seq2.length();

    // Initialize DP table and direction table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    vector<vector<char>> direction(m + 1, vector<char>(n + 1)); // 'D' = Diagonal, 'U' = Up, 'L' = Left

    // Initialize base cases
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i * GAP;
        direction[i][0] = 'U';
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j * GAP;
        direction[0][j] = 'L';
    }
    direction[0][0] = '0'; // origin

    // Fill the DP and direction matrices
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int scoreDiag = dp[i - 1][j - 1] + getScore(seq1[i - 1], seq2[j - 1]);
            int scoreUp = dp[i - 1][j] + GAP;
            int scoreLeft = dp[i][j - 1] + GAP;

            dp[i][j] = max({scoreDiag, scoreLeft, scoreUp});

            // Set direction for traceback
            if (dp[i][j] == scoreDiag)
                direction[i][j] = 'D';
            else if (dp[i][j] == scoreLeft)
                direction[i][j] = 'L';
            else
                direction[i][j] = 'U';
        }
    }

    // Backtrack to get aligned sequences
    string aligned1 = "", aligned2 = "";
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && direction[i][j] == 'D') {
            aligned1 += seq1[i - 1];
            aligned2 += seq2[j - 1];
            i--;
            j--;
        } else if (j > 0 && direction[i][j] == 'L') {
            aligned1 += '_';
            aligned2 += seq2[j - 1];
            j--;
        } else if (i > 0 && direction[i][j] == 'U') {
            aligned1 += seq1[i - 1];
            aligned2 += '_';
            i--;
        }
    }

    // Since we built the alignment in reverse, reverse it
    reverse(aligned1.begin(), aligned1.end());
    reverse(aligned2.begin(), aligned2.end());

    // Output result
    cout << "\nOptimal Alignment Score: " << dp[m][n] << endl;
    cout << "Aligned Sequence 1: " << aligned1 << endl;
    cout << "Aligned Sequence 2: " << aligned2 << endl;

    return 0;
}
