#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    ll N, tc, tm;
    cin >> N >> tc >> tm;

    vector<array<ll, 3>> friends(N);

    for (int i = 0; i < N; i++) {
      cin >> friends[i][0] >> friends[i][1] >> friends[i][2];
    }

    ll ans = LLONG_MAX;

    if (tc <= tm) {
      // Enumerate cookie upgrades
      for (ll x = 0; x < tc; x++) {
        ll y = 0;
        bool ok = true;

        for (auto [a, b, c] : friends) {
          ll need = a * (tc - x) + b * tm - c;

          if (need <= 0)
            continue;

          ll req = (need + b - 1) / b;

          if (req >= tm) {
            ok = false;
            break;
          }

          y = max(y, req);
        }

        if (ok)
          ans = min(ans, x + y);
      }
    } else {
      // Enumerate muffin upgrades
      for (ll y = 0; y < tm; y++) {
        ll x = 0;
        bool ok = true;

        for (auto [a, b, c] : friends) {
          ll need = a * tc + b * (tm - y) - c;

          if (need <= 0)
            continue;

          ll req = (need + a - 1) / a;

          if (req >= tc) {
            ok = false;
            break;
          }

          x = max(x, req);
        }

        if (ok)
          ans = min(ans, x + y);
      }
    }

    cout << ans << '\n';
  }

  return 0;
}