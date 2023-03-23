/** The first IOI problem I got 100 points in (also in one try), just Kruskal with DSU*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define mp make_pair
#define fir first
#define sec second

const int maxn = 200010;
int p[1000];

int findSet(int i) { return p[i]==i ? i : p[i] = findSet(p[i]); }

void unionSet(int i, int j) { int x = findSet(i), y = findSet(j); p[y] = x; }

int kruskal(vector< pair<int, pair<int, int> > > edges)
{
    sort(edges.begin(), edges.end());
    int cost = 0;
    for(int i = 0; i < 1000; i++) p[i] = i;
    for(int i = 0; i < edges.size(); i++)
    {
        int a = edges[i].sec.fir, b = edges[i].sec.sec, c = edges[i].fir;
        if(findSet(a)!=findSet(b)) unionSet(a, b), cost+=c;
    }
    return cost;
}

int main()
{
    int n, w;
    cin >> n >> w;
    vector< pair<int, pair<int, int> > > edges;
    while(w--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back(mp(c, mp(a, b)));
        int cost = kruskal(edges);
        bool ok=true;
        if(findSet(a)!=findSet(b))
            unionSet(a, b);
        for(int i = 2; i <= n; i++)
            if(findSet(1)!=findSet(i))
                ok=false;
        if(!ok) cout << -1 << endl;
        else cout << cost << endl;
    }
}
