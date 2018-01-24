//
// Created by Michele Vascellari on 13.12.17.
//

#ifndef PKP_SFOR_HPP
#define PKP_SFOR_HPP

#include "model.hpp"
#include "ModelFactory.hpp"

namespace pkp{
    // SFOR
    const dvector sforParDefault = {1e6, 50e6, 0.6};
    const parVector sforParNames = {"A", "E", "y0"};
    const dvector sforInitState = {0.0}; // [vol]
    //
    //  Single First Order Reaction (SFOR) model class
    //
    class SFOR: public Model
    {
    public:
        SFOR(const dvector &par= sforParDefault);
        ~SFOR(){}
        virtual void calcRate(const std::vector<double> &y, std::vector<double> &dydt, double t, double T);
    };
}
#endif //PKP_SFOR_HPP
