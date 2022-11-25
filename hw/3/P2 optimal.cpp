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

ll Dijkstra(int s, vector<vector<edge>> &G, int V, int *d, int *used) {
    // vertec: 1~V
    fill(d, d + V + 1, INF);
    fill(used, used + V + 1, 0);

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

#include <cctype>
#include <cstdio>
int hasEOF = 0;
int readchar();
int ReadInt(int *x);
void WriteInt(int x);
void WriteLL(long long int x);
void ReadStr(char *str);

int main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int N, M;

    // cin >> N >> M;
    ReadInt(&N), ReadInt(&M);

    if (N == 0) {
        putchar('0');
        return 0;
    }

    int pos[N + 1];  // stores the pos of road from 1 to i
    fill(pos, pos + N + 1, -1);
    vector<vector<edge>> G(N + 1);

    while (M--) {
        int a, b, c;
        ReadInt(&a), ReadInt(&b), ReadInt(&c);
        G[a].emplace_back(edge(b, c));

        if (a == 1) {
            pos[b] = G[a].size() - 1;
        }
    }

    int used[N + 1], d[N + 1];

    ll res = INF;
    for (int j = 2; j <= N; j++) {
        // build portal at (1, j)
        int flag, buf;
        if (pos[j] == -1)
            G[1].emplace_back(edge(j, 0)), flag = 0;
        else
            buf = G[1][pos[j]].cost, G[1][pos[j]].cost = 0, flag = 1;

        ll cur = Dijkstra(1, G, N, used, d);
        // cout << "cur = " << cur << '\n';
        res = min(res, cur);

        if (!flag) {
            G[1].pop_back();
        } else
            G[1][pos[j]].cost = buf;
    }

    WriteLL(res);
}

int readchar() {
    static int N = 1 << 20;
    static char buf[1 << 20];
    static char *p = buf, *end = buf;
    if (p == end) {
        if ((end = buf + fread(buf, 1, N, stdin)) == buf) {
            hasEOF = 1;
            return EOF;
        }
        p = buf;
    }
    return *p++;
}

int ReadInt(int *x) {
    char c, neg;
    while ((c = readchar()) < '-') {
        if (c == EOF) return 0;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c - '0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c - '0';
    *x *= neg;
    return 1;
}

void WriteInt(int x) {
    if (!x)
        putchar('0');
    else {
        char s[100];
        int i, j = 0;
        if (x < 0) putchar('-'), x = -x;
        for (; x > 0; x /= 10) s[j++] = x % 10;
        for (i = j - 1; i >= 0; i--) putchar(s[i] + 48);
    }
}

void WriteLL(long long int x) {
    if (!x)
        putchar('0');
    else {
        char s[100];
        int i, j = 0;
        if (x < 0) putchar('-'), x = -x;
        for (; x > 0; x /= 10) s[j++] = x % 10;
        for (i = j - 1; i >= 0; i--) putchar(s[i] + 48);
    }
}

void ReadStr(char *str) {
    char c;
    while (!isgraph(c = readchar()))
        ;

    // printf("c = %c\n", c);
    int cur = 0;
    str[cur++] = c;
    while (isgraph(c = readchar())) {
        str[cur++] = c;
    }
}
