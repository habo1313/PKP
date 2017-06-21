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
  // for (int i=0; i < times.size(); ++i)
  //   {
  //     //std::cout << times[i] << " " << states[i][0] << std::endl;
  //   }
  run.dump("solution.csv");
						      
  return 0;
}
