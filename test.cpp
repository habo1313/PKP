//
//  main.cpp
//  testing
//
//  Created by Michele Vascellari on 16.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include <iostream>
#include "model.hpp"
#include "cutest.h"
#include <cmath>
#include <string>

// prototypes
double rate_sfor(const dvector &p, const double T, const double y);
double arrhenius(const double A, const double E, const double T);
double rate_c2sm(const dvector &p, const double T, const double s);


// calc SFOR rate
double rate_sfor(const dvector &p, const double T, const double y)
{
    return arrhenius(p[0], p[1], T) * (p[2] - y);
}

double rate_c2sm(const dvector &p, const double T, const double s)
{
    double k1 = arrhenius(p[0], p[1], T);
    double k2 = arrhenius(p[3], p[4], T);
    return (p[2] * k1 + p[5] * k2) * s;
}


double arrhenius(const double A, const double E, const double T)
{
    return A * exp(-E/ Rgas /T);
}

void test_init_model()
{
    dvector p = {1e7, 50e6, 0.5};
    SFOR model(p);
    double T = 1000;
    TEST_CHECK_(model.getNParameters() == 3, "Test number of parameters");
    //double rate = p[0] * exp(-p[1]/Rgas/T) * p[2];
    
    double rate = rate_sfor(p, T, 0);
    
    dvector y = {0, T};
    dvector dydt(2);
    
    model.calcRate(0, y, dydt);
    TEST_CHECK_(dydt[0] == rate , "Test rate");
}

void test_model_select()
{
    dvector parameters = {1e7, 50e6, 0.5};
    Model *model = new SFOR(parameters);
    
    double T = 1000;
    double yv = 0.05;
    
    double rate = rate_sfor(parameters, T, yv);
    
    dvector y = {yv, T};
    dvector dydt(2);
    
    model->calcRate(0, y, dydt);
    TEST_CHECK_(dydt[0] == rate , "Test rate");
    delete model;
}

void test_c2sm()
{
    C2SM model;
    const dvector par = model.getParameters();
    const dvector y = {0, 1, 1000};
    dvector dydt(3);
    double T = y[2];
    double s = y[1];
    double rate = rate_c2sm(par, T, s);
    model.calcRate(0, y, dydt);
    TEST_CHECK_(dydt[0] == rate , "Test rate");
}

void test_parametersDefault()
{
  Model *model = new SFOR();
  TEST_CHECK_(model->getParameters() == model->getParametersDefault(), "Test par default");
  delete model;
}

void test_name()
{
  Model *model = new SFOR();
  //std::cout << model->getName() << std::endl;
  TEST_CHECK_(model->getName() == "SFOR", "Test name");
  delete model;
}

TEST_LIST = {
    { "init", test_init_model },
    { "model_select", test_model_select },
    {"parameters default", test_parametersDefault},
    {"c2sm", test_c2sm},
    {"name", test_name},
    { 0 }
};


/*
int main()
{
    dvector p = {1e7, 50e6, 0.5};
    SFOR model(p);
    std::cout << model.getNParameters() << std::endl;
}
*/
