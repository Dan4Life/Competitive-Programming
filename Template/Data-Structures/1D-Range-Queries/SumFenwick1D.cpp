/*
Supports point update, range query
To add: Binary search on Fenwick
*/

template<class T, int SZ>
struct SumFenwick1D{
    T fen[SZ+1];
    int offset;

    void init(int n=SZ, int off=0){
        offset = off;
        for(int i = 1; i <= n; i++) fen[i]=0;
    }

    void upd(int x, T v){
        for(x+=offset; x<=SZ; x+=x&-x)
            fen[x]+=v;
    }

    T sum(int x){
        T s(0);
        for(x+=offset; x>0; x-=x&-x)
            s+=fen[x];
        return s;
    }

    T sum(int l, int r){
        return l>r?T(0):sum(r)-sum(l-1);
    }
};
