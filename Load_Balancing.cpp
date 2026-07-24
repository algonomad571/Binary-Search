#include <bits/stdc++.h>
using namespace std;

struct Cow {
  int x, y;
};

struct Node {
  int lc = 0, rc = 0;
};

int n;
vector<Cow> cows;
vector<Node> seg;

void update(int node, int l, int r, int idx, int dl, int dr) {
  seg[node].lc += dl;
  seg[node].rc += dr;

  if (l == r)
    return;

  int mid = (l + r) / 2;

  if (idx <= mid)
    update(node * 2, l, mid, idx, dl, dr);
  else
    update(node * 2 + 1, mid + 1, r, idx, dl, dr);
}

int query(int node, int l, int r, int left, int right, int totL, int totR) {
  int bl = left + seg[node].lc;
  int br = right + seg[node].rc;
  int tl = totL - bl;
  int tr = totR - br;

  if (l == r) {
    int below = max({left, right, totL - left, totR - right});
    int above = max({bl, br, tl, tr});
    return min(below, above);
  }

  int mid = (l + r) / 2;

  int nbl = left + seg[node * 2].lc;
  int nbr = right + seg[node * 2].rc;

  int ntl = totL - nbl;
  int ntr = totR - nbr;

  int ans = max(max(nbl, nbr), max(ntl, ntr));

  if (max(nbl, nbr) < max(ntl, ntr))
    ans = min(ans, query(node * 2 + 1, mid + 1, r, nbl, nbr, totL, totR));
  else
    ans = min(ans, query(node * 2, l, mid, left, right, totL, totR));

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("balancing.in", "r", stdin);
  freopen("balancing.out", "w", stdout);

  cin >> n;

  cows.resize(n);
  vector<int> ys;

  for (int i = 0; i < n; i++) {
    cin >> cows[i].x >> cows[i].y;
    ys.push_back(cows[i].y);
  }

  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  for (auto &c : cows)
    c.y = lower_bound(ys.begin(), ys.end(), c.y) - ys.begin() + 1;

  sort(cows.begin(), cows.end(), [](Cow &a, Cow &b) { return a.x < b.x; });

  int m = ys.size();
  seg.resize(4 * (m + 5));

  for (auto &c : cows)
    update(1, 1, m, c.y, 0, 1);

  int ans = n;
  int left = 0, right = n;

  for (int i = 0; i < n;) {
    int j = i;

    while (j < n && cows[j].x == cows[i].x) {
      update(1, 1, m, cows[j].y, 1, -1);
      left++;
      right--;
      j++;
    }

    ans = min(ans, query(1, 1, m, 0, 0, left, right));
    i = j;
  }

  cout << ans << '\n';
}