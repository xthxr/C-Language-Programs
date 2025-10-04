#include <stdio.h>
#include <string.h>

int dp[1005][3][2]; // assuming max prices length <= 1000

int solve(int prices[], int n, int k, int idx, int holding) {
    if (idx == n) return 0;
    if (k == 0) return 0;

    if (dp[idx][k][holding] != -1)
        return dp[idx][k][holding];

    int transaction, np_transact;

    if (holding == 1) {
        // Sell
        transaction = prices[idx] + solve(prices, n, k - 1, idx + 1, 0);
    } else {
        // Buy
        transaction = -prices[idx] + solve(prices, n, k, idx + 1, 1);
    }

    np_transact = solve(prices, n, k, idx + 1, holding);

    dp[idx][k][holding] = (transaction > np_transact) ? transaction : np_transact;
    return dp[idx][k][holding];
}

int maxProfit(int prices[], int n) {
    memset(dp, -1, sizeof(dp));
    return solve(prices, n, 2, 0, 0);
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    printf("Max Profit: %d\n", maxProfit(prices, n));
    return 0;
}
