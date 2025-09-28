#include <bits/stdc++.h>
int n;

int main() {
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (i & 1) ans -= i * i * i;
        else ans += i * i * i;
    printf("%d\n", ans);
    return 0;
}