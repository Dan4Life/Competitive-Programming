#include "perm.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
vector<int> construct_permutation(ll n)
{
	vector<int> A;
	ll xd = 1, ok=0, l=0, p=0;
	while(xd*2<=n) xd*=2, p++;
	for(int i = p-1; i>=0; i--){
		A.push_back(l++);
		if((n>>i)&1){
			if(i and (n>>(i-1)&1) and ok>1)
				A.push_back(l++), A.insert(begin(A)+2,l++),i--;
			else A.insert(begin(A),l++),ok++;
		}
	}
	return A;
}
