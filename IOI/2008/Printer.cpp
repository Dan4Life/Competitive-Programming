#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
const int mxS = 25000*21;
int n, cnt;
vector<char> ans;
int trieNode = 0;
int trie[27][mxS];
int dep[27][mxS];
bitset<mxS> word;
 
void add(string s){
    int v = 0;
    for(auto u : s){
        int c = u-'a';
        if(!trie[c][v])
            trie[c][v] = ++trieNode;
        dep[c][v]=max(dep[c][v],sz(s));
        v = trie[c][v];
    }
    word[v]=1;
}
 
void dfs(int s){
    if(word[s]) ans.pb('P'),cnt++;
    vector<int> ord(26,0); iota(all(ord),0);
    sort(all(ord),[&](int a, int b){
        return dep[a][s]<dep[b][s];
    });
    for(int c : ord){
        if(!trie[c][s]) continue;
        ans.pb(char('a'+c));
        dfs(trie[c][s]);
    }
    if(cnt!=n) ans.pb('-');
}
 
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++){
        string s; cin >> s; add(s);
    }
    dfs(0); cout << sz(ans) << "\n";
    for(auto u : ans) cout << u << "\n";
}
