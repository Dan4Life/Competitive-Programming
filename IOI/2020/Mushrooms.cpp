#include "mushrooms.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
 
int U(vector<int> v){ return use_machine(v); }
const int B = 100;
vector<int> V[2];
 
int count_mushrooms(int n) {
    int ans = 1, i=1, P;
    if(n<=200){
        for(int i = 1; i < n; i++) 
            ans+=!U({0,i});
        return ans;
    }
    V[0].clear(), V[1].clear(); V[0].pb(0);
    for(int j:{0,1}) V[U({0,i})].pb(i), i++;
    P = sz(V[1])>sz(V[0]);
    int x = U({V[P][0],i,V[P][1],i+1});
    V[x%2?!P:P].pb(i+1); V[x>=2?!P:P].pb(i); i+=2;
 
    while(i<n and sz(V[0])+sz(V[1])<2*B){
        vector<int> v; v.clear();
        P = sz(V[1])>sz(V[0]);
        v.pb(V[P][0]), v.pb(i+1);
        v.pb(V[P][1]), v.pb(i+2);
        v.pb(V[P][2]), v.pb(i);
        int x = U(v), c1=P, c2=P, c3=P, c4=P, c5=P;
        if(x%2) c3^=1, x--; 
        if(x!=2){
            if(x==4) c1^=1, c2^=1;
            V[c1].pb(i+1); V[c2].pb(i+2); V[c3].pb(i); i+=3;
        }
        else{ 
            if(sz(V[!P])>=2){
                v.clear(); v.pb(V[!P][0]), v.pb(i+1), v.pb(V[!P][1]); v.pb(V[P][0]); 
                v.pb(i+2); v.pb(V[P][1]); v.pb(i+3); v.pb(V[P][2]); v.pb(i+4);
                x = U(v)-1; c1 = !P;
                if(x%2) c5^=1, x--;
                if(x==2) c4^=1;
                else if(x==4) c1^=1, c2^=1;
                else if(x==6) c1^=1, c2^=1, c4^=1;
                V[c1].pb(i+1); V[c2].pb(i+2); V[c3].pb(i); V[c4].pb(i+3); V[c5].pb(i+4); i+=5;
            }
            else{ 
                if(U({0,i+1})) c1=1,c2=0;
                else c1=0, c2=1;
                V[c1].pb(i+1); V[c2].pb(i+2); V[c3].pb(i); i+=3;
            }
        }
    }
    ans=sz(V[0]);
    while(i<n){
        P = sz(V[1])>sz(V[0]);
        vector<int> v; v.clear();
        for(int j = 0; j < sz(V[P]) and i<n; j++)
            v.pb(V[P][j]), v.pb(i), i++;
        int x = U(v);
        if(!P) ans+=sz(v)/2;
        if(x%2) ans+=P?1:-1, V[P^1].pb(v.back());
        else V[P].pb(v.back());
        ans+=x/2*(P?1:-1);
    }
    return ans;
}
