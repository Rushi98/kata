// https://leetcode.com/submissions/detail/506652991/
class Solution {
    bool doesAlexPlayFirst(int n, int i, int j) {
        return (n - (j - i + 1)) % 2 == 0;
    }
    int differenceIfRemoveLeft(const vector<vector<int>> &dp, int i, int j, const vector<int> &piles) {
        int n = dp.size();
        if (doesAlexPlayFirst(n, i, j)) return piles[i] + dp[i + 1][j];
        else return -piles[j] + dp[i][j - 1];
    }
    int differenceIfRemoveRight(const vector<vector<int>> &dp, int i, int j, const vector<int> &piles) {
        int n = dp.size();
        if (doesAlexPlayFirst(n, i, j)) return piles[j] + dp[i][j - 1];
        else return -piles[j] + dp[i][j - 1];
    }
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        
        // dp[i][j] : (Alex's score - Lee's score) for stones [i...j]
        // Note: It's Alex's first turn if (n - len([i...j])) is even
        //       else it's Lee's first turn.
        vector<vector<int>> dp(n, vector<int>(n));
        
        // base case
        // dp[i][i]
        //     if Alex plays first: piles[i]
        //     else: -piles[i]
        for (int i = 0; i < n; i++) {
            if (doesAlexPlayFirst(n, i, i)) dp[i][i] = piles[i];
            else dp[i][i] = -piles[i];
        }
        
        // bottom up
        // dp[i][j]
        //     if Alex plays first: max(difference if left is removed, difference if right is removed)
        //     else: min(difference if left is removed, difference if right is removed)
        for (int l = 2; l <= n; l++) {
            for (int i = 0; i + l <= n; i++) {
                int j = i + l - 1;
                int leftRemovalDifference = differenceIfRemoveLeft(dp, i, j, piles);
                int rightRemovalDifference = differenceIfRemoveRight(dp, i, j, piles);
                if (doesAlexPlayFirst(n, i, j)) dp[i][j] = max(leftRemovalDifference, rightRemovalDifference);
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
        return dp[0][n - 1] > 0;
    }
};
