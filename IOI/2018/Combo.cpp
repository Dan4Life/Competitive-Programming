#include "combo.h"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
 
string guess_sequence(int N) {
    string ans = "", s = "ABXY"; vector<char> v;
    if(press("AB")) ans+=(press("A")?'A':'B');
    else ans+=(press("X")?'X':'Y');
    if(N==1) return ans;
    for(auto u : s) if(u!=ans[0]) v.pb(u);
    for(int i = 2; i <= N-1; i++){
        random_shuffle(begin(v),end(v));
        string p = ans+v[0];
        for(auto u : v) p+=ans+v[1]+u;
        int coins = press(p);
        if(coins==sz(ans)) ans+=v[2];
        else ans+=v[--coins!=sz(ans)];
    }
    int coins = press(ans+v[0]);
    if(coins==N) return ans+v[0];
    coins = press(ans+v[1]);
    if(coins==N) return ans+v[1];
    return ans+v[2];
}
