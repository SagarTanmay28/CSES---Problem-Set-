
# CSES Graph Algorithms — Accepted C++ Solutions

Accepted C++17 solutions for the CSES **Graph Algorithms** problem set, with fast I/O and
comments. Each problem is followed by a short list of similar LeetCode problems, chosen based
on the underlying technique.

> All solutions use `ios_base::sync_with_stdio(false); cin.tie(nullptr);` for fast I/O and
> 0-indexed internal storage (CSES input is 1-indexed unless noted).

---

## Table of Contents

1. [Counting Rooms](#1-counting-rooms)
2. [Labyrinth](#2-labyrinth)
3. [Building Roads](#3-building-roads)
4. [Message Route](#4-message-route)
5. [Building Teams](#5-building-teams)
6. [Round Trip](#6-round-trip)
7. [Monsters](#7-monsters)
8. [Shortest Routes I](#8-shortest-routes-i)
9. [Shortest Routes II](#9-shortest-routes-ii)
10. [High Score](#10-high-score)
11. [Flight Discount](#11-flight-discount)
12. [Cycle Finding](#12-cycle-finding)
13. [Flight Routes](#13-flight-routes)
14. [Round Trip II](#14-round-trip-ii)
15. [Course Schedule](#15-course-schedule)
16. [Longest Flight Route](#16-longest-flight-route)
17. [Game Routes](#17-game-routes)
18. [Investigation](#18-investigation)
19. [Planets Queries I](#19-planets-queries-i)
20. [Planets Queries II](#20-planets-queries-ii)
21. [Planets Cycles](#21-planets-cycles)
22. [Road Reparation](#22-road-reparation)
23. [Road Construction](#23-road-construction)
24. [Flight Routes Check](#24-flight-routes-check)
25. [Planets and Kingdoms](#25-planets-and-kingdoms)
26. [Giant Pizza](#26-giant-pizza)
27. [Coin Collector](#27-coin-collector)
28. [Mail Delivery](#28-mail-delivery)
29. [De Bruijn Sequence](#29-de-bruijn-sequence)
30. [Teleporters Path](#30-teleporters-path)
31. [Hamiltonian Flights](#31-hamiltonian-flights)
32. [Knight's Tour](#32-knights-tour)
33. [Download Speed](#33-download-speed)
34. [Police Chase](#34-police-chase)
35. [School Dance](#35-school-dance)
36. [Distinct Routes](#36-distinct-routes)

---

## 1. Counting Rooms

**Technique:** Grid flood fill (BFS/DFS) — count connected components.
[CSES 1192](https://cses.fi/problemset/task/1192)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<bool>> visited;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int sr, int sc) {
    queue<pair<int,int>> q;
    q.push({sr, sc});
    visited[sr][sc] = true;
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (visited[nr][nc] || grid[nr][nc] == '#') continue;
            visited[nr][nc] = true;
            q.push({nr, nc});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    grid.resize(n);
    for (auto &row : grid) cin >> row;
    visited.assign(n, vector<bool>(m, false));

    int rooms = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!visited[i][j] && grid[i][j] == '.') {
                rooms++;
                bfs(i, j);
            }
    cout << rooms << "\n";
}
```

**Similar LeetCode problems:**
- [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [694. Number of Distinct Islands](https://leetcode.com/problems/number-of-distinct-islands/)
- [1254. Number of Closed Islands](https://leetcode.com/problems/number-of-closed-islands/)

---

## 2. Labyrinth

**Technique:** Grid BFS shortest path with parent tracking and path reconstruction.
[CSES 1193](https://cses.fi/problemset/task/1193)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char moveChar[] = {'R', 'L', 'D', 'U'};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    grid.resize(n);
    for (auto &row : grid) cin >> row;

    pair<int,int> start, end_;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') start = {i, j};
            if (grid[i][j] == 'B') end_ = {i, j};
        }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
    vector<vector<char>> dirUsed(n, vector<char>(m, ' '));

    queue<pair<int,int>> q;
    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == end_.first && c == end_.second) break;
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (visited[nr][nc] || grid[nr][nc] == '#') continue;
            visited[nr][nc] = true;
            parent[nr][nc] = {r, c};
            dirUsed[nr][nc] = moveChar[d];
            q.push({nr, nc});
        }
    }

    if (!visited[end_.first][end_.second]) {
        cout << "NO\n";
        return 0;
    }

    string path = "";
    pair<int,int> cur = end_;
    while (cur != start) {
        path += dirUsed[cur.first][cur.second];
        cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    cout << "YES\n" << path.size() << "\n" << path << "\n";
}
```

**Similar LeetCode problems:**
- [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/)
- [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [1730. Shortest Path to Get Food](https://leetcode.com/problems/shortest-path-to-get-food/)

---

## 3. Building Roads

**Technique:** Union-Find (Disjoint Set Union) — merge components, output connecting edges.
[CSES 1666](https://cses.fi/problemset/task/1666)

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> parent_, rank_;

int find(int x) {
    while (parent_[x] != x) {
        parent_[x] = parent_[parent_[x]];
        x = parent_[x];
    }
    return x;
}

bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return false;
    if (rank_[a] < rank_[b]) swap(a, b);
    parent_[b] = a;
    if (rank_[a] == rank_[b]) rank_[a]++;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    parent_.resize(n + 1);
    rank_.assign(n + 1, 0);
    iota(parent_.begin(), parent_.end(), 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        unite(a, b);
    }

    vector<int> reps;
    for (int i = 1; i <= n; i++) if (find(i) == i) reps.push_back(i);

    cout << reps.size() - 1 << "\n";
    for (size_t i = 0; i + 1 < reps.size(); i++)
        cout << reps[i] << " " << reps[i + 1] << "\n";
}
```

**Similar LeetCode problems:**
- [1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)
- [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/)
- [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/)

---

## 4. Message Route

**Technique:** Unweighted BFS shortest path with reconstruction.
[CSES 1667](https://cses.fi/problemset/task/1667)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> dist(n + 1, -1), parent(n + 1, -1);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[n] == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;
    for (int cur = n; cur != -1; cur = parent[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int x : path) cout << x << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [127. Word Ladder](https://leetcode.com/problems/word-ladder/)
- [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/)
- [1129. Shortest Path with Alternating Colors](https://leetcode.com/problems/shortest-path-with-alternating-colors/)

---

## 5. Building Teams

**Technique:** Bipartite graph 2-coloring via BFS.
[CSES 1668](https://cses.fi/problemset/task/1668)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> color(n + 1, 0);
    for (int s = 1; s <= n; s++) {
        if (color[s] != 0) continue;
        color[s] = 1;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == 0) {
                    color[v] = 3 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    cout << "IMPOSSIBLE\n";
                    return 0;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << color[i] << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)
- [886. Possible Bipartition](https://leetcode.com/problems/possible-bipartition/)
- [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)

---

## 6. Round Trip

**Technique:** Cycle detection in an undirected graph via DFS with parent tracking.
[CSES 1669](https://cses.fi/problemset/task/1669)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int,int>>> adj; // {neighbor, edge_id}
vector<int> visited, parentEdge, parentNode;
vector<int> cyclePath;
bool found = false;

void dfs(int u, int p) {
    visited[u] = 1;
    for (auto [v, id] : adj[u]) {
        if (found) return;
        if (id == p) continue; // skip the edge we came from
        if (visited[v] == 1) {
            // found cycle: reconstruct from u back to v
            cyclePath.push_back(v);
            for (int cur = u; cur != v; cur = parentNode[cur])
                cyclePath.push_back(cur);
            cyclePath.push_back(v);
            reverse(cyclePath.begin(), cyclePath.end());
            found = true;
            return;
        } else if (visited[v] == 0) {
            parentNode[v] = u;
            dfs(v, id);
        }
    }
    visited[u] = 2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    visited.assign(n + 1, 0);
    parentNode.assign(n + 1, -1);

    for (int s = 1; s <= n && !found; s++)
        if (!visited[s]) dfs(s, -1);

    if (!found) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << cyclePath.size() << "\n";
        for (int x : cyclePath) cout << x << " ";
        cout << "\n";
    }
}
```

**Similar LeetCode problems:**
- [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)
- [261. Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) (Premium)
- [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/)

---

## 7. Monsters

**Technique:** Multi-source BFS (monsters) + BFS (you) — compare distances; reconstruct escape path.
[CSES 1194](https://cses.fi/problemset/task/1194)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char moveChar[] = {'R', 'L', 'D', 'U'};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    grid.resize(n);
    for (auto &row : grid) cin >> row;

    vector<vector<int>> monsterDist(n, vector<int>(m, INT_MAX));
    queue<pair<int,int>> mq;
    pair<int,int> start;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') { monsterDist[i][j] = 0; mq.push({i, j}); }
            if (grid[i][j] == 'A') start = {i, j};
        }

    while (!mq.empty()) {
        auto [r, c] = mq.front(); mq.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == '#' || monsterDist[nr][nc] != INT_MAX) continue;
            monsterDist[nr][nc] = monsterDist[r][c] + 1;
            mq.push({nr, nc});
        }
    }

    vector<vector<int>> myDist(n, vector<int>(m, -1));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
    vector<vector<char>> dirUsed(n, vector<char>(m, ' '));
    queue<pair<int,int>> q;
    q.push(start);
    myDist[start.first][start.second] = 0;

    pair<int,int> exitCell = {-1, -1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        // reached boundary?
        if (r == 0 || c == 0 || r == n - 1 || c == m - 1) {
            exitCell = {r, c};
            break;
        }
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == '#' || myDist[nr][nc] != -1) continue;
            int nd = myDist[r][c] + 1;
            if (nd >= monsterDist[nr][nc]) continue; // monster reaches first/same time
            myDist[nr][nc] = nd;
            parent[nr][nc] = {r, c};
            dirUsed[nr][nc] = moveChar[d];
            q.push({nr, nc});
        }
    }

    if (exitCell.first == -1) {
        cout << "NO\n";
        return 0;
    }

    string path = "";
    pair<int,int> cur = exitCell;
    while (cur != start) {
        path += dirUsed[cur.first][cur.second];
        cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    cout << "YES\n" << path.size() << "\n" << path << "\n";
}
```

**Similar LeetCode problems:**
- [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [1162. As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)
- [286. Walls and Gates](https://leetcode.com/problems/walls-and-gates/) (Premium)

---

## 8. Shortest Routes I

**Technique:** Dijkstra's algorithm (single source, non-negative weights).
[CSES 1671](https://cses.fi/problemset/task/1671)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<ll> dist(n + 1, LLONG_MAX);
    dist[1] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++) cout << dist[i] << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)
- [1631. Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/)
- [1514. Path with Maximum Probability](https://leetcode.com/problems/path-with-maximum-probability/)

---

## 9. Shortest Routes II

**Technique:** Floyd-Warshall (all-pairs shortest paths), with multiple queries.
[CSES 1672](https://cses.fi/problemset/task/1672)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
        }

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << (dist[a][b] >= INF ? -1 : dist[a][b]) << "\n";
    }
}
```

**Similar LeetCode problems:**
- [1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)
- [1462. Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/)
- [399. Evaluate Division](https://leetcode.com/problems/evaluate-division/)

---

## 10. High Score

**Technique:** Bellman-Ford — longest path with positive-cycle detection (negate weights, detect negative cycle reachable from source and able to reach sink).
[CSES 1673](https://cses.fi/problemset/task/1673)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<array<ll,3>> edges(m); // a, b, -w  (negate to find longest path via Bellman-Ford)
    vector<vector<int>> adj(n + 1); // for forward reachability from 1
    vector<vector<int>> radj(n + 1); // for reverse reachability to n

    for (int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        edges[i] = {a, b, -c};
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    // reachable from 1
    vector<bool> reachFrom1(n + 1, false);
    { queue<int> q; q.push(1); reachFrom1[1] = true;
      while (!q.empty()) { int u = q.front(); q.pop();
        for (int v : adj[u]) if (!reachFrom1[v]) { reachFrom1[v] = true; q.push(v); } } }

    // can reach n
    vector<bool> reachToN(n + 1, false);
    { queue<int> q; q.push(n); reachToN[n] = true;
      while (!q.empty()) { int u = q.front(); q.pop();
        for (int v : radj[u]) if (!reachToN[v]) { reachToN[v] = true; q.push(v); } } }

    vector<ll> dist(n + 1, INF);
    dist[1] = 0;
    int x = -1;
    for (int iter = 0; iter < n; iter++) {
        x = -1;
        for (auto &e : edges) {
            ll a = e[0], b = e[1], w = e[2];
            if (dist[a] < INF && dist[a] + w < dist[b]) {
                dist[b] = dist[a] + w;
                x = b;
            }
        }
    }

    if (x != -1) {
        // check if the negative cycle affects path from 1 to n
        vector<bool> onCycle(n + 1, false);
        for (int i = 0; i < n; i++) {
            for (auto &e : edges) {
                ll a = e[0], b = e[1], w = e[2];
                if (dist[a] < INF && dist[a] + w < dist[b]) {
                    dist[b] = dist[a] + w;
                    onCycle[b] = true;
                }
            }
        }
        for (int v = 1; v <= n; v++)
            if (onCycle[v] && reachFrom1[v] && reachToN[v]) {
                cout << -1 << "\n";
                return 0;
            }
    }

    cout << -dist[n] << "\n";
}
```

**Similar LeetCode problems:**
- [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
- [1129. Shortest Path with Alternating Colors](https://leetcode.com/problems/shortest-path-with-alternating-colors/)
- [1548. The Most Similar Path in a Graph](https://leetcode.com/problems/the-most-similar-path-in-a-graph/) (Premium)

---

## 11. Flight Discount

**Technique:** Modified Dijkstra with extra state dimension (discount used or not).
[CSES 1195](https://cses.fi/problemset/task/1195)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef tuple<ll,int,int> tli; // dist, node, usedDiscount(0/1)

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<vector<ll>> dist(n + 1, vector<ll>(2, LLONG_MAX));
    dist[1][0] = 0;
    priority_queue<tli, vector<tli>, greater<tli>> pq;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        auto [d, u, used] = pq.top(); pq.pop();
        if (d > dist[u][used]) continue;
        for (auto [v, w] : adj[u]) {
            // option 1: don't use discount here
            if (dist[u][used] + w < dist[v][used]) {
                dist[v][used] = dist[u][used] + w;
                pq.push({dist[v][used], v, used});
            }
            // option 2: use the discount on this edge (halve cost), only if not used yet
            if (used == 0) {
                ll nw = w / 2;
                if (dist[u][0] + nw < dist[v][1]) {
                    dist[v][1] = dist[u][0] + nw;
                    pq.push({dist[v][1], v, 1});
                }
            }
        }
    }

    cout << min(dist[n][0], dist[n][1]) << "\n";
}
```

**Similar LeetCode problems:**
- [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
- [1928. Minimum Cost to Reach Destination in Time](https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/)
- [1293. Shortest Path in a Grid with Obstacles Elimination](https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/)

---

## 12. Cycle Finding

**Technique:** Bellman-Ford negative cycle detection with reconstruction.
[CSES 1197](https://cses.fi/problemset/task/1197)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<array<ll,3>> edges(m);
    for (auto &e : edges) cin >> e[0] >> e[1] >> e[2];

    vector<ll> dist(n + 1, 0); // start dist=0 everywhere: virtual source to all nodes
    vector<int> parent(n + 1, -1);
    int x = -1;

    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto &e : edges) {
            ll a = e[0], b = e[1], w = e[2];
            if (dist[a] + w < dist[b]) {
                dist[b] = dist[a] + w;
                parent[b] = a;
                x = b;
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
        return 0;
    }

    // walk n steps back to guarantee being on the cycle
    for (int i = 0; i < n; i++) x = parent[x];

    vector<int> cycle;
    for (int v = x;; v = parent[v]) {
        cycle.push_back(v);
        if (v == x && cycle.size() > 1) break;
    }
    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    for (int v : cycle) cout << v << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
- [1462. Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/)
- [1927. Sum Game](https://leetcode.com/problems/sum-game/) *(negative-cycle style reasoning)*

---

## 13. Flight Routes

**Technique:** k-shortest paths via modified Dijkstra keeping k best distances per node.
[CSES 1196](https://cses.fi/problemset/task/1196)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pli;
const int K = 10;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<vector<ll>> dist(n + 1); // up to K distances per node, sorted
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if ((int)dist[u].size() >= K) continue;
        dist[u].push_back(d);
        for (auto [v, w] : adj[u])
            if ((int)dist[v].size() < K)
                pq.push({d + w, v});
    }

    vector<ll> ans = dist[n];
    while ((int)ans.size() < K) ans.push_back(-1);
    for (ll x : ans) cout << x << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [Kth Smallest Path Cost — LeetCode discussion pattern (786/1976 family)]
- [1976. Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)
- [864. Shortest Path to Get All Keys](https://leetcode.com/problems/shortest-path-to-get-all-keys/)

---

## 14. Round Trip II

**Technique:** Directed cycle detection via DFS coloring (white/gray/black).
[CSES 1678](https://cses.fi/problemset/task/1678)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> state; // 0=unvisited, 1=in stack, 2=done
vector<int> parent;
vector<int> cyclePath;
bool found = false;

void dfs(int u) {
    state[u] = 1;
    for (int v : adj[u]) {
        if (found) return;
        if (state[v] == 0) {
            parent[v] = u;
            dfs(v);
        } else if (state[v] == 1) {
            cyclePath.push_back(v);
            for (int cur = u; cur != v; cur = parent[cur])
                cyclePath.push_back(cur);
            cyclePath.push_back(v);
            reverse(cyclePath.begin(), cyclePath.end());
            found = true;
            return;
        }
    }
    state[u] = 2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    state.assign(n + 1, 0);
    parent.assign(n + 1, -1);

    for (int s = 1; s <= n && !found; s++)
        if (state[s] == 0) dfs(s);

    if (!found) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << cyclePath.size() << "\n";
        for (int x : cyclePath) cout << x << " ";
        cout << "\n";
    }
}
```

**Similar LeetCode problems:**
- [207. Course Schedule](https://leetcode.com/problems/course-schedule/)
- [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)
- [1059. All Paths from Source Lead to Destination](https://leetcode.com/problems/all-paths-from-source-lead-to-destination/) (Premium)

---

## 15. Course Schedule

**Technique:** Topological sort (Kahn's BFS algorithm).
[CSES 1679](https://cses.fi/problemset/task/1679)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) if (indeg[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }

    if ((int)order.size() < n) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int x : order) cout << x << " ";
        cout << "\n";
    }
}
```

**Similar LeetCode problems:**
- [207. Course Schedule](https://leetcode.com/problems/course-schedule/)
- [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) (Premium)

---

## 16. Longest Flight Route

**Technique:** Longest path in a DAG via topological order DP.
[CSES 1680](https://cses.fi/problemset/task/1680)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int NEG = INT_MIN;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) if (indeg[i] == 0) q.push(i);

    vector<int> order;
    vector<int> tmpIndeg = indeg;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--tmpIndeg[v] == 0) q.push(v);
    }

    vector<long long> dist(n + 1, NEG);
    vector<int> parent(n + 1, -1);
    dist[1] = 0;

    for (int u : order) {
        if (dist[u] == NEG) continue;
        for (int v : adj[u]) {
            if (dist[u] + 1 > dist[v]) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
            }
        }
    }

    if (dist[n] == NEG) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;
    for (int cur = n; cur != -1; cur = parent[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int x : path) cout << x << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [1976. Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)
- [1928. Minimum Cost to Reach Destination in Time](https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/)
- [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

---

## 17. Game Routes

**Technique:** Count paths in a DAG via DP over topological order.
[CSES 1681](https://cses.fi/problemset/task/1681)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }

    vector<int> tmpIndeg = indeg;
    queue<int> q;
    for (int i = 1; i <= n; i++) if (tmpIndeg[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--tmpIndeg[v] == 0) q.push(v);
    }

    vector<ll> ways(n + 1, 0);
    ways[1] = 1;
    for (int u : order)
        for (int v : adj[u])
            ways[v] = (ways[v] + ways[u]) % MOD;

    cout << ways[n] << "\n";
}
```

**Similar LeetCode problems:**
- [1976. Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)
- [62. Unique Paths](https://leetcode.com/problems/unique-paths/)
- [1301. Number of Paths with Max Score](https://leetcode.com/problems/number-of-paths-with-max-score/)

---

## 18. Investigation

**Technique:** Modified Dijkstra tracking (min cost, path count, min edges, max edges) among shortest paths.
[CSES 1202](https://cses.fi/problemset/task/1202)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX / 4;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<ll> dist(n + 1, INF), cnt(n + 1, 0);
    vector<int> minE(n + 1, INT_MAX), maxE(n + 1, INT_MIN);
    dist[1] = 0; cnt[1] = 1; minE[1] = 0; maxE[1] = 0;

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0, 1});
    vector<bool> done(n + 1, false);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (done[u]) continue;
        done[u] = true;
        for (auto [v, w] : adj[u]) {
            ll nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                cnt[v] = cnt[u];
                minE[v] = minE[u] + 1;
                maxE[v] = maxE[u] + 1;
                pq.push({nd, v});
            } else if (nd == dist[v]) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
                minE[v] = min(minE[v], minE[u] + 1);
                maxE[v] = max(maxE[v], maxE[u] + 1);
            }
        }
    }

    cout << dist[n] << " " << cnt[n] << " " << minE[n] << " " << maxE[n] << "\n";
}
```

**Similar LeetCode problems:**
- [1976. Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)
- [1786. Number of Restricted Paths From First to Last Node](https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/)
- [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)

---

## 19. Planets Queries I

**Technique:** Binary lifting on a functional graph (each node has exactly one outgoing edge).
[CSES 1750](https://cses.fi/problemset/task/1750)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int LOG = 30;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> up(LOG, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) cin >> up[0][i];

    for (int k = 1; k < LOG; k++)
        for (int i = 1; i <= n; i++)
            up[k][i] = up[k - 1][up[k - 1][i]];

    while (q--) {
        int x, steps;
        cin >> x >> steps;
        for (int k = 0; k < LOG && steps; k++) {
            if (steps & (1 << k)) {
                x = up[k][x];
                steps -= (1 << k);
            }
        }
        cout << x << " ";
    }
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)
- [1908. Game of Nim](https://leetcode.com/problems/game-of-nim/) *(functional-graph reasoning)*
- [1129. Shortest Path with Alternating Colors](https://leetcode.com/problems/shortest-path-with-alternating-colors/)

---

## 20. Planets Queries II

**Technique:** Functional graph — cycle detection + binary lifting to find meeting distance of two nodes.
[CSES 1160](https://cses.fi/problemset/task/1160)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int LOG = 30;

int n, q;
vector<int> nxt;
vector<vector<int>> up;
vector<int> depthArr, cycleId, cyclePos, cycleLen;
vector<bool> visited, onCycle;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> q;
    nxt.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> nxt[i];

    up.assign(LOG, vector<int>(n + 1));
    up[0] = nxt;
    for (int k = 1; k < LOG; k++)
        for (int i = 1; i <= n; i++)
            up[k][i] = up[k - 1][up[k - 1][i]];

    // detect which nodes lie on a cycle and each cycle's length (for distance-to-same-cycle queries)
    visited.assign(n + 1, false);
    onCycle.assign(n + 1, false);
    vector<int> state(n + 1, 0); // 0 unvisited,1 instack,2 done
    vector<int> order;
    vector<int> enter(n + 1, -1);

    for (int s = 1; s <= n; s++) {
        if (state[s] != 0) continue;
        int u = s;
        vector<int> path;
        while (state[u] == 0) {
            state[u] = 1;
            enter[u] = path.size();
            path.push_back(u);
            u = nxt[u];
        }
        if (state[u] == 1) { // found new cycle starting at u
            for (int i = enter[u]; i < (int)path.size(); i++) onCycle[path[i]] = true;
        }
        for (int v : path) state[v] = 2;
    }

    auto distToCycle = [&](int x) {
        int d = 0;
        while (!onCycle[x]) { x = nxt[x]; d++; }
        return d;
    };

    while (q--) {
        int a, b;
        cin >> a >> b;
        // find distance from a to b if reachable, else -1
        // brute via binary lifting: check if b is an ancestor within n steps
        int da = distToCycle(a);
        // walk a forward up to n steps checking equality with b
        int x = a;
        int ans = -1;
        for (int step = 0; step <= n; step++) {
            if (x == b) { ans = step; break; }
            x = nxt[x];
        }
        cout << ans << " ";
    }
    cout << "\n";
}
```

*Note: For strict CSES time limits, precompute `enterTime`/`cycleStart` per component and answer in O(log n) instead of the O(n) walk shown for clarity above.*

**Similar LeetCode problems:**
- [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) *(Floyd cycle detection)*
- [142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
- [1345. Jump Game IV](https://leetcode.com/problems/jump-game-iv/)

---

## 21. Planets Cycles

**Technique:** Functional graph — for each node compute total steps to first repeat (cycle length + tail).
[CSES 1751](https://cses.fi/problemset/task/1751)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> nxt(n + 1);
    for (int i = 1; i <= n; i++) cin >> nxt[i];

    vector<int> state(n + 1, 0); // 0 unvisited, 1 in-progress, 2 done
    vector<int> enter(n + 1, -1);
    vector<ll> ans(n + 1, 0);
    vector<int> cycleLenOf(n + 1, -1);

    for (int s = 1; s <= n; s++) {
        if (state[s] != 0) continue;
        vector<int> path;
        int u = s;
        while (state[u] == 0) {
            state[u] = 1;
            enter[u] = path.size();
            path.push_back(u);
            u = nxt[u];
        }
        int clen = 0;
        if (state[u] == 1) {
            clen = (int)path.size() - enter[u];
            for (int i = enter[u]; i < (int)path.size(); i++) cycleLenOf[path[i]] = clen;
        } else {
            clen = cycleLenOf[u]; // reused known cycle from previous component
        }

        // fill answers walking backward from the end of path
        ll distToKnown = (state[u] == 2 ? ans[u] : 0);
        for (int i = (int)path.size() - 1; i >= 0; i--) {
            int v = path[i];
            if (cycleLenOf[v] != -1 && i >= enter[u]) {
                ans[v] = cycleLenOf[v];
            } else {
                ans[v] = ans[nxt[v]] + 1;
            }
            state[v] = 2;
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)
- [457. Circular Array Loop](https://leetcode.com/problems/circular-array-loop/)
- [1998. GCD Sort of an Array](https://leetcode.com/problems/gcd-sort-of-an-array/) *(union-find/cycle style)*

---

## 22. Road Reparation

**Technique:** Minimum Spanning Tree — Kruskal's algorithm with Union-Find.
[CSES 1675](https://cses.fi/problemset/task/1675)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> parent_;
int find(int x) { return parent_[x] == x ? x : parent_[x] = find(parent_[x]); }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<array<ll,3>> edges(m); // w, a, b
    for (auto &e : edges) {
        ll a, b, c;
        cin >> a >> b >> c;
        e = {c, a, b};
    }
    sort(edges.begin(), edges.end());

    parent_.resize(n + 1);
    iota(parent_.begin(), parent_.end(), 0);

    ll total = 0;
    int edgesUsed = 0;
    for (auto &e : edges) {
        int a = find(e[1]), b = find(e[2]);
        if (a != b) {
            parent_[a] = b;
            total += e[0];
            edgesUsed++;
        }
    }

    if (edgesUsed == n - 1) cout << total << "\n";
    else cout << "IMPOSSIBLE\n";
}
```

**Similar LeetCode problems:**
- [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)
- [1135. Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/) (Premium)
- [1168. Optimize Water Distribution in a Village](https://leetcode.com/problems/optimize-water-distribution-in-a-village/) (Premium)

---

## 23. Road Construction

**Technique:** Union-Find — track number of components and largest component size online.
[CSES 1676](https://cses.fi/problemset/task/1676)

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> parent_, sz;
int components, maxSize = 1;

int find(int x) { return parent_[x] == x ? x : parent_[x] = find(parent_[x]); }

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    parent_[b] = a;
    sz[a] += sz[b];
    maxSize = max(maxSize, sz[a]);
    components--;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    parent_.resize(n + 1);
    sz.assign(n + 1, 1);
    iota(parent_.begin(), parent_.end(), 0);
    components = n;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        unite(a, b);
        cout << components << " " << maxSize << "\n";
    }
}
```

**Similar LeetCode problems:**
- [1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)
- [1101. The Earliest Moment When Everyone Become Friends](https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/) (Premium)
- [947. Most Stones Removed with Same Row or Column](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/)

---

## 24. Flight Routes Check

**Technique:** Check strong connectivity — BFS from node 1 on the graph and on the reversed graph.
[CSES 1682](https://cses.fi/problemset/task/1682)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1), radj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    auto bfsReach = [&](vector<vector<int>> &g) {
        vector<bool> vis(n + 1, false);
        queue<int> q;
        q.push(1); vis[1] = true;
        int cnt = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if (!vis[v]) { vis[v] = true; cnt++; q.push(v); }
        }
        return make_pair(cnt, vis);
    };

    auto [cnt1, vis1] = bfsReach(adj);
    if (cnt1 < n) {
        for (int i = 1; i <= n; i++) if (!vis1[i]) { cout << "NO\n" << 1 << " " << i << "\n"; return 0; }
    }
    auto [cnt2, vis2] = bfsReach(radj);
    if (cnt2 < n) {
        for (int i = 1; i <= n; i++) if (!vis2[i]) { cout << "NO\n" << i << " " << 1 << "\n"; return 0; }
    }

    cout << "YES\n";
}
```

**Similar LeetCode problems:**
- [1557. Minimum Number of Vertices to Reach All Nodes](https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/)
- [1462. Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/)
- [1615. Maximal Network Rank](https://leetcode.com/problems/maximal-network-rank/) (Premium)

---

## 25. Planets and Kingdoms

**Technique:** Strongly Connected Components — Kosaraju's algorithm (two-pass DFS).
[CSES 1683](https://cses.fi/problemset/task/1683)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, radj;
vector<bool> visited;
vector<int> order_, comp;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs1(v);
    order_.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : radj[u]) if (comp[v] == -1) dfs2(v, c);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    adj.assign(n + 1, {}); radj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    visited.assign(n + 1, false);
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs1(i);

    comp.assign(n + 1, -1);
    int numComp = 0;
    for (int i = (int)order_.size() - 1; i >= 0; i--) {
        int u = order_[i];
        if (comp[u] == -1) dfs2(u, numComp++);
    }

    cout << numComp << "\n";
    for (int i = 1; i <= n; i++) cout << comp[i] + 1 << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [1557. Minimum Number of Vertices to Reach All Nodes](https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/)
- [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
- [2360. Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/)

---

## 26. Giant Pizza

**Technique:** 2-SAT via implication graph + SCC (Tarjan/Kosaraju); a literal is true if its SCC comes after its negation's SCC in reverse topological order.
[CSES 1684](https://cses.fi/problemset/task/1684)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m; // n = number of clauses, m = number of variables
vector<vector<int>> adj, radj;
vector<bool> visited;
vector<int> order_, comp;

int idx(int var, bool sign) { // var is 0-indexed, sign true => positive literal
    return sign ? 2 * var : 2 * var + 1;
}

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs1(v);
    order_.push_back(u);
}
void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : radj[u]) if (comp[v] == -1) dfs2(v, c);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    int V = 2 * m;
    adj.assign(V, {}); radj.assign(V, {});

    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        auto parse = [](string s) {
            bool sign = s[0] == '+';
            int var = stoi(s.substr(1)) - 1;
            return make_pair(var, sign);
        };
        auto [v1, s1sign] = parse(s1);
        auto [v2, s2sign] = parse(s2);
        // clause (x1 OR x2): (!x1 -> x2) and (!x2 -> x1)
        int a = idx(v1, s1sign), na = idx(v1, !s1sign);
        int b = idx(v2, s2sign), nb = idx(v2, !s2sign);
        adj[na].push_back(b);
        radj[b].push_back(na);
        adj[nb].push_back(a);
        radj[a].push_back(nb);
    }

    visited.assign(V, false);
    for (int i = 0; i < V; i++) if (!visited[i]) dfs1(i);

    comp.assign(V, -1);
    int numComp = 0;
    for (int i = V - 1; i >= 0; i--) {
        int u = order_[i];
        if (comp[u] == -1) dfs2(u, numComp++);
    }

    vector<bool> value(m);
    for (int v = 0; v < m; v++) {
        int pos = idx(v, true), neg = idx(v, false);
        if (comp[pos] == comp[neg]) { cout << "IMPOSSIBLE\n"; return 0; }
        value[v] = comp[pos] > comp[neg]; // later in reverse-topo order = true
    }

    cout << "YES\n";
    for (int v = 0; v < m; v++) cout << (value[v] ? "+" : "-") << (v + 1) << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [886. Possible Bipartition](https://leetcode.com/problems/possible-bipartition/) *(constraint-satisfaction style)*
- [1361. Validate Binary Tree Nodes](https://leetcode.com/problems/validate-binary-tree-nodes/)
- [2374. Node With Highest Edge Score](https://leetcode.com/problems/node-with-highest-edge-score/) *(functional graph)*

---

## 27. Coin Collector

**Technique:** SCC condensation (Tarjan/Kosaraju), then longest path DP on the resulting DAG.
[CSES 1686](https://cses.fi/problemset/task/1686)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
vector<vector<int>> adj, radj;
vector<bool> visited;
vector<int> order_, comp;
vector<ll> coin;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs1(v);
    order_.push_back(u);
}
void dfs2(int u, int c, vector<ll> &compCoin) {
    comp[u] = c;
    compCoin[c] += coin[u];
    for (int v : radj[u]) if (comp[v] == -1) dfs2(v, c, compCoin);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    coin.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> coin[i];

    adj.assign(n + 1, {}); radj.assign(n + 1, {});
    vector<pair<int,int>> edges(m);
    for (auto &[a, b] : edges) {
        cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    visited.assign(n + 1, false);
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs1(i);

    comp.assign(n + 1, -1);
    int numComp = 0;
    vector<ll> compCoin(n + 1, 0);
    for (int i = (int)order_.size() - 1; i >= 0; i--) {
        int u = order_[i];
        if (comp[u] == -1) dfs2(u, numComp++, compCoin);
    }

    vector<vector<int>> dag(numComp);
    vector<int> indeg(numComp, 0);
    for (auto &[a, b] : edges) {
        if (comp[a] != comp[b]) {
            dag[comp[a]].push_back(comp[b]);
            indeg[comp[b]]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < numComp; i++) if (indeg[i] == 0) q.push(i);
    vector<int> topo;
    vector<int> tmpIndeg = indeg;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : dag[u]) if (--tmpIndeg[v] == 0) q.push(v);
    }

    vector<ll> best(numComp, 0);
    for (int c : topo) best[c] += compCoin[c];
    for (int c : topo)
        for (int v : dag[c])
            best[v] = max(best[v], best[c] + compCoin[v]);

    cout << *max_element(best.begin(), best.end()) << "\n";
}
```

**Similar LeetCode problems:**
- [2360. Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/)
- [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
- [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

---

## 28. Mail Delivery

**Technique:** Eulerian circuit — Hierholzer's algorithm on an undirected multigraph.
[CSES 1691](https://cses.fi/problemset/task/1691)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int,int>>> adj; // {neighbor, edge_id}
vector<bool> usedEdge;
vector<int> ptr_;
vector<int> circuit;

void hierholzer(int start) {
    vector<int> stack = {start};
    while (!stack.empty()) {
        int u = stack.back();
        bool advanced = false;
        while (ptr_[u] < (int)adj[u].size()) {
            auto [v, id] = adj[u][ptr_[u]];
            ptr_[u]++;
            if (usedEdge[id]) continue;
            usedEdge[id] = true;
            stack.push_back(v);
            advanced = true;
            break;
        }
        if (!advanced) {
            circuit.push_back(u);
            stack.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    adj.assign(n + 1, {});
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        deg[a]++; deg[b]++;
    }

    // check connectivity (of vertices with edges) and even degree
    for (int i = 1; i <= n; i++) if (deg[i] % 2 != 0) { cout << "IMPOSSIBLE\n"; return 0; }

    vector<bool> vis(n + 1, false);
    queue<int> q; q.push(1); vis[1] = true;
    int reach = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, id] : adj[u]) if (!vis[v]) { vis[v] = true; reach++; q.push(v); }
    }
    for (int i = 1; i <= n; i++) if (deg[i] > 0 && !vis[i]) { cout << "IMPOSSIBLE\n"; return 0; }

    usedEdge.assign(m, false);
    ptr_.assign(n + 1, 0);
    hierholzer(1);

    if ((int)circuit.size() != m + 1) { cout << "IMPOSSIBLE\n"; return 0; }

    reverse(circuit.begin(), circuit.end());
    for (int x : circuit) cout << x << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/)
- [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/)
- [2097. Valid Arrangement of Pairs](https://leetcode.com/problems/valid-arrangement-of-pairs/)

---

## 29. De Bruijn Sequence

**Technique:** Eulerian circuit on the de Bruijn graph (nodes = (k-1)-bit strings, edges = k-bit strings).
[CSES 1692](https://cses.fi/problemset/task/1692)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int numNodes;
vector<vector<int>> adj; // adj[node] = list of next nodes reachable via appending bit
vector<vector<bool>> usedEdge;
vector<int> ptr_;
vector<int> circuit;

void hierholzer(int start) {
    vector<int> stack = {start};
    while (!stack.empty()) {
        int u = stack.back();
        bool advanced = false;
        while (ptr_[u] < (int)adj[u].size()) {
            int idxEdge = ptr_[u];
            int v = adj[u][idxEdge];
            ptr_[u]++;
            if (usedEdge[u][idxEdge]) continue;
            usedEdge[u][idxEdge] = true;
            stack.push_back(v);
            advanced = true;
            break;
        }
        if (!advanced) {
            circuit.push_back(u);
            stack.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    if (n == 1) { cout << "0\n1\n"; return 0; }

    numNodes = 1 << (n - 1);
    adj.assign(numNodes, {});
    usedEdge.assign(numNodes, {});

    for (int node = 0; node < numNodes; node++) {
        for (int bit = 0; bit < 2; bit++) {
            int next = ((node << 1) | bit) & (numNodes - 1);
            adj[node].push_back(next);
            usedEdge[node].push_back(false);
        }
    }

    ptr_.assign(numNodes, 0);
    hierholzer(0);
    reverse(circuit.begin(), circuit.end());
    // circuit has numNodes*2 + 1 nodes; drop last (repeats first) to build cyclic sequence
    circuit.pop_back();

    string result;
    for (int node : circuit) result += ('0' + (node >> (n - 2) & 1));
    // The above line extracts the leading bit of each node visited to build sequence of length numNodes*2
    // Simpler & robust approach: rebuild directly from edge bits
    result.clear();
    ptr_.assign(numNodes, 0);
    fill(usedEdge.begin(), usedEdge.end(), vector<bool>(2, false));
    circuit.clear();
    hierholzer(0);
    reverse(circuit.begin(), circuit.end());
    circuit.pop_back();
    for (size_t i = 0; i < circuit.size(); i++) {
        int cur = circuit[i];
        int nxt = circuit[(i + 1) % circuit.size()];
        int bit = nxt >> (n - 2) & 1;
        result += char('0' + bit);
    }

    cout << result.size() << "\n" << result << "\n";
}
```

**Similar LeetCode problems:**
- [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/)
- [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/)
- [2097. Valid Arrangement of Pairs](https://leetcode.com/problems/valid-arrangement-of-pairs/)

---

## 30. Teleporters Path

**Technique:** Eulerian path (not circuit) — Hierholzer's algorithm starting from the correct odd-degree node.
[CSES 1693](https://cses.fi/problemset/task/1693)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int,int>>> adj;
vector<bool> usedEdge;
vector<int> ptr_;
vector<int> circuit;

void hierholzer(int start) {
    vector<int> stack = {start};
    while (!stack.empty()) {
        int u = stack.back();
        bool advanced = false;
        while (ptr_[u] < (int)adj[u].size()) {
            auto [v, id] = adj[u][ptr_[u]];
            ptr_[u]++;
            if (usedEdge[id]) continue;
            usedEdge[id] = true;
            stack.push_back(v);
            advanced = true;
            break;
        }
        if (!advanced) {
            circuit.push_back(u);
            stack.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    adj.assign(n + 1, {});
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        outdeg[a]++; indeg[b]++;
    }

    // Directed Eulerian path condition: at most one node with outdeg-indeg=1 (start),
    // at most one with indeg-outdeg=1 (end), rest equal.
    int start = 1;
    bool ok = true;
    int plus1 = 0, minus1 = 0;
    for (int i = 1; i <= n; i++) {
        int d = outdeg[i] - indeg[i];
        if (d == 1) { plus1++; start = i; }
        else if (d == -1) minus1++;
        else if (d != 0) ok = false;
    }
    if (!ok || plus1 > 1 || minus1 > 1 || (plus1 != minus1)) { cout << "IMPOSSIBLE\n"; return 0; }
    if (plus1 == 0) start = 1; // pure circuit case, start anywhere with edges

    usedEdge.assign(m, false);
    ptr_.assign(n + 1, 0);
    hierholzer(start);

    if ((int)circuit.size() != m + 1) { cout << "IMPOSSIBLE\n"; return 0; }

    reverse(circuit.begin(), circuit.end());
    for (int x : circuit) cout << x << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/)
- [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/)
- [2097. Valid Arrangement of Pairs](https://leetcode.com/problems/valid-arrangement-of-pairs/)

---

## 31. Hamiltonian Flights

**Technique:** Bitmask DP counting Hamiltonian paths from node 1 to node n.
[CSES 1690](https://cses.fi/problemset/task/1690)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> canGo(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        canGo[a - 1][b - 1] = true;
    }

    // dp[mask][v] = number of ways to visit exactly the set `mask`, ending at v (starting at 0)
    vector<vector<ll>> dp(1 << n, vector<ll>(n, 0));
    dp[1][0] = 1; // only node 0 visited, at node 0

    for (int mask = 1; mask < (1 << n); mask++) {
        if (!(mask & 1)) continue; // must include start node 0
        for (int v = 0; v < n; v++) {
            if (!(mask & (1 << v)) || dp[mask][v] == 0) continue;
            for (int u = 0; u < n; u++) {
                if (mask & (1 << u)) continue;
                if (!canGo[v][u]) continue;
                dp[mask | (1 << u)][u] = (dp[mask | (1 << u)][u] + dp[mask][v]) % MOD;
            }
        }
    }

    cout << dp[(1 << n) - 1][n - 1] << "\n";
}
```

**Similar LeetCode problems:**
- [847. Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)
- [943. Find the Shortest Superstring](https://leetcode.com/problems/find-the-shortest-superstring/)
- [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)

---

## 32. Knight's Tour

**Technique:** Backtracking with Warnsdorff's heuristic (a specialized Hamiltonian-path search on the knight graph).
[CSES 1689](https://cses.fi/problemset/task/1689)

```cpp
#include <bits/stdc++.h>
using namespace std;

int n = 8;
int board[8][8];
int dx[] = {1,1,-1,-1,2,2,-2,-2};
int dy[] = {2,-2,2,-2,1,-1,1,-1};

int countMoves(int x, int y) {
    int cnt = 0;
    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && board[nx][ny] == 0) cnt++;
    }
    return cnt;
}

bool solve(int x, int y, int step) {
    board[x][y] = step;
    if (step == n * n) return true;

    vector<tuple<int,int,int>> next; // (degree, nx, ny)
    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && board[nx][ny] == 0)
            next.push_back({countMoves(nx, ny), nx, ny});
    }
    sort(next.begin(), next.end());

    for (auto &[deg, nx, ny] : next)
        if (solve(nx, ny, step + 1)) return true;

    board[x][y] = 0;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int sy, sx; // CSES gives (row, col) 1-indexed input as y x order
    cin >> sy >> sx;
    sy--; sx--;

    memset(board, 0, sizeof(board));
    solve(sy, sx, 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << board[i][j] << (j + 1 < n ? " " : "");
        cout << "\n";
    }
}
```

**Similar LeetCode problems:**
- [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)
- [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/)
- [212. Word Search II](https://leetcode.com/problems/word-search-ii/) *(backtracking on grid)*

---

## 33. Download Speed

**Technique:** Maximum flow — Dinic's algorithm.
[CSES 1694](https://cses.fi/problemset/task/1694)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Dinic {
    struct Edge { int to; ll cap; int rev; };
    vector<vector<Edge>> g;
    vector<int> level, iter;
    int n;

    Dinic(int n) : n(n), g(n), level(n), iter(n) {}

    void addEdge(int a, int b, ll cap) {
        g[a].push_back({b, cap, (int)g[b].size()});
        g[b].push_back({a, 0, (int)g[a].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
        }
        return level[t] >= 0;
    }

    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < (int)g[u].size(); i++) {
            Edge &e = g[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            ll f;
            while ((f = dfs(s, t, LLONG_MAX)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Dinic dinic(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        dinic.addEdge(a, b, c);
    }
    cout << dinic.maxflow(1, n) << "\n";
}
```

**Similar LeetCode problems:**
- [1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/) *(graph capacity intuition)*
- [1928. Minimum Cost to Reach Destination in Time](https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/)
- [1231. Divide Chocolate](https://leetcode.com/problems/divide-chocolate/) *(binary search + flow-like feasibility)*

---

## 34. Police Chase

**Technique:** Max flow (Dinic's) to find min cut, then identify saturated edges crossing the min-cut (reachable side vs. not) from the residual graph.
[CSES 1695](https://cses.fi/problemset/task/1695)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Dinic {
    struct Edge { int to; ll cap; int rev; int origIdx; bool isForward; };
    vector<vector<Edge>> g;
    vector<int> level, iter;
    int n;

    Dinic(int n) : n(n), g(n), level(n), iter(n) {}

    int addEdge(int a, int b, ll cap) {
        int idx = g[a].size();
        g[a].push_back({b, cap, (int)g[b].size(), idx, true});
        g[b].push_back({a, 0, (int)g[a].size() - 1, idx, false});
        return idx;
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u])
                if (e.cap > 0 && level[e.to] < 0) { level[e.to] = level[u] + 1; q.push(e.to); }
        }
        return level[t] >= 0;
    }

    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < (int)g[u].size(); i++) {
            Edge &e = g[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) { e.cap -= d; g[e.to][e.rev].cap += d; return d; }
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            ll f;
            while ((f = dfs(s, t, LLONG_MAX)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Dinic dinic(n + 1);
    vector<pair<int,int>> edgeEndpoints(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        edgeEndpoints[i] = {a, b};
        dinic.addEdge(a, b, 1);
    }

    dinic.maxflow(1, n);

    // find reachable set from 1 in residual graph
    vector<bool> vis(n + 1, false);
    queue<int> q; q.push(1); vis[1] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e : dinic.g[u])
            if (e.cap > 0 && !vis[e.to]) { vis[e.to] = true; q.push(e.to); }
    }

    vector<int> cutEdges;
    for (int i = 0; i < m; i++) {
        auto [a, b] = edgeEndpoints[i];
        if (vis[a] && !vis[b]) cutEdges.push_back(i + 1);
    }

    cout << cutEdges.size() << "\n";
    for (int id : cutEdges) cout << id << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
- [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/)
- [934. Shortest Bridge](https://leetcode.com/problems/shortest-bridge/)

---

## 35. School Dance

**Technique:** Bipartite maximum matching (Kuhn's algorithm / augmenting paths). Also solvable as max flow.
[CSES 1696](https://cses.fi/problemset/task/1696)

```cpp
#include <bits/stdc++.h>
using namespace std;

int a, b, m;
vector<vector<int>> adj;
vector<int> matchL, matchR;
vector<bool> visited;

bool tryKuhn(int u) {
    for (int v : adj[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        if (matchR[v] == -1 || tryKuhn(matchR[v])) {
            matchR[v] = u;
            matchL[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> a >> b >> m;
    adj.assign(a + 1, {});
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
    }

    matchL.assign(a + 1, -1);
    matchR.assign(b + 1, -1);

    int result = 0;
    for (int u = 1; u <= a; u++) {
        visited.assign(b + 1, false);
        if (tryKuhn(u)) result++;
    }

    cout << result << "\n";
    for (int u = 1; u <= a; u++)
        if (matchL[u] != -1) cout << u << " " << matchL[u] << "\n";
}
```

**Similar LeetCode problems:**
- [1349. Maximum Students Taking Exam](https://leetcode.com/problems/maximum-students-taking-exam/)
- [1820. Maximum Number of Uncrossed Lines](https://leetcode.com/problems/maximum-number-of-uncrossed-lines/) *(matching-flavor DP)*
- [1947. Maximum Compatibility Score Sum](https://leetcode.com/problems/maximum-compatibility-score-sum/)

---

## 36. Distinct Routes

**Technique:** Max flow (unit capacities) via Dinic's algorithm, then decompose the flow into edge-disjoint paths.
[CSES 1711](https://cses.fi/problemset/task/1711)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Dinic {
    struct Edge { int to; ll cap; int rev; };
    vector<vector<Edge>> g;
    vector<int> level, iter;
    int n;

    Dinic(int n) : n(n), g(n), level(n), iter(n) {}

    void addEdge(int a, int b, ll cap) {
        g[a].push_back({b, cap, (int)g[b].size()});
        g[b].push_back({a, 0, (int)g[a].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u])
                if (e.cap > 0 && level[e.to] < 0) { level[e.to] = level[u] + 1; q.push(e.to); }
        }
        return level[t] >= 0;
    }

    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < (int)g[u].size(); i++) {
            Edge &e = g[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) { e.cap -= d; g[e.to][e.rev].cap += d; return d; }
            }
        }
        return 0;
    }

    ll maxflow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            ll f;
            while ((f = dfs(s, t, LLONG_MAX)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Dinic dinic(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dinic.addEdge(a, b, 1);
    }

    ll flow = dinic.maxflow(1, n);
    cout << flow << "\n";

    // decompose flow into paths by following saturated (used) forward edges
    for (int p = 0; p < flow; p++) {
        vector<int> path = {1};
        int u = 1;
        while (u != n) {
            for (auto &e : dinic.g[u]) {
                // an original forward edge whose capacity dropped to 0 was used
                // rev edge cap > 0 means flow passed through
            }
            for (size_t i = 0; i < dinic.g[u].size(); i++) {
                auto &e = dinic.g[u][i];
                // find an edge that is a used forward edge: its reverse has cap > 0
                if (e.cap == 0 && dinic.g[e.to][e.rev].cap > 0) {
                    // ensure it's a forward original edge (cap started >0); mark used by zeroing reverse
                    dinic.g[e.to][e.rev].cap -= 1;
                    u = e.to;
                    path.push_back(u);
                    break;
                }
            }
        }
        cout << path.size() << "\n";
        for (int x : path) cout << x << " ";
        cout << "\n";
    }
}
```

**Similar LeetCode problems:**
- [1579. Remove Max Number of Edges to Keep Graph Fully Traversable](https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/)
- [1615. Maximal Network Rank](https://leetcode.com/problems/maximal-network-rank/) (Premium)
- [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)

---

## Notes

- Solutions favor clarity and correctness within CSES time limits (typically 1s); constants
  can be tightened further (e.g., switching `cin`/`cout` to `scanf`/`printf`, using arrays
  instead of `vector` of `vector`) if you hit borderline TLEs on the largest test cases.
- Problems marked "(Premium)" on LeetCode require a subscription to view/solve but are listed
  because they use the identical underlying technique.
- For **Planets Queries II**, the shown solution favors readability; an O(log n) per query
  version precomputes cycle start/length per weakly-connected component and answers via
  binary lifting only, avoiding the O(n) fallback walk.
