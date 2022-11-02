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

#define MAX_M (100000 + 10)

struct cust{
    int cook, eat;
};

struct group{
    int size;
    ll cook, eat;
};


int main(){
    int N;
    ReadInt(&N);
    
    cust v[MAX_M];
    group G[N];
    for(int i=0; i<N; i++){
        int m;
        ReadInt(&m);
    
        for(int j=0; j<m; j++)
            ReadInt(&v[j].cook), ReadInt(&v[j].eat);

        auto cmp = [](cust &a, cust &b) {
            return a.eat > b.eat;
        };
        sort(v, v + m, cmp);

        ll res = 0, chef = 0;
        for(int j=0; j<m; j++){
            res = max(res, chef + v[j].cook + v[j].eat);
            chef += v[j].cook;
        }

        G[i].cook = chef;
        G[i].eat = res - chef;
        G[i].size = m;
    }


    auto cmp = [](group &a, group &b){
        return (ll) a.size * b.cook - (ll) a.cook * b.size > 0;
    };
    sort(G, G + N, cmp);

    ll sum = 0, preSum = 0;
    for(auto &i: G){
        preSum += i.cook;
        sum += i.size * (preSum + i.eat);
    }
    WriteLL(sum);
}
