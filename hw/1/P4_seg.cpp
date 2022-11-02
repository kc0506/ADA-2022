#include <bits/stdc++.h>

using namespace std;

#define MAX_N 60000

struct node {
    int min;
    node *l, *r;
};

node* build(int l, int r, vector<int> &arr){
    node* cur = new node;
    if(l == r){
        cur->min = arr[l];
        return cur;
    }

    int mid = (l + r) / 2;
    cur->l = build(l, mid, arr);
    cur->r = build(mid + 1, r, arr);
    cur->min = min(cur->l->min, cur->r->min);
    return cur;
}

int query(int l, int r, node *cur, int L, int R){
    // cout << l << ' ' << r << ' ' << L << ' ' << R << '\n'; 

    if(l == L && r == R)
        return cur->min;

    int mid = (L + R) / 2;
    if(r <= mid)
        return query(l, r, cur->l, L, mid);
    else if(l > mid)
        return query(l, r, cur->r, mid + 1, R);
    return min(query(l, mid, cur->l, L, mid), query(mid + 1, r, cur->r, mid + 1, R));
}

int solve(node *root, int N, vector<int> A, int l, int r){
    if(l == r)
        return 0;
    int res = 0, mid = (l + r) / 2;
    res += solve(root, N, A, l, mid) + solve(root, N, A, mid + 1, r);

    for(int i=l; i<=mid; i++)
    for(int j=mid+1; j<=r; j++)
        res += query(i, j, root, 0, N - 1) == abs(A[i] - A[j]);
    printf("%d %d, res = %d\n", l, r, res);
    return res;
}

int main(){
    // ios_base::sync_with_stdio(0), cin.tie(0);

    clock_t st = clock();

    int N;
    cin >> N;

    vector<int> A(N);
    for(int i=0; i<N; i++)
        cin >> A[i];

    node *root = build(0, N - 1, A);

    // for(int i=0; i<N; i++){
    //     for(int j=i; j<N; j++)   
    //         cout << "min of [" << i << ", " << j << "] = " << query(i, j, root, 0, N - 1) << '\n';
    // }

    // cout << "build time: " << (double)(clock() - st) / CLOCKS_PER_SEC << "\n";

    // int res = 0;
    // for(int i=0; i<N; i++){
    //     for(int j=i+1; j<N; j++){
    //         res += query(i, j, root, 0, N - 1) == abs(A[i] - A[j]);
    //     }
    // }
    
    int res = solve(root, N, A, 0, N - 1);
    cout << res << "\n";

    // cout << "time: " << (double)(clock() - st) / CLOCKS_PER_SEC;
}

/*
Get-Content text | .\P4 > out
*/