#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)2e5+10;
const int INF = (int)1e9+10;
int n, q, a[mxN];
 
struct Vertex{
    int l, r, lazy, sum=0;
    Vertex *le, *ri;
 
    Vertex(int l, int r):l(l),r(r){
        le=ri=nullptr; lazy=INF;
    }
 
    ~Vertex(){
        delete le;
        delete ri;
    }
 
    void extend(){
        if(!le and l!=r){
            int m = (l+r)/2;
            le=new Vertex(l,m);
            ri=new Vertex(m+1,r);
        }
    }
 
    void prop(){
        if(l==r or lazy==INF) return;
        int m = (l+r)/2;
        if(!le) return;
        le->lazy = lazy;
        ri->lazy = lazy;
        le->sum = (m-l+1)*lazy;
        ri->sum = (r-m)*lazy;
        lazy=INF;
    }
 
    void upd(int i, int j, int v){
        if(i>r or j<l or i>j) return;
        if(i<=l and r<=j){
            sum = v*(r-l+1); lazy = v;
            return;
        }
        extend(); prop();
        int m = (l+r)/2;
        if(i<=m) le->upd(i,j,v);
        if(m<j) ri->upd(i,j,v);
        sum=le->sum+ri->sum;
    }
 
    int query(int i, int j){
        if(i>r or j<l or i>j) return 0;
        if(i<=l and r<=j) return sum;
        extend(); prop();
        int m = (l+r)/2;
        int sum = 0;
        if(i<=m) sum+=le->query(i,j);
        if(m<j) sum+=ri->query(i,j);
        return sum;
    }
 
};
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> q; int c = 0; Vertex Root(1,INF);
    while(q--){
        int t, x, y; cin >> t >> x >> y; x+=c, y+=c;
        if(t==1){ c = Root.query(x,y); cout << c << "\n"; }
        else Root.upd(x,y,1);
    }
}
