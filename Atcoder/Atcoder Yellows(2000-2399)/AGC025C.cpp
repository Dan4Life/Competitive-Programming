/*
Solved by myself
It is always optimal to move into endpoints of a range
Say we are in point x, and we want to move to range {l,r}:
If x < l, move to l,
If x > r, move to r,
If none of above conditions hold, move to 0 and end the game.
This is because it means the remaining intervals to be chosen are such that:
L_i <= X <= R_i which X is already inside. This basically fixes the score of player 2.
Therefore the game can be reduced to a single-player game where the player finds an order of picking indices such that the score is maximum.
It is always optimal to make Player 2 'ZigZag' such that each ZigZag is as big as possible.
This means we should make sure we o to the biggest l(if line 5 holds) or the smallest r(if line 6 holds).
The question remains: "Which should i pick if i can do both lines 5 and 6?"
It turns out this is only possible in the first range to be chosen as once you chose that range, the game is fixed if we follow our strategy.
Its not hard to prove the above, so now we can try both ways and see which gives the maximum answer.
This can be implemented with two set of pairs(one to keep track of biggest l, and the other, smallest r) as shown below.
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
const int LINF = (int)1e9+7;

int n;
multiset<pair<int,int>> S1, S2;

int calc(bool ok, multiset<pair<int,int>> S1, multiset<pair<int,int>> S2){
    int sum = 0, x = 0;
    while(!S1.empty()){
        int l, r;
        if(ok){
            auto itr = prev(S1.end());
            l = itr->fi, r = itr->se;
            if(l>x) sum+=l-x, x=l;
            else break;
        }
        else{
            auto itr = S2.begin();
            l = itr->se, r = itr->fi;
            if(r<x) sum+=x-r, x=r;
            else break;
        }
        S1.erase(S1.find({l,r}));
        S2.erase(S2.find({r,l}));
        ok=!ok;
    }
    return sum+abs(x);
}

int32_t main(){
    cin >> n; int ans = 0;

    for(int i = 0; i < n; i++){
        int l, r; cin >> l >> r;
        S1.insert({l,r}), S2.insert({r,l});
    }

    for(int _ = 0; _ < 2; _++)
        ans = max(ans, calc(_,S1,S2));
    cout << ans;
}