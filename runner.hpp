//
//  runner.hpp
//  testing
//
//  Created by Michele Vascellari on 19.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#ifndef runner_hpp
#define runner_hpp

//#include <memory>
#include "model.hpp"
#include <iostream>
#include <string>

void printv(const dvector &y, const double t);

struct push_back_state_and_time
{
    std::vector< dvector >& m_states;
    std::vector< double >& m_times;

    push_back_state_and_time( std::vector< dvector > &states , std::vector< double > &times )
      : m_states( states ) , m_times( times ) {}

    void operator()( const dvector &x , double t )
    {
      m_states.push_back( x );
      m_times.push_back( t );
    }
};

class Runner
{
protected:
  Model * model;
  std::vector<double> times;
  std::vector<dvector> states;
  //std::unique_ptr<Model> model;
public:
  //enum models {sfor, c2sm};
  Runner(int modelType, dvector parameters)
  {
    if (modelType == 0)
      {
	model = new SFOR(parameters);
      }
    else if (modelType == 1)
      {
	model = new C2SM(parameters);
      }
    else
      {
	throw 1;
      }
    // switch (modelType)
    //   {
    //   case(0):
    // 	  std::cout << "SFOR" << std::endl;
    // 	  model = new SFOR(parameters);
    // 	//model = std::make_unique<SFOR>(parameters);
    //   case(1):
    // 	  std::cout << "C2SM" << std::endl;
    // 	  model = new C2SM(parameters);
    // 	//model = std::make_unique<SFOR>(parameters);
    //   }
  }
  Runner(int modelType)
    {
    if (modelType == 0)
      {
	model = new SFOR;
      }
    else if (modelType == 1)
      {
	model = new C2SM;
      }
    else
      {
	throw 1;
      }
    }
  ~Runner(){delete model;}
  void solve(dvector y0, double t0, double tEnd, double dt);
  dvector const getParameters(){return model->getParameters();}
  std::vector<double> getTimes(){return times;}
  std::vector<dvector> getStates(){return states;}
  void dump(const std::string &csv, std::string sep = ",");
};



#endif /* runner_hpp */
