#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;
using int64 = long long;

long long countDigitUpTo(long long n, int d) {

    if (n <= 0) 
        return 0;
    
    long long cnt = 0;
    
    for (long long pos = 1; pos <= n; pos *= 10) {

        long long high = n / (pos * 10);
        
        int curr = (n / pos) % 10;
        
        long long low = n % pos;

        if (d == 0) {
            if (high == 0) 
                continue;
            if (curr == 0) 
                cnt += (high - 1) * pos + (low + 1);
            else
               cnt += (high - 1) * pos + pos;
        } else {
            if (curr > d)  
                cnt += high * pos + pos;
            else if (curr == d) 
                cnt += high * pos + (low + 1);
            else
                cnt += high * pos;
        }
    }
    return cnt;
}

// 1..n에서 0~9 전체 카운트
vector<long long> countAllDigits(long long n) {
    vector<long long> res;
    for (int d = 0; d < 10; d++)
        res.push_back(countDigitUpTo(n, d));
    return res;
}

int main(){
    
    cin.tie(0)->sync_with_stdio(0);

    long long n;
    cin >> n;

    auto c = countAllDigits(n);
    for(auto& i : c)
        cout << i << ' ';
    return 0;
}