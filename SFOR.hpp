//
// Created by Michele Vascellari on 13.12.17.
//

#ifndef PKP_SFOR_HPP
#define PKP_SFOR_HPP

#include "model.hpp"
//
//  Single First Order Reaction (SFOR) model class
//
class SFOR: public Model
{
public:
  SFOR(const std::vector<double> &par= sforParDefault): Model(par, sforParDefault, "SFOR",
                                                              sforParNames, sforInitState){}
  //SFOR(): Model(sforParDefault, sforParDefault, "SFOR", sforParNames,
  //    sforInitState){};
  ~SFOR(){}
  virtual void calcRate(const std::vector<double> &y, std::vector<double> &dydt, double t, double T);
};



#endif //PKP_SFOR_HPP
