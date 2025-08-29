#include <bits/stdc++.h>
using namespace std;

/*
['.#..', '.#.#', '######', '...#.', '...###'], output = 3
['#..', '#..#', '.##.', '...'] , output = 2
['###', '###', '#####', '#**#', '.#####.', '..#..'], out = 5
['.....', '#####', '....*'], out = 1
*/

int minRobotRuns(const vector<string> &grid)
{
  if (grid.empty() || grid[0].empty())
    return 0;
  /* known directions */
  const vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  // variables
  int rows = grid.size();
  int cols = grid[0].size();
  vector<pair<int, int>> dirtyCells;
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));

  /* Find all dirty cells */
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (grid[i][j] == '*')
        dirtyCells.push_back({i, j});
    }
  }

  /* If we find no dirty cells */
  if (dirtyCells.empty())
    return 0;
  /* BFS to detect all connected components */
  auto bfs = [&](int start_i, int start_j) -> vector<pair<int, int>>
  {
    queue<pair<int, int>> q;
    q.push({start_i, start_j});
    visited[start_i][start_j] = true;
    vector<pair<int, int>> connected_components;
    while (!q.empty())
    {
      auto [i, j] = q.front();
      q.pop();
      connected_components.push_back({i, j});
      for (const auto &[dir_i, dir_j] : dirs)
      {
        int di = i + dir_i;
        int dj = j + dir_j;
        /* if points are inbound */
        if (di >= 0 && di < rows && dj >= 0 && dj < cols &&
            !visited[di][dj] && grid[di][dj] != '#')
        {
          visited[di][dj] = true;
          q.push({di, dj});
        }
      }
    }
    return connected_components;
  };

  int cnt_comp = 0;
  for (const auto &[i, j] : dirtyCells)
  {
    if (!visited[i][j])
    {
      auto comp = bfs(i, j);
      /* Check if this component contains at least one dirty cell */
      bool hasDirty = false;
      for (const auto &[x, y] : comp)
      {
        if (grid[x][y] == '*')
        {
          hasDirty = true;
          break;
        }
      }
      if (hasDirty)
        ++cnt_comp;
    }
  }
  return cnt_comp;
}

int main()
{
  vector<vector<string>> testCases = {
      {".#..", ".#.#", "######", "...#.", "...###"},       // Expected: 3
      {"#..", "#..#", ".##.", "..."},                      // Expected: 2
      {"###", "###", "#####", "#**#", ".#####.", "..#.."}, // Expected: 5
      {".....", "#####", "....*"}                          // Expected: 1
  };

  for (const auto &vec : testCases)
  {
    auto res = minRobotRuns(vec);
    cout << "res: " << res << endl;
  }
  return 0;
}
