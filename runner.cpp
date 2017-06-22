#include "runner.hpp"
#include "model.hpp"
#include <iostream>
#include <functional>
#include <boost/numeric/odeint.hpp>
#include <fstream>

#include "csv.hpp"

namespace pl = std::placeholders;

void printv(const dvector &y, const double t)
{
  std::cout << "t=" << t << " y=" << y[0] << std::endl;
}


void Runner::solve(double t, double dt)
{
  //
  double T = 1000;
  dvector y0 = model->getInitState();
  y0.push_back(T);
  dvector dydt(y0.size());

  // define integral function from model
  //auto fct = std::bind(&Model::calcRate, model, pl::_1 , pl::_2 , pl::_3);
  auto fct = std::bind(&Runner::dydt, this, pl::_1 , pl::_2 , pl::_3);

  double t0 = 0.0;

  std::vector<double> ts = {t0};
  std::vector<dvector> xs = {y0};

  // initialize push structure
  push_back_state_and_time solution(xs, ts);

  // integrate
  boost::numeric::odeint::integrate(fct, y0 , t0 , t,  dt, solution);

  // store solutions
  states = solution.m_states;
  times = solution.m_times;
}

void Runner::dydt(const dvector &y, dvector &dydt, double t)
{
    size_t n = dydt.size();
    //double T = dydt.back();
    //double T = y[n-1];
    double T = y.back();
    model->calcRate(y, dydt, t, T);
    dydt[n-1] = 0.0; // const temperature
}


void Runner::dump(const std::string &csv, std::string sep)
{
  // std::ofstream file(csv);
  // for (int i=0; i < times.size(); ++i)
  //   {
  //     file << times[i];
  //     for (int j=0; j < states[i].size(); ++j)
  // 	file << sep << states[i][j];
  //     file << std::endl;
  //   }
  // file.close();
  csvfile file(csv);
  file << "time" ;
  char buffer[2];
  for (int j=0; j< states[0].size()-1; ++j)
    {
      std::sprintf (buffer, "y%d", j);
      file << std::string(buffer);
    }
  file << "Temperature" << endrow;

  for (int i=0; i < times.size(); ++i)
    {
      file << times[i];
      for (int j=0; j < states[i].size(); ++j)
	{
	  file << states[i][j];
	}
      file << endrow;
    }
}
