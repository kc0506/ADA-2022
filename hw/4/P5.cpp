#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N;
    cin >> N;

    int A[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    // cout << "single\n";
    // single[k][i][j] 第 k 種排法 (k, k+1, ..., k-1) 時 [i, j] 的值
    int single[N][N][N];
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++) {
                // 實際上 [i, j] 會是 [(i+k)%N, (j+k)%N]
                // 長度為 j-i+1  =>  j = i-1+len
                // A[i][j] = i ~ j-1
                // => single[i][j] = A[i][j+1]
                single[k][i][j] = A[(i + k) % N][(j + k + 1) % N];
            }
        }
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++) {
                // cout << single[k][i][j] << ' ';
            }
            // cout << '\n';
        }
        // cout << '\n';
    }
    // cout << '\n';

    // dp[k][i][s] := 第 k 種排法，[i, N-1] 切成 s 段
    // N-i >= s  =>  i <= N-s
    ll dp[N][N][N + 1] = {0};

    // cout << "edge case\n";
    // Edge case
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            dp[k][i][1] = single[k][i][N - 1];
            // cout << dp[k][i][1] << ' ';
        }
        // cout << '\n';
    }

    // cout << '\n';

    // 狀態轉移
    for (int s = 2; s <= N; s++) {
        for (int k = 0; k < N; k++) {
            for (int i = 0; i <= N - s; i++) {
                // dp[k][i][s] = max([i,j] + [j+1, N-1]) for (N-j-1) >= s-1 => j <= N-s
                dp[k][i][s] = 0;
                for (int j = i; j <= N - s; j++) {
                    dp[k][i][s] = max(
                        dp[k][i][s], single[k][i][j] + dp[k][j + 1][s - 1]);
                    // cout << k << ", " << i << ", " << s << ' ' << j << '\n';
                    // cout << dp[k][i][s] << '\n';
                }
            }
        }
    }

    // cout << "result:\n";

    for (int s = 1; s <= N; s++) {
        ll res = 0;
        for (int k = 0; k < N; k++)
            res = max(res, dp[k][0][s]);
        cout << res << ' ';
    }
}
