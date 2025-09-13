#include <bits/stdc++.h>
using namespace std;

struct FeasibleChecker {
    int n;
    const vector<long double> &h, &p;
    vector<long double> H, S; // prefix sums of h and h*(p-x)

    FeasibleChecker(int n, const vector<long double>& h, const vector<long double>& p)
        : n(n), h(h), p(p), H(n+1,0.0L), S(n+1,0.0L) {}

    // Check if exists [a,b] with L <= sum(h) <= R and sum(h*(p-x)) >= 0
    // If arg != nullptr, also record one best (a,b) achieving nonnegative gain (optional).
    bool feasible(long double L, long double R, long double x, pair<int,int>* arg = nullptr) {
        H[0] = 0.0L; S[0] = 0.0L;
        for (int i = 1; i <= n; ++i) {
            H[i] = H[i-1] + h[i-1];
            S[i] = S[i-1] + h[i-1] * (p[i-1] - x);
        }

        deque<int> dq; // store indices j (for a-1), maintaining S[j] nondecreasing
        int add_ptr = 0, rm_ptr = 0;
        const long double EPS_H = 1e-15L;
        const long double EPS  = 1e-12L;

        long double bestGain = -1e300L;
        int bestJ = -1, bestB = -1;

        for (int b = 1; b <= n; ++b) {
            // bring in j with H[j] <= H[b] - L
            while (add_ptr <= b-1 && H[add_ptr] <= H[b] - L + EPS_H) {
                while (!dq.empty() && S[dq.back()] >= S[add_ptr]) dq.pop_back();
                dq.push_back(add_ptr);
                ++add_ptr;
            }
            // remove j with H[j] < H[b] - R
            while (rm_ptr < add_ptr && H[rm_ptr] < H[b] - R - EPS_H) {
                if (!dq.empty() && dq.front() == rm_ptr) dq.pop_front();
                ++rm_ptr;
            }
            if (!dq.empty()) {
                long double gain = S[b] - S[dq.front()];
                if (gain >= -EPS) {
                    if (!arg) return true; // feasibility only
                    if (gain > bestGain) {
                        bestGain = gain;
                        bestJ = dq.front(); bestB = b;
                    }
                }
            }
        }
        if (arg && bestJ != -1) {
            *arg = {bestJ + 1, bestB}; // 1-based [a,b]
            return true;
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L;
    if (!(cin >> n >> L)) return 0;

    vector<long double> h(n), p(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> p[i];

    int q; 
    cin >> q;

    // Precompute p range for binary search range
    long double pmin = p[0], pmax = p[0];
    for (int i = 1; i < n; ++i) {
        pmin = min(pmin, p[i]);
        pmax = max(pmax, p[i]);
    }

    FeasibleChecker checker(n, h, p);

    cout.setf(std::ios::fixed); 
    cout << setprecision(6);

    for (int qi = 0; qi < q; ++qi) {
        long double L, R;
        cin >> L >> R;

        // Optional: quick existence check (whether any window with sum(h) in [L,R] exists)
        // We can test feasible with a very small x (effectively -inf). If false, print NaN.
        // Use a very negative x so that any valid window passes S[b]-S[j] >= 0.
        bool anyWindow = checker.feasible(L, R, -1e18L, nullptr);
        if (!anyWindow) {
            // No subarray with sum(h) in [L,R]
            cout << "NaN\n";
            continue;
        }

        // Binary search on x in [pmin, pmax]
        long double lo = pmin, hi = pmax;
        for (int it = 0; it < 60; ++it) { // enough for 1e-6 with long double
            long double mid = (lo + hi) * 0.5L;
            if (checker.feasible(L, R, mid, nullptr)) lo = mid;
            else hi = mid;
        }

        // lo is the maximum achievable x within ~1e-6
        cout << (double)lo << "\n";
        // If you want interval [a,b], you could call:
        // pair<int,int> seg;
        // checker.feasible(L, R, lo, &seg);
        // cerr << seg.first << " " << seg.second << "\n";
    }

    return 0;
}
