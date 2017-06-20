#include "runner.hpp"
#include "model.hpp"
#include <iostream>
#include <functional>
#include <boost/numeric/odeint.hpp>

namespace pl = std::placeholders;

void printv(const dvector &y, const double t)
{
  std::cout << "t=" << t << " y=" << y[0] << std::endl;
}


void Runner::solve(dvector y0, double t0, double tEnd, double dt)
{
  //
  dvector dydt(y0.size());
  //model->calcRate(y0, dydt, t0);
  auto fct = std::bind(&Model::calcRate, model, pl::_1 , pl::_2 , pl::_3);
  double tstart = 0.0;
  boost::numeric::odeint::integrate(fct,
  				    y0 , t0 , tEnd,  dt, printv);
}
