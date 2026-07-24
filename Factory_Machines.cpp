#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  int64 t;
  cin >> n >> t;

  vector<int64> k(n);

  int64 mn = LLONG_MAX;
  for (int i = 0; i < n; i++) {
    cin >> k[i];
    mn = min(mn, k[i]);
  }

  int64 lo = 0;
  int64 hi = mn * t; // Fastest machine makes all products.

  while (lo < hi) {
    int64 mid = lo + (hi - lo) / 2;

    int64 products = 0;
    for (int i = 0; i < n; i++) {
      products += mid / k[i];

      // Prevent unnecessary overflow/work.
      if (products >= t)
        break;
    }

    if (products >= t)
      hi = mid;
    else
      lo = mid + 1;
  }

  cout << lo << '\n';
  return 0;
}