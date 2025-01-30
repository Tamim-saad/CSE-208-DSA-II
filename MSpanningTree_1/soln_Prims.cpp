#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1e4 + 5;
const ll INF = 2e18 + 5;

vector<pair<ll, ll>> adj[N];

void prims(ll n) {
  vector<ll> value(n + 1, INF);
  vector<ll> parent(n + 1, -1);
  vector<bool> visited(n + 1, false);

  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

  pq.push({0, 1});
  value[1] = 0;

  while (!pq.empty()) {
    ll curr = pq.top().second;
    ll currWeight = pq.top().first;
    pq.pop();

    if (visited[curr])
      continue;
    visited[curr] = true;

    for (auto neighbor : adj[curr]) {
      ll nextNode = neighbor.first;
      ll edgeWeight = neighbor.second;

      if (!visited[nextNode] && edgeWeight < value[nextNode]) {
        parent[nextNode] = curr;
        value[nextNode] = edgeWeight;
        pq.push({value[nextNode], nextNode});
      }
    }
  }

  ll ans = 0;
  for (ll i = 2; i <= n; i++) {
    ans += value[i];
  }

  cout << ans << endl;

  // cout << "Edges of MST:" << endl;
  // for (ll i = 2; i <= n; i++) {
  //   cout << parent[i] << " - " << i << " : " << value[i] << endl;
  // }
}

int main() {
  ll n, m, s;
  cin >> n >> m;

  for (ll i = 0; i < m; i++) {
    ll u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  // cin >> s;

  prims(n);
  return 0;
}
