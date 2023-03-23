/*
Solved by myself
Root the tree at the node with the max degree
For every subtree rooted at x, say we have k children
We need to pick at least one antenna from at least k-1 of the children
if we have a straight line, we can just pick any vertex
else we dfs into each subtree that isnt a straight line
Its certain each "non-straight" subtree is going to have at least one antenna
It is also better to pick k-1 children instead of k children whenever possible
Therefore we can discard one subtree that is "straight", if there is any.
This doesnt necessarily work if we root at a subtree with just degree of 3 :/
*/

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn = (int)2e5+10;
vector<int> adj[maxn];
bool isStraight[maxn];

void recur(int s, int p){
	if(adj[s].size()>2) isStraight[s]=0;
	for(auto u : adj[s]){
		if(u==p) continue;
		recur(u,s); isStraight[s]&=isStraight[u];
	}
}

int dfs(int s, int p){
	if(isStraight[s]) return 1;
	int ans = 0, cnt = 0;
	for(auto u : adj[s]){
		if(u==p) continue;
		if(isStraight[u]) cnt++;
		else ans+=dfs(u,s);
	}
	return ans+cnt-(cnt>0);
}

int main() {
	int n, a, b; cin >> n;
	fill(isStraight, isStraight+maxn, true);
	for(int i = 0; i < n-1; i++) 
		cin >> a >> b, adj[a].pb(b), adj[b].pb(a);
	int p = 0, mx = 0;
	for(int i = 0; i < n; i++)
		if(mx<(int)adj[i].size()) mx=(int)adj[i].size(), p=i;
	recur(p,-1); cout << dfs(p,-1);
}