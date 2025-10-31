/*
Basic DSU
Supports findSet, sameSet, findSz, unionSet, count ccs.
*/

template<int SZ>
struct DSU{
    int p[SZ+1], sz[SZ+1], cc;

    void init(int n=SZ, bool zero=0){
        cc = 0;
        for(int i = 1-zero; i <= n-zero; i++) 
            p[i]=i, sz[i]=1, cc++;
    }

    int findSet(int i){
        return i==p[i]?i:p[i]=findSet(p[i]);
    }

    bool isSameSet(int i, int j){
        return findSet(i)==findSet(j);
    }

    int findSz(int i){ return sz[findSet(i)]; }

    void unionSet(int i, int j){
        int x = findSet(i), y = findSet(j);
        if(x==y) return;
        if(sz[x]<sz[y])swap(x,y);
        p[y] = x, sz[x]+=sz[y]; cc--;
    }
};
