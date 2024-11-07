class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> HashTable;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            HashTable[nums[i]] = i;
        }

        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];
            if (HashTable.count(complement) && HashTable[complement] != i) {
                return {i, HashTable[complement]};
            }
        }

        return {};
    }
};