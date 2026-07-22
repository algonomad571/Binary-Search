#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<long long> a;

bool possible(long long R) {
  int cows = 1;
  long long reach = a[0] + 2 * R;

  for (int i = 1; i < n; i++) {
    if (a[i] > reach) {
      cows++;
      reach = a[i] + 2 * R;
    }
  }

  return cows <= k;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;

  a.resize(n);

  for (int i = 0; i < n; i++)
    cin >> a[i];

  sort(a.begin(), a.end());

  long long lo = 0;
  long long hi = a[n - 1] - a[0];
  long long ans = hi;

  while (lo <= hi) {
    long long mid = lo + (hi - lo) / 2;

    if (possible(mid)) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  cout << ans << '\n';

  return 0;
}