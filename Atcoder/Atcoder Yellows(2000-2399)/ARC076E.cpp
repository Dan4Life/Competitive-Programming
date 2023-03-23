/* 
Solved by myself
Ignore all numbers such that both points are not on the border rectangle
because we can always change the shape of border lines so that they dont intersect with them
So now, basically just cut the rectangle with the remaining lines and make sure they dont intersect
We can number the points on the border rectangle in clockwise order starting from top left corner
The problem becomes: each number has a pair of indexes, make sure there is no two numbers with
indexes {a,b} and {c,d} such that: a < c < b < d  (ie they must not intersect)
this can be easily done with fenwick tree (or using bracket sequence logic with stack like in editorial)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()

const int maxn = (int)2e5+10;
const int INF = (int)1e8+1;
vector<int> v;
bool ok[maxn];
int cnt=1, r, c, n;
vector<pair<int,int>> order;
unordered_map<int,int> num; 
int x[2][maxn], y[2][maxn];
int start[maxn], fenwick[maxn];

inline bool border(int x, int y){ return (!x or x==r or !y or y==c); }

void update(int x, int v){
    for(; x < maxn; x+=(x&-x)) fenwick[x]+=v;
}

int sum(int x){
    int tot = 0;
    for(; x>0; x-=(x&-x)) 
        tot+=fenwick[x];
    return tot;
}

int query(int a, int b){return sum(b)-sum(a-1);}

int32_t main(){
    cin >> r >> c >> n;

    fill(ok, ok+maxn, true);
    fill(start, start+maxn, -1);

    for(int i = 0; i < n; i++){  
        for(int _=0; _ < 2; _++){
            cin >> x[_][i] >> y[_][i];
            ok[i]&=border(x[_][i], y[_][i]);
        }
    }

    for(int i = 0; i < n; i++)
        for(int _ = 0; _ < 2; _++)
            if(ok[i]) order.pb({x[_][i],y[_][i]});

    sort(all(order));
    for(auto u : order) if(!u.fi) 
        num[u.fi*INF+u.se]=cnt++;

    for(auto u : order) 
        if(u.se==c and !num.count(u.fi*INF+u.se)) 
            num[u.fi*INF+u.se]=cnt++;

    reverse(all(order));
    for(auto u : order) 
        if(u.fi==r and !num.count(u.fi*INF+u.se)) 
            num[u.fi*INF+u.se]=cnt++;

    for(auto u : order) 
        if(!u.se and !num.count(u.fi*INF+u.se)) 
            num[u.fi*INF+u.se]=cnt++;

    for(int i = 0; i < n; i++){
        if(!ok[i]) continue;
        int a = num[x[0][i]*INF+y[0][i]];
        int b = num[x[1][i]*INF+y[1][i]];
        if(a>b) swap(a,b);
        start[b] = a; v.pb(a), v.pb(b);
    }
    sort(all(v));
    for(auto u : v){
        if(start[u]==-1) update(u,1);
        else{
            update(start[u],-1);
            if(query(start[u],u)){
                cout << "NO\n"; return 0;
            }
        }
    }
    cout << "YES\n";
}