#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

std::pair<int, int> FindInSortedMatrix(std::vector<std::vector<int>>& matrix, int key) {
  int first_row{0};
  int last_row = matrix.size() - 1;
  int first_col{0};
  int last_col = matrix[0].size() - 1;

  while (first_row <= last_row && first_col <= last_col) {
    if (matrix[first_row][first_col] == key) {
      return {first_row, first_col};
    }
    if (!(matrix[last_row][first_col] <= key && key <= matrix[last_row][last_col])) {
      --last_row;
    } else if (!(matrix[last_row][first_col] <= key && key <= matrix[first_row][first_col])) {
      ++first_col;
    } else if (!(matrix[first_row][first_col] <= key && key <= matrix[first_row][last_col])) {
      ++first_row;
    } else {
      --last_col;
    }
  }
  return {-1, -1};
}

int main() {
  std::vector<std::vector<int>> matrix1{{9, 10, 13}, {6, 8, 12}, {1, 5, 7}};
  assert(FindInSortedMatrix(matrix1, 9) == std::make_pair(0, 0));
  assert(FindInSortedMatrix(matrix1, 10) == std::make_pair(0, 1));
  assert(FindInSortedMatrix(matrix1, 13) == std::make_pair(0, 2));
  assert(FindInSortedMatrix(matrix1, 6) == std::make_pair(1, 0));
  assert(FindInSortedMatrix(matrix1, 8) == std::make_pair(1, 1));
  assert(FindInSortedMatrix(matrix1, 12) == std::make_pair(1, 2));
  assert(FindInSortedMatrix(matrix1, 1) == std::make_pair(2, 0));
  assert(FindInSortedMatrix(matrix1, 5) == std::make_pair(2, 1));
  assert(FindInSortedMatrix(matrix1, 7) == std::make_pair(2, 2));
  assert(FindInSortedMatrix(matrix1, 3) == std::make_pair(-1, -1));
  assert(FindInSortedMatrix(matrix1, 54) == std::make_pair(-1, -1));
  assert(FindInSortedMatrix(matrix1, 60) == std::make_pair(-1, -1));
  assert(FindInSortedMatrix(matrix1, 62) == std::make_pair(-1, -1));
  assert(FindInSortedMatrix(matrix1, 69) == std::make_pair(-1, -1));
  assert(FindInSortedMatrix(matrix1, 44) == std::make_pair(-1, -1));
}