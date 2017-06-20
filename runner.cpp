#include "runner.hpp"
#include "model.hpp"


void Runner::solve(dvector y0, double t0, double tEnd, double dt)
{
  //
  dvector dydt(y0.size());
  model->calcRate(t0, y0, dydt);
}
