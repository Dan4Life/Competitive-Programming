#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int maxn = (int)2e5+10;
const int LINF = (int)1e18;

int n, x, y, q;
vector<int> ind[maxn];
int nxt[maxn][20], tmp[maxn][20];
struct query{ int l,r,ind; } Q[maxn];
int a[maxn], ans[maxn], fenwick[maxn];

void upd(int x, int v){ for(; x < maxn; x+=(x&-x)) fenwick[x]+=v; }
int sum(int x){ int ans = 0; for(; x > 0; x-=(x&-x)) ans+=fenwick[x]; return ans; }

void add(int pos){
    for(int i = 0; i < 18; i++){
        int sub = pos%(1<<i), nxx = nxt[pos][i];
        if(nxx and (!tmp[sub][i] or tmp[sub][i]>nxx)){
            if(tmp[sub][i]) upd(tmp[sub][i],-1);
            tmp[sub][i]=nxx, upd(nxx,1);
        }
    }    
}

int32_t main()
{
    cin >> n >> x >> y;
    for(int i = 1; i <= n; i++) cin >> a[i], ind[a[i]].pb(i);
    
    for(int i = n; i >= 1; i--){
        reverse(ind[i].begin(),ind[i].end());
        for(int j = 0; j < 18; j++){
            for(auto pos : ind[i]){
                int sub = pos%(1<<j);
                nxt[pos][j] = tmp[sub][j];
                tmp[sub][j] = pos;
            }
        }
        for(int j = 0; j < 18; j++)
            for(auto pos : ind[i])
                tmp[pos%(1<<j)][j]=0;
    }
    
    cin >> q; int cur = n;
    for(int i = 0; i < q; i++) cin >> Q[i].l >> Q[i].r, Q[i].ind=i;
    sort(Q,Q+q,[&](query a, query b){ return a.l>b.l; }); 
    for(int i = 0; i < q; i++){
        while(cur>=Q[i].l) add(cur--);
        ans[Q[i].ind] = sum(Q[i].r);
    }
    for(int i = 0; i < q; i++) cout << ans[i]*(x+y)+x << "\n";
}
