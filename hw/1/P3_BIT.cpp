#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long int ll;
#define X first
#define Y second
#define lowbit(x) ((x & (-x)))

clock_t st;

class BIT{
    vector<int> tree;  // tree[i] 儲存 1~i 的元素數
    int size;
    public:
        BIT(int size){
            this->size = size;
            tree.resize(size + 1);
            fill(tree.begin(), tree.end(), 0);
        }
        int query(int x){
            int res = 0;
            for(; x > 0; x -= lowbit(x))
                res += tree[x];
            return res;
        }
        void update(int x, int v){
            for(; x <= this->size; x += lowbit(x))
                tree[x] += v;
        }
        void print(){
            for(int i=1; i<=this->size; i++)
                cout << tree[i] << ' ';
            cout << '\n';
        }
};

void print(vector<ll> A){
    for(auto i: A)
        cout << i << ' ';
    cout << '\n';
}

int get_id(ll &value, vector<ll> &D){
    // 在 D 中尋找 value 的排序 (從 1 開始)
    return lower_bound(D.begin(), D.end(), value) - D.begin() + 1;
}

ll solve_l(pii A[], int n, int l1, int l2){
    // 轉為 dl 陣列
    sort(A, A + n, [](pii a, pii b){return a.X < b.X;});
    vector<ll> X(n);
    transform(A, A + n, X.begin(), [&](pii a)->ll{
        return (ll) l2 * a.Y - (ll) l1 * a.X;
    });

    // 離散化
    vector<ll> D = X;
    sort(D.begin(), D.end());  
    D.erase(unique(D.begin(), D.end()), D.end());    

    // 建 BIT
    BIT tree = BIT(D.size());

    // 找出 X 中的逆序對
    // => 從背後走，看當前已有多少元素比自己小
    ll res = 0;
    clock_t G = 0, Q = 0, U = 0;
    for(int i = n - 1; i >= 0; i--){
        clock_t s1 = clock();
        int idx = get_id(X[i], D);
        clock_t s2 = clock();
        G += s2 - s1;
        int q = tree.query(idx - 1);
        clock_t s3 = clock();
        res += q;
        Q += s3 - s2;
        tree.update(idx, 1);
        U += clock() - s3;
    }

    return res;
}

ll solve_r(pii A[], int n, int r1, int r2){
    // 首先排序 A => O(nlogn)
    sort(A, A + n, [](pii a, pii b){return a.X < b.X;});

    // 用 X 裝 dr => O(n)
    vector<ll> X(n);
    transform(A, A + n, X.begin(), [&](pii x){
        return (ll) r2 * x.Y - (ll) r1 * x.X;
    });

    // 離散化 => O(nlogn)
    vector<ll> D = X;
    sort(D.begin(), D.end());
    auto u = unique(D.begin(), D.end());
    D.erase(u, D.end());

    // 建 BIT
    BIT tree = BIT(D.size());

    // 數正序對 => O(nlogn)
    ll res = 0;
    for(auto i: X){
        int idx = get_id(i, D);
        res += tree.query(idx - 1);
        tree.update(idx, 1);
    }
    return res;
}

int main(){
    st = clock();
    ios_base::sync_with_stdio(0), cin.tie(0);

    int n;
    cin >> n;

    int l1, l2, r1, r2;
    cin >> l1 >> l2 >> r1 >> r2;


    pii coords[n];
    for(int i=0; i<n; i++)
        cin >> coords[i].X >> coords[i].Y;

    ll comb = (ll) n * (n - 1) / 2, lres, rres;
    lres = solve_l(coords, n, l1, l2);
    rres = solve_r(coords, n, r1, r2);

    cout << comb - lres - rres;
}
