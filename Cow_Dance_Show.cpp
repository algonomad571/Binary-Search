#include <bits/stdc++.h>
using namespace std;

int n, t;
vector<int> duration;

bool possible(int k){
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for(int i=0; i<k; i++) pq.push(duration[i]);
    
    for(int i=k; i<n; i++){
        int earliest=pq.top();
        pq.pop();
        
        pq.push(earliest+duration[i]);
    }
    
    int finish = 0;

    while(!pq.empty())
    {
        finish = max(finish, pq.top());
        pq.pop();
    }
    
    return finish<=t;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin>>n>>t;
	
	duration.resize(n);

    for (int i = 0; i < n; i++) cin >> duration[i];
    
    int lo = 1, hi = n;
    int ans = n;

    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;

        if (possible(mid))
        {
            ans = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }

    cout << ans << '\n';

    return 0;
	
}
