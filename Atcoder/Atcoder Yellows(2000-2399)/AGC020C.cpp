/*
Solved with help (editorial)
Say you put all subsets on a line, including empty set
We can pair each set and its complementary set giving a total of 2^(n-1) pairs
The sum of each pair is fixed as total_sum of array
The median is in the pair such that their difference is as small as possible
And the median subset is the bigger subset in the median pair
We also know that since first subset sum <= second subset sum for all pairs:
Then, second subset sum must be >= (total_sum+1)/2
The second subest sum has to be as small as possible, so we find the smallest possible subset sum >= (total_sum+1)/2
This can be done with knapsack dp, where dp[i][j] = considering first i elements, if j can be a subset sum
But this gives O(N*N*max_A) which is too slow
We can speed this up with bitsets in O(N*N*max_A/64)
*/

#include <bits/stdc++.h>
using namespace std;
int n, a[2010];

int32_t main() {
	cin >> n;
	for(int i = 0; i < n; i++) cin >> a[i];
	bitset<4000001> dp; dp[0]=1;
	for(int i = 0; i < n; i++) dp |= (dp<<a[i]);
	for(int i = (accumulate(a,a+n,0)+1)/2; ; i++){
		if(!dp[i]) continue; cout << i; return 0;
	}
}