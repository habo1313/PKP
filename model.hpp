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

// SFOR
const dvector sforParDefault = {1e6, 50e6, 0.6};
const parVector sforParNames = {"A", "E", "y0"};
const dvector sforInitState = {0.0}; // [vol]

// C2SM
const dvector c2smParDefault = {1e6, 50e6, 0.3, 1e8, 100e6, 1.0};
const parVector c2smParNames = {"A1", "E1", "y1", "A2", "E2", "y2"};
const dvector c2smInitState = {0.0, 1.0}; // [vol, solid]

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
    parameters(par), parametersDefault(parDef), name(model),
    parametersNames(parNames), initState(istate)
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
};

//
//  Single First Order Reaction (SFOR) model class
//
class SFOR: public Model
{
public:
  SFOR(const dvector &par): Model(par, sforParDefault, "SFOR", sforParNames,
    sforInitState){}
  SFOR(): Model(sforParDefault, sforParDefault, "SFOR", sforParNames,
    sforInitState){};
  ~SFOR(){}
  virtual void calcRate(const dvector &y, dvector &dydt, double t, double T);
};

//
// Competing 2 Step Model (C2SM) class
//
class C2SM: public Model
{
public:
  C2SM(const dvector &par): Model(par, c2smParDefault, "C2SM", c2smParNames,
    c2smInitState){};
  C2SM(): Model(c2smParDefault, c2smParDefault, "C2SM", c2smParNames,
    c2smInitState){};
  ~C2SM(){};
  virtual void calcRate(const dvector &y, dvector &dydt, double t, double T);
};


#endif /* model_hpp */
