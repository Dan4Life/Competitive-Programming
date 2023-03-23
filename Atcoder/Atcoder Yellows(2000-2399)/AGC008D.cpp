/*
Solved by myself
This problem is seriously overrated. Maybe its due to fewer participants cuz of late contest reminder
Basically, we can sort by smallest X[i], (remember to keep track of the X[i] mapping to i by using pairs)
For current {X[i],i}:
We must assign i-1 is to positions < X[i] and the ith i to x[i]
It never hurts to make the assigned positions as small as possible(greedy) as there's a higher chance of getting a Yes that way
If we cant do it, answer is no
After we're done with all {X[i], i} there will be n-i is to be filled for each i
To do that, just assign all the is to positions > X[i]
If we can't do it, answer is no
else print. Everything can be simulated with sets in O(N^2logN) or 2 pointers to simulate lowerbound in O(N^2) //Why is N<=500 lol
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(a) a.begin(), a.end()

const int maxn = (int)5e2+10; 
const int INF = (int)1e9; 

int n;
int a[maxn*maxn];
int x[maxn], num[maxn];
vector<pair<int,int>> v;

set<int> S;

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> x[i], v.pb({x[i],i}), num[i]=i-1;
    sort(all(v));
    for(int i = 1; i <= n*n; i++) S.insert(i);
    for(int i = 0; i < (int)v.size(); i++)  S.erase(v[i].first);
    for(auto u : v){
        int X = u.first, Y = u.second;
        while(num[Y] and !S.empty()){
            auto pos = *S.begin();
            if(pos>X) break;
            num[Y]--, a[pos]=Y;
            S.erase(S.begin());
        }
        a[X]=Y; if(num[Y]){cout<<"No\n";return 0;}
    }
    
    for(auto u : v){
        int X = u.first, Y = u.second;
        int cnt = n-Y;
        while(cnt--){
            auto itr = S.lower_bound(X);
            if(itr==S.end()){cout<<"No";return 0;}
            a[*itr]=Y; S.erase(itr);
        }
    }
    cout << "Yes\n";
    for(int i = 1; i <= n*n; i++) cout << a[i] << " ";
}