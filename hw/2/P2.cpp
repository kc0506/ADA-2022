#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

struct cust{
    int cook, eat;
};

struct group{
    int size;
    ll cook, eat;
};

ll leave_time(vector<cust> &A){
    // 吃最慢的排最前
    auto cmp = [](cust &a, cust &b) {
        return a.eat > b.eat;
    };
    sort(A.begin(), A.end(), cmp);

    ll res = 0, chef = 0;
    for(auto &c: A){
        res = max(res, chef + c.cook + c.eat);
        chef += c.cook;
    }
    return res;
}

ll cook_time(vector<cust> &A){
    ll sum = 0;
    for_each(A.begin(), A.end(), [&](cust c){
        sum += c.cook;
    });
    return sum;
}

void print_A(vector<vector<cust>> &A){
    for(auto &v: A){
        for(auto &c: v)
            cout << c.cook << ' ' << c.eat << ' ';
        cout << '\n';
    }
}

group to_group(vector<cust> &A){
    group g;
    g.cook = cook_time(A);
    g.eat = leave_time(A) - g.cook;
    g.size = A.size();
    return g;
}

int main(){
    // ios_base::sync_with_stdio(0), cin.tie(0);

    int N;
    cin >> N;
    
    vector<vector<cust>> A;
    for(int i=0; i<N; i++){
        int m;
        cin >> m;
        
        vector<cust> v(m);
        for(auto &j: v)
            cin >> j.cook >> j.eat;
        A.push_back(v);
    }

    group G[N];
    transform(A.begin(), A.end(), G, to_group);

    auto cmp = [](group a, group b){
        return (ll) a.size * b.cook - (ll) a.cook * b.size > 0;
    };
    sort(G, G + N, cmp);

    ll sum = 0, preSum = 0;
    for(auto &i: G){
        preSum += i.cook;
        sum += i.size * (preSum + i.eat);
    }
    cout << sum;
}
