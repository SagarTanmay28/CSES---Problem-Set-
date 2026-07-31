# CSES Dynamic Programming — C++ Solutions

Each problem below includes two accepted C++ approaches:

1. **Top-Down (Recursion + Memoization)**
2. **Bottom-Up (Tabulation)**

...followed by 2–3 similar LeetCode problems for extra practice.

> All solutions use `long long` and `MOD = 1e9+7` where the CSES problem requires modular output. Fast I/O (`ios_base::sync_with_stdio(false); cin.tie(0);`) is assumed in `main()` for every solution but omitted from snippets for brevity.

---

## 1. Dice Combinations
**Tag:** 1D DP · 🟢 Easy
Count the number of ways to construct sum `n` using dice throws (1–6), order matters.

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
vector<long long> memo;

long long solve(int n) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    if (memo[n] != -1) return memo[n];
    long long ways = 0;
    for (int f = 1; f <= 6; f++)
        ways = (ways + solve(n - f)) % MOD;
    return memo[n] = ways;
}

int main() {
    int n; cin >> n;
    memo.assign(n + 1, -1);
    cout << solve(n) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    int n; cin >> n;
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int f = 1; f <= 6; f++)
            if (i - f >= 0) dp[i] = (dp[i] + dp[i - f]) % MOD;
    cout << dp[n] << "\n";
}
```

**Similar LeetCode problems:**
- [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
- [377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/)
- [1137. N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/)

---

## 2. Minimizing Coins
**Tag:** 1D DP · 🟢 Easy
Find the minimum number of coins to form sum `x` (unbounded, unlimited supply of each coin).

### Recursion + Memoization
```cpp
const long long INF = 1e9;
vector<int> coins;
vector<long long> memo;

long long solve(int x) {
    if (x == 0) return 0;
    if (x < 0) return INF;
    if (memo[x] != -1) return memo[x];
    long long best = INF;
    for (int c : coins) best = min(best, solve(x - c) + 1);
    return memo[x] = best;
}

int main() {
    int n, x; cin >> n >> x;
    coins.resize(n);
    for (auto &c : coins) cin >> c;
    memo.assign(x + 1, -1);
    long long ans = solve(x);
    cout << (ans >= INF ? -1 : ans) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    int n, x; cin >> n >> x;
    vector<int> coins(n);
    for (auto &c : coins) cin >> c;
    vector<long long> dp(x + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= x; i++)
        for (int c : coins)
            if (i - c >= 0) dp[i] = min(dp[i], dp[i - c] + 1);
    cout << (dp[x] >= INF ? -1 : dp[x]) << "\n";
}
```

**Similar LeetCode problems:**
- [322. Coin Change](https://leetcode.com/problems/coin-change/)
- [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/)

---

## 3. Coin Combinations I
**Tag:** 1D DP (Ordered) · 🟢 Easy
Count the number of **ordered** ways (sequences) to produce sum `x` using given coins.

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
vector<int> coins;
vector<long long> memo;

long long solve(int x) {
    if (x == 0) return 1;
    if (x < 0) return 0;
    if (memo[x] != -1) return memo[x];
    long long ways = 0;
    for (int c : coins) ways = (ways + solve(x - c)) % MOD;
    return memo[x] = ways;
}

int main() {
    int n, x; cin >> n >> x;
    coins.resize(n);
    for (auto &c : coins) cin >> c;
    memo.assign(x + 1, -1);
    cout << solve(x) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    int n, x; cin >> n >> x;
    vector<int> coins(n);
    for (auto &c : coins) cin >> c;
    vector<long long> dp(x + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= x; i++)
        for (int c : coins)
            if (i - c >= 0) dp[i] = (dp[i] + dp[i - c]) % MOD;
    cout << dp[x] << "\n";
}
```

**Similar LeetCode problems:**
- [377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/) (identical concept — order matters)
- [39. Combination Sum](https://leetcode.com/problems/combination-sum/)

---

## 4. Coin Combinations II
**Tag:** 1D DP (Unordered) · 🟢 Easy
Count the number of **unordered** combinations (order doesn't matter) that sum to `x`.

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
vector<int> coins;
vector<vector<long long>> memo; // memo[idx][sum]

long long solve(int idx, int x) {
    if (x == 0) return 1;
    if (x < 0 || idx == (int)coins.size()) return 0;
    if (memo[idx][x] != -1) return memo[idx][x];
    // either skip this coin type, or use it (stay on same idx since unlimited supply)
    long long ways = (solve(idx + 1, x) + solve(idx, x - coins[idx])) % MOD;
    return memo[idx][x] = ways;
}

int main() {
    int n, x; cin >> n >> x;
    coins.resize(n);
    for (auto &c : coins) cin >> c;
    memo.assign(n + 1, vector<long long>(x + 1, -1));
    cout << solve(0, x) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    int n, x; cin >> n >> x;
    vector<int> coins(n);
    for (auto &c : coins) cin >> c;
    vector<long long> dp(x + 1, 0);
    dp[0] = 1;
    for (int c : coins)              // coin loop OUTSIDE -> combinations, not permutations
        for (int i = c; i <= x; i++)
            dp[i] = (dp[i] + dp[i - c]) % MOD;
    cout << dp[x] << "\n";
}
```

**Similar LeetCode problems:**
- [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/) (identical concept)
- [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/)

---

## 5. Removing Digits
**Tag:** 1D DP · 🟢 Easy
Minimum number of steps to reduce `n` to `0`, where each step subtracts one of `n`'s own (current) digits.

### Recursion + Memoization
```cpp
vector<int> memo;

int solve(int n) {
    if (n == 0) return 0;
    if (memo[n] != -1) return memo[n];
    int best = INT_MAX;
    int t = n;
    while (t > 0) {
        int d = t % 10;
        t /= 10;
        if (d > 0) best = min(best, 1 + solve(n - d));
    }
    return memo[n] = best;
}

int main() {
    int n; cin >> n;
    memo.assign(n + 1, -1);
    cout << solve(n) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    int n; cin >> n;
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int t = i;
        while (t > 0) {
            int d = t % 10;
            t /= 10;
            if (d > 0) dp[i] = min(dp[i], dp[i - d] + 1);
        }
    }
    cout << dp[n] << "\n";
}
```

**Similar LeetCode problems:**
- [1553. Minimum Number of Days to Eat N Oranges](https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/)
- [991. Broken Calculator](https://leetcode.com/problems/broken-calculator/)

---

## 6. Grid Paths I
**Tag:** 2D DP · 🟢 Easy
Count monotonic (right/down only) paths from `(1,1)` to `(n,n)` in an `n×n` grid, avoiding traps `*`, mod `1e9+7`.

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
int n;
vector<string> grid;
vector<vector<long long>> memo;

long long solve(int r, int c) {
    if (r < 0 || c < 0 || grid[r][c] == '*') return 0;
    if (r == 0 && c == 0) return 1;
    if (memo[r][c] != -1) return memo[r][c];
    return memo[r][c] = (solve(r - 1, c) + solve(r, c - 1)) % MOD;
}

int main() {
    cin >> n;
    grid.resize(n);
    for (auto &row : grid) cin >> row;
    memo.assign(n, vector<long long>(n, -1));
    cout << solve(n - 1, n - 1) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n;
    grid.resize(n);
    for (auto &row : grid) cin >> row;
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == '*') continue;
            if (r == 0 && c == 0) { dp[r][c] = 1; continue; }
            long long from_up = (r > 0) ? dp[r-1][c] : 0;
            long long from_left = (c > 0) ? dp[r][c-1] : 0;
            dp[r][c] = (from_up + from_left) % MOD;
        }
    cout << dp[n-1][n-1] << "\n";
}
```

**Similar LeetCode problems:**
- [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)
- [62. Unique Paths](https://leetcode.com/problems/unique-paths/)
- [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)

---

## 7. Book Shop
**Tag:** 0/1 Knapsack · 🟢 Easy
Given `n` books with price `h[i]` and pages `s[i]`, and budget `x`, maximize total pages bought (each book at most once).

### Recursion + Memoization
```cpp
int n, x;
vector<int> price, pages;
vector<vector<int>> memo;

int solve(int idx, int budget) {
    if (idx == n || budget == 0) return 0;
    if (memo[idx][budget] != -1) return memo[idx][budget];
    int best = solve(idx + 1, budget); // skip book
    if (price[idx] <= budget)
        best = max(best, pages[idx] + solve(idx + 1, budget - price[idx]));
    return memo[idx][budget] = best;
}

int main() {
    cin >> n >> x;
    price.resize(n); pages.resize(n);
    for (auto &p : price) cin >> p;
    for (auto &s : pages) cin >> s;
    memo.assign(n, vector<int>(x + 1, -1));
    cout << solve(0, x) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n >> x;
    vector<int> price(n), pages(n);
    for (auto &p : price) cin >> p;
    for (auto &s : pages) cin >> s;
    vector<int> dp(x + 1, 0);
    for (int i = 0; i < n; i++)
        for (int b = x; b >= price[i]; b--)     // iterate backwards: 0/1 knapsack
            dp[b] = max(dp[b], dp[b - price[i]] + pages[i]);
    cout << dp[x] << "\n";
}
```

**Similar LeetCode problems:**
- [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
- [494. Target Sum](https://leetcode.com/problems/target-sum/)
- [1049. Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/)

---

## 8. Array Description
**Tag:** DP with Constraints · 🟡 Medium
An array of length `n` has values in `[1,m]`. Known entries are given, `0` means unknown. Adjacent values differ by at most 1. Count valid arrays mod `1e9+7`.

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
int n, m;
vector<int> a;
vector<vector<long long>> memo;

long long solve(int idx, int val) { // val is 1-indexed value chosen for position idx
    if (a[idx] != 0 && a[idx] != val) return 0;
    if (idx == n - 1) return 1;
    if (memo[idx][val] != -1) return memo[idx][val];
    long long ways = 0;
    for (int nv = max(1, val - 1); nv <= min(m, val + 1); nv++)
        ways = (ways + solve(idx + 1, nv)) % MOD;
    return memo[idx][val] = ways;
}

int main() {
    cin >> n >> m;
    a.resize(n);
    for (auto &v : a) cin >> v;
    memo.assign(n, vector<long long>(m + 1, -1));
    long long ans = 0;
    for (int v = 1; v <= m; v++) ans = (ans + solve(0, v)) % MOD;
    cout << ans << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n >> m;
    vector<int> a(n);
    for (auto &v : a) cin >> v;
    vector<vector<long long>> dp(n, vector<long long>(m + 2, 0));
    for (int v = 1; v <= m; v++)
        if (a[0] == 0 || a[0] == v) dp[0][v] = 1;

    for (int i = 1; i < n; i++)
        for (int v = 1; v <= m; v++) {
            if (a[i] != 0 && a[i] != v) continue;
            dp[i][v] = (dp[i-1][v-1] + dp[i-1][v] + dp[i-1][v+1]) % MOD; // v-1=0 or v+1=m+1 are 0
        }

    long long ans = 0;
    for (int v = 1; v <= m; v++) ans = (ans + dp[n-1][v]) % MOD;
    cout << ans << "\n";
}
```

**Similar LeetCode problems:**
- [1269. Number of Ways to Stay in the Same Place After Some Steps](https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/)
- [935. Knight Dialer](https://leetcode.com/problems/knight-dialer/)

---

## 9. Counting Towers
**Tag:** DP on Columns · 🟡 Medium
Count the number of distinct towers of height `n` and width `2` built from blocks of width 1 or 2, mod `1e9+7`.

Let `dp[i][0]` = ways where the top row is one merged block (uniform), `dp[i][1]` = ways where the top row is split into two separate blocks.

Recurrence: `dp[i][0] = dp[i-1][0] + dp[i-1][1]`, `dp[i][1] = 2*dp[i-1][0] + 3*dp[i-1][1]`.

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
vector<array<long long,2>> memo; // memo[i] = {dp0, dp1}, -1 means uncomputed
vector<bool> done;

array<long long,2> solve(int i) {
    if (i == 1) return {1, 1};
    if (done[i]) return memo[i];
    auto prev = solve(i - 1);
    long long d0 = (prev[0] + prev[1]) % MOD;
    long long d1 = (2 * prev[0] + 3 * prev[1]) % MOD;
    done[i] = true;
    return memo[i] = {d0, d1};
}

int main() {
    int t; cin >> t;
    int maxN = 1000001;
    memo.assign(maxN, {0,0});
    done.assign(maxN, false);
    while (t--) {
        int n; cin >> n;
        auto r = solve(n);
        cout << (r[0] + r[1]) % MOD << "\n";
    }
}
```

### Bottom-Up
```cpp
int main() {
    const int MAXN = 1000001;
    vector<long long> dp0(MAXN), dp1(MAXN);
    dp0[1] = dp1[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        dp0[i] = (dp0[i-1] + dp1[i-1]) % MOD;
        dp1[i] = (2*dp0[i-1] + 3*dp1[i-1]) % MOD;
    }
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        cout << (dp0[n] + dp1[n]) % MOD << "\n";
    }
}
```

**Similar LeetCode problems:**
- [790. Domino and Tromino Tiling](https://leetcode.com/problems/domino-and-tromino-tiling/)
- [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)

---

## 10. Edit Distance
**Tag:** 2D String DP · 🟢 Easy
Minimum number of insert/delete/replace operations to convert string `a` into string `b`.

### Recursion + Memoization
```cpp
string a, b;
vector<vector<int>> memo;

int solve(int i, int j) { // convert a[i..] into b[j..]
    if (i == (int)a.size()) return b.size() - j;
    if (j == (int)b.size()) return a.size() - i;
    if (memo[i][j] != -1) return memo[i][j];
    int res;
    if (a[i] == b[j]) res = solve(i + 1, j + 1);
    else res = 1 + min({ solve(i + 1, j),       // delete from a
                          solve(i, j + 1),       // insert into a
                          solve(i + 1, j + 1) }); // replace
    return memo[i][j] = res;
}

int main() {
    cin >> a >> b;
    memo.assign(a.size() + 1, vector<int>(b.size() + 1, -1));
    cout << solve(0, 0) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> a >> b;
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    cout << dp[n][m] << "\n";
}
```

**Similar LeetCode problems:**
- [72. Edit Distance](https://leetcode.com/problems/edit-distance/) (identical problem)
- [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)

---

## 11. Longest Common Subsequence
**Tag:** 2D String DP · 🟢 Easy
Find the length (and construction) of the longest common subsequence of two arrays/strings.

### Recursion + Memoization
```cpp
vector<int> a, b;
vector<vector<int>> memo;

int solve(int i, int j) {
    if (i == (int)a.size() || j == (int)b.size()) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    int res;
    if (a[i] == b[j]) res = 1 + solve(i + 1, j + 1);
    else res = max(solve(i + 1, j), solve(i, j + 1));
    return memo[i][j] = res;
}

int main() {
    int n, m; cin >> n >> m;
    a.resize(n); b.resize(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    memo.assign(n, vector<int>(m, -1));
    cout << solve(0, 0) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    cout << dp[n][m] << "\n";
}
```

**Similar LeetCode problems:**
- [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) (identical problem)
- [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)
- [712. Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/)

---

## 12. Rectangle Cutting
**Tag:** 2D DP · 🟡 Medium
Cut an `a × b` rectangle into squares using the minimum number of straight cuts (each cut splits a rectangle into two rectangles).

### Recursion + Memoization
```cpp
vector<vector<int>> memo;

int solve(int a, int b) {
    if (a == b) return 0;
    if (memo[a][b] != -1) return memo[a][b];
    int best = INT_MAX;
    for (int i = 1; i < a; i++) best = min(best, solve(i, b) + solve(a - i, b) + 1);
    for (int j = 1; j < b; j++) best = min(best, solve(a, j) + solve(a, b - j) + 1);
    return memo[a][b] = best;
}

int main() {
    int a, b; cin >> a >> b;
    memo.assign(a + 1, vector<int>(b + 1, -1));
    cout << solve(a, b) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    int A, B; cin >> A >> B;
    vector<vector<int>> dp(A + 1, vector<int>(B + 1, 0));
    for (int a = 1; a <= A; a++)
        for (int b = 1; b <= B; b++) {
            if (a == b) { dp[a][b] = 0; continue; }
            int best = INT_MAX;
            for (int i = 1; i < a; i++) best = min(best, dp[i][b] + dp[a-i][b] + 1);
            for (int j = 1; j < b; j++) best = min(best, dp[a][j] + dp[a][b-j] + 1);
            dp[a][b] = best;
        }
    cout << dp[A][B] << "\n";
}
```

**Similar LeetCode problems:**
- [1547. Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)
- [312. Burst Balloons](https://leetcode.com/problems/burst-balloons/)

---

## 13. Minimal Grid Path
**Tag:** Greedy / DP on Grid · 🟡 Medium
On an `n×n` grid with blocked cells, find the lexicographically smallest path (alphabet order `D < L < R < U`) of length `2n-2` from top-left to bottom-right. Because the path length equals the Manhattan distance, only `D` (down) and `R` (right) moves can appear in a valid shortest path; we greedily prefer `D` when it still allows reaching the destination.

### Recursion + Memoization (feasibility check)
```cpp
int n;
vector<string> grid;
vector<vector<int>> memo; // 1 = reachable, 0 = not, -1 = unknown

bool reachable(int r, int c) {
    if (r >= n || c >= n || grid[r][c] == '*') return false;
    if (r == n-1 && c == n-1) return true;
    if (memo[r][c] != -1) return memo[r][c];
    bool res = reachable(r + 1, c) || reachable(r, c + 1);
    return memo[r][c] = res;
}

int main() {
    cin >> n;
    grid.resize(n);
    for (auto &row : grid) cin >> row;
    memo.assign(n, vector<int>(n, -1));
    if (!reachable(0, 0)) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    string path;
    int r = 0, c = 0;
    while (r != n-1 || c != n-1) {
        if (r + 1 < n && grid[r+1][c] != '*' && reachable(r+1, c)) { path += 'D'; r++; }
        else { path += 'R'; c++; }
    }
    cout << path << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n;
    grid.resize(n);
    for (auto &row : grid) cin >> row;
    vector<vector<bool>> can(n, vector<bool>(n, false));
    for (int r = n - 1; r >= 0; r--)
        for (int c = n - 1; c >= 0; c--) {
            if (grid[r][c] == '*') continue;
            if (r == n-1 && c == n-1) { can[r][c] = true; continue; }
            bool down  = (r + 1 < n) && can[r+1][c];
            bool right = (c + 1 < n) && can[r][c+1];
            can[r][c] = down || right;
        }
    if (!can[0][0]) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    string path;
    int r = 0, c = 0;
    while (r != n-1 || c != n-1) {
        if (r + 1 < n && can[r+1][c]) { path += 'D'; r++; }
        else { path += 'R'; c++; }
    }
    cout << path << "\n";
}
```

**Similar LeetCode problems:**
- [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)
- [1102. Path With Maximum Minimum Value](https://leetcode.com/problems/path-with-maximum-minimum-value/)

---

## 14. Money Sums
**Tag:** Subset Sum · 🟢 Easy
Given `n` coins, find every distinct total sum achievable using any non-empty subset.

### Recursion + Memoization
```cpp
int n;
vector<int> coins;
int totalSum;
vector<vector<int>> memo; // memo[idx][sum] = can we make `sum` using coins[idx..]? (-1/0/1)

bool solve(int idx, int sum) {
    if (sum == 0) return true;
    if (idx == n || sum < 0) return false;
    if (memo[idx][sum] != -1) return memo[idx][sum];
    bool res = solve(idx + 1, sum) || solve(idx + 1, sum - coins[idx]);
    return memo[idx][sum] = res;
}

int main() {
    cin >> n;
    coins.resize(n);
    for (auto &c : coins) cin >> c;
    totalSum = accumulate(coins.begin(), coins.end(), 0);
    memo.assign(n + 1, vector<int>(totalSum + 1, -1));
    vector<int> achievable;
    for (int s = 1; s <= totalSum; s++)
        if (solve(0, s)) achievable.push_back(s);
    cout << achievable.size() << "\n";
    for (int s : achievable) cout << s << " ";
    cout << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n;
    vector<int> coins(n);
    for (auto &c : coins) cin >> c;
    int totalSum = accumulate(coins.begin(), coins.end(), 0);
    vector<bool> dp(totalSum + 1, false);
    dp[0] = true;
    for (int c : coins)
        for (int s = totalSum; s >= c; s--)
            dp[s] = dp[s] || dp[s - c];
    vector<int> achievable;
    for (int s = 1; s <= totalSum; s++) if (dp[s]) achievable.push_back(s);
    cout << achievable.size() << "\n";
    for (int s : achievable) cout << s << " ";
    cout << "\n";
}
```

**Similar LeetCode problems:**
- [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
- [494. Target Sum](https://leetcode.com/problems/target-sum/)

---

## 15. Removal Game
**Tag:** Interval DP / Game Theory · 🟡 Medium
Two players alternately remove a number from either end of an array; both play optimally to maximize their own total. Find the first player's maximum achievable score.

### Recursion + Memoization
```cpp
int n;
vector<long long> a, prefix;
vector<vector<long long>> memo;

long long rangeSum(int i, int j) { return prefix[j+1] - prefix[i]; }

long long solve(int i, int j) { // best score current player can get from a[i..j]
    if (i > j) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    long long takeLeft  = a[i] + (rangeSum(i+1, j) - solve(i+1, j));
    long long takeRight = a[j] + (rangeSum(i, j-1) - solve(i, j-1));
    return memo[i][j] = max(takeLeft, takeRight);
}

int main() {
    cin >> n;
    a.resize(n); prefix.assign(n + 1, 0);
    for (auto &x : a) cin >> x;
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + a[i];
    memo.assign(n, vector<long long>(n, -1));
    cout << solve(0, n - 1) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n;
    vector<long long> a(n), prefix(n + 1, 0);
    for (auto &x : a) cin >> x;
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + a[i];
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = a[i];
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            long long total = prefix[j+1] - prefix[i];
            long long takeLeft  = a[i] + (total - a[i] - dp[i+1][j]);
            long long takeRight = a[j] + (total - a[j] - dp[i][j-1]);
            dp[i][j] = max(takeLeft, takeRight);
        }
    cout << dp[0][n-1] << "\n";
}
```

**Similar LeetCode problems:**
- [877. Stone Game](https://leetcode.com/problems/stone-game/)
- [486. Predict the Winner](https://leetcode.com/problems/predict-the-winner/)
- [1140. Stone Game II](https://leetcode.com/problems/stone-game-ii/)

---

## 16. Two Sets II
**Tag:** Subset Sum Counting · 🟡 Medium
Count the number of ways to split `{1, ..., n}` into two sets with equal sum, mod `1e9+7`.

If `n(n+1)/2` is odd, the answer is `0`. Otherwise count subsets summing to `n(n+1)/4`, then divide by 2 (each partition is counted twice — once as set S, once as its complement).

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
int n, half;
vector<vector<long long>> memo;

long long solve(int idx, int sum) {
    if (sum == 0) return 1;
    if (idx == 0 || sum < 0) return 0;
    if (memo[idx][sum] != -1) return memo[idx][sum];
    long long ways = (solve(idx - 1, sum) + solve(idx - 1, sum - idx)) % MOD;
    return memo[idx][sum] = ways;
}

int main() {
    cin >> n;
    long long total = 1LL * n * (n + 1) / 2;
    if (total % 2 != 0) { cout << 0 << "\n"; return 0; }
    half = total / 2;
    memo.assign(n + 1, vector<long long>(half + 1, -1));
    long long ways = solve(n, half);
    long long inv2 = (MOD + 1) / 2; // modular inverse of 2
    cout << (ways * inv2) % MOD << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n;
    long long total = 1LL * n * (n + 1) / 2;
    if (total % 2 != 0) { cout << 0 << "\n"; return 0; }
    int half = total / 2;
    vector<long long> dp(half + 1, 0);
    dp[0] = 1;
    for (int v = 1; v <= n; v++)
        for (int s = half; s >= v; s--)
            dp[s] = (dp[s] + dp[s - v]) % MOD;
    long long inv2 = (MOD + 1) / 2;
    cout << (dp[half] * inv2) % MOD << "\n";
}
```

**Similar LeetCode problems:**
- [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
- [494. Target Sum](https://leetcode.com/problems/target-sum/)

---

## 17. Mountain Range
**Tag:** DP / Monotonic Stack · 🟡 Medium
Given heights of mountains in a row, for each mountain find the farthest mountain visible to the left and right (a taller mountain blocks the view beyond it). Compute the largest visible span.

### Recursion + Memoization (nearest greater element, memoized jumps)
```cpp
int n;
vector<long long> h;
vector<int> nextGreaterR, nextGreaterL; // precomputed with a stack (O(n))
vector<int> memoR, memoL; // memoized jump pointers if computed recursively

int solve(vector<int> &jump, vector<int> &memo, int i, bool right) {
    // jump[i] = index of the next element >= h[i] in that direction, or -1
    if (memo[i] != -2) return memo[i];
    memo[i] = jump[i];
    return memo[i];
}

int main() {
    cin >> n;
    h.resize(n);
    for (auto &x : h) cin >> x;

    nextGreaterR.assign(n, n);
    nextGreaterL.assign(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {                 // farthest visible to the right
        while (!st.empty() && h[st.top()] < h[i]) { nextGreaterR[st.top()] = i; st.pop(); }
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {             // farthest visible to the left
        while (!st.empty() && h[st.top()] < h[i]) { nextGreaterL[st.top()] = i; st.pop(); }
        st.push(i);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int left  = (nextGreaterL[i] == -1) ? 0 : nextGreaterL[i] + 1;
        int right = (nextGreaterR[i] == n)  ? n - 1 : nextGreaterR[i] - 1;
        ans = max(ans, (long long)(right - left + 1));
    }
    cout << ans << "\n";
}
```

### Bottom-Up (same monotonic-stack O(n) sweep, iterative by construction)
```cpp
int main() {
    cin >> n;
    vector<long long> h(n);
    for (auto &x : h) cin >> x;

    vector<int> R(n, n), L(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && h[st.top()] < h[i]) { R[st.top()] = i; st.pop(); }
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && h[st.top()] < h[i]) { L[st.top()] = i; st.pop(); }
        st.push(i);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int left  = (L[i] == -1) ? 0 : L[i] + 1;
        int right = (R[i] == n)  ? n - 1 : R[i] - 1;
        ans = max(ans, (long long)(right - left + 1));
    }
    cout << ans << "\n";
}
```

**Similar LeetCode problems:**
- [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)

---

## 18. Increasing Subsequence
**Tag:** LIS (Patience Sorting) · 🟡 Medium
Find the length of the longest strictly increasing subsequence in `O(n log n)`.

### Recursion + Memoization (classic O(n²) memoized version)
```cpp
int n;
vector<int> a;
vector<int> memo;

int solve(int i) { // length of LIS starting at index i
    if (memo[i] != -1) return memo[i];
    int best = 1;
    for (int j = i + 1; j < n; j++)
        if (a[j] > a[i]) best = max(best, 1 + solve(j));
    return memo[i] = best;
}

int main() {
    cin >> n;
    a.resize(n);
    for (auto &x : a) cin >> x;
    memo.assign(n, -1);
    int ans = 0;
    for (int i = 0; i < n; i++) ans = max(ans, solve(i));
    cout << ans << "\n";
}
```

### Bottom-Up (O(n log n) patience sorting — the accepted approach for CSES limits)
```cpp
int main() {
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    vector<int> tails; // tails[k] = smallest possible tail of an increasing subsequence of length k+1
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x); // strictly increasing -> lower_bound
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    cout << tails.size() << "\n";
}
```

**Similar LeetCode problems:**
- [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) (identical problem)
- [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/)
- [1671. Minimum Number of Removals to Make Mountain Array](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/)

---

## 19. Projects
**Tag:** DP + Binary Search · 🟡 Medium
Given `n` projects, each with a start day, end day, and reward, and no two chosen projects may overlap (even by one day), maximize total reward — a weighted interval scheduling problem.

### Recursion + Memoization
```cpp
int n;
vector<array<long long,3>> proj; // {end, start, reward}, sorted by end
vector<long long> memo;

int findPrev(int idx) { // largest index j < idx with proj[j].end < proj[idx].start (binary search)
    long long start = proj[idx][1];
    int lo = 0, hi = idx - 1, res = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (proj[mid][0] < start) { res = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    return res;
}

long long solve(int idx) { // best reward using proj[0..idx]
    if (idx < 0) return 0;
    if (memo[idx] != -1) return memo[idx];
    long long skip = solve(idx - 1);
    long long take = proj[idx][2] + solve(findPrev(idx));
    return memo[idx] = max(skip, take);
}

int main() {
    cin >> n;
    proj.resize(n);
    for (auto &p : proj) { long long s, e, r; cin >> s >> e >> r; p = {e, s, r}; }
    sort(proj.begin(), proj.end());
    memo.assign(n, -1);
    cout << solve(n - 1) << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n;
    vector<array<long long,3>> proj(n); // {end, start, reward}
    for (auto &p : proj) { long long s, e, r; cin >> s >> e >> r; p = {e, s, r}; }
    sort(proj.begin(), proj.end());

    vector<long long> ends(n);
    for (int i = 0; i < n; i++) ends[i] = proj[i][0];

    vector<long long> dp(n + 1, 0); // dp[i] = best using first i projects (1-indexed)
    for (int i = 1; i <= n; i++) {
        long long start = proj[i-1][1], reward = proj[i-1][2];
        int j = lower_bound(ends.begin(), ends.begin() + (i - 1), start) - ends.begin();
        // j = first index with end >= start -> j itself may overlap, so usable projects are [0, j-1]
        dp[i] = max(dp[i-1], reward + dp[j]);
    }
    cout << dp[n] << "\n";
}
```

**Similar LeetCode problems:**
- [1235. Maximum Profit in Job Scheduling](https://leetcode.com/problems/maximum-profit-in-job-scheduling/) (identical problem)
- [646. Maximum Length of Pair Chain](https://leetcode.com/problems/maximum-length-of-pair-chain/)

---

## 20. Elevator Rides
**Tag:** Bitmask DP · 🔴 Hard
Given `n` people with weights and an elevator of capacity `x`, minimize the number of rides needed to carry everyone (ties are broken by minimizing the weight of the last ride).

### Recursion + Memoization
```cpp
int n; long long x;
vector<long long> w;
vector<long long> sum;         // sum[mask] = total weight of people in mask
vector<pair<int,long long>> memo; // {rides, weightOfLastRide}, uncomputed = {-1,-1}

pair<int,long long> solve(int mask) {
    if (mask == 0) return {0, 0};
    if (memo[mask].first != -1) return memo[mask];
    pair<int,long long> best = {INT_MAX, LLONG_MAX};
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        if (sum[sub] > x) continue;                 // this subset doesn't fit in one ride
        auto rest = solve(mask ^ sub);
        pair<int,long long> cand = {rest.first + 1, sum[sub]};
        if (cand.first < best.first ||
           (cand.first == best.first && cand.second < best.second))
            best = cand;
    }
    return memo[mask] = best;
}

int main() {
    cin >> n >> x;
    w.resize(n);
    for (auto &v : w) cin >> v;
    int full = 1 << n;
    sum.assign(full, 0);
    for (int mask = 1; mask < full; mask++) {
        int lb = mask & (-mask), idx = __builtin_ctz(lb);
        sum[mask] = sum[mask ^ lb] + w[idx];
    }
    memo.assign(full, {-1, -1});
    cout << solve(full - 1).first << "\n";
}
```

### Bottom-Up
```cpp
int main() {
    cin >> n >> x;
    vector<long long> w(n);
    for (auto &v : w) cin >> v;
    int full = 1 << n;
    vector<long long> sum(full, 0);
    for (int mask = 1; mask < full; mask++) {
        int lb = mask & (-mask), idx = __builtin_ctz(lb);
        sum[mask] = sum[mask ^ lb] + w[idx];
    }

    vector<int> rides(full, INT_MAX);
    vector<long long> lastW(full, LLONG_MAX);
    rides[0] = 0; lastW[0] = 0;

    for (int mask = 1; mask < full; mask++) {
        for (int sub = mask; sub; sub = (sub - 1) & mask) {
            if (sum[sub] > x) continue;
            int rest = mask ^ sub;
            if (rides[rest] == INT_MAX) continue;
            int candRides = rides[rest] + 1;
            long long candW = sum[sub];
            if (candRides < rides[mask] ||
               (candRides == rides[mask] && candW < lastW[mask])) {
                rides[mask] = candRides;
                lastW[mask] = candW;
            }
        }
    }
    cout << rides[full - 1] << "\n";
}
```

**Similar LeetCode problems:**
- [1723. Find Minimum Time to Finish All Jobs](https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/)
- [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)
- [2305. Fair Distribution of Cookies](https://leetcode.com/problems/fair-distribution-of-cookies/)

---

## 21. Counting Tilings
**Tag:** Broken Profile DP · 🔴 Hard
Count the number of ways to tile an `n×m` grid completely using `1×2` dominoes, mod `1e9+7` (broken-profile / bitmask-over-columns DP).

### Recursion + Memoization
```cpp
const long long MOD = 1e9+7;
int n, m;
vector<vector<vector<long long>>> memo; // memo[row][col][mask]

long long solve(int row, int col, int mask) {
    if (col == m) return solve(row + 1, 0, 0);          // move to next row (well-formed rows handled below)
    if (row == n) return (mask == 0) ? 1 : 0;
    if (memo[row][col][mask] != -1) return memo[row][col][mask];

    long long ways = 0;
    bool filled = mask & (1 << col);
    if (filled) {
        // already filled by a vertical domino from the row above -> move on
        ways = solve(row, col + 1, mask & ~(1 << col));
    } else {
        // place a vertical domino downward (if room)
        if (row + 1 < n) ways = (ways + solve(row, col + 1, mask | (1 << col))) % MOD;
        // place a horizontal domino to the right (if room and that cell free)
        if (col + 1 < m && !(mask & (1 << (col + 1))))
            ways = (ways + solve(row, col + 2, mask)) % MOD;
    }
    return memo[row][col][mask] = ways;
}

int main() {
    cin >> n >> m;
    memo.assign(n + 1, vector<vector<long long>>(m + 1, vector<long long>(1 << m, -1)));
    cout << solve(0, 0, 0) << "\n";
}
```

### Bottom-Up (row-by-row transition using submasks)
```cpp
int main() {
    cin >> n >> m;
    int full = 1 << m;
    vector<long long> dp(full, 0);
    dp[0] = 1; // before placing any row, "carry mask" 0

    for (int row = 0; row < n; row++) {
        vector<long long> ndp(full, 0);
        // step 1: expand every incoming carry-mask into all ways of filling THIS row
        vector<vector<long long>> cur(full, vector<long long>(0));
        for (int carry = 0; carry < full; carry++) {
            if (dp[carry] == 0) continue;
            // recursively fill columns of this row given carry mask (which cells are pre-filled from above)
            vector<long long> layer(full, 0);
            // BFS/DFS over columns for this specific carry
            function<void(int,int,int)> fillRow = [&](int col, int mask, int nextCarryPart) {
                if (col == m) { layer[mask] = (layer[mask] + 1) % MOD; return; }
                if (carry & (1 << col)) { fillRow(col + 1, mask, 0); return; }
                // vertical domino down -> sets bit in next row's carry mask
                fillRow(col + 1, mask | (1 << col), 0);
                // horizontal domino
                if (col + 1 < m && !(carry & (1 << (col + 1))))
                    fillRow(col + 2, mask, 0);
            };
            fillRow(0, 0, 0);
            for (int nm = 0; nm < full; nm++)
                ndp[nm] = (ndp[nm] + dp[carry] * layer[nm]) % MOD;
        }
        dp = ndp;
    }
    cout << dp[0] << "\n";
}
```
> Note: the bottom-up version above still uses a small recursive helper (`fillRow`) to enumerate placements within a row — this is standard for broken-profile DP; the outer loop over rows is fully iterative/tabulated.

**Similar LeetCode problems:**
- [790. Domino and Tromino Tiling](https://leetcode.com/problems/domino-and-tromino-tiling/)
- [1411. Number of Ways to Paint N × 3 Grid](https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/)

---

## 22. Counting Numbers
**Tag:** Digit DP · 🔴 Hard
Count integers in `[a, b]` that have no two adjacent equal digits.

### Recursion + Memoization
```cpp
vector<int> digits;
vector<vector<vector<int>>> memo; // memo[pos][lastDigit][tight]

int solve(int pos, int last, bool tight, bool started) {
    if (pos == (int)digits.size()) return started ? 1 : 0;
    if (!tight && started && memo[pos][last][0] != -1) return memo[pos][last][0];

    int limit = tight ? digits[pos] : 9;
    int ways = 0;
    for (int d = 0; d <= limit; d++) {
        if (started && d == last) continue;              // no two adjacent equal digits
        bool nowStarted = started || d != 0;
        ways += solve(pos + 1, nowStarted ? d : -1, tight && (d == limit), nowStarted);
    }
    if (!tight && started) memo[pos][last][0] = ways;
    return ways;
}

long long countUpTo(long long n) {
    if (n < 0) return 0;
    digits.clear();
    string s = to_string(n);
    for (char c : s) digits.push_back(c - '0');
    memo.assign(digits.size() + 1, vector<vector<int>>(11, vector<int>(2, -1)));
    return solve(0, -1, true, false);
}

int main() {
    long long a, b; cin >> a >> b;
    cout << countUpTo(b) - countUpTo(a - 1) << "\n";
}
```

### Bottom-Up (iterative digit DP table filled from the least-significant digit position upward)
```cpp
long long countUpTo(long long n) {
    if (n < 0) return 0;
    string s = to_string(n);
    int L = s.size();
    // dp[pos][last][tight] filled bottom-up from pos = L (base case) down to pos = 0
    vector<vector<vector<long long>>> dp(L + 1, vector<vector<long long>>(11, vector<long long>(2, 0)));
    for (int last = 0; last <= 10; last++) { dp[L][last][0] = 1; dp[L][last][1] = 1; } // "started" base case = valid

    // We iterate positions from the end backward, and for each compute contributions.
    for (int pos = L - 1; pos >= 0; pos--) {
        for (int last = 0; last <= 10; last++) {          // 10 = "no digit chosen yet"
            for (int tight = 0; tight <= 1; tight++) {
                int limit = tight ? (s[pos] - '0') : 9;
                long long ways = 0;
                for (int d = 0; d <= limit; d++) {
                    if (last != 10 && d == last) continue;
                    int nlast = (last == 10 && d == 0) ? 10 : d;
                    int ntight = (tight && d == limit) ? 1 : 0;
                    ways += dp[pos + 1][nlast][ntight];
                }
                dp[pos][last][tight] = ways;
            }
        }
    }
    long long total = dp[0][10][1];
    total -= 1; // subtract the case where the number is all zeros (i.e., "0" counted as started=false)
    return total;
}

int main() {
    long long a, b; cin >> a >> b;
    cout << countUpTo(b) - countUpTo(a - 1) << "\n";
}
```

**Similar LeetCode problems:**
- [2376. Count Special Integers](https://leetcode.com/problems/count-special-integers/)
- [1012. Numbers With Repeated Digits](https://leetcode.com/problems/numbers-with-repeated-digits/)
- [902. Numbers At Most N Given Digit Set](https://leetcode.com/problems/numbers-at-most-n-given-digit-set/)

---

## 23. Increasing Subsequence II
**Tag:** BIT (LIS Count) · 🔴 Hard
Count the number of strictly increasing subsequences of the array (subsequences of any length ≥ 1), mod `1e9+7`, using a Fenwick tree (BIT) for efficient prefix-sum queries.

### Recursion + Memoization (conceptual O(n²), memoized on compressed value)
```cpp
const long long MOD = 1e9+7;
int n;
vector<int> a, comp;
vector<long long> memo;

// solve(i) = number of increasing subsequences ENDING at index i (mod p)
long long solve(int i) {
    if (memo[i] != -1) return memo[i];
    long long ways = 1; // the subsequence consisting of just a[i]
    for (int j = 0; j < i; j++)
        if (a[j] < a[i]) ways = (ways + solve(j)) % MOD;
    return memo[i] = ways;
}

int main() {
    cin >> n;
    a.resize(n);
    for (auto &x : a) cin >> x;
    memo.assign(n, -1);
    long long ans = 0;
    for (int i = 0; i < n; i++) ans = (ans + solve(i)) % MOD;
    cout << ans << "\n";
}
```

### Bottom-Up (O(n log n) using a Fenwick tree over compressed values)
```cpp
const long long MOD = 1e9+7;

struct BIT {
    vector<long long> tree;
    int sz;
    BIT(int n) : tree(n + 1, 0), sz(n) {}
    void update(int i, long long val) {
        for (++i; i <= sz; i += i & (-i)) tree[i] = (tree[i] + val) % MOD;
    }
    long long query(int i) { // prefix sum [0, i]
        long long res = 0;
        for (++i; i > 0; i -= i & (-i)) res = (res + tree[i]) % MOD;
        return res;
    }
};

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    vector<int> comp(a);
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for (auto &x : a) x = lower_bound(comp.begin(), comp.end(), x) - comp.begin();

    BIT bit(comp.size());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long smaller = a[i] > 0 ? bit.query(a[i] - 1) : 0;
        long long ways = (smaller + 1) % MOD; // +1 for the subsequence of just a[i]
        ans = (ans + ways) % MOD;
        bit.update(a[i], ways);
    }
    cout << ans << "\n";
}
```

**Similar LeetCode problems:**
- [673. Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/) (related — counts only the *longest* ones)
- [1713. Minimum Operations to Make a Subsequence](https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/)
- [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/) (BIT/Fenwick technique practice)

---

## Notes

- Problems 20–23 involve heavier techniques (bitmask DP, broken-profile DP, digit DP, BIT-accelerated DP) — read the CSES editorial alongside the code if the recurrence isn't immediately obvious.
- For competitive-programming judges (CSES), always use fast I/O and `long long` for anything that can exceed `2^31`.
- For strict "recursion + memoization" submissions on very large inputs (e.g., problem 9's `n` up to `10^6`), increase the stack size or prefer the bottom-up version to avoid stack overflow — this is noted inline where relevant.
