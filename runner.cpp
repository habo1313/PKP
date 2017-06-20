#include "runner.hpp"
#include "model.hpp"


void Runner::solve(dvector y0, double t0, double tEnd, double dt)
{
  //
  dvector dydt(y0.size());
  model->calcRate(y0, dydt, t0);
}
