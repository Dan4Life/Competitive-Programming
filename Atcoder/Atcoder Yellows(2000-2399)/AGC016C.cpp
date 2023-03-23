/*
Solved by myself
Basically same as official editorial
We just need to make each hxw subarray sum = -1 as much as possible and make occurence of negatives as small as possible
Then we also need to make sure the positive numbers are big enough to overturn any deficits
*/

#include <bits/stdc++.h>
using namespace std;

int H, W, h, w;
int a[510][510], pref[510][510];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> H >> W >> h >> w;
    if(H%h==0 and W%w==0){ cout<<"No"; return 0; }
    int x = 100000000/(h*w-1);
    cout << "Yes\n";
    for(int i = 1; i <= H; i++){
        for(int j = 1; j <= W; j++)
            cout << (i%h==0 and j%w==0?-(h*w-1)*x-1:x) << " ";
        cout << "\n";
    }
}