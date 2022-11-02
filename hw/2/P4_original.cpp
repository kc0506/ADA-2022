#include <bits/stdc++.h>

using namespace std;

#define MOD_ADD(a, b) (a >= M - b ?a - M + b :a + b)

typedef long long int ll;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N, K;
    ll M;
    cin >> N >> K >> M;

    vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(K+1, vector<ll>(K+1, 0)));
    // dp[n][b][k]: 長度為 n，可以使用 k 次操作，在前一個元素為 b 時的解
    // 所求為 dp[N][0][K]

    // 狀態轉移：
    // (1) dp[1][b][k] = k + 1
    // (2) dp[n][b][k] = sum(  )

    for(int b = 0; b <= K; b++){
        for(int k = 0; k <= K; k++)
            dp[1 % 2][b][k] = k + 1;
    }

    for(int i = 2; i <= N; i++){
        for(int k = 0; k <= K; k++){
            for(int b = 0; b <= k; b++){
                if(k == 0){
                    dp[i % 2][b][k] = 1;
                    continue;
                }
                
                dp[i % 2][b][k] = 0;
                for(int j = 0; j <= k; j++){
                    int k_new = k - max(0, b - j);
                    dp[i % 2][b][k] = MOD_ADD(dp[i % 2][b][k], dp[(i - 1) % 2][j][k - max(0, b - j)]);
                }
            }
        }
    }


    // for(int i=1; i<=N; i++)
    //     cout << dp[i][0][K] << '\n';

    cout << dp[N % 2][0][K];
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