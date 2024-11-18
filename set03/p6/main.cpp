#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int estimate(const std::vector<int>& spots) {
  std::vector<bool> add_diags(2 * spots.size() + 1);
  std::vector<bool> sub_diags(2 * spots.size() + 1);
  int count{};

  for (int i = 0; i < spots.size(); ++i) {
    if (!add_diags[i + spots[i]] && !sub_diags[i - spots[i] + spots.size() - 1]) {
      add_diags[i + spots[i]] = true;
      sub_diags[i - spots[i] + spots.size() - 1] = true;
      ++count;
    }
  }

  return count;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n{};
  std::cin >> n;

  std::vector<int> spots(n);
  std::iota(spots.begin(), spots.end(), 0);

  std::random_device dev{};
  std::mt19937 rng(dev());
  rng.seed(914123);
  std::uniform_real_distribution<double> unif(0, 1);
  std::shuffle(spots.begin(), spots.end(), rng);

  int energy = estimate(spots);
  double ti = 1;

  for (int i = 0; i < 30000; ++i) {
    ti *= 0.95;

    auto new_spots = spots;
    std::swap(new_spots[rng() % n], new_spots[rng() % n]);
    int new_energy = estimate(new_spots);
    int d_energy = new_energy - energy;

    if (new_energy > energy || unif(rng) < std::exp(d_energy / ti)) {
      spots = std::move(new_spots);
      energy = new_energy;
    }
  }

  for (int i = 0; i < spots.size(); ++i) {
    std::cout << spots[i] + 1 << ' ';
  }

  // std::cout << estimate({4, 0, 1, 2, 3, 6, 7, 5});

  return 0;
}