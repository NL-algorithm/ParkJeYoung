#include <iostream>
#include <vector>
#include <string>
using namespace std;
constexpr long long MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k;
    
    string N; 
    
    cin >> k >> N;

    long long dp_cnt[2][2] = {{0,0},{0,0}};
    long long dp_sum[2][2] = {{0,0},{0,0}};
    
    dp_cnt[1][0] = 1;

    for (char ch : N) {

        int lim_digit = ch - '0';

        long long nxt_cnt[2][2] = {{0,0},{0,0}};
        long long nxt_sum[2][2] = {{0,0},{0,0}};

        for (int ti = 0; ti <= 1; ti++) {

            for (int st = 0; st <= 1; st++) {

                long long cnt = dp_cnt[ti][st];
                long long sum = dp_sum[ti][st];
                
                if (!cnt) continue;

                int lim = (ti ? lim_digit : 9);

                for (int d = 0; d <= lim; d++) {
                    
                    int nti = ti && (d == lim);
                    int nst = st || (d != 0);

                    if (!nst) {

                        nxt_cnt[nti][0] = (nxt_cnt[nti][0] + cnt) % MOD;

                        nxt_sum[nti][0] = (nxt_sum[nti][0] + sum) % MOD;

                    } else { // start spreading

                        nxt_cnt[nti][1] = (nxt_cnt[nti][1] + cnt) % MOD;

                        /*
                            plan : 
                            s = 10 * s + d;
                            if (d == k) continue;
                        */
                        if (d == k) {

                            nxt_sum[nti][1] = (nxt_sum[nti][1] + sum) % MOD;

                        } else {

                            long long add = ( (10LL * sum) % MOD + (1LL * d * cnt) % MOD ) % MOD;
                            
                            nxt_sum[nti][1] = (nxt_sum[nti][1] + add) % MOD;

                        }

                    }
                }
            }
        }

        for (int ti = 0; ti <= 1; ti++)
            for (int st = 0; st <= 1; st++) {
                dp_cnt[ti][st] = nxt_cnt[ti][st];
                dp_sum[ti][st] = nxt_sum[ti][st];
            }
    }


    long long ans = 0;

    for (int ti = 0; ti <= 1; ti++)
        for (int st = 0; st <= 1; st++)
            ans = (ans + dp_sum[ti][st]) % MOD;

    cout << ans % MOD;
    return 0;
}