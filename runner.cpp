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


void Runner::solve(dvector y0, double t0, double tEnd, double dt)
{
  //
  dvector dydt(y0.size());

  // define integral function from model
  auto fct = std::bind(&Model::calcRate, model, pl::_1 , pl::_2 , pl::_3);
  double tstart = 0.0;

  std::vector<double> t = {t0};
  std::vector<dvector> x = {y0};

  // initialize push structure
  push_back_state_and_time solution(x, t);

  // integrate
  boost::numeric::odeint::integrate(fct, y0 , t0 , tEnd,  dt, solution);

  // store solutions
  states = solution.m_states;
  times = solution.m_times;
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
