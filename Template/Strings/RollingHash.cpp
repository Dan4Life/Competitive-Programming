/*
Uses rabin karp rolling hash
Unhackable with 2 MODs and random base :)
*/

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
const ll HASH_BASE = uniform_int_distribution<ll>(256,1000000000)(rng);

template<int MOD> struct RollingHash{
    vi base, hash;

    RollingHash(const string &s): base(sz(s)+1), hash(sz(s)+1){
        base[0] = 1;
        for(int i = 0; i < sz(s); i++){
            base[i+1] = base[i]*HASH_BASE%MOD;
            hash[i+1] = (hash[i]*HASH_BASE+(unsigned char)s[i]+1)%MOD;
        }
    }

    ll get(int l, int r){ return (hash[r+1]-hash[l]*base[r-l+1]%MOD+MOD)%MOD; }

    ll compute_hash(const string &s){
        ll h = 0;
        for(unsigned char c:s) h = (h*HASH_BASE+c+1)%MOD;
        return h;
    }
};

RollingHash<(int)1e9+7> hash1;
RollingHash<(int)1e9+9> hash2;
