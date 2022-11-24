#include <bits/stdc++.h>

using namespace std;

class Graph {
   public:
    Graph() : size(0){};
    Graph(int n) : size(n) { adjacentList.resize(n); };

    void insertEdge(int u, int v);

    // For DFS
    void DFS_init();
    void DFS_visit(int u, int &time);
    void DFS(int *travel_order = nullptr, int cur_size = 0);
    int get_pi(int u);

    int *get_sorted();
    int *get_last();

    // Print
    void print_data(int *data);
    void print_dtime();
    void print_ftime();
    void print_pi();
    void print_last();

   private:
    int size;
    vector<list<int>> adjacentList;

    // For DFS
    int *color, *dtime, *ftime, *pi;
    int *sorted_arr, *last;
};

#include <cctype>
#include <cstdio>
int hasEOF = 0;
int readchar();
int ReadInt(int *x);
void WriteInt(int x);
void WriteLL(long long int x);
void ReadStr(char *str);

int main() {
    int N, M;
    ReadInt(&N), ReadInt(&M);

    int C[N], D[N], Pi[N], S[N] = {0}, *sorted_arr, *last;
    int dp[N + 1][M + 1] = {0};

    // init graph
    Graph G(N);
    int roots[N], top = -1;
    for (int i = 0; i < N; i++) {
        int parent;
        ReadInt(&parent);

        Pi[i] = parent;

        if (parent == -1) {
            roots[++top] = i;
        } else {
            G.insertEdge(parent, i);
        }
    }

    for (int i = 0; i < N; i++) {
        ReadInt(C + i), ReadInt(D + i);
    }

    G.DFS(roots, top + 1);
    sorted_arr = G.get_sorted();  // index -> num
    last = G.get_last();          // index -> index

    for (int i = 0; i < N; i++) {
        int num = sorted_arr[i];

        S[num] += C[num];
        if (Pi[num] != -1)
            S[Pi[num]] += S[num];
    }

    int flag = 1;
    for (int i = 0; i < N; i++) {
        // i = real index
        int num = sorted_arr[i];

        for (int j = 0; j <= M; j++) {
            char what_case = (j >= C[num] && j >= D[num])
                                 ? 'A'
                             : (j >= C[num])
                                 ? 'B'
                             : (j >= D[num])
                                 ? 'C'
                                 : 'D';
            int res;
            switch (what_case) {
                case 'A':
                    res = max(
                        dp[i][j],
                        max(dp[i][j - C[num]] + C[num],
                            dp[last[i] + 1][j - D[num]] + S[num]));
                    break;
                case 'B':
                    res = max(
                        dp[i][j],
                        dp[i][j - C[num]] + C[num]);
                    break;
                case 'C':
                    res = max(
                        dp[i][j],
                        dp[last[i] + 1][j - D[num]] + S[num]);
                    break;
                case 'D':
                    res = dp[i][j];
                    break;
            }
            dp[i + 1][j] = res;
        }
    }

    // cout << "answer:\n";
    // for (int j = 0; j <= M; j++) {
    //     cout << setw(4) << j << " | ";
    //     for (int i = 0; i <= N; i++) {
    //         cout << setw(4) << dp[i][j];
    //     }
    //     cout << '\n';
    // }

    WriteInt(dp[N][M]);
}

void Graph::insertEdge(int u, int v) {
    adjacentList[u].push_back(v);
}

// For DFS
void Graph::DFS_init() {
    color = new int[size]();
    dtime = new int[size]();
    ftime = new int[size]();
    pi = new int[size];
    for (int u = 0; u < size; u++)
        pi[u] = -1;
}

void Graph::DFS_visit(int u, int &time) {
    // call visit => not visited
    color[u] = 1;
    dtime[u] = ++time;

    // visit every adjacent vertex
    for (int &v : adjacentList[u]) {
        if (color[v] == 0) {
            pi[v] = u;
            DFS_visit(v, time);
        }
    }

    ftime[u] = ++time;
}

void Graph::DFS(int *travel_order, int cur_size) {
    DFS_init();

    if (travel_order == nullptr) {
        cur_size = size;
        travel_order = new int[size];
        for (int i = 0; i < size; i++)
            travel_order[i] = i;
    }

    int time = 0;
    for (int i = 0; i < cur_size; i++) {
        int u = travel_order[i];
        if (color[u] == 0) {
            DFS_visit(u, time);
        }
    }
}

int Graph::get_pi(int u) {
    return pi[u];
}

int *Graph::get_sorted() {
    sorted_arr = new int[size];
    iota(sorted_arr, sorted_arr + size, 0);

    sort(sorted_arr, sorted_arr + size, [&](const int &a, const int &b) {
        return ftime[a] < ftime[b];
    });

    return sorted_arr;
}

int *Graph::get_last() {
    last = new int[size];

    stack<int> S;

    for (int i = 0; i < size; i++) {
        int flag = 0, cur = sorted_arr[i];
        while (!S.empty()) {
            int bef = sorted_arr[S.top()];
            if (dtime[bef] < dtime[cur]) {
                flag = 1;
                last[i] = S.top();
                break;
            }
            S.pop();
        }
        if (!flag) {
            last[i] = -1;
        }
        S.push(i);
    }

    return last;
}

void Graph::print_data(int *data) {
    for (int i = 0; i < size; i++)
        cout << setw(4) << i;
    cout << '\n';
    for (int i = 0; i < size; i++)
        cout << "----";
    cout << '\n';
    for (int i = 0; i < size; i++)
        cout << setw(4) << data[i];
    cout << '\n';
}

void Graph::print_dtime() {
    cout << "Dtime:\n";
    print_data(dtime);
}

void Graph::print_ftime() {
    cout << "Ftime:\n";
    print_data(ftime);
}

void Graph::print_pi() {
    cout << "Pi:\n";
    print_data(pi);
}

void Graph::print_last() {
    cout << "last:\n";
    print_data(last);
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
