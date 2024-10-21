#include "scales.h"
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
 
using vi = vector<int>;
using ar5 = array<int,5>;
map<vector<vi>,ar5> mem;
int ans[6], lim[] = {243,81,27,9,3,1};
 
int which(vector<int> v, int a, int b, int c, int d, int t) {
    vector<int> ord; ord.clear();
    for(auto i : v) if(i==a or i==b or i==c or i==d) ord.pb(i);
    if(t<=2) return ord[t];
    if(ord[0]==d) return ord[1];
    if(ord[1]==d) return ord[2];
    if(ord[2]==d) return ord[3];
    if(ord[3]==d) return ord[0];
}
 
int get(int a, int b, int c, int d, int t) {
    if(t==0) return getLightest(a,b,c);
    if(t==1) return getMedian(a,b,c);
    if(t==2) return getHeaviest(a,b,c);
    return getNextLightest(a,b,c,d);
}
 
bool recur(vector<vi> possible, int dep=0){
    if(sz(possible)<=1) return 1;
    for(int i = 1; i <= 6; i++){
        for(int j = i+1; j <= 6; j++){
            for(int k = j+1; k <= 6; k++){
                for(int t = 0; t < 4; t++){
                    for(int l = 1; l <= 7; l++){
                        if(l==i or l==j or l==k) continue;
                        if(t!=3 and l!=7) continue;
                        if(t==3 and l==7) continue;
                        vector<vi> chose[7]; int mx=0;
                        for(int _=1;_<=6; _++) chose[_].clear();
                        for(auto v : possible) chose[which(v,i,j,k,l,t)].pb(v);
                        for(int _=1;_<=6; _++) mx=max(mx, sz(chose[_]));
                        if(mx<=lim[dep] and recur(chose[i],dep+1)){
                            if(recur(chose[j],dep+1) and recur(chose[k],dep+1)){
                                mem[possible]={i,j,k,l,t}; return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
 
void dfs(vector<vi> tot){
    if(sz(tot)==1){
        for(int i = 0; i < 6; i++) ans[i]=tot[0][i];
        return;
    }
    auto [a,b,c,d,t] = mem[tot];
    vector<vi> chose[7];
    for(int _=1;_<=6; _++) chose[_].clear();
    for(auto v : tot) chose[which(v,a,b,c,d,t)].pb(v);
    dfs(chose[get(a,b,c,d,t)]);
}
 
vector<vi> possible;
void init(int T) {
    vi v {1,2,3,4,5,6};
    do possible.pb(v);
    while(next_permutation(all(v)));
    recur(possible);
}
 
void orderCoins(){ dfs(possible); answer(ans); }
