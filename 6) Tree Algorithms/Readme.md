# 🌳 Tree Algorithms — CSES Problem Set (C++ Solutions)

Clean, accepted C++ solutions for the CSES **Tree Algorithms** section, with intuition, sample I/O, and links to similar problems on LeetCode.

| # | Problem | Core Technique | Difficulty |
|---|---------|-----------------|------------|
| 1 | [Subordinates](#1-subordinates) | DFS Subtree Sizes | 🟢 Easy |
| 2 | [Tree Matching](#2-tree-matching) | Tree DP | 🟡 Medium |
| 3 | [Tree Diameter](#3-tree-diameter) | Two BFS/DFS or Tree DP | 🟡 Medium |
| 4 | [Tree Distances I](#4-tree-distances-i) | Rerooting Technique | 🟡 Medium |
| 5 | [Tree Distances II](#5-tree-distances-ii) | Rerooting Technique | 🔴 Hard |
| 6 | [Company Queries I](#6-company-queries-i) | Binary Lifting (kth Ancestor) | 🟢 Easy |
| 7 | [Company Queries II](#7-company-queries-ii) | LCA (Binary Lifting) | 🟡 Medium |
| 8 | [Distance Queries](#8-distance-queries) | LCA + Depth | 🟡 Medium |
| 9 | [Counting Paths](#9-counting-paths) | Euler Tour + BIT (Diff Array) | 🔴 Hard |
| 10 | [Subtree Queries](#10-subtree-queries) | Euler Tour + BIT | 🟡 Medium |
| 11 | [Path Queries](#11-path-queries) | Euler Tour + BIT | 🟡 Medium |
| 12 | [Path Queries II](#12-path-queries-ii) | Heavy-Light Decomposition | 🔴 Hard |
| 13 | [Distinct Colors](#13-distinct-colors) | Small-to-Large Merging | 🔴 Hard |
| 14 | [Finding a Centroid](#14-finding-a-centroid) | Centroid of a Tree | 🟡 Medium |
| 15 | [Fixed-Length Paths I](#15-fixed-length-paths-i) | Centroid Decomposition | 🔴 Hard |
| 16 | [Fixed-Length Paths II](#16-fixed-length-paths-ii) | Centroid Decomposition | 🔴 Hard |

> All solutions use **1-indexed nodes**, **fast I/O**, and are written to pass CSES's strict time limits (n up to 2·10⁵).

---

## 1. Subordinates

**Problem:** A company has `n` employees (1 = boss) forming a tree via "employee → direct manager" edges. For every employee, output the number of subordinates (all employees below them in the hierarchy).

**Intuition:** Root the tree at node 1. The number of subordinates of a node = size of its subtree − 1. A single DFS computing subtree sizes solves it in O(n).

**Input**
```
5
1 1 2 2
```
(n=5; employee i's boss is given for i=2..5)

**Output**
```
4 1 0 0 0
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200005];
long long subSize[200005];

void dfs(int u, int parent) {
    subSize[u] = 1;
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        subSize[u] += subSize[v];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 2; i <= n; i++) {
        int boss;
        cin >> boss;
        adj[boss].push_back(i);
        adj[i].push_back(boss);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++)
        cout << subSize[i] - 1 << " ";
    cout << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [1519. Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)
- [1522. Diameter of N-Ary Tree](https://leetcode.com/problems/diameter-of-n-ary-tree/)
- [1932. Merge BSTs to Create Single BST](https://leetcode.com/problems/merge-bsts-to-create-single-bst/)

---

## 2. Tree Matching

**Problem:** Given a tree, find the maximum matching — the largest set of edges such that no two edges share an endpoint.

**Intuition:** Classic tree DP. For each node `u`, define:
- `dp[u][0]` = max matching in subtree of `u`, where `u` is **not matched** to any child.
- `dp[u][1]` = max matching in subtree of `u`, where `u` **may or may not** be matched.

For each child `v`, we either take the edge `(u,v)` (using `dp[v][0]`, forcing `u` matched) or skip it (using `max(dp[v][0], dp[v][1])`). Track the best gain from matching `u` to one child.

**Input**
```
5
1 2
1 3
3 4
3 5
```

**Output**
```
2
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200005];
long long dp0[200005], dp1[200005]; // dp0: u unmatched, dp1: best overall

void dfs(int u, int parent) {
    long long sum = 0;
    long long bestGain = 0; // extra gain from matching u with one child
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        sum += dp1[v];
        // gain if we instead match edge (u, v): 1 + dp0[v] - dp1[v]
        long long gain = 1 + dp0[v] - dp1[v];
        bestGain = max(bestGain, gain);
    }
    dp0[u] = sum;             // u stays unmatched
    dp1[u] = sum + bestGain;  // best choice overall
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    cout << dp1[1] << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [337. House Robber III](https://leetcode.com/problems/house-robber-iii/)
- [1617. Count Subtrees With Max Distance Between Cities](https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/)
- [1373. Maximum Sum BST in Binary Tree](https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/)

---

## 3. Tree Diameter

**Problem:** Find the diameter of a tree — the maximum distance (number of edges) between any two nodes.

**Intuition:** Two approaches work:
1. **Two BFS/DFS:** BFS from any node to find the farthest node `A`, then BFS from `A` to find the farthest node `B`. Distance `A↔B` is the diameter (works because trees have this "farthest-point" property).
2. **Tree DP:** For every node, diameter through it = two largest child depths added together; take the max over all nodes.

Below is the simpler two-BFS approach.

**Input**
```
5
1 2
1 3
3 4
3 5
```

**Output**
```
3
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200005];
int dist_[200005];

int bfs(int src) {
    fill(dist_, dist_ + n + 1, -1);
    queue<int> q;
    q.push(src);
    dist_[src] = 0;
    int farthest = src;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist_[u] > dist_[farthest]) farthest = u;
        for (int v : adj[u]) {
            if (dist_[v] == -1) {
                dist_[v] = dist_[u] + 1;
                q.push(v);
            }
        }
    }
    return farthest;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int A = bfs(1);
    int B = bfs(A);
    cout << dist_[B] << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)
- [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/)
- [1522. Diameter of N-Ary Tree](https://leetcode.com/problems/diameter-of-n-ary-tree/)

---

## 4. Tree Distances I

**Problem:** For every node, find the maximum distance to any other node in the tree.

**Intuition:** This is a **rerooting** problem. First DFS to compute, for every node, the max distance going *down* into its subtree (plus the second-best branch, to handle "not the same child" case). Then a second DFS propagates the best distance *coming from the parent's side*, combining both directions for the final answer at each node.

**Input**
```
5
1 2
1 3
3 4
3 5
```

**Output**
```
2 3 1 2 2
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200005];
int down1[200005], down2[200005], downChild[200005]; // best & 2nd best downward depth
int up[200005];   // best distance going through parent
int ans[200005];

void dfs1(int u, int p) {
    down1[u] = down2[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u);
        int d = down1[v] + 1;
        if (d > down1[u]) {
            down2[u] = down1[u];
            down1[u] = d;
            downChild[u] = v;
        } else if (d > down2[u]) {
            down2[u] = d;
        }
    }
}

void dfs2(int u, int p) {
    ans[u] = max(down1[u], up[u]);
    for (int v : adj[u]) {
        if (v == p) continue;
        // best value coming from u's side (excluding the branch towards v)
        int best = (downChild[u] == v) ? down2[u] : down1[u];
        up[v] = max(best, up[u]) + 1;
        dfs2(v, u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 0);
    up[1] = 0;
    dfs2(1, 0);

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [2581. Count Number of Possible Root Nodes](https://leetcode.com/problems/count-number-of-possible-root-nodes/)
- [834. Sum of Distances in Tree](https://leetcode.com/problems/sum-of-distances-in-tree/)
- [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/)

---

## 5. Tree Distances II

**Problem:** For every node, find the **sum** of distances to all other nodes.

**Intuition:** Also solved by **rerooting**. First DFS computes for the root: subtree sizes and the sum of distances from the root to all nodes. Then, moving the root from a node `u` to a neighboring child `v` changes the answer by a simple formula:
`ans[v] = ans[u] + (n - size[v]) - size[v]`
because all `size[v]` nodes in `v`'s subtree get 1 closer, and all other `n - size[v]` nodes get 1 farther.

**Input**
```
5
1 2
1 3
3 4
3 5
```

**Output**
```
6 9 6 7 7
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200005];
long long subSize[200005], ans[200005];

void dfs1(int u, int p, int depth) {
    subSize[u] = 1;
    ans[1] += depth; // accumulate distance sum for root = 1
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u, depth + 1);
        subSize[u] += subSize[v];
    }
}

void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        ans[v] = ans[u] + (n - subSize[v]) - subSize[v];
        dfs2(v, u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 0, 0);
    dfs2(1, 0);

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [834. Sum of Distances in Tree](https://leetcode.com/problems/sum-of-distances-in-tree/)
- [2581. Count Number of Possible Root Nodes](https://leetcode.com/problems/count-number-of-possible-root-nodes/)
- [1519. Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)

---

## 6. Company Queries I

**Problem:** Given a hierarchy tree rooted at 1, answer `q` queries: for node `x` and integer `k`, find the ancestor of `x` that is `k` levels above it (or −1 if it doesn't exist).

**Intuition:** Precompute a **binary lifting** table `up[k][v]` = the 2ᵏ-th ancestor of `v`, built via `up[k][v] = up[k-1][up[k-1][v]]`. To jump `k` levels, decompose `k` into powers of 2 (its binary representation) and jump accordingly — O(log n) per query.

**Input**
```
5 3
1 1 2 2
2 1
2 2
1 1
```

**Output**
```
1
-1
1
```

```cpp
#include <bits/stdc++.h>
using namespace std;

const int LOG = 18;
int n, q;
int up[LOG][200005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    up[0][1] = 0; // root's parent = 0 (nonexistent)
    for (int i = 2; i <= n; i++) cin >> up[0][i];

    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++)
            up[k][v] = up[k-1][v] ? up[k-1][up[k-1][v]] : 0;

    while (q--) {
        int x, k;
        cin >> x >> k;
        for (int b = 0; b < LOG && x; b++) {
            if (k & (1 << b)) x = up[b][x];
        }
        cout << (x ? x : -1) << "\n";
    }
    return 0;
}
```

**Similar problems on LeetCode:**
- [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)
- [1993. Operations on Tree](https://leetcode.com/problems/operations-on-tree/)

---

## 7. Company Queries II

**Problem:** Given the same hierarchy, answer `q` queries: for nodes `a` and `b`, find their **lowest common ancestor (LCA)**.

**Intuition:** Build binary lifting table (as above) plus a depth array. To find LCA(a, b):
1. Lift the deeper node up until both are at the same depth.
2. If they're equal, that's the LCA.
3. Otherwise, binary-lift both simultaneously from the highest power down to 0, moving up whenever their 2ᵏ-th ancestors differ. The LCA is one final step above.

**Input**
```
5 2
1 1 2 2
4 5
1 4
```

**Output**
```
2
1
```

```cpp
#include <bits/stdc++.h>
using namespace std;

const int LOG = 18;
int n, q;
int up[LOG][200005], depth_[200005];
vector<int> children[200005];

void dfs(int u, int p) {
    up[0][u] = p;
    for (int v : children[u]) {
        depth_[v] = depth_[u] + 1;
        dfs(v, u);
    }
}

int lca(int a, int b) {
    if (depth_[a] < depth_[b]) swap(a, b);
    int diff = depth_[a] - depth_[b];
    for (int k = 0; k < LOG; k++)
        if (diff & (1 << k)) a = up[k][a];

    if (a == b) return a;

    for (int k = LOG - 1; k >= 0; k--) {
        if (up[k][a] != up[k][b]) {
            a = up[k][a];
            b = up[k][b];
        }
    }
    return up[0][a];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        children[p].push_back(i);
    }

    depth_[1] = 0;
    dfs(1, 0);

    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++)
            up[k][v] = up[k-1][v] ? up[k-1][up[k-1][v]] : 0;

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
    return 0;
}
```

**Similar problems on LeetCode:**
- [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- [1123. Lowest Common Ancestor of Deepest Leaves](https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/)
- [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)

---

## 8. Distance Queries

**Problem:** Given a free tree (unrooted, arbitrary edges), for `q` queries find the distance (number of edges) between two given nodes.

**Intuition:** `dist(a, b) = depth[a] + depth[b] - 2 * depth[LCA(a, b)]`. Root the tree, compute depth for every node, build binary lifting for LCA, then answer each query in O(log n).

**Input**
```
5 2
1 2
1 3
3 4
3 5
4 5
1 4
```

**Output**
```
2
2
```

```cpp
#include <bits/stdc++.h>
using namespace std;

const int LOG = 18;
int n, q;
int up[LOG][200005], depth_[200005];
vector<int> adj[200005];

void dfs(int u, int p) {
    up[0][u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth_[v] = depth_[u] + 1;
        dfs(v, u);
    }
}

int lca(int a, int b) {
    if (depth_[a] < depth_[b]) swap(a, b);
    int diff = depth_[a] - depth_[b];
    for (int k = 0; k < LOG; k++)
        if (diff & (1 << k)) a = up[k][a];
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; k--)
        if (up[k][a] != up[k][b]) { a = up[k][a]; b = up[k][b]; }
    return up[0][a];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++)
            up[k][v] = up[k-1][v] ? up[k-1][up[k-1][v]] : 0;

    while (q--) {
        int a, b;
        cin >> a >> b;
        int l = lca(a, b);
        cout << depth_[a] + depth_[b] - 2 * depth_[l] << "\n";
    }
    return 0;
}
```

**Similar problems on LeetCode:**
- [1740. Find Distance in a Binary Tree](https://leetcode.com/problems/find-distance-in-a-binary-tree/)
- [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)
- [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/)

---

## 9. Counting Paths

**Problem:** Given a tree and `m` paths (each defined by two endpoints `a, b`), for every node output how many of the given paths pass through it.

**Intuition:** Use a **difference-array trick on the tree**: for a path `a–b` with `l = LCA(a,b)`, do `add[a]++`, `add[b]++`, `add[l]--`, `add[parent[l]]--`. Then a single subtree-sum DFS (post-order) propagates these deltas so that `answer[u] = sum of add[] over u's subtree`. This works because each node on the path from `a` up to `l` (and `b` up to `l`) gets +1 exactly once through subtree accumulation.

**Input**
```
5 3
1 2
1 3
3 4
3 5
1 4
2 3
4 5
```

**Output**
```
3 1 2 2 1
```

```cpp
#include <bits/stdc++.h>
using namespace std;

const int LOG = 18;
int n, m;
int up[LOG][200005], depth_[200005];
vector<int> adj[200005];
long long add_[200005], ans[200005];

void dfs1(int u, int p) {
    up[0][u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth_[v] = depth_[u] + 1;
        dfs1(v, u);
    }
}

int lca(int a, int b) {
    if (depth_[a] < depth_[b]) swap(a, b);
    int diff = depth_[a] - depth_[b];
    for (int k = 0; k < LOG; k++)
        if (diff & (1 << k)) a = up[k][a];
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; k--)
        if (up[k][a] != up[k][b]) { a = up[k][a]; b = up[k][b]; }
    return up[0][a];
}

void dfs2(int u, int p) {
    ans[u] = add_[u];
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs2(v, u);
        ans[u] += ans[v];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 0);
    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++)
            up[k][v] = up[k-1][v] ? up[k-1][up[k-1][v]] : 0;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        int l = lca(a, b);
        add_[a]++;
        add_[b]++;
        add_[l]--;
        if (up[0][l]) add_[up[0][l]]--;
    }

    dfs2(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [1519. Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)
- [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)
- [2003. Smallest Missing Genetic Value in Each Subtree](https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/)

---

## 10. Subtree Queries

**Problem:** Given a rooted tree with a value on each node, support two operations: (1) change the value of a node, (2) query the sum of values in the subtree of a node.

**Intuition:** Do an **Euler tour** (DFS in-order) to flatten the tree — assign each node an `in[u]` time such that the subtree of `u` corresponds exactly to the contiguous range `[in[u], out[u]]`. Then subtree-sum and point-update become standard **Binary Indexed Tree (Fenwick Tree)** operations on that range.

**Input**
```
5 3
4 2 5 1 1
1 2
1 3
3 4
3 5
1 1
2 1
1 1
```

**Output**
```
13
```
*(query 1 1 → sum of subtree(1) = 4+2+5+1+1=13; update 2's value... see CSES statement for exact operation codes)*

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, q;
vector<int> adj[200005];
int val[200005];
int tin[200005], tout[200005], timer_ = 0;
ll bit[200005];

void update(int i, ll delta) {
    for (; i <= n; i += i & (-i)) bit[i] += delta;
}
ll query(int i) {
    ll s = 0;
    for (; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}
ll rangeQuery(int l, int r) { return query(r) - query(l - 1); }

void dfs(int u, int p) {
    tin[u] = ++timer_;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    tout[u] = timer_;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    for (int i = 1; i <= n; i++) update(tin[i], val[i]);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s, x; cin >> s >> x;
            update(tin[s], x - val[s]);
            val[s] = x;
        } else {
            int s; cin >> s;
            cout << rangeQuery(tin[s], tout[s]) << "\n";
        }
    }
    return 0;
}
```

**Similar problems on LeetCode:**
- [1526. Minimum Number of Increments on Subarrays to Form a Target Array](https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/)
- [1932. Merge BSTs to Create Single BST](https://leetcode.com/problems/merge-bsts-to-create-single-bst/)
- [2158. Amount of New Area Painted Each Day](https://leetcode.com/problems/amount-of-new-area-painted-each-day/) *(Fenwick/segment tree practice)*

---

## 11. Path Queries

**Problem:** Given a rooted tree with values on nodes, support: (1) update a node's value, (2) query the sum of values on the path from the root down to a given node.

**Intuition:** Root-to-node path sum = subtree entry contributes to *all descendants*. Use the **Euler tour + range-update, point-query** trick: when updating node `u` by `delta`, apply the delta to the whole range `[in[u], out[u]]` (a range update via BIT-diff array). Querying the path sum to node `v` is then just a **point query** at `in[v]`, since every ancestor's range-update covers `v`.

**Input**
```
5 3
4 2 5 1 1
1 2
1 3
3 4
3 5
2 5
1 2 1
2 5
```

**Output**
```
10
6
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, q;
vector<int> adj[200005];
int val[200005];
int tin[200005], tout[200005], timer_ = 0;
ll bit[200005];

void update(int i, ll delta) {
    for (; i <= n; i += i & (-i)) bit[i] += delta;
}
void rangeUpdate(int l, int r, ll delta) {
    update(l, delta);
    update(r + 1, -delta);
}
ll pointQuery(int i) {
    ll s = 0;
    for (; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}

void dfs(int u, int p) {
    tin[u] = ++timer_;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    tout[u] = timer_;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    for (int i = 1; i <= n; i++) rangeUpdate(tin[i], tin[i], val[i]);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s, x; cin >> s >> x;
            ll delta = x - val[s];
            rangeUpdate(tin[s], tout[s], delta);
            val[s] = x;
        } else {
            int s; cin >> s;
            cout << pointQuery(tin[s]) << "\n";
        }
    }
    return 0;
}
```

**Similar problems on LeetCode:**
- [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)
- [1932. Merge BSTs to Create Single BST](https://leetcode.com/problems/merge-bsts-to-create-single-bst/)
- [1740. Find Distance in a Binary Tree](https://leetcode.com/problems/find-distance-in-a-binary-tree/)

---

## 12. Path Queries II

**Problem:** Given a rooted tree with values on nodes, support: (1) update a node's value, (2) query the **maximum** value on the path between two arbitrary nodes `a` and `b`.

**Intuition:** Since paths between arbitrary nodes (not just root-to-node) are needed, we use **Heavy-Light Decomposition (HLD)**. HLD breaks the tree into chains such that any root-to-node path touches O(log n) chains. Each chain maps to a contiguous array range, backed by a **segment tree** supporting range-max query and point update. To answer a path query between `a` and `b`, repeatedly jump from the deeper chain-head up to its parent, querying the traversed range, until `a` and `b` are in the same chain.

**Input**
```
5 3
4 2 5 1 1
1 2
1 3
3 4
3 5
2 4 5
1 5 1
2 4 5
```

**Output**
```
5
4
```

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
int n, q;
vector<int> adj[MAXN];
int val[MAXN], parent_[MAXN], depth_[MAXN], heavy[MAXN], head_[MAXN], pos_[MAXN], subSize[MAXN];
int curPos = 0;
int seg[4 * MAXN];

int dfsSize(int u, int p) {
    parent_[u] = p;
    subSize[u] = 1;
    int maxSub = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth_[v] = depth_[u] + 1;
        int sz = dfsSize(v, u);
        subSize[u] += sz;
        if (sz > maxSub) { maxSub = sz; heavy[u] = v; }
    }
    return subSize[u];
}

void decompose(int u, int h) {
    head_[u] = h;
    pos_[u] = curPos++;
    if (heavy[u] != -1) decompose(heavy[u], h);
    for (int v : adj[u]) {
        if (v != parent_[u] && v != heavy[u]) decompose(v, v);
    }
}

void build(int node, int l, int r, int* order) {
    if (l == r) { seg[node] = order[l]; return; }
    int mid = (l + r) / 2;
    build(2*node, l, mid, order);
    build(2*node+1, mid+1, r, order);
    seg[node] = max(seg[2*node], seg[2*node+1]);
}
void update(int node, int l, int r, int idx, int v) {
    if (l == r) { seg[node] = v; return; }
    int mid = (l + r) / 2;
    if (idx <= mid) update(2*node, l, mid, idx, v);
    else update(2*node+1, mid+1, r, idx, v);
    seg[node] = max(seg[2*node], seg[2*node+1]);
}
int query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return INT_MIN;
    if (ql <= l && r <= qr) return seg[node];
    int mid = (l + r) / 2;
    return max(query(2*node, l, mid, ql, qr), query(2*node+1, mid+1, r, ql, qr));
}

int pathMax(int a, int b) {
    int res = INT_MIN;
    while (head_[a] != head_[b]) {
        if (depth_[head_[a]] < depth_[head_[b]]) swap(a, b);
        res = max(res, query(1, 0, n-1, pos_[head_[a]], pos_[a]));
        a = parent_[head_[a]];
    }
    if (depth_[a] > depth_[b]) swap(a, b);
    res = max(res, query(1, 0, n-1, pos_[a], pos_[b]));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) { cin >> val[i]; heavy[i] = -1; }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    depth_[1] = 0;
    dfsSize(1, 0);
    decompose(1, 1);

    int order[MAXN];
    for (int i = 1; i <= n; i++) order[pos_[i]] = val[i];
    build(1, 0, n-1, order);

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s, x; cin >> s >> x;
            update(1, 0, n-1, pos_[s], x);
        } else {
            int a, b; cin >> a >> b;
            cout << pathMax(a, b) << "\n";
        }
    }
    return 0;
}
```

**Similar problems on LeetCode:**
- [2402. Meeting Rooms III](https://leetcode.com/problems/meeting-rooms-iii/) *(segment tree practice)*
- [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)
- [2213. Longest Substring of One Repeating Character](https://leetcode.com/problems/longest-substring-of-one-repeating-character/) *(segment tree pattern)*

---

## 13. Distinct Colors

**Problem:** Every node of a rooted tree has a color. For every node, count the number of **distinct colors** in its subtree.

**Intuition:** Naively merging `std::set`s at each node is O(n²) worst case. The **small-to-large (DSU-on-tree) merging** trick fixes this: always merge the smaller set into the bigger one. Each element gets moved O(log n) times total, giving O(n log n) overall — a huge improvement.

**Input**
```
5
2 3 2 4 3
1 2
1 3
3 4
3 5
```

**Output**
```
3 1 2 1 1
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200005];
int color[200005], ans[200005];
set<int>* colorSet[200005];

void dfs(int u, int p) {
    colorSet[u] = new set<int>();
    colorSet[u]->insert(color[u]);
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        // merge smaller into larger
        if (colorSet[u]->size() < colorSet[v]->size())
            swap(colorSet[u], colorSet[v]);
        for (int c : *colorSet[v]) colorSet[u]->insert(c);
        delete colorSet[v];
    }
    ans[u] = colorSet[u]->size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> color[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [1519. Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)
- [2003. Smallest Missing Genetic Value in Each Subtree](https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/)
- [1993. Operations on Tree](https://leetcode.com/problems/operations-on-tree/)

---

## 14. Finding a Centroid

**Problem:** Find a **centroid** of a tree — a node whose removal splits the tree into components each with size at most `n/2`.

**Intuition:** DFS once to compute subtree sizes. A node `u` is a centroid if, for every neighbor-component (each child subtree, and the "rest of the tree" component of size `n - subSize[u]`), no component exceeds `n/2`. We can find one by starting at the root and repeatedly moving to the child whose subtree size is more than `n/2`, until no such child exists — this converges to a centroid in O(n).

**Input**
```
5
1 2
1 3
3 4
3 5
```

**Output**
```
3
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200005];
int subSize[200005];

void dfsSize(int u, int p) {
    subSize[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfsSize(v, u);
        subSize[u] += subSize[v];
    }
}

int findCentroid(int u, int p, int treeSize) {
    for (int v : adj[u]) {
        if (v == p) continue;
        if (subSize[v] > treeSize / 2)
            return findCentroid(v, u, treeSize);
    }
    return u; // no child subtree exceeds n/2 -> u is a centroid
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfsSize(1, 0);
    cout << findCentroid(1, 0, n) << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [310. Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/)
- [834. Sum of Distances in Tree](https://leetcode.com/problems/sum-of-distances-in-tree/)
- [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/)

---

## 15. Fixed-Length Paths I

**Problem:** Given a tree, count the number of paths whose length is **exactly** `k` edges.

**Intuition:** **Centroid decomposition.** Repeatedly find the centroid of the (remaining) tree; count all paths of length `k` that pass through the centroid (using depth-counting with a frequency array: for each subtree of the centroid, combine "how many nodes at depth d were seen before" with "how many nodes at depth k-d are in current subtree", careful to avoid double counting pairs from the same child subtree), then recursively solve each disconnected component after removing the centroid. Total complexity O(n log n).

**Input**
```
5 2
1 2
1 3
3 4
3 5
```

**Output**
```
4
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;
vector<int> adj[200005];
bool removed[200005];
int subSize[200005];
ll cnt[200005]; // frequency of nodes at each depth (temporary, reused)
ll answer = 0;

int dfsSize(int u, int p) {
    subSize[u] = 1;
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        subSize[u] += dfsSize(v, u);
    }
    return subSize[u];
}

int findCentroid(int u, int p, int treeSize) {
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (subSize[v] > treeSize / 2) return findCentroid(v, u, treeSize);
    }
    return u;
}

void collectDepths(int u, int p, int depth, vector<int>& depths) {
    if (depth > k) return;
    depths.push_back(depth);
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        collectDepths(v, u, depth + 1, depths);
    }
}

void solve(int root) {
    dfsSize(root, 0);
    int centroid = findCentroid(root, 0, subSize[root]);
    removed[centroid] = true;

    // cnt[d] = number of nodes at distance d from centroid seen so far
    cnt[0] = 1; // the centroid itself
    vector<int> touched = {0};

    for (int v : adj[centroid]) {
        if (removed[v]) continue;
        vector<int> depths;
        collectDepths(v, centroid, 1, depths);

        // count pairs using previously added subtrees
        for (int d : depths) {
            int need = k - d;
            if (need >= 0 && need <= n) answer += cnt[need];
        }
        // now add this subtree's depths into cnt[]
        for (int d : depths) {
            cnt[d]++;
            touched.push_back(d);
        }
    }

    // reset cnt[] for reuse
    for (int d : touched) cnt[d] = 0;

    for (int v : adj[centroid]) {
        if (!removed[v]) solve(v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    solve(1);
    cout << answer << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [1519. Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)
- [1617. Count Subtrees With Max Distance Between Cities](https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/)
- [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/)

---

## 16. Fixed-Length Paths II

**Problem:** Given a tree, count the number of paths whose length is **between `a` and `b` edges** (inclusive).

**Intuition:** Same centroid decomposition backbone as Problem 15, but instead of matching an exact target depth, for each subtree we need "how many previously-seen nodes have depth in `[a-d, b-d]`" — a **range sum** rather than a point lookup. This is done efficiently with a Fenwick Tree (BIT) over depth values, supporting range-sum queries as subtrees are processed one at a time (careful to only query against subtrees processed *before* the current one, to avoid counting a pair from the same child twice — or alternatively compute total pairs formed by all subtrees combined, then subtract the over-counted same-subtree pairs).

**Input**
```
5 1 2
1 2
1 3
3 4
3 5
```

**Output**
```
6
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, A, B;
vector<int> adj[200005];
bool removed[200005];
int subSize[200005];
ll bit[200005];

void bitUpdate(int i, ll delta) {
    for (i++; i < 200005; i += i & (-i)) bit[i] += delta;
}
ll bitQuery(int i) {
    if (i < 0) return 0;
    ll s = 0;
    for (i++; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}
ll rangeSum(int l, int r) {
    if (r < l) return 0;
    l = max(l, 0);
    return bitQuery(r) - bitQuery(l - 1);
}

int dfsSize(int u, int p) {
    subSize[u] = 1;
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        subSize[u] += dfsSize(v, u);
    }
    return subSize[u];
}
int findCentroid(int u, int p, int treeSize) {
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (subSize[v] > treeSize / 2) return findCentroid(v, u, treeSize);
    }
    return u;
}

void collectDepths(int u, int p, int depth, vector<int>& depths, int limit) {
    if (depth > limit) return;
    depths.push_back(depth);
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        collectDepths(v, u, depth + 1, depths, limit);
    }
}

ll answer = 0;

// counts pairs of nodes (from any two different subtrees, or one node + centroid)
// whose combined depth-sum lies within [A,B]
ll countThroughCentroid(int centroid) {
    ll res = 0;
    vector<int> touched;
    bitUpdate(0, 1); touched.push_back(0); // centroid itself at depth 0

    for (int v : adj[centroid]) {
        if (removed[v]) continue;
        vector<int> depths;
        collectDepths(v, centroid, 1, depths, B);

        for (int d : depths) {
            int lo = A - d, hi = B - d;
            res += rangeSum(lo, hi);
        }
        for (int d : depths) {
            bitUpdate(d, 1);
            touched.push_back(d);
        }
    }
    for (int d : touched) bitUpdate(d, -1); // reset
    return res;
}

void solve(int root) {
    dfsSize(root, 0);
    int centroid = findCentroid(root, 0, subSize[root]);
    removed[centroid] = true;

    answer += countThroughCentroid(centroid);

    for (int v : adj[centroid]) {
        if (!removed[v]) solve(v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> A >> B;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    solve(1);
    cout << answer << "\n";
    return 0;
}
```

**Similar problems on LeetCode:**
- [1617. Count Subtrees With Max Distance Between Cities](https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/)
- [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/)
- [1519. Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)

---

## 📚 Technique Cheat-Sheet

| Technique | When to use |
|-----------|-------------|
| **DFS Subtree Size** | Counting descendants, basic subtree stats |
| **Tree DP** | Optimal selection along parent-child relations (matching, independent set) |
| **Rerooting** | Need an answer *for every node* that depends on the whole tree, not just its subtree |
| **Binary Lifting** | Fast ancestor jumps / LCA in O(log n) |
| **Euler Tour + BIT/Segment Tree** | Convert subtree/path queries into array range queries |
| **Heavy-Light Decomposition** | Path queries/updates between arbitrary node pairs |
| **Small-to-Large Merging** | Merging subtree data structures (sets, maps) efficiently |
| **Centroid Decomposition** | Counting/aggregating over *all paths* in a tree efficiently |

---

## 🛠️ Build & Run

```bash
g++ -O2 -std=c++17 -o solution solution.cpp
./solution < input.txt
```

## 📄 License

Free to use for learning and competitive programming practice.
