/*
Solved by myself (The idea is too easy to be yellow, this is more like low blue?)
Notice player 2 actually controls the game cuz the game ends immediately player 1 picks option 2
The problem can be remodelled as this:
You must go down(if you can't, game over), then you can optionally go right, make the game end as quickly as possible
Worst case answer is H (going down till the end of grid)
We just need to pick an obstacle and force a premature end by making player one go to the spot above the obstacle
We can greedily prove it is never worse to go to a column as early as possible
Then check if it is best to stop at the nearest obstacle at current column if there is one
*/

#include <bits/stdc++.h>
using namespace std;

int h, w, n;
set<int> S[200010];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> h >> w >> n;
    for(int i = 0; i < n; i++){
        int x,y; cin >> x >> y; S[y].insert(x);
    }
    for(int i = 1; i <= w; i++) S[i].insert(h+1);
    int x = 1, y = 1, ans = h, turn = 1, dis = 0, mn_dis=h+w+1;
    while(x<=h and y<=w){
        int a = *S[y].upper_bound(x); int b = a-x;
        if(mn_dis > dis+b) mn_dis=dis+b, ans = a-1;
        else if(mn_dis==dis+b) ans=min(ans, a-1);
        if(turn){ if(S[y].count(x+1)) break; x++; }
        else{ if(!S[y+1].count(x)) y++; dis++; }
        turn=!turn;
    }
    cout << ans;
}