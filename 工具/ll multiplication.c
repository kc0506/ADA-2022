
typedef long long int ll;

ll product(ll a, ll b){
    ll res = 0;
    while(a > 0){
        if(a & 1)
            res += b;
        a = a >> 1;
        b = b << 1;
    }
    return res;
}
