#include <bits/stdc++.h>

using namespace std;

#define WHITE 0
#define GREY 1

typedef long long int ll;

struct node
{
    bool color;
    int pi, d, f;
};

void DFS_recur(vector<vector<int>> &G, int cur, node DFS_res[], int &time)
{

    DFS_res[cur].d = ++time;
    DFS_res[cur].color = GREY;

    vector<int> &u = G[cur];
    int size = u.size();
    for (int &v : u)
    {
        if (DFS_res[v].color == WHITE)
        {
            DFS_res[v].pi = cur;
            DFS_recur(G, v, DFS_res, time);
        }
    }
    DFS_res[cur].f = ++time;
}

void DFS(vector<vector<int>> &G, int N, node DFS_res[])
{
    for (int i = 1; i <= N; i++)
    {
        DFS_res[i].color = WHITE;
        DFS_res[i].pi = -1;
    }

    int time = 0;
    for (int i = 1; i <= N; i++)
    {
        // For all vertex, dfs it if not visited
        if (!DFS_res[i].color)
            DFS_recur(G, i, DFS_res, time);
    }
}

int compression(int cur, node DFS_res[])
{
    if (DFS_res[cur].pi == -1)
        return cur;

    return DFS_res[cur].pi = compression(DFS_res[cur].pi, DFS_res);
}

int main()
{
    // ios_base::sync_with_stdio(0), cin.tie(0);

    // N for vertex, M for edge
    int N, M;
    cin >> N >> M;

    // Adjacent list
    vector<vector<int>> G(N + 1, vector<int>());

    for (int i = 0; i < M; i++)
    {
        // from a -> b
        int a, b;
        cin >> a >> b;

        if (a != b)
            G[a].push_back(b);
    }

    // First DFS
    node first_res[N + 1];
    DFS(G, N, first_res);

    // for (int i = 1; i <= N; i++)
    // {
    //     auto &u = first_res[i];
    //     cout << u.d << ' ' << u.f << ' ' << u.pi << '\n';
    // }

    // Transpose G
    vector<vector<int>> G_T(N + 1, vector<int>());
    for (int i = 1; i <= N; i++)
    {
        for (auto &v : G[i])
        {
            G_T[v].push_back(i);
        }
    }

    // Sort in order of final
    int V[N];
    for (int i = 0; i < N; i++)
    {
        V[i] = i + 1;
    }

    sort(V, V + N, [&](int a, int b)
         { return first_res[a].f > first_res[b].f; });

    // cout << "Sorted by final: (big first): \n";
    // for (int i = 0; i < N; i++)
    //     cout << V[i] << '\n';

    // Second DFS
    node second_res[N + 1];
    // DFS(G_T, N, second_res);
    {
        for (int i = 1; i <= N; i++)
        {
            second_res[i].color = WHITE;
            second_res[i].pi = -1;
        }

        int time = 0;
        for (int i = 0; i < N; i++)
        {
            int cur = V[i];
            // For all vertex, dfs it if not visited
            if (!second_res[cur].color)
                DFS_recur(G_T, i, second_res, time);
        }
    }

    // Output

    for (int i = 1; i <= N; i++)
    {
        compression(i, second_res);
    }

    int size_count[N + 1] = {0};

    for (int i = 1; i <= N; i++)
    {
        if (second_res[i].pi != -1)
            size_count[second_res[i].pi]++;
        else
            size_count[i]++;
    }

    // for (int i = 1; i <= N; i++)
    // {
    //     auto &u = second_res[i];
    //     cout << u.d << ' ' << u.f << ' ' << u.pi << '\n';
    // }

    int count_SCC = count_if(size_count + 1, size_count + N + 1, [](int x)
                             { return x != 0; });
    // cout << "# of SCC: " << count_SCC << '\n';

    ll res = 0;
    for_each(size_count + 1, size_count + N + 1, [&](int x)
             { res += (ll)x * (x - 1) / 2; });
    cout << res;
}
