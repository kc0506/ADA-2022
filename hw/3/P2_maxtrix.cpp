#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#define INF ((ll)1e9)

ll Dijkstra(int s, vector<vector<int>> &G, int V, int *d, bool *used) {
    // vertec: 1~V
    // for (int i = 1; i <= V; i++) {
    //     for (int j = 1; j <= V; j++)
    //         cout << G[i][j] << ' ';
    //     cout << '\n';
    // }

    fill(d, d + V + 1, INF);
    fill(used, used + V + 1, false);

    d[s] = 0;

    ll res = 0;
    while (true) {
        int v = -1;
        for (int u = 1; u <= V; u++)
            // find smallest d[u]
            if (!used[u] && (v == -1 || d[u] < d[v]))
                v = u;

        if (v == -1)
            break;
        res += d[v];
        used[v] = true;

        for (int u = 1; u <= V; u++) {
            d[u] = min(d[u], d[v] + G[v][u]);
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N, M;

    cin >> N >> M;

    if (N == 0) {
        cout << 0;
        return 0;
    }

    int pos[N + 1];  // stores the pos of road from 1 to i
    fill(pos, pos + N + 1, -1);
    vector<vector<int>> G(N + 1, vector<int>(N + 1, INF));

    while (M--) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a][b] = c;
    }

    int d[N + 1];
    bool used[N + 1];

    const int root = 1;
    ll res = INF;
    for (int j = 2; j <= N; j++) {
        // build portal at (1, j)
        int tmp = G[root][j];
        G[root][j] = 0;

        ll cur = Dijkstra(1, G, N, d, used);
        // cout << "cur = " << cur << '\n';
        res = min(res, cur);

        G[root][j] = tmp;
    }

    cout << res;
}
