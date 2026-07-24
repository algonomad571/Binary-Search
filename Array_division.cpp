#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>


using namespace std;

int n, k;
vector<long long> a;

bool isPossible(long long target) {
  int count = 1;
  long long current_sum = 0;

  for (int i = 0; i < n; i++) {
    if (current_sum + a[i] > target) {
      count++;
      current_sum = a[i];
    } else {
      current_sum += a[i];
    }
  }

  return count <= k;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  if (!(cin >> n >> k))
    return 0;

  a.resize(n);
  long long max_val = 0;
  long long total_sum = 0;

  for (int i = 0; i < n; i++) {
    cin >> a[i];
    max_val = max(max_val, a[i]);
    total_sum += a[i];
  }

  long long lo = max_val;
  long long hi = total_sum;
  long long ans = total_sum;

  while (lo <= hi) {
    long long mid = lo + (hi - lo) / 2;

    if (isPossible(mid)) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  cout << ans << '\n';
  return 0;
}