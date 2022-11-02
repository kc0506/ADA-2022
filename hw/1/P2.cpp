#include <bits/stdc++.h>
#include <cctype>

using namespace std;

#define MAX_N 5100
#define MAX_W 5100

int hasEOF = 0;
int readchar()
{
    static int N = 1 << 20;
    static char buf[1 << 20];
    static char *p = buf, *end = buf;
    if (p == end)
    {
        if ((end = buf + fread(buf, 1, N, stdin)) == buf)
        {
            hasEOF = 1;
            return EOF;
        }
        p = buf;
    }
    return *p++;
}

int ReadInt(int *x)
{
    char c, neg;
    while ((c = readchar()) < '-')
    {
        if (c == EOF)
            return 0;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c - '0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c - '0';
    *x *= neg;
    return 1;
}

void WriteInt(int x)
{
    if (!x)
        putchar('0');
    else
    {
        char s[100];
        int i, j = 0;
        if (x < 0)
            putchar('-'), x = -x;
        for (; x > 0; x /= 10)
            s[j++] = x % 10;
        for (i = j - 1; i >= 0; i--)
            putchar(s[i] + 48);
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    int n, w, A[MAX_M];
    ReadInt(&n);
    ReadInt(&w);
    for (int i = 0; i < n; i++)
        ReadInt(A + i);

    // Solve for greedy
    // time = O(W + N logN)
    int G[MAX_W], A_sorted[MAX_M];
    copy(A, A + n, A_sorted);
    sort(A_sorted, A_sorted + n);

    G[0] = 0;
    for (int i = 0; i <= w; i++)
    {
        // 找到不超過目前重量的最貴 gem
        int *idx = upper_bound(A_sorted, A_sorted + n, i);
        // 買到不能再買;
        G[i] = (idx == A_sorted) ? i : G[i % (*(idx - 1))];
    }

    // Solve for optimized
    // time = O(W * N)

    // Strategy:
    // dp[i+1][j] = 使用 0~i，在不超過 j 時能剩下的最少金額
    // (1) dp[0][j] = j
    // (2) dp[i+1][j] = dp[i][j]，如果 j < a_i
    // (3) dp[i+1][j] = min(dp[i][j] % a_i, dp[i+1][j - a_i])

    int dp[2][MAX_W]; // 只會用到兩個
    // (1)
    for (int j = 0; j <= w; j++)
        dp[0][j] = j;
    // 求取剩下的
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= w; j++)
        {
            if (j < A[i - 1])
                dp[i % 2][j] = dp[(i + 1) % 2][j];
            else
                dp[i % 2][j] = min(dp[(i + 1) % 2][j] % A[i - 1], dp[i % 2][j - A[i - 1]]);
        }
    }

    // 輸出答案
    for (int j = 1; j <= w; j++)
    {
        WriteInt(G[j] - dp[n % 2][j]);
        putchar('\n');
    }
}
