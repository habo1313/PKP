//
// Created by Michele Vascellari on 13.12.17.
//

#ifndef PKP_C2SM_HPP
#define PKP_C2SM_HPP

#include "model.hpp"

// C2SM
const dvector c2smParDefault = {1e6, 50e6, 0.3, 1e8, 100e6, 1.0};
const parVector c2smParNames = {"A1", "E1", "y1", "A2", "E2", "y2"};
const dvector c2smInitState = {0.0, 1.0}; // [vol, solid]
//
// Competing 2 Step Model (C2SM) class
//
class C2SM: public Model
{
public:
  C2SM(const std::vector<double> &par= c2smParDefault):
    Model(par, c2smParDefault, "C2SM", c2smParNames, c2smInitState){};
  //C2SM(): Model(c2smParDefault, c2smParDefault, "C2SM", c2smParNames,
  //    c2smInitState){};
  ~C2SM(){};
  virtual void calcRate(const std::vector<double> &y, std::vector<double> &dydt, double t, double T);
};

#endif //PKP_C2SM_HPP
