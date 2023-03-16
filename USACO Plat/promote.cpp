/*****************************************************************************************************
Preprocess offline, preprocess all the prefix sums f(i, x) of cows from 1 to i with proficiency > x
Answer queries a..b with proficiency > x as f(b,x)-f(a-1,x). Coordinate compress the proficiencies btw
After euler renaming, the required ranges for each node v is the subarray from start to end of the
node v visit times since it contains the entire subtree of node v in that range
Then preprocess queries in sorted order OFFLINE and update as needed using appropriate data structure
*****************************************************************************************************/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define int long long

const int maxn = 100010;
vector<int> adj[maxn], w;
map<pair<int,int>, int> M;
unordered_map<int,int> num;
vector<pair<pair<int,int>, int>> offline;
int segTree[4*maxn], a[maxn], st[maxn], en[maxn], prof[maxn], timer = 1, n, mx=1;

int query(int i, int j, int p=1, int l=1, int r=mx)
{
    if(i>j)return 0;
    if(l>=i and r<=j) return segTree[p];
    int mid = (l+r)/2;
    int left = query(i, min(j, mid), p*2, l, mid);
    int right = query(max(i, mid+1), j, p*2+1, mid+1, r);
    return left+right;
}

void update(int x, int val, int p=1, int l=1, int r=mx)
{
    if(l==r) { segTree[p]+=val; return; }
    int mid = (l+r)/2;
    if(x<=mid) update(x, val, p*2, l, mid);
    else update(x, val, p*2+1, mid+1, r);
    segTree[p] = segTree[p*2]+segTree[p*2+1];
}

void dfs(int s, int p = -1)
{
    st[s] = timer++; a[timer-1]=s;
    for(auto u : adj[s])
        if(u!=p) dfs(u, s);
    en[s] = timer-1;
}

bool cmp(pair<pair<int,int>, int> a, pair<pair<int,int>, int> b)
{
    if(a.fi.se!=b.fi.se) return a.fi.se<b.fi.se;
    return a.fi.fi<b.fi.fi;
}

int32_t main()
{
    ifstream cin("promote.in");
    ofstream cout("promote.out");
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> prof[i];
        w.pb(prof[i]);
    }
    sort(all(w)), w.erase(unique(all(w)), w.end());
	for(auto u : w) num[u]=mx, mx++;
	for(int i = 1; i <= n; i++) prof[i] = num[prof[i]];
    for(int i = 2; i <= n; i++)
    {
        int x; cin >> x;
        adj[x].pb(i);
    } dfs(1);
    for(int i = 1; i <= n; i++)
        offline.pb(mp(mp(st[i],en[i]), prof[i]));
    sort(all(offline));
    int cur = 1;
    for(auto u : offline)
    {
        while(cur<u.fi.fi) update(prof[a[cur]], 1), cur++;
        M[mp(u.fi.fi-1, u.se)]=query(u.se+1,mx);
    }
    sort(all(offline), cmp), cur = 1;
    for(int i = 1; i <= 4*mx; i++) segTree[i]=0;
    for(auto u : offline)
    {
        while(cur<=u.fi.se) update(prof[a[cur]], 1), cur++;
        M[mp(u.fi.se, u.se)]=query(u.se+1,mx);
    }
    for(int i = 1; i <= n; i++)
        cout << M[mp(en[i],prof[i])]-M[mp(st[i]-1,prof[i])] << "\n";
}
