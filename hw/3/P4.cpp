#include <bits/stdc++.h>

using namespace std;

class edge {
   public:
    int to, cost, len;
    edge(int x, int c, int l) : to(x), cost(c), len(l){};
};

class node {
   public:
    int l, c, u;
    node(int x, int y, int z) : l(x), c(y), u(z){};
};

typedef vector<vector<edge>> graph;
typedef long long int ll;

#define INF ((int)1e9)
#define INFLL ((ll)1e15)

ll Prim(graph G, int N) {
    const int root = 0;

    bool poped[N] = {0};
    int max_len[N], len[N];
    ll cost[N];
    fill(len, len + N, INF);
    fill(cost, cost + N, INFLL);

    // arr3: l, c, u
    auto comp = [](const node &a, const node &b) {
        if (b.l == a.l)
            return b.c <= a.c;
        return b.l < a.l;
    };  // return "b is smaller"
    priority_queue<node, vector<node>, decltype(comp)> Q(comp);

    max_len[root] = 0;
    len[root] = 0;
    cost[root] = 0;
    Q.emplace(node(0, 0, root));

    ll res = 0;
    while (!Q.empty()) {
        node cur = Q.top();
        Q.pop();

        int l = cur.l, c = cur.c, u = cur.u;
        if (l > len[u] || c > cost[u] || poped[u])
            continue;

        poped[u] = true;
        res += cost[u];

        for (edge &e : G[u]) {
            // what will be the cost if travel to v by u
            int v = e.to;
            int new_cost = (max_len[u] > e.len)
                               ? cost[u]
                           : (max_len[u] == e.len)
                               ? cost[u] + e.cost
                               : e.cost;

            if (e.len < len[v] || (e.len == len[v] && new_cost < cost[v])) {
                max_len[v] = max(max_len[u], e.len);
                len[v] = e.len;
                cost[v] = new_cost;
                Q.emplace(node(len[v], cost[v], v));
            }
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N, M;
    cin >> N >> M;

    graph G(N);

    while (M--) {
        int a, b, l, c;
        cin >> a >> b >> l >> c;
        G[a].emplace_back(edge(b, c, l));
        G[b].emplace_back(edge(a, c, l));
    }

    cout << Prim(G, N);
}
