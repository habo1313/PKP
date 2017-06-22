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
  void dydt(const dvector y, dvector dydt, double t);
  //std::unique_ptr<Model> model;
public:
  enum models {sfor, c2sm};
  Runner(models modelType, dvector parameters)
  {
    switch (modelType)
      {
      case sfor:
	model = new SFOR(parameters); break;
      case c2sm:
	model = new C2SM(parameters); break;
      }
    //throw 0;
  }
  Runner(models modelType)
  {
    switch (modelType)
      {
      case sfor:
	model = new SFOR(); break;
      case c2sm:
	model = new C2SM(); break;
      }
    //throw 0;
  }
  ~Runner(){delete model;}
  void solve(double t, double dt=1e-4);
  dvector const getParameters(){return model->getParameters();}
  std::vector<double> getTimes(){return times;}
  std::vector<dvector> getStates(){return states;}
  void dump(const std::string &csv, std::string sep = ",");
  void printParameters(){model->printParameters();}
};



#endif /* runner_hpp */
