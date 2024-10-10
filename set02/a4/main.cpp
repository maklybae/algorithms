class Solution {
  public:
    // arr[]: Input Array
    // N : Size of the Array arr[]
    // Function to count inversions in the array.
    long long int inversionCount(vector<long long> &arr) {
        if (arr.size() == 1) {
            return 0;
        }
        size_t mid = arr.size() / 2;
        std::vector<long long> left(arr.begin(), arr.begin() + mid);
        std::vector<long long> right(arr.begin() + mid, arr.end());
        
        auto count_left = inversionCount(left);
        auto count_right = inversionCount(right);
        
        long long count_merge{};
        for (auto iter = arr.begin(), iter_left = left.begin(), iter_right = right.begin(); iter != arr.end();++iter) {
            if (iter_left != left.end() && (iter_right == right.end() || *iter_left <= *iter_right)) {
                *iter = *iter_left;
                ++iter_left;
            } else {
                *iter = *iter_right;
                count_merge += std::distance(iter_left, left.end());
                ++iter_right;                
            }
        }
        
        return count_left + count_right + count_merge;
    }
};