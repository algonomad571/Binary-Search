#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<pair<ll, ll>> intervals;

bool possible(ll d) {
  ll last = intervals[0].first;
  int cows = 1;

  for (int i = 0; i < m; i++) {
    ll start = intervals[i].first;
    ll end = intervals[i].second;

    ll pos = max(start, last + d);

    while (pos <= end) {
      cows++;
      if (cows >= n)
        return true;

      last = pos;
      pos = last + d;
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  intervals.resize(m);

  for (int i = 0; i < m; i++)
    cin >> intervals[i].first >> intervals[i].second;

  sort(intervals.begin(), intervals.end());

  ll lo = 1;
  ll hi = intervals.back().second - intervals.front().first;
  ll ans = 1;

  while (lo <= hi) {
    ll mid = lo + (hi - lo) / 2;

    if (possible(mid)) {
      ans = mid;
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  cout << ans << '\n';

  return 0;
}