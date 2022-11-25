#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

class Graph
{
public:
    Graph() : size(0){};
    Graph(int n) : size(n) { adjacentList.resize(n); };

    void insertEdge(int u, int v)
    {
        adjacentList[u].push_back(v);
    }

    // For DFS
    void DFS_init()
    {
        color = new int[size]();
        dtime = new int[size]();
        ftime = new int[size]();
        pi = new int[size];
        for (int u = 0; u < size; u++)
            pi[u] = -1;
    }

    void DFS_visit(int u, int &time)
    {
        // call visit => not visited
        color[u] = 1;
        dtime[u] = ++time;

        // visit every adjacent vertex
        for (int &v : adjacentList[u])
        {
            if (color[v] == 0)
            {
                pi[v] = u;
                DFS_visit(v, time);
            }
        }

        ftime[u] = ++time;
    }

    void DFS(int *travel_order = nullptr)
    {
        DFS_init();

        if (travel_order == nullptr)
        {
            travel_order = new int[size];
            for (int i = 0; i < size; i++)
                travel_order[i] = i;
        }

        int time = 0;
        for (int i = 0; i < size; i++)
        {
            int u = travel_order[i];
            if (color[u] == 0)
            {
                DFS_visit(u, time);
            }
        }
    }

    int path_compression_recur(int u)
    {
        if (pi[u] == -1)
            return u;
        return pi[u] = path_compression_recur(pi[u]);
    }

    void path_compression()
    {
        for (int i = 0; i < size; i++)
        {
            path_compression_recur(i);
        }
    }

    // For SCC
    int get_pi(int u)
    {
        return pi[u];
    }

    void getTranspose()
    {
        GT = new Graph(size);
        for (int u = 0; u < size; u++)
        {
            for (auto &v : adjacentList[u])
                GT->insertEdge(v, u);
        }
    }

    ll SCC()
    {
        // 1st DFS - G
        DFS();

        // transpose
        getTranspose();

        // sort by larger ftime
        int travel_order[size];
        for (int i = 0; i < size; i++)
            travel_order[i] = i;
        sort(travel_order, travel_order + size, [&](int a, int b)
             { return ftime[a] > ftime[b]; });

        // 2nd DFS - GT
        GT->DFS(travel_order);

        // Path compression
        GT->path_compression();

        // Count SCC size
        int count[size] = {0};
        ll connected_pairs_count = 0;
        for (int i = 0; i < size; i++)
        {
            int root = GT->get_pi(i) == -1 ? i : GT->get_pi(i);
            connected_pairs_count += count[root]++;
        }

        return connected_pairs_count;
    }

    // Print
    void print_data(int *data)
    {
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

    void print_dtime()
    {
        cout << "Dtime:\n";
        print_data(dtime);
    }

    void print_ftime()
    {
        cout << "Ftime:\n";
        print_data(ftime);
    }

    void print_pi()
    {
        cout << "Pi:\n";
        print_data(pi);
    }

private:
    int size;
    vector<list<int>> adjacentList;

    // For DFS
    int *color, *dtime, *ftime, *pi;

    // For SCC
    Graph *GT;
};

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N, M;
    cin >> N >> M;

    Graph G(N);

    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        G.insertEdge(u - 1, v - 1);
    }

    G.DFS();

    cout << G.SCC();
}
