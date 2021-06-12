class Solution {
    bool doesAlicePlayFirst(int n, int i, int j) {
        return (n - (j - i + 1)) % 2 == 0;
    }
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
    int differenceIfRemoveLeft(const vector<vector<int>> &dp, int i, int j, const vector<int> &cumulativeArray) {
        int n = dp.size();
        if (doesAlicePlayFirst(n, i, j)) return sumSubarray(cumulativeArray, i + 1, j) + dp[i + 1][j];
        else return -sumSubarray(cumulativeArray, i + 1, j) + dp[i + 1][j];
    }
    int differenceIfRemoveRight(const vector<vector<int>> &dp, int i, int j, const vector<int> &cumulativeArray) {
        int n = dp.size();
        if (doesAlicePlayFirst(n, i, j)) return sumSubarray(cumulativeArray, i, j - 1) + dp[i][j - 1];
        else return -sumSubarray(cumulativeArray, i, j - 1) + dp[i][j - 1];
    }
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<int> cumulativeArray = computeCumulativeArray(stones);
        bool bobPlaysOdd = (n % 2 == 1);
        
        // dp[i][j] : alice's score - bob's score for stones [i...j]
        // Note: It's alice's first turn if (n - len([i...j])) is even
        //       else if's bob's first turn.
        vector<vector<int>> dp(n, vector<int>(n));
        
        // base case
        // dp[i][i] = 0
        for (int i = 0; i < n; i++) {
            dp[i][i] = 0;
        }
        
        // bottom up
        // dp[i][j]
        //     if Alice plays first: max(difference if left is removed, difference if right is removed)
        //     else: min(difference if left is removed, difference if right is removed)
        for (int l = 2; l <= n; l++) {
            for (int i = 0; i + l <= n; i++) {
                int j = i + l - 1;
                int leftRemovalDifference = differenceIfRemoveLeft(dp, i, j, cumulativeArray);
                int rightRemovalDifference = differenceIfRemoveRight(dp, i, j, cumulativeArray);
                if (doesAlicePlayFirst(n, i, j)) dp[i][j] = max(leftRemovalDifference, rightRemovalDifference);
                else dp[i][j] = min(leftRemovalDifference, rightRemovalDifference);
            }
        }
        /*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i > j) cout << "\t";
                else cout << dp[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
        */
        return dp[0][n - 1];
    }
};
