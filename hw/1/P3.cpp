#include <bits/stdc++.h>
#include <cctype>

using namespace std;

typedef pair<int, int> pii;
typedef long long int ll;
#define X first
#define Y second

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

ll ReadLL(ll *x) {
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

ll l1, l2, r1, r2;

ll dr(const pii *a){
    return a->Y * r2 - a->X * r1;
}

ll dl(const pii *a){
    return a->Y * l2 - a->X * l1;
}

ll solve_r(const pii *A[], const pii *tempL[], const pii *tempR[], int l, int r){
    // before: for any (i, j) x(i) <= x(j)
    // after: for any (i, j) dr(i) <= dr(j)
    // return (i, j) such that dr(j) > dr(i)

    if(r - l <= 25){
        int res = 0;
        for(int i=l; i<r; i++)
            for(int j=i+1; j<=r; j++)
                res += dr(A[i]) < dr(A[j]);
        sort(A + l, A + r + 1, [](const pii *a, const pii *b)->bool{return dr(a) < dr(b);});
        return res;
    }

    int mid = (l + r) / 2;
    ll res = 0, 
        lres = solve_r(A, tempL, tempR, l, mid), 
        rres = solve_r(A, tempL, tempR, mid + 1, r);
    res += lres + rres;

    int lsize = mid - l + 1, rsize = r - mid;
    copy(A + l, A + mid + 1, tempL);
    copy(A + mid + 1, A + r + 1, tempR);

    ll pairs_count = 0;
    int cur = l, lcur = 0, rcur = 0, rcount = rsize; 
    while(lcur < lsize && rcur < rsize){
        if(dr(tempL[lcur]) < dr(tempR[rcur])){
            A[cur++] = tempL[lcur++];
            pairs_count += rcount;
        } else{
            A[cur++] = tempR[rcur++];
            rcount--;
        }
    }
    while(lcur < lsize)
        A[cur++] = tempL[lcur++];
    while(rcur < rsize)
        A[cur++] = tempR[rcur++], rcount--;
    assert(rcount == 0 && cur == r + 1);
    res += pairs_count;

    return res;
}

ll solve_l(const pii *A[], const pii *tempL[], const pii *tempR[], int l, int r){
    // before: for (i, j), x(i) <= x(j)
    // after: for (i, j), dl(i) <= dl(j)
    // return (i, j) s.t. dl(i) > dl(j)

    if(r - l <= 25){
        int res = 0;
        for(int i=l; i<r; i++)
            for(int j=i+1; j<=r; j++)
                res += dl(A[i]) > dl(A[j]);
        sort(A + l, A + r + 1, [](const pii *a, const pii *b)->bool{return dl(a) < dl(b);});
        return res;
    }

    int mid = (l + r) / 2;
    ll res = 0, 
        lres = solve_l(A, tempL, tempR, l, mid), 
        rres = solve_l(A, tempL, tempR, mid + 1, r);
    res += lres + rres;

    int lsize = mid - l + 1, rsize = r - mid;
    copy(A + l, A + mid + 1, tempL);
    copy(A + mid + 1, A + r + 1, tempR);

    ll pairs_count = 0;
    int cur = l, lcur = 0, rcur = 0, lcount = lsize;
    while(lcur < lsize && rcur < rsize){
        if(dl(tempL[lcur]) > dl(tempR[rcur])){
            A[cur++] = tempR[rcur++];
            pairs_count += lcount;
        } else{
            A[cur++] = tempL[lcur++];
            lcount--;
        }
    }
    while(lcur < lsize)
        A[cur++] = tempL[lcur++], lcount--;
    while(rcur < rsize)
        A[cur++] = tempR[rcur++];
    assert(lcount == 0 && cur == r + 1);
    res += pairs_count;
    
    return res;
}

ll edge_case(const pii *A[], int n){
    unordered_map<ll, int> H;
    ll res = 0;
    for(int i=0; i<n; i++)
        res += H[dr(A[i])], H[dr(A[i])]++;
    return res;
}

int main(){
    int n;
    ReadInt(&n);

    ReadLL(&l1), ReadLL(&l2), ReadLL(&r1), ReadLL(&r2);

    pii coords[n];
    for(auto &i: coords)
        ReadInt(&(i.X)), ReadInt(&(i.Y));
    sort(coords, coords + n, [](pii &a, pii &b){return a.X < b.X;});

    /*

    (m <= r && m >= l)
    = !(m > r || m < l)
    = !(r2 * m - r1 > 0 || l2 * m - l1 < 0)

    兩個 case 不會 overlap。
    如果我們確保 x 為升序
    那麼 dx > 0
    則就有 r2 * dy - r1 * dx > 0 || l2 * dy - l1 * dx < 0
    可以用二維偏序解。
    */

    const pii *A[n], *tempL[n], *tempR[n];

    if(l1 * r2 == l2 * r1){
        for(int i=0; i<n; i++) A[i] = coords + i;
        WriteLL(edge_case(A, n));
        return 0;
    }

    ll comb = (ll) n * ((ll) n - 1) / 2, lres, rres;

    for(int i=0; i<n; i++) A[i] = coords + i;
    lres = solve_l(A, tempL, tempR, 0, n - 1);
    for(int i=0; i<n; i++) A[i] = coords + i;
    rres = solve_r(A, tempL, tempR, 0, n - 1);

    ll res = comb - lres - rres;
    WriteLL(res);
}
