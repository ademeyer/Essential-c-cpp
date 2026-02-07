#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> solveMinesweeper(std::vector<std::string> &board)
{
  int n = board.size();
  int m = board[0].size();

  std::vector<std::string> result = board;

  // neighbour direction 8 dir
  const std::vector<std::pair<int, int>> dirs =
      {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      if (board[i][j] == 'X')
        result[i][j] = 'X'; // keep mines as 'X'
      else
      {
        // count mines in the surrounding cells
        int count = 0;
        for (const auto &dir : dirs)
        {
          int ni = i + dir.first;
          int nj = j + dir.second;

          if (ni >= 0 && ni < n && nj >= 0 && nj < m && board[ni][nj] == 'X')
            ++count;
        }
        // Convert count to char (0 - 8)
        result[i][j] = count + '0';
      }
    }
  }
  return result;
}

// Helper function to print results for testing
void printBoard(const std::vector<std::string> &board)
{
  for (const auto &row : board)
  {
    std::cout << row << std::endl;
  }
  std::cout << std::endl;
}

int main()
{
  // Test case 1
  std::vector<std::string> test1 = {"XOO", "OOO", "XXO"};
  std::vector<std::string> result1 = solveMinesweeper(test1);
  std::cout << "Test 1 Output:" << std::endl;
  printBoard(result1);

  // Test case 2
  std::vector<std::string> test2 = {
      "XOOXXXOO",
      "OOOOXOXX",
      "XXOXXOOO",
      "OXOOOXXX",
      "OOXXXXOX",
      "XOXXXOXO",
      "OOOXOXOX",
      "XOXXOXOX"};
  std::vector<std::string> result2 = solveMinesweeper(test2);
  std::cout << "Test 2 Output:" << std::endl;
  printBoard(result2);

  return 0;
}