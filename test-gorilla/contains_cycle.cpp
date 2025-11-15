#include <bits/stdc++.h>
using namespace std;

bool contain_cycle(const vector<int> graph[], const int n)
{
  vector<bool> visited(n, false);
  vector<bool> recStack(n, false);

  function<bool(int)> isCyclicDFS = [&](int node) -> bool
  {
    visited[node] = true;
    recStack[node] = true;
    
    for(auto nxtNode : graph[node])
    {      
      // if nxtNode is inbound, might have children node too
      if(!visited[nxtNode])
      {
        if(isCyclicDFS(nxtNode))
          return true;
      }
      else if(visited[nxtNode] && recStack[nxtNode])
        return true;
    }

    recStack[node] = false;
    return false;
  };

  for(int i = 0; i < n; ++i)
  {
    if(!visited[i])
    {
      if(isCyclicDFS(i))
        return true;
    }
  }
  return false;
}

void makeEdges(const vector<pair<int,int>> p, vector<int> g[])
{
  for(const auto& n : p)
  {
    g[n.first].push_back(n.second);
  }
}

void printVecArr(const vector<int> g[], int s)
{
  for(int i = 0; i < s; ++i)
  {
    cout << i << ": ";
    for(const auto& n : g[i])
      cout << n << ",";
    cout << endl;
  }
  cout << endl;
}

int main()
{
  vector<pair<int,int>> g{ {0,1}, {1,2}, {2,3}, {3,4}, {4,2} };
  int N = g.size();
  vector<int> graph1[N];
  makeEdges(g, graph1);
  printVecArr(graph1, N);
  cout << "contains cycle: " << (contain_cycle(graph1, N) ? "True" : "False") << endl;
  
  g = { {0,1}, {1,2}, {2,3}, {3,4} };
  N = g.size();
  vector<int> graph2[N];
  makeEdges(g, graph2);
  printVecArr(graph2, N);
  cout << "contains cycle: " << (contain_cycle(graph2, N) ? "True" : "False") << endl;
  return 0;
}
