#include "PID.h"

using namespace std;

PID::PID(double Kp, double Ki, double Kd, int steps) 
  : p_error(0), i_error(0), d_error(0), 
    Kp(Kp), Ki(Ki), Kd(Kd), 
    twiddle_(0.0001, {Kp, Ki, Kd}, {0.1, 1.0, 0.00000}), 
    updateCounter(0), 
    bestError(0.0), 
    isFirstUpdate(true), steps(steps)
{}

PID::~PID() {}

void PID::UpdateError(double cte) 
{
  // There is no d_error in the first step
  if (isFirstUpdate)
  {
    p_error = cte;
    isFirstUpdate = false;
  }

  d_error = cte - p_error; 
  i_error += cte;
  p_error = cte;

  bestError += cte * cte;
 
  //if (updateCounter > 0 && updateCounter % steps == 0)
  //{
  //  auto error = bestError / static_cast<double>(steps);

  //  bestError = 0.0;
  //  twiddle_.Optimize(error);

  //  auto params = twiddle_.Params();
  //  
  //  Kp = params[0];
  //  Ki = params[1];
  //  Kd = params[2];
  //}

  //++updateCounter;
}

double PID::TotalError() const
{
  return -Kp * p_error - Ki * d_error - Kd * i_error;
}
