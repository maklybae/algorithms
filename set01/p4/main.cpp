#include <iostream>
#include <stack>
#include <utility>
#include <vector>

int main() {
  int n{};
  std::cin >> n;

  std::stack<int> st{};
  int needed{1};
  int pushed{};
  std::vector<std::pair<int, int>> ans{};

  for (int i = 0; i < n; ++i) {
    int cur{};
    std::cin >> cur;

    st.push(cur);
    ++pushed;
    if (st.top() == needed) {
      ans.emplace_back(1, pushed);
      int prev_needed{needed};
      while (!st.empty() && st.top() == needed) {
        st.pop();
        ++needed;
      }
      ans.emplace_back(2, needed - prev_needed);
      pushed = 0;
    }
  }

  if (st.empty()) {
    for (auto& [t, count] : ans) {
      std::cout << t << ' ' << count << '\n';
    }
  } else {
    std::cout << 0 << '\n';
  }
  return 0;
}
