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
#include <string.h>


int main(int argc, char **argv)
{
  //dvector parameters = {1e6, 60e6, 0.1};
  std::cout << "Main program" << std::endl;

  Runner::models model;
  std::string modelName;

  if (argc==1)
    {
      model = Runner::sfor;
      modelName = "sfor";
    }
  else{
    if(strcmp(argv[1],"sfor")==0)
      {
	       model = Runner::sfor;
	       modelName = argv[1];
      }
    else if(strcmp(argv[1],"c2sm")==0)
      {
	       model = Runner::c2sm;
	       modelName = argv[1];
      }
    else
    {
      std::cout << "Model " << argv[1] << " not defined" << std::endl;
      return -1;
    }
  }


  // set runner with SFOR=0
  std::cout << "Init Runner with " << modelName <<" - " << model << std::endl;
  Runner run(model);

  std::cout << "Parameters:";
  //dvector parameters = run.getParameters();
  //for (auto p: parameters)
  //{
  //  std::cout << p << "\t";
  //}
  //std::cout << std::endl;
  run.printParameters();

  // define parameters
  //dvector y = {0, 1000};
  double tend = 0.02;
  //double t0 = 0.0;
  double dt = 1e-6;

  // solve
  std::cout << "Solve" << std::endl;
  run.solve(tend, dt);

  // get solutions
  std::vector<double> times = run.getTimes();
  std::vector<dvector> states = run.getStates();

  run.dump("solution.csv");

  return 0;
}
