/*
Solved with editorial
*/

#include <bits/stdc++.h>
using namespace std;

set<int> S;
int n, m, k;
int p[2010];
string a[1001];

int findSet(int i){return p[i]==i?i:p[i]=findSet(p[i]);}
bool isSameSet(int i, int j){return findSet(i)==findSet(j); }
void unionSet(int i, int j){
    int x = findSet(i), y = findSet(j);
    if(x==y) return; p[y] = x;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i <= n+m; i++) p[i]=i;
    for(int i = 0; i < n; i++) cin >> a[i];
    a[0][0] = a[0][m-1] = a[n-1][0] = a[n-1][m-1] = '#';
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(a[i][j]=='#') unionSet(i,n+j);
    for(int i = 0; i < n; i++) S.insert(findSet(i));
    int ans = (int)S.size()-1; S.clear();
    for(int i = 0; i < m; i++) S.insert(findSet(i+n));
    cout << min(ans, (int)S.size()-1);
}
