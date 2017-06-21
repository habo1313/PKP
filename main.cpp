//
//  main.cpp
//  testing
//
//  Created by Michele Vascellari on 16.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include <iostream>

#include <cmath>
#include <string>
#include <boost/numeric/odeint.hpp>


// #include <functional>


// #include "model.hpp"
#include "runner.hpp"

// namespace pl = std::placeholders;


// int main2()
// {
//   SFOR model;

//   // variables
//   double t=0;
//   double tend = 0.1;
//   double dt=1e-4;
//   dvector y = {0, 1000};
//   dvector dydt(2);

//   model.calcRate(y, dydt, t);
//   std::cout << "dydt=" << dydt[0] << std::endl;
//   auto fct = std::bind(&SFOR::calcRate, model, pl::_1 , pl::_2 , pl::_3);
//   //auto fct = std::bind(&SFOR::calcRate, model, t , y , pl::_1);

//   fct(y, dydt, t);
//   //fct(dydt);

//   std::cout << "[bind] dydt=" << dydt[0] << std::endl;

//   boost::numeric::odeint::integrate(fct,
//   				    y , t , tend,  dt, printv);
//   return 0;
// }


// int main2()
// {
//   Model *model = new SFOR();

//   // variables
//   double t=0;
//   double tend = 0.1;
//   double dt=1e-4;
//   dvector y = {0, 1000};
//   dvector dydt(2);

//   model->calcRate(y, dydt, t);
//   std::cout << "dydt=" << dydt[0] << std::endl;
//   auto fct = std::bind(&Model::calcRate, model, pl::_1 , pl::_2 , pl::_3);

//   fct(y, dydt, t);

//   std::cout << "[bind] dydt=" << dydt[0] << std::endl;
  
//   boost::numeric::odeint::integrate(fct,
//   				    y , t , tend,  dt, printv);
//   return 0;
// }

int main()
{
  //dvector parameters = {1e6, 60e6, 0.1};
  std::cout << "Main " << std::endl;
  std::cout << "program" << std::endl;

  // set runner with SFOR=0
  Runner run(0);

  // define parameters
  dvector y = {0, 1000};
  double tend = 0.02;
  double t0 = 0.0;
  double dt = 1e-6;

  // solve
  run.solve(y, t0, tend, dt);

  // get solutions
  std::vector<double> times = run.getTimes();
  std::vector<dvector> states = run.getStates();
  
  // print solutions
  for (int i=0; i < times.size(); ++i)
      std::cout << times[i] << " " << states[i][0] << std::endl;
  
  return 0;
}
