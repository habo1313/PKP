//
// Created by Michele Vascellari on 13.12.17.
//

#include "C2SM.hpp"
#include <cmath>

//using namespace std;

namespace pkp{

    void C2SM::calcRate(const std::vector<double> &y, std::vector<double> &dydt, double t, double T)
    {
        const std::vector<double> par = getParameters();
        //double T = y[2];
        //double v = y[0];

        // fraction of solid
        double s = y[1];
        double k1 = par[0] * exp(-par[1] / Rgas / T);
        double k2 = par[3] * exp(-par[4] / Rgas / T);

        // rates
        dydt[0] = (par[2] * k1 + par[5] * k2) * s;
        dydt[1] = -(k1 + k2) * s;
    }

    ModelFactoryRegister<C2SM> addC2SM("C2SM");

}
