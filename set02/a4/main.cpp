long long CINV(std::vector<long long> &arr) {
    // Base case
    if (arr.size() == 1) {
        return 0;
    }

    // 1. Divide
    size_t mid = arr.size() / 2;
    std::vector<long long> left(arr.begin(), arr.begin() + mid);
    std::vector<long long> right(arr.begin() + mid, arr.end());

    // 2. Conquer
    auto count_left = CINV(left);
    auto count_right = CINV(right);
    
    // 3. Combine
    long long count_merge{};
    for (auto iter = arr.begin(), iter_left = left.begin(), iter_right = right.begin();
            iter != arr.end(); ++iter) {
        if (iter_left != left.end() &&
              (iter_right == right.end() || *iter_left <= *iter_right)) {
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

long long CSINV(std::vector<long long> &arr) {
    // Base case
    if (arr.size() == 1) {
        return 0;
    }

    // 1. Divide
    size_t mid = arr.size() / 2;
    std::vector<long long> left(arr.begin(), arr.begin() + mid);
    std::vector<long long> right(arr.begin() + mid, arr.end());

    // 2. Conquer
    auto count_left = CSINV(left);
    auto count_right = CSINV(right);
    
    // 3. Combine

    // 3.1. Combine - Count inversions which starts at left half and ends at right part 
    long long count_merge{};
    for (auto iter_left = left.begin(), iter_right = right.begin();
            iter_left != left.end() && iter_right != right.end();) {
        if (iter_left != left.end() &&
              (iter_right == right.end() || *iter_left <= 2 * *iter_right)) {
            ++iter_left;
        } else {
            count_merge += std::distance(iter_left, left.end());
            ++iter_right;                
        }
    }

    // 3.2. Combine - Merge two halfs to make array sorted
    for (auto iter = arr.begin(), iter_left = left.begin(), iter_right = right.begin();
            iter != arr.end(); ++iter) {
        if (iter_left != left.end() &&
              (iter_right == right.end() || *iter_left <= *iter_right)) {
            *iter = *iter_left;
            ++iter_left;
        } else {
            *iter = *iter_right;
            ++iter_right;
        }
    }
    
    return count_left + count_right + count_merge;
}