#include <bits/stdc++.h>

using namespace std;

struct node
{
    node *left, *right, *p;
    int f;
};

struct cmp
{
    bool operator()(node *a, node *b)
    {
        return a->f > b->f;
    }
};

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    int N;
    cin >> N;

    int F[N];
    for (auto &i : F)
        cin >> i;

    if (N == 1)
    {
        cout << '0';
        return 0;
    }

    priority_queue<node *, vector<node *>, cmp> H;
    node *nodes = new node[N];
    for (int i = 0; i < N; i++)
    {
        nodes[i].f = F[i];
        nodes[i].p = nullptr;
        H.push(&(nodes[i]));
    }

    for (int i = 1; i < N; i++)
    {
        node *z = new node, *x, *y;
        x = H.top();
        H.pop();
        y = H.top();
        H.pop();

        x->p = z;
        y->p = z;
        z->left = x;
        z->right = y;
        z->p = nullptr;
        z->f = x->f + y->f;
        H.emplace(z);
    }

    for (int i = 0; i < N; i++)
    {
        node *cur = nodes + i;
        string res = "";
        while (cur->p)
        {
            if (cur == cur->p->left)
            {
                res = '0' + res;
            }
            else
            {
                res = '1' + res;
            }
            cur = cur->p;
        }
        cout << res << '\n';
    }
}
