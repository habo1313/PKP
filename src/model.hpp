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
typedef std::vector<std::string> parVector;

const double Rgas = 8314.33;

class Model
{
protected:
  dvector parameters;
  const dvector parametersDefault;
  std::string name;
  parVector parametersNames;
  dvector initState;

public:
  Model(const dvector &par, const dvector &parDef, const std::string &model,
  const parVector parNames, const dvector istate):
    parameters(par),
    parametersDefault(parDef),
    name(model),
    parametersNames(parNames),
    initState(istate)
  {
    if (par.size() != parDef.size())
      throw 0;
  }
  virtual ~Model(){}
  size_t getNParameters(){return parametersDefault.size();}
  dvector const getParameters(){return parameters;}
  dvector const getParametersDefault(){return parametersDefault;}
  virtual void calcRate(const dvector &y, dvector &dydt, double t, double T)=0;
  std::string const getName(){return name;}
  parVector const getParametersNames(){return parametersNames;}
  void const printParameters();
  dvector const getInitState(){return initState;}
  void setParameters(const dvector & par);
  friend std::ostream& operator<< (std::ostream& stream, const Model & t);
};


#endif /* model_hpp */
