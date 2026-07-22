#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

struct Grazing {
  long long x, y, t;

  bool operator<(const Grazing &other) const { return t < other.t; }
};

bool isValid(const Grazing &a, const Grazing &b) {
  long long dx = a.x - b.x;
  long long dy = a.y - b.y;
  long long dt = abs(a.t - b.t);

  return (dx * dx + dy * dy) <= (dt * dt);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int G, N;
  if (!(cin >> G >> N))
    return 0;

  vector<Grazing> grazings(G);
  for (int i = 0; i < G; ++i) {
    cin >> grazings[i].x >> grazings[i].y >> grazings[i].t;
  }

  sort(grazings.begin(), grazings.end());

  int innocent_count = 0;

  for (int i = 0; i < N; ++i) {
    Grazing alibi;
    cin >> alibi.x >> alibi.y >> alibi.t;

    // Find the first grazing that happens after the alibi time
    auto it = upper_bound(grazings.begin(), grazings.end(), alibi);

    bool possible = true;

    // Check the grazing immediately after the alibi
    if (it != grazings.end()) {
      if (!isValid(alibi, *it)) {
        possible = false;
      }
    }

    // Check the grazing immediately before the alibi
    if (it != grazings.begin()) {
      if (!isValid(alibi, *prev(it))) {
        possible = false;
      }
    }

    // If it fails either check, the cow is definitively innocent
    if (!possible) {
      innocent_count++;
    }
  }

  cout << innocent_count << "\n";

  return 0;
}