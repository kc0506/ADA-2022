#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> pii;

class edge {
   public:
    int to, cost;
    edge(int x, int c) : to(x), cost(c){};
};

#define INF ((ll)1e16)

ll Dijkstra(int s, vector<vector<edge>> G, int V) {
    // vertec: 1~V
    int d[V + 1], used[V + 1] = {0};
    fill(d, d + V + 1, INF);

    priority_queue<pii, vector<pii>, greater<pii>> Q;  // compare by first, smallest
    d[s] = 0;
    Q.emplace(pii(0, s));

    ll res = 0;

    while (!Q.empty()) {
        pii p = Q.top();
        Q.pop();

        int v = p.second;

        // cout << "v = " << v << '\n';

        if (d[v] > p.first || used[v])
            continue;  // out-of-date information

        // solved => add to res;
        // cout << "d of " << v << ": " << d[v] << '\n';
        used[v] = 1;
        res += d[v];

        // update all neighbors
        for (auto &e : G[v]) {
            // cout << "to = " << e.to << '\n';
            if (d[e.to] > d[v] + e.cost) {
                // update
                d[e.to] = d[v] + e.cost;
                Q.emplace(pii(d[e.to], e.to));
            }
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
    vector<vector<edge>> G(N + 1);

    while (M--) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].emplace_back(edge(b, c));

        if (a == 1) {
            pos[b] = G[a].size() - 1;
        }
    }

    ll res = INF;
    for (int j = 2; j <= N; j++) {
        // build portal at (1, j)
        int flag, buf;
        if (pos[j] == -1)
            G[1].emplace_back(edge(j, 0)), flag = 0;
        else
            buf = G[1][pos[j]].cost, G[1][pos[j]].cost = 0, flag = 1;

        ll cur = Dijkstra(1, G, N);
        // cout << "cur = " << cur << '\n';
        res = min(res, cur);

        if (!flag) {
            G[1].pop_back();
        } else
            G[1][pos[j]].cost = buf;
    }

    cout << res;
}
