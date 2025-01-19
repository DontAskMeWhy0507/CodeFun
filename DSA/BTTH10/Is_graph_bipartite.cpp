class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> color(graph.size(), 0);
        for (int i = 0; i < graph.size(); i++) {
            if (color[i] == 0 && !dfs(graph, color, i, 1)) {
                return false;
            }
        }
        return true;
    }

    bool dfs(vector<vector<int>>& graph, vector<int>& color, int node, int c) {
        if (color[node] != 0) {
            return color[node] == c;
        }
        color[node] = c;
        for (int i = 0; i < graph[node].size(); i++) {
            if (!dfs(graph, color, graph[node][i], -c)) {
                return false;
            }
        }
        return true;
    }
};