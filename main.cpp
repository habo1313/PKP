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

// yaml reader
#include <yaml-cpp/yaml.h>


// #include <functional>


// #include "model.hpp"
#include "reactor.hpp"
#include <string.h>


int main(int argc, char **argv)
{
  //dvector parameters = {1e6, 60e6, 0.1};
  std::cout << "Main program" << std::endl;


  //YAML::Node config = YAML::LoadFile(argv[1]);
  YAML::Node config = YAML::LoadFile(argv[1]);

  Runner::models model;
  std::string modelName = config["model"]["type"].as<std::string>();
  dvector parameters = config["model"]["parameters"].as<dvector>();



  if(modelName==std::string("SFOR"))
  {
      model = Runner::sfor;
  }
  else if(modelName==std::string("C2SM"))
  {
      model = Runner::c2sm;
  }
  else
  {
      std::cout << "Model " << argv[1] << " not defined" << std::endl;
      return -1;
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
  double t = config["operating_conditions"]["t"].as<double>();
  double T = config["operating_conditions"]["T"].as<double>();
  //double t0 = 0.0;
  double dt = config["operating_conditions"]["dt"].as<double>();

  // solve
  std::cout << "Solve" << std::endl;
  run.solve(t, T, dt, true);

  // get solutions
  std::vector<double> times = run.getTimes();
  std::vector<dvector> states = run.getStates();

  run.dump("solution.csv");

  return 0;
}
