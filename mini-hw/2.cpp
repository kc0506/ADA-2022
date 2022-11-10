#include <bits/stdc++.h>
#include <cctype>

using namespace std;

typedef long long int ll;

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

void WriteInt(int x){
    if (!x) putchar('0');
    else{
        char s[100];
        int i,j=0;
        if(x<0) putchar('-'), x = -x;
        for (;x>0;x/=10) s[j++]=x%10;
        for (i=j-1;i>=0;i--) putchar(s[i]+48);
    }
}

void WriteLL(ll x){
    if (!x) putchar('0');
    else{
        char s[100];
        int i,j=0;
        if(x<0) putchar('-'), x = -x;
        for (;x>0;x/=10) s[j++]=x%10;
        for (i=j-1;i>=0;i--) putchar(s[i]+48);
    }
}

int main(){
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int n;
    ReadInt(&n);

    int Arr[500000];
    for(int i=0; i<n; i++)
        ReadInt(Arr + i);

    ll res = (ll) Arr[0], ma_here = (ll) Arr[0];
    for(int i=1; i<n; i++) {
        ma_here = max(ma_here + Arr[i], (ll) Arr[i]);
        res = max(res, ma_here);
    }

    WriteLL(res);
}   
