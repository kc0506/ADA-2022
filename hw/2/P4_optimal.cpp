#include <bits/stdc++.h>

using namespace std;

#define MOD_ADD(a, b) (a >= M - b ? a - M + b : a + b)
#define MOD_MINUS(a, b) (a < b ? a - b + M : a - b)

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N, K, M;
    cin >> N >> K >> M;

    int dp[2][K+1][K+1] = {0};
    int preSum[K+1] = {0};
    // dp[n][b][k]: 長度為 n，可以使用 k 次操作，在前一個元素為 b 時的解
    // 所求為 dp[N][0][K]

    // 狀態轉移：
    // (1) dp[1][b][k] = k + 1
    // (2) dp[n][b][k] = sum(  )

    dp[1][0][0] = MOD_ADD(1, 0);
    preSum[0] = dp[1][0][0];
    for (int k = 1; k <= K; k++)
        for (int b = 0; b <= k; b++){
            dp[1][k][b] = MOD_ADD(dp[1][k - 1][0], 1);
            preSum[k] = MOD_ADD(preSum[k], dp[1][k][b]);
    }

    // for(int k=0; k<=K; k++)
    //     cout << preSum[k] <<'\n';

    for (int i = 2; i <= N; i++){
        int cur = i & 1;
        dp[cur][0][0] = MOD_ADD(1, 0);

        for (int k = 1; k <= K; k++){
            // b = 0
            // dp[cur][k][0] = 0;
            // for (int j = 0; j <= k; j++)
            //     dp[cur][k][0] = MOD_ADD(dp[cur][k][0], dp[!cur][k][j]);
            dp[cur][k][0] = preSum[k];

            // b = 1
            // dp[i % 2][k][1] = dp[i % 2][k][0] - dp[(i - 1) % 2][k][0] + dp[(i - 1) % 2][k - 1][0];
            dp[cur][k][1] = MOD_MINUS(dp[cur][k][0], dp[!cur][k][0]);
            dp[cur][k][1] = MOD_ADD(dp[cur][k][1], dp[!cur][k - 1][0]);
            preSum[k] = MOD_ADD(preSum[k], dp[cur][k][1]);

            // b > 1
            for (int b = 2; b <= k; b++){
                // dp[i % 2][k][b] =
                //     dp[i % 2][k][b - 1] +
                //     dp[i % 2][k - 1][b - 1] -
                //     dp[i % 2][k - 1][b - 2] -
                //     dp[(i - 1) % 2][k][b - 1] +
                //     dp[(i - 1) % 2][k - 1][b - 1];
                dp[cur][k][b] = 0;
                dp[cur][k][b] = MOD_ADD(dp[cur][k][b], dp[cur][k][b - 1]);
                dp[cur][k][b] = MOD_ADD(dp[cur][k][b], dp[cur][k - 1][b - 1]);
                dp[cur][k][b] = MOD_MINUS(dp[cur][k][b], dp[cur][k - 1][b - 2]);
                dp[cur][k][b] = MOD_MINUS(dp[cur][k][b], dp[!cur][k][b - 1]);
                dp[cur][k][b] = MOD_ADD(dp[cur][k][b], dp[!cur][k - 1][b - 1]);

                preSum[k] = MOD_ADD(preSum[k], dp[cur][k][b]);
            }
        }
    }

    // for(int i=1; i<=N; i++)
    //     cout << dp[i][0][K] << '\n';

    cout << dp[N & 1][K][0];
}

/*
N=3, K=2: ans=23

(0, 0, 0) (0, 0, 1) (0, 0, 2)
(0, 1, 0) (0, 1, 1) (0, 1, 2)
(0, 2, 0) (0, 2, 1) (0, 2, 2)

(1, 0, 0) (1, 0, 1)
(1, 1, 0) (1, 1, 1) (1, 1, 2)
(1, 2, 0) (1, 2, 1) (1, 2, 2)

(2, 0, 0)
(2, 1, 0) (2, 1, 1) (2, 2, 1)
(2, 2, 0) (2, 2, 1) (2, 2, 2)

差分：

(0, 0, 0, 0) (0, 0, 1, -1) (0, 0, 2, -2)
(0, 1, -1, 0) (0, 1, 0, -1) (0, 1, 1, -2)
(0, 2, -2, 0) (0, 2, -1, -1) (0, 2, 0, -2)

(1, -1, 0, 0) (1, -1, 1, -1)
(1, 0, -1, 0) (1, 0, 0, -1) (1, 0, 1, -2)
(1, 1, -2, 0) (1, 1, -1, -1) (1, 1, 0, -2)

(2, -2, 0, 0)
(2, -1, -1, 0) (2, -1, 0, -1)
(2, 0, -2, 0) (2, 0, -1, -1) (2, 0, 0, -2)

*/