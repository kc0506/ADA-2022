#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#define MAX_N (400 + 50)
int A[MAX_N][MAX_N];
ll dp[MAX_N][2];
ll res[MAX_N];

#include <cctype>
#include <cstdio>
int hasEOF = 0;
int readchar();
int ReadInt(int*x);
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

    for (int s = 1; s <= N; s++)
        res[s] = 0;

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            int mod = (i + k >= N) ? (i + k - N) : (i + k);
            dp[i][1] = A[mod][k];
        }
        if (dp[0][1] > res[1])
            res[1] = dp[0][1];

        for (int s = 2; s <= N; s++) {
            for (int i = 0; i <= N - s; i++) {
                ll nxt = 0, cur = 0;

                for (int j = i; j <= N - s; j++) {
                    int modi = (i + k >= N) ? (i + k - N) : (i + k),
                        modj = (j + k + 1 >= N) ? (j + k + 1 - N) : (j + k + 1);

                    nxt = A[modi][modj] + dp[j + 1][(s - 1) & 1];

                    if (nxt > cur)
                        cur = nxt;
                }
                dp[i][s & 1] = cur;
            }
            if (res[s] < dp[0][s & 1])
                res[s] = dp[0][s & 1];
        }
    }

    for (int s = 1; s <= N; s++)
        WriteLL(res[s]), putchar(' ');
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
