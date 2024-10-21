#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, s;
string a[900];
int x[] = {1, -1, 0, 0};
int y[] = {0, 0, 1, -1};
int dis1[900][900], dis2[900][900];
queue<pair<int,int>> Q, Q1;
pair<int,int> st, en;
vector<pair<int,int>> bees;
bool bfs(int mid)
{
    for(int i = 0; i < 900; i++)
        for(int j = 0; j < 900; j++)
            dis1[i][j] = dis2[i][j] = (int)1e18;
    while(!Q.empty()) Q.pop();
    while(!Q1.empty()) Q1.pop();
    for(auto u : bees) Q.push(u), dis2[u.first][u.second]=0;
    Q1.push(st); dis1[st.first][st.second] = 0;
    while(!Q.empty())
    {
        auto cur = Q.front();
        int i = cur.first, j = cur.second;
        if(dis2[i][j]==mid) break; Q.pop();
        for(int k = 0; k < 4; k++)
        {
            int I = i+x[k], J = j+y[k];
            if(I<0 or J<0 or I>=n or J>=n) continue;
            if(a[I][J]!='G') continue;
            if(dis2[I][J]==(int)1e18)
                Q.push({I,J}), dis2[I][J] = dis2[i][j]+1;
        }
    }
    int last = 0, xx = mid;
    while(!Q1.empty())
    {
        xx++;
        while(!Q1.empty())
        {
            auto cur = Q1.front();
            int i = cur.first, j = cur.second;
            if(dis1[i][j]-last==s) break; Q1.pop();
            if(dis2[i][j]!=(int)1e18) continue;
            for(int k = 0; k < 4; k++)
            {
                int I = i+x[k], J = j+y[k];
                if(I<0 or J<0 or I>=n or J>=n) continue;
                if(dis2[I][J]!=(int)1e18) continue;
                if(a[I][J]=='D' and dis1[I][J]==(int)1e18) return true;
                if(a[I][J]!='G') continue;
                if(dis1[I][J]==(int)1e18)
                    Q1.push({I,J}), dis1[I][J] = dis1[i][j]+1;
            }
        }
        while(!Q.empty())
        {
            auto cur = Q.front();
            int i = cur.first, j = cur.second;
            if(dis2[i][j]==xx) break; Q.pop();
            for(int k = 0; k < 4; k++)
            {
                int I = i+x[k], J = j+y[k];
                if(I<0 or J<0 or I>=n or J>=n) continue;
                if(a[I][J]!='G') continue;
                if(dis2[I][J]==(int)1e18)
                    Q.push({I,J}), dis2[I][J] = dis2[i][j]+1;
            }
        }
        last+=s;
    }
    return false;
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> s;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        for(int j = 0; j < n; j++)
        {
            if(a[i][j]=='M') st = {i,j}, a[i][j] = 'G';
            else if(a[i][j]=='D') en = {i,j};
            else if(a[i][j]=='H') bees.push_back({i,j});
        }
    }
    int l = -1, r = 1e9;
    while(l<r)
    {
        int mid = (l+r+1)/2; if(mid<0) break;
        if(bfs(mid)) l = mid;
        else r = mid-1;
    }
    cout << l;
}
