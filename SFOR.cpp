//
// Created by Michele Vascellari on 13.12.17.
//

#include "SFOR.hpp"
#include <cmath>

void SFOR::calcRate(const std::vector<double> &y, std::vector<double> &dydt, double t, double T)
{
    double vol = y[0];
    //double T = y[1];
    std::vector<double> par = getParameters();
    dydt[0] = par[0] * exp(-par[1]/8314.33/T) * (par[2] - vol);
}