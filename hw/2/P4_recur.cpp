#include <bits/stdc++.h>

using namespace std;

#define MOD_ADD(a, b) (a >= M - b ?a - M + b :a + b)

int solve(vector<vector<vector<int>>> &dp, int i, int b, int k, int M){
    if(i == 1)
        return k + 1;
    if(k == 0)
        return 1;
    if(dp[i][b][k] != 0)
        return dp[i][b][k];
    int res = 0;
    for(int j = 0; j <= k; j++){
        int d = b > j ?b - j :0;
        res = MOD_ADD(res, solve(dp, i - 1, j, k - d, M));
    }
    return dp[i][b][k] = res;
}

int main(){
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int N, K, M;
    cin >> N >> K >> M;

    vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(K+1, vector<int>(K+1, 0)));
    // dp[n][b][k]: 長度為 n，可以使用 k 次操作，在前一個元素為 b 時的解
    // 所求為 dp[N][0][K]

    // 狀態轉移：
    // (1) dp[1][b][k] = k + 1
    // (2) dp[n][b][k] = sum(  )

    cout << solve(dp, N, 0, K, M);   
}
