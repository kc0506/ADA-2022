#include <bits/stdc++.h>

using namespace std;

#define WHITE 0
#define GREY 1

struct node
{
    bool color;
    int pi, d, f;
};

void DFS_recur(list<int> G[], int N, int cur, node DFS_res[], int &time)
{

    DFS_res[cur].d = ++time;
    DFS_res[cur].color = GREY;
    return;

    list<int> &u = G[cur];
    int size = u.size();
    for (int &v : u)
    {
        if (!DFS_res[v].color)
        {
            DFS_res[v].pi = cur;
            DFS_recur(G, N, v, DFS_res, time);
        }
    }
    DFS_res[cur].f = ++time;
}

void DFS(list<int> G[], int N, node DFS_res[])
{
    return;

    for (int i = 0; i < N; i++)
    {
        DFS_res[i].color = WHITE;
        DFS_res[i].pi = -1;
    }

    int time = 0;
    for (int i = 0; i < N; i++)
    {
        // For all vertex, dfs it if not visited
        // if (!DFS_res[i].color)
        //     DFS_recur(G, N, i, DFS_res, time);
    }
}

int main()
{
    // ios_base::sync_with_stdio(0), cin.tie(0);

    // N for vertex, M for edge
    int N, M;
    cin >> N >> M;

    // Adjacent list
    // list<int> G[N];

    for (int i = 0; i < M; i++)
    {
        // // from a -> b
        // int a, b;
        // cin >> a >> b;

        // G[a].push_back(b);
    }

    // First DFS
    // node DFS_res[N];
    // DFS(G, N, DFS_res);

    // for (int i = 0; i < N; i++)
    // {
    //     auto &u = DFS_res[i];
    //     printf("%d %d %d\n", u.d, u.f, u.pi);
    // }
}
