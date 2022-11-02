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

#define MAX_A 200500

typedef unsigned long long int ll;

int c = 0;

int left_hash[MAX_A] = {0}, right_hash[MAX_A] = {0};

ll basic_case(int A[], int l, int r){
    ll res = 0;
    for(int i=l; i<=r; i++){
        int cur_min = A[i];
        for(int j = i+1; j<=r; j++){
            cur_min = min(cur_min, A[j]);
            res += abs(A[i] - A[j]) == cur_min;
        }
    }
    return res;
}

ll solve(int A[], int l, int r){    
    if(r - l <= 25)    
        return basic_case(A, l, r);
    
    int mid = (l + r) / 2;
    ll res = 0;
    res += solve(A, l, mid);
    res += solve(A, mid + 1, r);

    int lb = mid, rb = mid + 1, cur_min;

    // lb, rb 為尚未處理的點
    while(lb >= l && rb <= r){
        cur_min = max(A[lb], A[rb]);

        while(lb >= l && A[lb] >= cur_min){
            // 當 lb < l 或 A[lb] < cur_min 時跳出
            // 現在要處理 lb
            left_hash[A[lb]]++;
            res += right_hash[A[lb] - cur_min];
            res += right_hash[A[lb] + cur_min];
            lb--;
        }
        while(rb <= r && A[rb] >= cur_min){
            right_hash[A[rb]]++;
            res += left_hash[A[rb] - cur_min];
            res += left_hash[A[rb] + cur_min];
            rb++;
        }
    }

    while(lb >= l){
        // 代表 rb > r
        cur_min = min(A[lb], cur_min);
        left_hash[A[lb]]++;
        res += right_hash[A[lb] - cur_min];
        res += right_hash[A[lb] + cur_min];
        lb--;
    }
    while(rb <= r){
        cur_min = min(A[rb], cur_min);        
        right_hash[A[rb]]++;
        res += left_hash[A[rb] - cur_min];
        res += left_hash[A[rb] + cur_min];
        rb++;
    }
    
    for(int i=l; i<=mid; i++)
        left_hash[A[i]]--;
    for(int i=mid+1; i<=r; i++)
        right_hash[A[i]]--;

    return res;
}

int main(){

    int n;
    ReadInt(&n);

    int A[n];
    for(auto &i: A)
        ReadInt(&i);
    
    ll res = solve(A, 0, n - 1);
    WriteLL(res);
}

