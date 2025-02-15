int prims(int n, vector<vector<int>> edges, int start) {
    vector<vector<pair<int, int>>> adj(n);
    for(auto edge : edges) {
        adj[edge[0] - 1].push_back({edge[1] - 1, edge[2]});
        adj[edge[1] - 1].push_back({edge[0] - 1, edge[2]});
    }

    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        visited[u] = true;

        for(auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if(!visited[v] && dist[v] > weight) {
                dist[v] = weight;
                pq.push({dist[v], v});
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(dist[i] != INT_MAX) {
            ans += dist[i];
        }
    }

    return ans;
}
