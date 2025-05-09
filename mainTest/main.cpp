#include <iostream>
#include <vector>
#include <functional>
#include <queue>
using namespace std;

int getMinimumConnections(const std::vector<std::vector<bool>>& matrix)
{
    auto n = matrix.size();

    if(n == 0) return 0;

    vector<bool> visited(n, false);

    function<void(int)> bfs = [&](int i)
    {
        visited[i] = true;
        queue<int>q;
        q.push(i);

        while(!q.empty())
        {
            auto pos = q.front(); q.pop();

            for(int k = 0; k < n; ++k)
            {
                if(matrix[pos][k] && !visited[k])
                {
                    // mark as visited
                    visited[k] = true;
                    q.push(k);
                }
            }
        }
    };

    int result = 0;
    for(int i = 0; i < n; ++i)
    {
        if(!visited[i])
        {
            bfs(i);
            ++result;
        }
    }
    return result - 1;
}
