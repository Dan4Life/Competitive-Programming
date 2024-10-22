#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
const int mxN = (int)2e5+10;
const int mxLg = 20;
int n, k;
vector<int> v;
int L[mxN], R[mxN];
int jmp[mxLg][mxN*2];
set<pair<int,int>> cur;

int get(int l, int r){
    int tot = 0;
    for(int i = mxLg-1; i>=0; i--)
        if(jmp[i][l]<=r) l=jmp[i][l], tot+=(1<<i);
    return tot;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> L[i] >> R[i], v.pb(L[i]), v.pb(R[i]);
    sort(all(v)); v.erase(unique(all(v)),end(v));
    for(int i = 0; i <= sz(v); i++) jmp[0][i]=sz(v);
    for(int i = 1; i <= n; i++){
        L[i] = lower_bound(all(v),L[i])-begin(v);
        R[i] = lower_bound(all(v),R[i])-begin(v);
        jmp[0][L[i]] = min(jmp[0][L[i]],R[i]);
    }
    for(int i = sz(v)-1; i>=0; i--)
        jmp[0][i]=min(jmp[0][i],jmp[0][i+1]);
    for(int i = 1; i < mxLg; i++)
        for(int j = 0; j <= sz(v); j++)
            jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    int tot = get(0,sz(v)-1); int k = tot; cout << k << "\n";
    cur.insert({0,0}), cur.insert({sz(v)-1,sz(v)-1});
    for(int i = 1; i <= n; i++){
        int l = prev(cur.lower_bound({R[i],0}))->se;
        int r = cur.lower_bound({R[i],0})->fi;
        if(L[i]<l) continue;
        int num = tot-get(l,r)+get(l,L[i])+get(R[i],r)+1;
        if(num>=k){
            cout << i << " "; tot=num;
            cur.insert({L[i],R[i]});
            if(sz(cur)==k+2) break;
        }
    }
}
