#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
int n, k;
string s;
vector<int> v[26];
 
int main() {
	cin >> n >> k >> s; int ans = 1000000;
	for(int i = 0; i < n; i++)
		v[s[i]-'A'].pb(i);
	for(int i = 0; i < 26; i++) 
		if(!v[i].empty()) sort(all(v[i]));
	for(int i = 0; i < n; i++){
		if(s[i]!='J') continue;
		int J = 'J'-'A', O = 'O'-'A', I = 'I'-'A';
		auto itr = lower_bound(all(v[J]),i)-begin(v[J]);
		if(itr+k-1>=sz(v[J])) break;
		int posJ = v[J][itr+k-1];
		itr = lower_bound(all(v[O]),posJ)-begin(v[O]);
		if(itr+k-1>=sz(v[O])) break;
		int posO = v[O][itr+k-1];
		itr = lower_bound(all(v[I]),posO)-begin(v[I]);
		if(itr+k-1>=sz(v[I])) break;
		int posI = v[I][itr+k-1];
		ans = min(ans, posI-i+1-3*k);
	}
	cout << (ans==1000000?-1:ans);
}
