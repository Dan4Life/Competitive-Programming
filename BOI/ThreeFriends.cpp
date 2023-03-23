#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define all(a) a.begin(), a.end()
 
const int maxn = 200010;
const ll MOD = 1e9+7;
const int INF = 1e9;
const ll LINF = 1e18;
ll n, m, a[maxn];
map<int, int> M, N;
string s, ss;
set<int> S, SS;
 
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> s;
    if(n%2==0){ cout << "NOT POSSIBLE"; return 0; }
    string x = s.substr(0, n/2), y = s.substr(n/2+1, n/2);
    if(x==y){ cout << x; return 0; }
    string X = "", Y = "";
    int i = n/2, z= 0;
    for(i; i<n; i++) if(z<x.size() and x[z]==s[i])X+=s[i], z++;
    i=z=0;
    for(i; i <= n/2; i++) if(z<y.size() and y[z]==s[i])Y+=s[i],z++;
    if(X==x and Y==y) cout << "NOT UNIQUE";
    else if(X==x or Y==y)  cout << (X==x?x:y);
    else cout << "NOT POSSIBLE";
}
