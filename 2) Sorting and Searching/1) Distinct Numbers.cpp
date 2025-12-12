#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;
int main(){
    long long n;
    cin >> n;
    vector<long long> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
 
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
 
    cout << v.size();
 
}
