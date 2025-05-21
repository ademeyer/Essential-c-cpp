#include <bits/stdc++.h>
using namespace std;

enum class ball_t { GOLD, SILVER, CYAN, RED, BLUE, PURPLE, GREEN, PINK, PEACH, YELLOW };
                    /* There are 10 types of ball to select from */
const vector<pair<ball_t, string>> balls{ 
                  {ball_t::GOLD, "GOLD"}, {ball_t::SILVER, "SILVER"}, {ball_t::CYAN, "CYAN"}, 
                  {ball_t::RED, "RED"}, {ball_t::BLUE, "BLUE"}, {ball_t::PURPLE, "PURPLE"}, 
                  {ball_t::GREEN, "GREEN"}, {ball_t::PINK, "PINK"}, {ball_t::PEACH, "PEACH"}, 
                  {ball_t::YELLOW, "YELLOW"} };

const int nStack = 12;
const int nVector = 10;

vector<stack<ball_t>> create_stack_balls()
{
  /* Create exact number of balls */
  vector<vector<ball_t>> first_balls(nVector, 
                          vector<ball_t>(nStack));
  int pick = 0;
  for(int r = 0; r < nVector; ++r)
  {
    for(int c = 0; c < nStack; ++c)
      /* pick from the 10-types of ball */
      first_balls[r][c] = balls[pick].first;
    ++pick;
  }
  
  set<pair<int, int>> cache;
  vector<stack<ball_t>> myVec(nVector);
  for(int i = 0; i < nVector; ++i)
  {
    for(int j = 0; j < nStack; ++j)
    {
      /* Select a ball randomly from first_balls
       * without repeating a ball */
      int r = 0, c = 0;
      while(cache.count({r,c}))
      {
        r = rand() % nVector;
        c = rand() % nStack;
      }
      cache.insert({r,c});
      myVec[i].push(first_balls[r][c]);
    }
  }
  return myVec;
}

void print_balls(const vector<stack<ball_t>>& b)
{
  auto temp_balls = b;
  vector<vector<string>> buffer;
  /* create a ball stack string for printout */
  for(auto& vec : temp_balls)
  {
    auto st = vec;
    vector<string> temp_vec;
    while(!st.empty())
    {
      auto ball_idx = static_cast<int>(st.top()); st.pop(); 
      temp_vec.push_back(balls[ball_idx].second);
    }
    buffer.push_back(temp_vec);
  }

  // Printout balls
  cout << 
    "****************************** ball stacks ***********************************" 
    << endl;

  auto row = buffer.size();
  auto col = buffer[0].size();
  for(int c = 0; c < col; ++c)
  { 
    for(int r = 0; r < row; ++r)
    {
      cout << buffer[r][c] << "\t";
    }
      cout << "\n";
  }
  cout << endl;
}

/* Sort of the ball 
 * Approach: very lazy :- use of hash-map */

void sort_balls(vector<stack<ball_t>>& balls)
{
  if(balls.empty()) return;             // no balls, no show
  map<ball_t, int> balls_mp;  // balls type, number
  for(auto& st : balls)
  {
    while(!st.empty())
    {
      balls_mp[st.top()]++;
      st.pop();
    }
  }
  /* Reload balls back to the vector container */
  int idx = 0;
  for(const auto& mp : balls_mp)
  {
    if (mp.second != nStack) 
    {
     cerr << "we got a different no. of balls:" << mp.second 
          << " from expected: " << nStack <<  endl;
     // return;
    }

    for(int cnt = 0; cnt < mp.second; ++cnt)
    {
      balls[idx].push(mp.first);
    
      if(balls[idx].size() == nStack)
        ++idx;
    }
  }
}

int main()
{
  auto myballs = create_stack_balls();
  cout << "balls before sorting" << endl;
  print_balls(myballs);
  sort_balls(myballs);
  print_balls(myballs);
  cout << "balls after sorting" << endl;
  return 0;
}
