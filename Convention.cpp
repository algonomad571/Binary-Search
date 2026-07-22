#include <bits/stdc++.h>
using namespace std;

int n, m, c;
vector<int> a(n);

bool possible(int w) {

  int buses = 1;
  int firstArrival = a[0];
  int cows = 1;

  for (int i = 1; i < n; i++) {
    if (cows == c || a[i] - firstArrival > w) {
      buses++;
      firstArrival = a[i];
      cows = 1;
    } else {
      cows++;
    }
  }

  return buses <= m;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> c;

  a.resize(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  sort(a.begin(), a.end());

  int lo = 0, hi = a[n - 1] - a[0];
  int ans = hi;

  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;

    if (possible(mid)) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  cout << ans << "\n";

  return 0;
}
