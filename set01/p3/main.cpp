#include <iostream>
#include <stack>
#include <string>
#include <utility>

std::string Repeat(const std::string& sample, int count) {
  std::string res{};
  res.reserve(sample.size() * count);
  for (int i = 0; i < count; ++i) {
    res += sample;
  }
  return res;
}

int main() {
  std::string input{};
  std::getline(std::cin, input);

  std::stack<std::pair<int, std::string>> st{};
  st.emplace(1, "");
  int cur_repetition{};
  for (auto ch : input) {
    if ('0' <= ch && ch <= '9') {
      cur_repetition = ch - '0';
    } else if (ch == '[') {
      st.emplace(cur_repetition, "");
    } else if (ch == ']') {
      auto [times, sample] = st.top();
      st.pop();
      st.top().second += Repeat(sample, times);
    } else {
      st.top().second.push_back(ch);
    }
  }

  std::cout << st.top().second;
}