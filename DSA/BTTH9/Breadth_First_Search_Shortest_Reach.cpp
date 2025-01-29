vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) {
    vector<int> dist(n + 1, -1);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
        adj[edges[i][1]].push_back(edges[i][0]);
    }
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 6;
                q.push(v);
            }
        }
    }
    vector<int> res;
    for (int i = 1; i <= n; i++) {
        if (i != s) {
            res.push_back(dist[i]);
        }
    }
    return res;
}