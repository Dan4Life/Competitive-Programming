#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mxN = (int)1e5+10;
ll n, ans;
array<int,2> a[mxN];

template<int SZ>
struct LazySegTree{
    ll lz[SZ*2];
    void init(){ memset(lz,0,sizeof(lz)); }
    void apply(int p, ll v){ lz[p]+=v; }
    void prop(int p, int l, int r){
        if(!lz[p] or l==r) return;
        apply(p+2*((l+r)/2-l+1),lz[p]); 
        apply(p+1,lz[p]); lz[p]=0;
    }
    
    void upd(int i, int j, ll v, int p=0, int l=0, int r=SZ-1){
        if(i>r or j<l or i>j) return; prop(p,l,r);
        if(i<=l and r<=j) { apply(p,v); return; }
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        upd(i,j,v,p+1,l,mid); upd(i,j,v,rp,mid+1,r);
    }
    
    ll query(int x, int p=0, int l=0, int r=SZ-1){
        if(l==r) return lz[p]; prop(p,l,r);
        int mid = (l+r)/2; int rp = p+2*(mid-l+1);
        if(x<=mid) return query(x,p+1,l,mid);
        return query(x,rp,mid+1,r);
    }
};

LazySegTree<mxN> seg;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; seg.init();
    for(int i = 0; i < n; i++) 
        cin >> a[i][0] >> a[i][1];
    sort(a,a+n);
    for(int i = 0; i < n; i++){
        auto [h,k] = a[i];
        ll b = seg.query(h-k);
        int l = 0, r = h-k;
        while(l<r){
            int mid = (l+r)/2;
            if(seg.query(mid)==b) r=mid;
            else l=mid+1;
        }
        int x = l;
        l = h-k+1, r = h;
        while(l<r){
            int mid = (l+r)/2;
            if(seg.query(mid)==b) l=mid+1;
            else r=mid;
        }
        seg.upd(l,h-1,1); k-=h-l;
        if(k) seg.upd(x,x+k-1,1);
    }
    for(int i = 0; i < mxN; i++){
        ll x = seg.query(i); ans+=x*(x-1)/2;
    }
    cout << ans << "\n";
}
