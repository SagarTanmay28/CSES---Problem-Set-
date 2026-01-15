#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    long long n;
    cin >> n;
 
    vector<long long> v(n);
    for(long long i=0;i<n;i++) cin >> v[i];
 
    long long cost = 0;
    sort(v.begin(),v.end());
 
    long long x = v[n/2]; // median
 
    for(int i=0;i<n;i++){
        cost += abs(v[i] - x);
    }
 
    cout << cost;
 
}
