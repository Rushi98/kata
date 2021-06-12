// https://leetcode.com/submissions/detail/506676661/
class Solution {
    vector<int> computeCumulativeArray(const vector<int> &arr) {
        int n = arr.size();
        vector<int> cumulativeArray(n, arr[0]);
        for (int i = 1; i < n; i++) {
            cumulativeArray[i] = cumulativeArray[i - 1] + arr[i];
        }
        return cumulativeArray;
    }
    int sumSubarray(const vector<int> &cumulativeArray, int i, int j) {
        if (i == 0) return cumulativeArray[j];
        return cumulativeArray[j] - cumulativeArray[i - 1];
    }
    int calculateScore(const vector<vector<int>> &dp, int i, int m, int x, const vector<int> &cumulativeArray) {
        int n = cumulativeArray.size();
        int score = 0;
        // take all stones in first x piles
        score += sumSubarray(cumulativeArray, n - i, n - i + x - 1);
        
        int totalRemaining = sumSubarray(cumulativeArray, n - (i - x), n - 1);
        int newM = max(m, x);
        int newI = i - x;
        int maxM = min(newM, (newI + 1) / 2);
        score += totalRemaining - dp[newI][maxM];
        
        return score;
    }
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> cumulativeArray = computeCumulativeArray(piles);

        // dp[i][j] : maximum score of first player for last i piles and M = j
        // Note: maximum score of second player will be total number of stones - first player's max score
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        
        // bottom up
        for (int i = 1; i <= n; i++) {
            for (int m = n; m > 0; m--) {
                int maxScore = 0;
                if (2 * m >= i) {
                    // trivial case : x = i take all stones
                    dp[i][m] = sumSubarray(cumulativeArray, n - i, n - 1);
                } else {
                    int maxScore = 0;
                    for (int x = 1; x <= 2 * m; x++) {
                        int score = calculateScore(dp, i, m, x, cumulativeArray);
                        maxScore = max(maxScore, score);
                    }
                    dp[i][m] = maxScore;
                }
            }
        }
        
        return dp[n][1];
    }
};
