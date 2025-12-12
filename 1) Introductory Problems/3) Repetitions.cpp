#include <bits/stdc++.h>
using namespace std;
 
int solve(string S)
{
    int ans = 1, count = 1;
    int n = S.length();
    for (int i = 1; i < n; i++) {
        // If the current character is same as the previous
        // character, then increment the count
        if (S[i] == S[i - 1])
            count += 1;
        else
            // If the current character is different from
            // the previous character, then reset count to 1
            count = 1;
        ans = max(ans, count);
    }
    return ans;
}
 
int main()
{
    // Input
    string S;
    cin >> S;
 
    cout << solve(S) << endl;
    return 0;
}
