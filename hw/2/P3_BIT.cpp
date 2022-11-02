#include <bits/stdc++.h>

using namespace std;

#define lowbit(x) (x&-x)
typedef long long int ll;

void add(int tree[], int index, int N, int d){
    for( ; index <= N; index += lowbit(index))
        tree[index] += d;
}

void update(int tree[], int index, int N){
    // 使 [1, index] ++ 
    // => 差分之後：
    // 使 1 ++，index + 1 --
    add(tree, 1, N, 1);
    add(tree, index + 1, N, -1);
}

int query(int tree[], int index){
    // 求取 index 之 shift 值
    // => 差分之後：
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
    int tree[3 * n] = {0};

    vector<char> D;
    for(int i=0; i<10; i++)
        D.push_back(i + '0');
    for(int i='A'; i<='Z'; i++)
        D.push_back(i);
    for(int i='a'; i<='z'; i++)
        D.push_back(i);

    unordered_map<char, list<int>> M;
    for(int i=0; i<n; i++)
        M[s[i]].push_back(i);

    string res = "";
    int st = 0;
    while(k > 0 && st < n){
        for(auto &c: D){
            if(M[c].empty())
                continue;
            int index = M[c].front();
            int new_index = index + query(tree, index + 1);

            if(k >= new_index - st){
                update(tree, index + 1, n);
                s[index] = '#';
                res.push_back(c);
                M[c].pop_front();
                k -= new_index - st;
                ++st;
                break;
            }
        }
    }

    cout << res;
    for(auto &c: s)
        if(c != '#')
            cout << c;
}
