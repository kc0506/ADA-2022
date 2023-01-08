#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#define MAX_N (400 + 50)
int A[MAX_N][MAX_N];
ll dp[MAX_N][MAX_N][2];

#include <cctype>
#include <cstdio>
int hasEOF = 0;
int readchar();
int ReadInt(int *x);
void WriteLL(long long int &x);

int main() {
    int N;
    ReadInt(&N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            ReadInt(&(A[i][j]));

    // single[k][i][j] 第 k 種排法 (k, k+1, ..., k-1) 時 [i, j] 的值
    // 實際上 [i, j] 會是 [(i+k)%N, (j+k)%N]
    // 長度為 j-i+1  =>  j = i-1+len
    // A[i][j] = i ~ j-1
    // => single[i][j] = A[i][j+1]

    // dp[k][i][s] := 第 k 種排法，[i, N-1] 切成 s 段
    // N-i >= s  =>  i <= N-s

    // Edge case
    ll res = 0;
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            int mod = (i + k >= N) ? (i + k - N) : (i + k);
            dp[k][i][1] = A[mod][k];
        }
        if (dp[k][0][1] > res)
            res = dp[k][0][1];
    }
    WriteLL(res);
    putchar(' ');

    // 狀態轉移
    for (int s = 2; s <= N; s++) {
        res = 0;
        for (int k = 0; k < N; k++) {
            ll ans = 0;
            for (int i = 0; i <= N - s; i++) {
                // dp[k][i][s] = max([i,j] + [j+1, N-1]) for (N-j-1) >= s-1 => j <= N-s
                ll cur = 0;
                for (int j = i; j <= N - s; j++) {
                    int modi = (i + k >= N) ? (i + k - N) : (i + k),
                        modj = (j + k + 1 >= N) ? (j + k + 1 - N) : (j + k + 1);

                    if (A[modi][modj] + dp[k][j + 1][(s - 1) & 1] > cur)
                        cur = A[modi][modj] + dp[k][j + 1][(s - 1) & 1];
                }
                dp[k][i][s & 1] = cur;
                if(i == 0)
                    ans = dp[k][0][s & 1];
            }
            if (ans > res)
                res = ans;
        }
        WriteLL(res);
        putchar(' ');
    }
}

int readchar() {
    static int N = 1 << 20;
    static char buf[1 << 20];
    static char *p = buf, *end = buf;
    if (p == end) {
        if ((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;
        }
        p = buf;
    }
    return *p++;
}

int ReadInt(int *x) {
    char c, neg;
    while ((c = readchar()) < '-') {
        if (c == EOF) return 0;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c - '0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c - '0';
    *x *= neg;
    return 1;
}

void WriteLL(long long int &x) {
    if (!x)
        putchar('0');
    else {
        char s[100];
        int i, j = 0;
        if (x < 0) putchar('-'), x = -x;
        for (; x > 0; x /= 10) s[j++] = x % 10;
        for (i = j - 1; i >= 0; i--) putchar(s[i] + 48);
    }
}
