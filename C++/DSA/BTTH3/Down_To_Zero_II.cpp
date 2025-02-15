int downToZero(int n) {
    if (n == 0) return 0;

    queue<pair<int, int>> q;
    unordered_set<int> visited;

    q.push({n, 0});
    visited.insert(n);

    while (!q.empty()) {
        auto [current, moves] = q.front();
        q.pop();

        if (current == 0) return moves;

        if (visited.find(current - 1) == visited.end()) {
            q.push({current - 1, moves + 1});
            visited.insert(current - 1);
        }

        for (int i = 2; i <= sqrt(current); ++i) {
            if (current % i == 0) {
                int factor = current / i;
                if (visited.find(factor) == visited.end()) {
                    q.push({factor, moves + 1});
                    visited.insert(factor);
                }
            }
        }
    }

}