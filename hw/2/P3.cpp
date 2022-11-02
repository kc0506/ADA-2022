#include <bits/stdc++.h>

using namespace std;

#define lowbit(x) (x&-x)
typedef long long int ll;

void add(int tree[], int index, int N, int d){
    // 令 [index] += d
    for( ; index <= N; index += lowbit(index))
        tree[index] += d;
}

int query(int tree[], int index){
    // 求取 [1, index] 之和
    int sum = 0;
    for( ; index > 0; index -= lowbit(index))
        sum += tree[index];
    return sum;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);

    string s;
    ll k;
    cin >> s >> k;

    int n = s.size();

    // 窮舉會出現的字元
    const int D_size = 10 + 26 + 26;
    array<char, D_size> D;
    unordered_map<char, int> Order;  // start from 1
    int cur = 0;
    for(int i=0; i<10; i++)
        D[cur++] = i + '0', Order[i + '0'] = cur;
    for(int i='A'; i<='Z'; i++)
        D[cur++] = i, Order[i] = cur;
    for(int i='a'; i<='z'; i++)
        D[cur++] = i, Order[i] = cur;

    // P[i] = s[0, i-1] 中比 s[i] 大的字元數量
    int tree[3 * D_size] = {0}, P[n];
    for(int i=0; i<n; i++){
        P[i] = query(tree, Order[s[i]]);
        add(tree, Order[s[i]], D_size, 1);
    }

    unordered_map<char, list<int>> M;
    for(int i=0; i<n; i++)
        M[s[i]].push_back(i);

    string res = "";
    int st = 0;
    while(k > 0 && st < n){
        int it = 0;
        while(it < D_size){
            char c = D[it];
            if(M[c].empty())
                continue;
            else 
                ++it;
            
            int index = M[c].front();
            int swap_times = P[index];

            if(k >= swap_times){
                s[index] = '#';
                res.push_back(c);
                M[c].pop_front();
                k -= swap_times;
                break;
            }
        }
    }

    cout << res;
    for(auto &c: s)
        if(c != '#')
            cout << c;
}
