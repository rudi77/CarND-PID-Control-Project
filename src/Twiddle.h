#pragma once
#include <string>
#include <vector>

class Twiddle
{
public:
  // Contructor
  explicit Twiddle(double tolerance, const std::vector<double>& p, const std::vector<double>& dp);

  // Destructor
  virtual ~Twiddle();

  // Optimizes the parameters
  void Optimize(double error);

  // Returns parameters
  const std::vector<double>& Params() const { return p; }

private:
  enum State
  {
    State1,
    State2,
    State3,
    Finished
  };

  State currentState;

  // Parameters
  std::vector<double> p;

  // Potential changes that we want to probe
  std::vector<double> dp;

  // Termination condition
  double tolerance;

  int p_index;

  double best_err;

  std::string ToString() const;

  int UpdateIndex() const { return (p_index + 1) % 3; }
};
