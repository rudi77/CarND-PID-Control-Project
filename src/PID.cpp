#include "PID.h"

using namespace std;

PID::PID(double Kp, double Ki, double Kd) 
  : p_error(0), i_error(0), d_error(0), 
    Kp(Kp), Ki(Ki), Kd(Kd), 
    isFirstUpdate(true)
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
}

double PID::TotalError() const
{
  return -Kp * p_error - Kd * d_error - Ki * i_error;
}
