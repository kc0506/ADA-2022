#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> pii;
#define X first
#define Y second

ll l1, l2, r1, r2;

ll dr(pii p){
    return p.Y * r2 - p.X * r1;
}

ll dl(pii p){
    return p.Y * l2 - p.X * l1;
}

bool cmp_r(pii a, pii b){
    return dr(a) < dr(b);
}

bool cmp_l(pii a, pii b){
    return dl(a) < dl(b);
}

void print_A(pii A[], int l, int r){
    for(int i=l; i<=r; i++)
        printf("(%d, %d) ", A[i].X, A[i].Y);
    printf("\n");
}

void print_dl(pii A[], int l, int r){
    for(int i=l; i<=r; i++)
        printf("%lld ", dl(A[i]));
    printf("\n");
}

void print_dr(pii A[], int l, int r){
    for(int i=l; i<=r; i++)
        printf("%lld ", dr(A[i]));
    printf("\n");
}

ll solve_dup(vector<pii> A, int mid){
    // 這個 case 是拿來算當 dr(i) == dr(j) 時逆序對的數量
    // 只需要算 i<=mid, mid<j 的 case

    ll res = 0;
    for(int i=0; i<=mid; i++)
        res += upper_bound(A.begin() + mid + 1, A.end(), A[i], cmp_l) - A.begin() - mid - 1;
    return res;
}

ll solve(pii A[], int l, int r){
    bool check = 0;

    // 回傳在 A[l, r] 中使得 i < j, dl(A[i]) > dl(A[j]) 的 (i, j) 數量
    if(l == r)
        return 0;

    // 初始時 A 是依據 dr 的升序排列
    int mid = (l + r) / 2;
    ll res = 0;

    // 先找出橫跨兩陣列且 dr 相同的值
    int dup_mid;
    vector<pii> A_dup(0);
    for(int i=mid-1; i>=l && dr(A[i]) == dr(A[mid]); i--)
        A_dup.push_back(A[i]);
    dup_mid = A_dup.size();
    A_dup.push_back(A[mid]);
    for(int i=mid+1; i<=r && dr(A[i]) == dr(A[mid]); i++)
        A_dup.push_back(A[i]);


    ll comb_dup = ((ll) dup_mid + 1) * ((ll) A_dup.size() - dup_mid - 1), 
        res_dup = solve_dup(A_dup, dup_mid);
    res += comb_dup - res_dup;

    ll lres = solve(A, l, mid), rres = solve(A, mid + 1, r);
    res += lres + rres;

    // 在分治時會順便排序 dl
    // 因此現在在 A[l, mid] 中 dl 為升序排列；A[mid+1, r] 也是
    // 同時依據原本的條件，A[l, mid] 中的 dr 皆小於 A[mid+1, r] 中的 dr

    // 現在我們要統計 i in [l, mid], j in [mid+1, r]
    // 使得 [dr(i) - dr(j)] * [dl(i) - dl(j)] <= 0 的 (i, j) 數量
    // 我們已經確定 dr(i) - dr(j) <= 0
    // => 
    // case (1): dr(i) - dr(j) = 0
    // 則條件已滿足
    // case (2): dr(i) - dr(j) < 0
    // 則須找 dl(i) - dl(j) >= 0
    // => 
    // 正確答案為 (dr(i) - dr(j) = 0) 或 (dr(i) - dr(j) < 0 且 dl(i) - dl(j) >= 0)
    // = (dl(i) - dl(j) >= 0) - (dl(i) - dl(j) >= 0 且 dr(i) == dr(j)) + (dr(i) == dr(j))
    // = (dl(i) - dl(j) >= 0) + (dr(i) == dr(j) 且 dl(i) - dl(j) < 0)

    int lsize = mid - l + 1, rsize = r - mid;
    ll count_res = 0;
    pii A_l[lsize], A_r[rsize];
    copy(A + l, A + mid + 1, A_l);
    copy(A + mid + 1, A + r + 1, A_r);

    int cur = l, lp = 0, rp = 0, lcount = lsize;
    while(lp < lsize && rp < rsize){
        if(dl(A_l[lp]) >= dl(A_r[rp])){
            res += lcount;
            count_res += lcount;
            A[cur++] = A_r[rp++];
        } else{ 
            A[cur++] = A_l[lp++];
            lcount--;
        }
    }
    while(lp < lsize)
        A[cur++] = A_l[lp++];
    while(rp < rsize)
        A[cur++] = A_r[rp++];

    if(check) printf("(%d, %d) = %d + %d + %d + %d - %d\n", l, r, lres, rres, count_res, comb_dup, res_dup);
    if(check) printf("comb = %d * %d\n", (dup_mid + 1), (A_dup.size() - dup_mid - 1));
    return res;
}

int main(){
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int n;
    cin >> n;

    cin >> l1 >> l2 >> r1 >> r2;

    pii A[n];
    for(auto &i: A)
        cin >> i.X >> i.Y;
    
    // First sort by dr
    sort(A, A + n, cmp_r);
    // printf("\n");
    // print_A(A, 0, n - 1);
    // print_dl(A, 0, n - 1);
    // print_dr(A, 0, n - 1);
    // printf("\n");

    // 接著用 dl 找逆序數對
    ll res = solve(A, 0, n - 1);
    cout << res;
}
