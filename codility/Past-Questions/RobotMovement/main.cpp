#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> robotMovement(vector<vector<int>> &grid, string S)
{
  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<int>> path;
  /* Initial movement */
  int x = 0, y = 0;
  path.push_back({x, y});

  for (const auto &c : S)
  {
    int nx = x, ny = y;
    /* If move up: U */
    if (c == 'U')
      nx--;
    /* If move down: D */
    else if (c == 'D')
      nx++;
    /* If move left: L */
    else if (c == 'L')
      ny--;
    /* If move right: R */
    else if (c == 'R')
      ny++;
    else
    { /* No idea of this */
    }

    /*Check if the new position is inbound and not blocked*/
    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
        grid[nx][ny] == 0)
    {
      /* move */
      x = nx;
      y = ny;
    }
    /*update movement */
    path.push_back({x, y});
  }
  return path;
}

int main()
{
  vector<vector<int>> grid = {
      {0, 0},
      {1, 0}};
  string S = "UDRL";
  auto res = robotMovement(grid, S);
  cout << "[";
  for (const auto &u : res)
  {
    cout << "[";
    for (const auto &i : u)
      cout << i << ",";
    cout << "],";
  }
  cout << "]\n";
  return 0;
}
