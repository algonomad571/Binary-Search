#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int64 N, K, M;

bool possible(int64 X) {
  int64 given = 0;
  int64 days = 0;

  while (days < K && given < N) {
    int64 Y = (N - given) / X;

    if (Y <= M) {
      return given + (K - days) * M >= N;
    }

    int64 maxGiven = N - Y * X;

    int64 cnt = (maxGiven - given) / Y + 1;

    if (cnt <= 0)
      cnt = 1;

    if (days + cnt > K)
      cnt = K - days;

    given += cnt * Y;
    days += cnt;
  }

  return given >= N;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> K >> M;

  int64 lo = 1, hi = N, ans = 1;

  while (lo <= hi) {
    int64 mid = (lo + hi) / 2;

    if (possible(mid)) {
      ans = mid;
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  cout << ans << '\n';
}