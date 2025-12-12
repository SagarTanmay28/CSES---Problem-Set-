#include<iostream>
#include<vector>
using namespace std;
int main(){
  long long n;
  cin >> n;
  vector<int> v;
  for(int i=0;i<n-1;i++){
    long long x;
    cin >> x;
    v.push_back(x);
  }
  long long sum = 0;
  for(int i=0;i<v.size();i++){
    sum += v[i];
  }
  long long ans = n*(n+1)/2;
  cout << ans - sum;
}
