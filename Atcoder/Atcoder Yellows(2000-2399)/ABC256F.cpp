/*
Solved by myself
Similar to CSES Polynomial Queries
This is the only yellow I solved a long time ago so I can't really explain :/
*/

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
const int MOD =  998244353;
const ll LINF = 1e18;

int n, q, a[maxn], segTree[maxn*4], segTree2[maxn*4], lazy[maxn*4];
bool LAZY[maxn*4];
int addd(int l, int r){ return ((r*(r+1))/2 - (l*(l-1))/2+MOD)%MOD; }

void propagate(int p, int l, int r){
    int mid = (l+r)/2;
    if(lazy[p] and l!=r){
        lazy[p*2]+=lazy[p], lazy[p*2]%=MOD;
        lazy[p*2+1]+=lazy[p], lazy[p*2+1]%=MOD;
        segTree[p*2]+=lazy[p]*(mid-l+1), segTree[p*2]%=MOD;
        segTree[p*2+1]+=lazy[p]*(r-mid), segTree[p*2+1]%=MOD;
        segTree2[p*2]+=lazy[p]*addd(l,mid), segTree2[p*2]%=MOD;
        segTree2[p*2+1]+=lazy[p]*addd(mid+1,r), segTree2[p*2+1]%=MOD;
        lazy[p]=0;
    }
}

int query(int i, int j, int segTree[], int p = 1, int l = 1, int r = n){
    if(i>r or j<l or i>j) return 0ll; propagate(p,l,r);
    if(i<=l and r<=j) return segTree[p];
    int mid = (l+r)/2;
    return (query(i,j,segTree,p*2,l,mid)+query(i,j,segTree,p*2+1,mid+1,r))%MOD;
}

void update(int i, int j, int v, int p = 1, int l = 1, int r = n){
    if(i>r or j<l or i>j) return; propagate(p,l,r);
    if(i<=l and r<=j) {
        segTree[p]+=(v*(r-l+1))%MOD; segTree[p]%=MOD;
        segTree2[p]+=(v*addd(l,r))%MOD; segTree2[p]%=MOD;
        lazy[p]=v%MOD; return;
    }
    int mid = (l+r)/2;
    update(i,j,v,p*2,l,mid); update(i,j,v,p*2+1,mid+1,r);
    segTree[p] = (segTree[p*2]+segTree[p*2+1])%MOD;
    segTree2[p] = (segTree2[p*2]+segTree2[p*2+1])%MOD;
}

int sum(int i){ return ((i+1)*query(1,i,segTree)-query(1,i,segTree2)+MOD)%MOD; }

int query2(int l, int r){ return (sum(r)-sum(l-1)+MOD)%MOD; }

int32_t  main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q; a[0] = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i]; update(i,n,a[i]);
    }
    while(q--){
        int t, l, r; cin >> t >> l;
        if(t==1){
            cin >> r; int dif = r-a[l];
            a[l]=r, update(l,n,dif);
        }
        else cout << query2(1,l) << '\n';
    }
}
