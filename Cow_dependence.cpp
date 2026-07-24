#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
vector<int> occ[MAXN];
vector<int> nextOcc;

// Greedy for a fixed x (light labels)
int getGroups(int label, int x) {
  auto &pos = occ[label];

  int groups = 0;
  int left = 0, right = 0;

  while (left < (int)pos.size()) {
    while (right < (int)pos.size() && pos[right] - pos[left] <= x)
      right++;

    groups++;
    left = right;
  }

  return groups;
}

// Greedy using next array (heavy labels)
int getGroupsHeavy(int label, int x) {
  int groups = 0;
  int cur = occ[label][0];

  while (cur < n) {
    groups++;

    if (cur + x + 1 >= n)
      break;

    cur = nextOcc[cur + x + 1];
  }

  return groups;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  nextOcc.assign(n + 1, 0);

  for (int i = 0; i < n; i++) {
    int label;
    cin >> label;
    occ[label].push_back(i);
  }

  vector<int> lightAns(n + 1);
  vector<int> heavyAns(n + 1);

  int LIM = sqrt(n);

  for (int label = 1; label <= n; label++) {

    auto &pos = occ[label];

    if (pos.empty())
      continue;

    int freq = pos.size();

    // Heavy labels
    if (freq > LIM) {

      fill(nextOcc.begin(), nextOcc.end(), 0);

      for (int idx : pos)
        nextOcc[idx] = idx;

      nextOcc[n] = n;

      for (int i = n - 1; i >= 0; i--) {
        if (!nextOcc[i])
          nextOcc[i] = nextOcc[i + 1];
      }

      for (int x = 1; x <= n; x++) {
        heavyAns[x] += getGroupsHeavy(label, x);
      }
    }

    // Light labels
    else {

      for (int wantedGroups = 1; wantedGroups <= freq; wantedGroups++) {

        int low = 0;
        int high = n + 1;

        while (high - low > 1) {

          int mid = (low + high) / 2;

          if (getGroups(label, mid) < wantedGroups)
            high = mid;
          else
            low = mid;
        }

        lightAns[1]++;

        if (high <= n)
          lightAns[high]--;
      }
    }
  }

  for (int i = 2; i <= n; i++)
    lightAns[i] += lightAns[i - 1];

  for (int x = 1; x <= n; x++)
    cout << lightAns[x] + heavyAns[x] << '\n';
}