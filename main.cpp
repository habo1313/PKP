//
//  main.cpp
//  testing
//
//  Created by Michele Vascellari on 16.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include <iostream>
#include "model.hpp"
#include <cmath>
#include <string>
#include <boost/numeric/odeint.hpp>
#include <functional>

namespace pl = std::placeholders;

void printv(const dvector &y, const double t);

int main2()
{
  SFOR model;

  // variables
  double t=0;
  double tend = 0.1;
  double dt=1e-4;
  dvector y = {0, 1000};
  dvector dydt(2);

  model.calcRate(y, dydt, t);
  std::cout << "dydt=" << dydt[0] << std::endl;
  auto fct = std::bind(&SFOR::calcRate, model, pl::_1 , pl::_2 , pl::_3);
  //auto fct = std::bind(&SFOR::calcRate, model, t , y , pl::_1);

  fct(y, dydt, t);
  //fct(dydt);

  std::cout << "[bind] dydt=" << dydt[0] << std::endl;

  boost::numeric::odeint::integrate(fct,
  				    y , t , tend,  dt, printv);
  return 0;
}


void printv(const dvector &y, const double t)
{
  std::cout << "t=" << t << " y=" << y[0] << std::endl;
}


int main()
{
  Model *model = new SFOR();

  // variables
  double t=0;
  double tend = 0.1;
  double dt=1e-4;
  dvector y = {0, 1000};
  dvector dydt(2);

  model->calcRate(y, dydt, t);
  std::cout << "dydt=" << dydt[0] << std::endl;
  auto fct = std::bind(&Model::calcRate, model, pl::_1 , pl::_2 , pl::_3);

  fct(y, dydt, t);

  std::cout << "[bind] dydt=" << dydt[0] << std::endl;
  
  boost::numeric::odeint::integrate(fct,
  				    y , t , tend,  dt, printv);
  return 0;
}
