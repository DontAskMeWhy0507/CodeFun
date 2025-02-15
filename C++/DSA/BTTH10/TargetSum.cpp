class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        return findWays(nums, target, 0, 0);
        
    }

    int findWays(vector<int>& nums, int target, int index, int currentSum) {
        if (index == nums.size()) {
            return target == currentSum ? 1 : 0;
        }

        return findWays(nums, target, index+1, currentSum + nums[index]) +
        findWays(nums,target, index+1, currentSum - nums[index]);
    }
};