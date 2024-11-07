class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int ans = 0;
        unordered_map<char, int> HashTable;
        int i = 0; 

        for (int j = 0; j < n; j++) {
            if (HashTable.find(s[j]) != HashTable.end()) {
                i = max(HashTable[s[j]] + 1, i);
            }
            ans = max(ans, j - i + 1);
            HashTable[s[j]] = j;
        }

        return ans;
    }
};