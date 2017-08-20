#ifndef PID_H
#define PID_H
#include <sstream>
#include "Twiddle.h"

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Constructor
  */
  PID(double Kp, double Ki, double Kd, int steps);

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  //void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError() const;

  std::string ToString() const
  {
    std::stringstream ss;

    ss << "KP : " << Kp << " KI : " << Ki << " KD : " << Kd;

    return ss.str();
  }
private:
  Twiddle twiddle_;

  int updateCounter;

  double bestError;

  bool isFirstUpdate;

  int steps;
};

#endif /* PID_H */
