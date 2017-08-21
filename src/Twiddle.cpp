#include <iostream>
#include <algorithm>
#include <sstream>

#include "Twiddle.h"

using namespace std;


Twiddle::Twiddle(double tolerance, const vector<double>& p, const vector<double>& dp)
  : currentState(State1), 
    p(p), 
    dp(dp), 
    tolerance(tolerance), 
    p_index(0), 
    best_err(numeric_limits<double>::max())
{}

Twiddle::~Twiddle()
{}

void Twiddle::Optimize(double error)
{
  switch (currentState)
  {
  case State1:
    best_err = error;
    p[p_index] += dp[p_index];
    currentState = State2;
    break;
  case State2:
    if (error < best_err)
    {
      best_err = error;
      dp[p_index] *= 1.1;
      p_index = UpdateIndex();
    }
    else
    {
      // Undo
      p[p_index] -= 2 * dp[p_index];
    }

    currentState = State3;
    break;
  case State3:
    if (error < best_err)
    {
      best_err = error;
      dp[p_index] *= 1.1;
    }
    else
    {
      p[p_index] += dp[p_index];
      dp[p_index] *= 0.9;
    }

    p_index = UpdateIndex();

    if (accumulate(dp.begin(), dp.end(), 0.0) < tolerance)
    {
      currentState = Finished;
    }
    else
    {
      currentState = State1;
    }
    break;
    case Finished:
    cout << "Finished " << ToString() << endl;
    break;
  default: ;
  }

  cout << ToString() << endl;
}

string Twiddle::ToString() const
{
  auto ss = stringstream();
  ss << " p1 : " << p[0] << " p2 : " << p[1] << " p3 : " << p[2] << " dp1 : " << dp[0] << " dp2: " << dp[1] << " dp3: " << dp[2];

  return ss.str();
}
