class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int min = 0;
        int max = 0;
        for (int i : nums) {
            if (min < i) {min = i;}
            max += i;
        }
        while (min <= max) {
            int mid = min + (max - min) / 2;
            int split = splitCount(nums, mid);
            if (split > k) {
                min = mid + 1;
            }
            else {
                max = mid - 1;
            }
        }
        return min;
    }
    int splitCount(const vector<int> & nums, int mid) {
        int sum = 0;
        int count = 1;
        for (int i : nums) {
            if (sum + i > mid) {
                count++;
                sum = i;
            }
            else {
                sum += i;
            }
        }
        return count;
    };
};
