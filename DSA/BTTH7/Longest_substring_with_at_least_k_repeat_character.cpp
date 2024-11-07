class Solution {
public:
    int longestSubstring(string s, int k) {
        return longestSubstringHelper(s, 0, s.size(), k);
    }

private:
    int longestSubstringHelper(const string& s, int start, int end, int k) {
        if (end - start < k) return 0; // If the substring length is less than k, it can't have k repeating characters

        unordered_map<char, int> count;
        for (int i = start; i < end; i++) {
            count[s[i]]++;
        }

        for (int i = start; i < end; i++) {
            if (count[s[i]] < k) {
                int j = i + 1;
                while (j < end && count[s[j]] < k) j++;
                return max(longestSubstringHelper(s, start, i, k), longestSubstringHelper(s, j, end, k));
            }
        }

        return end - start;
    }
};