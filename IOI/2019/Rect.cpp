#include "rect.h"
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
 
using ll = long long;
using vi = vector<int>;
using ar2 = array<int16_t,2>;
 
const int mxN = 2502;
 
int n, m;
bitset<mxN> grid[mxN];
vector<int16_t> row[mxN][mxN], col[mxN][mxN];
deque<ar2> lines[mxN];
vector<int16_t> grid2[mxN];
int16_t R[mxN][mxN];
 
struct Fenwick2D{
    int fen[mxN][mxN];
    void init(int n, int m){
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                fen[i][j]=0;
    }
    void upd(int _x, int _y, int v){
        _x++, _y++;
        for(int x = _x; x<mxN; x+=x&-x)
            for(int y = _y; y < mxN; y+=y&-y)
                fen[x][y]+=v;
    }
    int sum(int _x, int _y){
        int s = 0; _x++, _y++;
        for(int x = _x; x>0; x-=x&-x)
            for(int y = _y; y>0; y-=y&-y)
                s+=fen[x][y];
        return s;
    }
    int sum(int x1, int y1, int x2, int y2){
        return sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1);
    }
} fen2d;
 
ll count_rectangles(vector<vi> a) {
    n = sz(a); m = sz(a[0]); ll ans = 0;
    for(int i = 0; i < n; i++){
        stack<int> S = stack<int>();
        for(int j = m-1; j >= 0; j--){
            while(sz(S) and a[i][S.top()]<a[i][j]) S.pop();
            if(sz(S) and abs(S.top()-j)>1)
                row[i][j].pb(S.top());
            S.push(j);
        }
        S = stack<int>();
        for(int j = 0; j < m; j++){
            while(sz(S) and a[i][S.top()]<a[i][j]) S.pop();
            if(sz(S) and abs(S.top()-j)>1)
                if(a[i][S.top()]!=a[i][j]) 
                    row[i][S.top()].pb(j);
            S.push(j);
        }
    }
    for(int j = 0; j < m; j++){
        stack<int> S = stack<int>();
        for(int i = n-1; i >= 0; i--){
            while(sz(S) and a[S.top()][j]<a[i][j]) S.pop();
            if(sz(S) and abs(S.top()-i)>1)
                col[i][j].pb(S.top());
            S.push(i);
        }
        S = stack<int>();
        for(int i = 0; i < n; i++){
            while(sz(S) and a[S.top()][j]<a[i][j]) S.pop();
            if(sz(S) and abs(S.top()-i)>1)
                if(a[S.top()][j]!=a[i][j])
                    col[S.top()][j].pb(i);
            S.push(i);
        }
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            sort(all(row[i][j])), sort(all(col[i][j]));
    fen2d.init(n,m);
    for(int i = 1; i < n-1; i++){
        for(int j = 0; j < m; j++)
            for(auto u : col[i-1][j]) 
                grid[u][j]=1, grid2[u].pb(j);
        for(int k = 0; k < n; k++){
            for(auto u : grid2[k]){
                int y = u;
                if(!y or !grid[k][y-1]){
                    while(y<m-1 and grid[k][y+1]) y++;
                    lines[u].pb({k,y});
                }
            }
        }
        for(auto [x,y] : lines[0]) fen2d.upd(x,y,1);
        for(int j = 0; j < m; j++){
            for(auto [x,y] : lines[j+1]) fen2d.upd(x,y,1);
            for(auto k : row[i][j]){
                if(i==1 or !binary_search(all(row[i-1][j]),k)){
                    R[j][k] = i+1;
                    while(R[j][k]<n and binary_search(all(row[R[j][k]][j]),k)) R[j][k]++;
                }
                int xd = fen2d.sum(i+1,k-1,R[j][k],mxN-2); ans+=xd;
            }
            for(auto u : col[i-1][j]) grid[u][j]=0;
        }
        for(int j = 0; j < m; j++){
            for(auto [x,y] : lines[j]) fen2d.upd(x,y,-1);
            lines[j].clear();
        }
        for(int k = 0; k < n; k++) grid2[k].clear();
    }
    return ans;
}
