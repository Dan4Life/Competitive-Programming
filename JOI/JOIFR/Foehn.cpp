#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define int long long
#define all(a) a.begin(),a.end()
using pii = pair<int,int>;
const int mxN = (int)2e5+10;
const int LINF = (int)1e8;
int n, q, x, y, S, T;
int a[mxN], fenwick[mxN];
 
void upd(int x, int v){
    for(; x<mxN; x+=x&-x) fenwick[x]+=v;
}
 
int pos(int x){
    if(!x) return 0;
    int s=0;
    for(;x>0;x-=x&-x) s+=fenwick[x];
    return s;
}
 
void f(int ind, int v){
    if(ind==n+1) return;
    int A = pos(ind-1), B = pos(ind);
    if(A<B) x+=v*(B-A);
    else y+=v*(A-B);
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q >> S >> T >> a[0];
    for(int i = 1; i <= n; i++)
        cin >> a[i], upd(i,a[i]), upd(i+1,-a[i]), f(i,1);
    while(q--){
        int l, r, xx; cin >> l >> r >> xx;
        f(l,-1), f(r+1,-1);
        upd(l,xx), upd(r+1,-xx);
        f(l,1), f(r+1,1);
        cout << y*T-x*S << "\n";
    }
}
