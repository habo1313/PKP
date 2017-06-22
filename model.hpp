//
//  model.hpp
//  testing
//
//  Created by Michele Vascellari on 20.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>


// double vector data
typedef std::vector<double> dvector;

const double Rgas = 8314.33;

// constant parameters
const dvector sforParDefault = {1e6, 50e6, 0.6};
const dvector c2smParDefault = {1e6, 50e6, 0.3, 1e8, 100e6, 1.0};


class Model
{
protected:
  dvector parameters;
  const dvector parametersDefault;
  std::string name;

public:
  Model(const dvector &par, const dvector &parDef, const std::string &model):
    parameters(par), parametersDefault(parDef), name(model)
  {
    if (par.size() != parDef.size())
      throw 0;
  }
  virtual ~Model(){}
  size_t getNParameters(){return parametersDefault.size();}
  dvector const getParameters(){return parameters;}
  dvector const getParametersDefault(){return parametersDefault;}
  virtual void calcRate(const dvector &y, dvector &dydt, double t)=0;
  std::string const getName(){return name;}
};


class SFOR: public Model
{
public:
  SFOR(const dvector &par): Model(par, sforParDefault, "SFOR"){
      //std::cout << "Init SFOR " << std::endl;
      //name = "SFOR";
  };
  SFOR(): Model(sforParDefault, sforParDefault, "SFOR"){};
  ~SFOR(){}
  virtual void calcRate(const dvector &y, dvector &dydt, double t);
};

class C2SM: public Model
{
public:
  C2SM(const dvector &par): Model(par, c2smParDefault, "C2SM"){};
  C2SM(): Model(c2smParDefault, c2smParDefault, "C2SM"){};
  ~C2SM(){};
  virtual void calcRate(const dvector &y, dvector &dydt, double t);
};


#endif /* model_hpp */
