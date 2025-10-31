/*
1D Segment Tree
Supports point update, range Max/Min queries
*/

template<class T, int SZ>
struct MaxSegTree1D{
    T seg[SZ*2];
    T MIN = numeric_limits<T>::lowest();

    void init(){
        for(int i = 0; i < SZ*2; i++) seg[i]=MIN;
    }

    void upd(int x, T v, int p=0, int l=0, int r=SZ-1){
        if(l==r){ seg[p] = v; return; }
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        if(x<=mid) upd(x,v,p+1,l,mid);
        else upd(x,v,rp,mid+1,r);
        seg[p] = max(seg[p+1], seg[rp]);
    }

    int query(int i, int j, int p=0, int l=0, int r=SZ-1){
        if(i>r or j<l or i>j) return MIN;
        if(i<=l and r<=j) return seg[p];
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        return max(query(i,j,p+1,l,mid),query(i,j,rp,mid+1,r));
    }

};
