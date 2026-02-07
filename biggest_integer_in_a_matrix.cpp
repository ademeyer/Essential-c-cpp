#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
  int solution(const std::vector<std::vector<int>> &board)
  {
    int N = board.size();    // row
    int M = board[0].size(); // column

    int best = -1;

    const std::vector<std::pair<int, int>> dirs =
        {{-1, 0},
         {1, 0},
         {0, -1},
         {0, 1}};

    std::function<void(int, int, int, int, std::vector<std::vector<bool>> &)> dfs =
        [&](int r, int c, int depth, int number, std::vector<std::vector<bool>> &visited)
    {
      if (depth == 4)
      {
        best = std::max(best, number);
        return;
      }

      // append current digit
      number = number * 10 + board[r][c];

      // mark as visited for this depth
      visited[r][c] = true;

      if (depth == 3)
        best = std::max(best, number);
      else
      {
        // find neighbours
        for (const auto &dir : dirs)
        {
          int nr = r + dir.first;
          int nc = c + dir.second;
          // check if in-bound
          if (nr >= 0 && nr < N && nc >= 0 && nc < M && !visited[nr][nc])
            dfs(nr, nc, depth + 1, number, visited);
        }
      }

      // Backtrack
      visited[r][c] = false;
    };

    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < M; ++j)
      {
        std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
        dfs(i, j, 0, 0, visited);
      }
    }

    return best;
  }
};

int main()
{
  std::vector<std::vector<int>> board =
      {
          {9, 1, 1, 0, 7},
          {1, 0, 2, 1, 0},
          {1, 9, 1, 1, 0}};

  Solution sol;
  int result = sol.solution(board);
  std::cout << "result: " << result << std::endl;

  return 0;
}
