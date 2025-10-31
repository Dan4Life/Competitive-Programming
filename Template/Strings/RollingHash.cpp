/*
Uses rabin karp rolling hash
Unhackable with 2 MODs and random base :)
*/

template<int _MOD, int SZ> struct RollingHash{
    const int MOD = _MOD;
    bool hasInit = 0;
    ll n, b, base[SZ+1], hash[SZ+1]; 
    
    void init(string s, ll B=-1){
        hasInit = 1; n = sz(s);
        mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
        b = (B==-1?uniform_int_distribution<ll>(MOD/5,MOD/2)(rng):B);
        base[0] = 1; hash[0] = 0;
        for(int i = 1; i <= n; i++)
            base[i]=(base[i-1]*b)%MOD;
        for(int i = 0; i < n; i++)
            hash[i+1]=(hash[i]*b+s[i]-'a'+1)%MOD;
    }

    ll compute_hash(string t){
        assert(hasInit);
        ll h = 0;
        for(int i = 0; i < sz(t); i++)
            h*=b, h+=t[i]-'a'+1, h%=MOD;
        return h;
    }

    ll get(int l, int r){
        return (hash[r+1]-((hash[l]*base[r-l+1])%MOD)+MOD)%MOD;
    }
};
RollingHash<(int)1e9+7,(int)2e5+10> hash1;
RollingHash<(int)1e9+9,(int)2e5+10> hash2;
