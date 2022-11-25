#include <bits/stdc++.h>

using namespace std;

class union_set {
    int *parent, *rank, size;

   public:
    union_set(int N) : size(N) {
        parent = new int[N + 1];
        rank = new int[N + 1];
        for (int i = 1; i <= N; i++)
            parent[i] = -1, rank[i] = 1;
    }
    int find_root(int u);
    void merge(int a, int b);
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<array<int, 3>> edge(M);
    for (int i = 0; i < M; i++) {
        cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
    }

    sort(edge.begin(), edge.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[2] < b[2];
    });

    long long res = 0;
    union_set Set(N);
    for (int i = 0; i < M; i++) {
        array<int, 3> &cur = edge[i];
        int a = cur[0], b = cur[1], c = cur[2];
        if (Set.find_root(a) != Set.find_root(b)) {
            Set.merge(a, b);
            res += c;
        }
    }

    cout << res;
}

int union_set::find_root(int u) {
    if (parent[u] == -1)
        return u;
    return parent[u] = find_root(parent[u]);
}

void union_set::merge(int a, int b) {
    int ra = find_root(a), rb = find_root(b);

    if (rank[ra] > rank[rb])
        parent[rb] = ra;
    else if (rank[ra] < rank[rb])
        parent[ra] = rb;
    else
        parent[rb] = ra, rank[ra]++;
}