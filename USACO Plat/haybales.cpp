#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
using pii = pair<int,int>;
const int maxn = (int)5e5+10;
const int LINF = (int)1e18;

int n, q, a[maxn];
int segTree[maxn*4], lazy[maxn*4], mn[maxn*4];

void prop(int p, int l, int r){
    if(l==r or !lazy[p]) return;
    int mid = (l+r)/2;
    lazy[p*2]+=lazy[p];
    lazy[p*2+1]+=lazy[p];
    segTree[p*2]+=(mid-l+1)*lazy[p];
    segTree[p*2+1]+=(r-mid)*lazy[p];
    mn[p*2]+=lazy[p];
    mn[p*2+1]+=lazy[p];
    lazy[p]=0;
}

void update(int i, int j, int v, int t=0, int p=1, int l=1, int r=n){
    if(i>r or j<l or i>j) return;
    prop(p,l,r);
    if(i<=l and r<=j){
        if(t) segTree[p]=(r-l+1)*v, mn[p]=v, lazy[p]=v;
        else segTree[p]+=(r-l+1)*v, mn[p]+=v, lazy[p]+=v;
        return;
    }
    int mid = (l+r)/2;
    update(i,j,v,t,p*2,l,mid);
    update(i,j,v,t,p*2+1,mid+1,r);
    segTree[p] = segTree[p*2]+segTree[p*2+1];
    mn[p] = min(mn[p*2],mn[p*2+1]);
}

int query(int i, int j, int t, int p=1, int l=1, int r=n){
    if(i>r or j<l or i>j) return t?0:LINF;
    prop(p,l,r);
    if(i<=l and r<=j) return t?segTree[p]:mn[p];
    int mid = (l+r)/2;
    int x = query(i,j,t,p*2,l,mid);
    int y = query(i,j,t,p*2+1,mid+1,r);
    return t?x+y:min(x,y);
}

int32_t main() {
	ifstream cin("haybales.in");
	ofstream cout("haybales.out");
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    fill(mn,mn+4*maxn,LINF);
    for(int i = 1; i <= n; i++) 
		cin >> a[i], update(i,i,a[i],1);
    while(q--){
        char t; int x, y, z; cin >> t >> x >> y;
        if(t=='P') cin >> z, update(x,y,z);
        else cout << query(x,y,t=='S') << "\n";
    }
}
