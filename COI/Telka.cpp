#include <bits/stdc++.h>
using namespace std;
#define int long long
const int tot = 23*60*60+59*60+59+1;
int n, q, pref[tot+10], pref2[tot+10];

int parse(string s){
    int num = ((s[0]-'0')*10+s[1]-'0')*60*60;
    num += ((s[3]-'0')*10+s[4]-'0')*60;
    return num+(s[6]-'0')*10+s[7]-'0';
}

int32_t main()
{
    cin >> n;
    for(int i = 0; i < n; i++){
        string s; cin >> s;
        int num1 = parse(s);
        cin >> s >> s;
        int num2 = parse(s);
        pref[num1]++, pref[num2+1]--;
        if(num1>num2) pref[0]++;
    }
    cin >> q;
    for(int i = 1; i < tot; i++) pref[i]+=pref[i-1];
    for(int i = 0; i < tot; i++) pref2[i+1]=pref2[i]+pref[i];
    while(q--){
        string s; cin >> s;
        int num1 = parse(s);
        cin >> s >> s;
        int num2 = parse(s);
        double ans = pref2[num2+1]-pref2[num1], length = num2-num1+1;
        if(num1>num2) ans+=pref2[tot], length+=tot;
        cout << fixed << setprecision(6) << ans/length << "\n";
    }
}
