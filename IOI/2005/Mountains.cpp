#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define all(a) a.begin(), a.end()

const int maxn = 200010;
const ll LINF = 4e18;

int N, n=0, q=0, a[maxn], b[maxn], d[maxn], pos[2*maxn], lazy[4*maxn], segTree[4*maxn], mx[4*maxn];
unordered_map<int, int> ind;
char t[maxn];

void propagate(int p, int l, int r){
    if(l+1>=r or lazy[p]==LINF) return;
    lazy[p*2]=lazy[p*2+1]=lazy[p];
    int mid = (l+r)/2;
    segTree[p*2]= lazy[p]*(pos[mid]-pos[l]);
    segTree[p*2+1]= lazy[p]*(pos[r]-pos[mid]);
    mx[p*2] = max(0ll, segTree[p*2]);
    mx[p*2+1] = max(0ll, segTree[p*2+1]);
    lazy[p] = LINF;
}

int query(int i, int j, int p=1, int l=0, int r=n-1){
    if(i>=r or j<=l or i>=j) return 0ll; propagate(p,l,r);
    if(i<=l and r<=j) return segTree[p];
    int mid = (l+r)/2;
    return query(i,j,p*2,l,mid)+query(i,j,p*2+1,mid,r);
}

void update(int i, int j, int v, int p=1, int l=0, int r=n-1){
    if(i>=r or j<=l or i>=j) return; propagate(p,l,r);
    if(i<=l and r<=j){
        lazy[p]=v; segTree[p]=v*(pos[r]-pos[l]);
        mx[p] = max(0ll, segTree[p]); return;
    }
    int mid = (l+r)/2;
    update(i,j,v,p*2,l,mid);
    update(i,j,v,p*2+1,mid,r);
    segTree[p] = segTree[p*2]+segTree[p*2+1];
    mx[p] = max(mx[p*2], segTree[p*2]+mx[p*2+1]);
}

int query2(int i, int j, int v, int p=1, int l=0, int r=n-1){
    if(i>=r or j<=l or i>=j) return 0ll; propagate(p,l,r);
    if(l==r-1) return (v>=segTree[p]?r:l); int mid = (l+r)/2;
    if(mx[p*2]<=v) return query2(i,j,v-segTree[p*2],p*2+1,mid,r);
    else return query2(i,j,v,p*2,l,mid);
}

int32_t  main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N; vector<int> v; v.pb(0); v.pb(N);
    while(1){
        cin >> t[q];
        if(t[q]=='I') { cin >> a[q] >> b[q] >> d[q]; a[q]--; v.pb(a[q]); v.pb(b[q]); }
        else if(t[q]=='Q') cin >> a[q];
        else if(t[q]=='E') break; q++;
    }
    sort(all(v)); v.erase(unique(all(v)), v.end());
    for(auto u : v) ind[u] = n, pos[n]=u, n++;
    fill(lazy, lazy+maxn*4, LINF);
    fill(segTree, segTree+maxn*4, 0ll);
    fill(mx, mx+maxn*4, 0ll);
    for(int i = 0; i < q; i++){
        if(t[i]=='I') update(ind[a[i]],ind[b[i]],d[i]);
        else{
            int P = query2(0,n-1,a[i]);
            int rem = a[i]-query(0,P), y = 0;
            if(P!=n-1) y = query(P,P+1)/(pos[P+1]-pos[P]);
            cout << pos[P]+(y>0?rem/y:0ll) << "\n";
        }
    }
}
