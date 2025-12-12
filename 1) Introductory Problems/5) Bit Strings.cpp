#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;
 
const long long MOD = 1e9 + 7;
long long modPow(long long x, long long n){
    long long ans = 1;
    while(n > 0){
        if(n % 2 != 0){
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        n /= 2;
    }
    return ans;
}
 
int main(){
    long long n;
    cin >> n;
 
    long long ans = modPow(2,n);
 
    cout << ans;
 
}
