#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using vi = vector<int>;
using ar2 = array<int,2>;

const int mxN = (int)3e5+10;
const int INF = (int)1e9;
const ll LINF = (ll)2e18;
const int MOD = (int)1e9+7;

int n, m, k, q, x;
int a[mxN], b[mxN];
string s;
set<int> S;
map<int,int> M;

vector<string> split(string lol="", char del=' '){
    if(lol=="") getline(cin,lol);
    stringstream ss(lol);
    vector<string> v; v.clear();
    string word;
    while(getline(ss,word,del)) v.pb(word);
    return v;
}

template<class T>
vector<T> conv(vector<string> v){
    vector<T> w; w.clear();
    for(auto u : v){
        if(is_same<T,int>::value) w.pb(stoi(u)); // beware of #define int long long
        else if(is_same<T,long long>::value) w.pb(stoll(u));
        else if(is_same<T,float>::value) w.pb(stof(u));
        else if(is_same<T,double>::value) w.pb(stod(u));
        else if(is_same<T,long double>::value) w.pb(stold(u));
    }
    return w;
}

void solve(){
    int n = conv<int>(split())[0];
    vi a = conv<int>(split());
    for(auto u : a) cout << u << " "; cout << "\n";
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1;
    //int t = conv<int>(split())[0];
    while(t--) solve();
}
