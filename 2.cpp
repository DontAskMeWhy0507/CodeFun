#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    const int MAX = 200;
    vector<vector<long double>> dp(MAX + 1, vector<long double>(MAX + 1, 0.0));

    // Cơ sở: 0 người -> xác suất 1
    for (int k = 0; k <= MAX; k++) dp[0][k] = 1.0;

    // Khi số người > số ghế -> chắc chắn có người phải đứng
    for (int n = 1; n <= MAX; n++) {
        for (int k = 1; k <= MAX; k++) {
            if (n > k) dp[n][k] = 0.0;
            else {
                // Người thứ n chọn 1 ghế trong K
                // Nếu chọn ghế trống -> xác suất (k - (n - 1)) / k
                // Nếu chọn ghế đã có người -> bị dồn lên => tương tự bài "người cuối chọn ghế còn trống"
                dp[n][k] = dp[n - 1][k] * (long double)(k - n + 1) / k;
            }
        }
    }

    cout << fixed << setprecision(6);
    while (T--) {
        int N, K;
        cin >> N >> K;
        cout << (double)dp[N][K] << "\n";
    }

    return 0;
}
