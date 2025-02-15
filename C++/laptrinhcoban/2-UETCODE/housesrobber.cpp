int getMoney(int* houses, char* path){
    ifstream file(path);
    if (!file) {
        return 0;
    }
    int count = 0;
    while (file >> houses[count]) {
        count++;
    }
    return count;
}
int rob(int* houses, int numOfHouses) {
    if (numOfHouses == 0) return 0;
    if (numOfHouses == 1) return houses[0];
    if (numOfHouses == 2) return max(houses[0], houses[1]);

    int dp[numOfHouses];    //hàm dp ở đây là hàm để lưu lại các giá trị đã tính toán trước đó.
    dp[0] = houses[0];
    dp[1] = max(houses[0], houses[1]);

    for (int i = 2; i < numOfHouses; i++) {
        dp[i] = max(houses[i] + dp[i-2], dp[i-1]);
    }

    return dp[numOfHouses - 1];
}