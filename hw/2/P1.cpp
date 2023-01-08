#include <bits/stdc++.h>

#include <cctype>
int hasEOF = 0;
int readchar() {
    static int N = 1<<20;
    static char buf[1<<20];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;   
        }
        p = buf;
    }
    return *p++;
}
int ReadInt(int *x) {
    char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
void WriteLL(long long int x){
    if (!x) putchar('0');
    else{
        char s[100];
        int i,j=0;
        if(x<0) putchar('-'), x = -x;
        for (;x>0;x/=10) s[j++]=x%10;
        for (i=j-1;i>=0;i--) putchar(s[i]+48);
    }
}

using namespace std;

typedef long long int ll;

int main(){
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int N, K;
    ReadInt(&N), ReadInt(&K);

    int A[N];
    for(int i=0; i<N; i++)
        ReadInt(A + i);
    
    ll dp[N + 1][K];  // dp[i][k] = 在 [i, N-1]，切成 k 段時能得到的最低 discomfort value
    // k <= N - i
    // dp[N][k] = 0
   
    // Let M[l, r] = 最大連續子陣列和 in [l, r]
    // dp[i][k] =  min(M[i, j] * (j - i + 1) + dp[j + 1][k - 1])
    
    int max_so_far, max_here;
    dp[N - 1][1] =  max_so_far = max_here = A[N - 1];
    for(int i = N - 2; i >= 0; i--){
        // 首先更新 max_so_far
        max_here =  max(max_here + A[i], A[i]);
        max_so_far = max(max_so_far, max_here);
        
        int size = N - i;
        dp[i][1] = (ll) size * max_so_far;
    }

    for(int k = 2; k <= K; k++ ){
        for(int i = N - 1; i >= 0; i--){
            if(k > N - i){
                dp[i][k] = 0;
                continue;
            }

            int max_so_far, max_here;
            ll res;
            max_so_far = max_here = A[i];
            res = A[i] + dp[i + 1][k - 1];      
            for(int j = i + 1; j < N - 1; j++){
                max_here =  max(max_here + A[j], A[j]);
                max_so_far = max(max_so_far, max_here);

                int size = j - i + 1;
                res = min(res, (ll) max_so_far * size + dp[j + 1][k - 1]);
            }
            dp[i][k] = res;
        }
    }
    WriteLL(dp[0][K]);
}
