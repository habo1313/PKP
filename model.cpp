//
//  model.cpp
//  testing
//
//  Created by Michele Vascellari on 20.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include "model.hpp"
#include <cmath>


void SFOR::calcRate(const dvector &y, dvector &dydt, double t)
{
    double vol = y[0];
    double T = y[1];
    dvector par = getParameters();
    dydt[0] = par[0] * exp(-par[1]/8314.33/T) * (par[2] - vol);
    dydt[1] = 0.0;
}

void C2SM::calcRate(const dvector &y, dvector &dydt, double t)
{
    const dvector par = getParameters();
    double T = y[2];
    //double v = y[0];
    
    // fraction of solid
    double s = y[1];
    double k1 = par[0] * exp(-par[1]/Rgas/T);
    double k2 = par[3] * exp(-par[4]/Rgas/T);
    
    // rates
    dydt[0] = (par[2] * k1 + par[5] * k2) * s;
    dydt[1] = -(k1 + k2) * s;
}
