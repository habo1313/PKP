/*
 * Template class for reactor
 */

#ifndef reactort_hpp
#define reactort_hpp

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <boost/numeric/odeint.hpp>
#include <fstream>

#include "model.hpp"
#include "reactor.hpp"
#include "csv.hpp"

// include gtest for testing purpose
#include "gtest/gtest_prod.h"

namespace pkp{
    namespace pl = std::placeholders;
    using namespace boost::numeric::odeint;

    typedef runge_kutta_cash_karp54< dvector > error_stepper_type;
    typedef controlled_runge_kutta< error_stepper_type > controlled_stepper_type;


    template <class T>
    class ReactorT
    {
    protected:
        T model;  // devolatilization model
        std::vector<double> times;
        std::vector<dvector> states;
        bool isoThermal;

        //FRIEND_TEST(ReactorTest2, dydt);

    public:
        ReactorT();
        ReactorT(const dvector & parameters);
        //~ReactorT();

        void dydt(const dvector &y, dvector &dydt, double t);
        void dTdt(const dvector &y, dvector &dydt, double t);

        dvector getModelParameters();
        void setModelParameters(const dvector &parameters);

        void solve(double t, double temperature=1000, double dt=1e-4, bool verbose=false);
        //void solve(std::vector<std::vector<double>> points, double dt=1e-4,
        //    bool verbose=false);
        std::vector<double> getTimes(){return times;}
        std::vector<dvector> getStates(){return states;}
        void dump(const std::string &csv, std::string sep = ",");
        void printParameters();//{model.printParameters();}
    };


    template <class T>
    ReactorT<T>::ReactorT(): isoThermal(true)
    {
        // do nothing keep model initialized
        //std::cout << "Construct ReactorT()" << '\n';
    }

    template <class T>
    ReactorT<T>::ReactorT(const dvector & parameters): isoThermal(true)
    {
        //std::cout << "Construct ReactorT(parameters)" << '\n';
        //model.setParameters(parameters);
        setModelParameters(parameters);
    }

    template <class T>
    dvector ReactorT<T>::getModelParameters()
    {
        return model.getParameters();
    }

    template<class T>
    void ReactorT<T>::printParameters()
    {
        model.printParameters();
    }

    template<class T>
    void ReactorT<T>::dydt(const dvector &y, dvector &dydt, double t)
    {
        //size_t n = dydt.size();
        double temperature = y.back();
        model.calcRate(y, dydt, t, temperature);
        dTdt(y, dydt, t);
    }

    template<class T>
    void ReactorT<T>::dTdt(const dvector &y, dvector &dydt, double t)
    {
        if (isoThermal)
            dydt[y.size()-1] = 0.0;
            //dydt.emplace(dydt.end()-1, 0.0);
    }

    template<class T>
    void ReactorT<T>::setModelParameters(const dvector &parameters)
    {
        model.setParameters(parameters);
    }

    template <class T>
    void ReactorT<T>::solve(
        double t,
        double temperature,
        double dt,
        bool verbose)
    {
        isoThermal = true;
        dvector y0 = model.getInitState();
        y0.push_back(temperature);
        dvector dydt(y0.size());

        auto fct = std::bind(&ReactorT::dydt, this, pl::_1 , pl::_2 , pl::_3);

        //double t0 = 0.0;

        dvector tsaved;
        std::vector<dvector> ysaved;

        //double last=1;

        controlled_stepper_type stepper = make_controlled<error_stepper_type>(1.0e-10 , 1.0e-6 );
        //
        std::for_each(
            make_adaptive_time_iterator_begin(stepper, fct, y0, 0.0, t, dt),
            make_adaptive_time_iterator_end(stepper, fct, y0),
            [&tsaved, &ysaved, verbose](std::pair< const dvector & , const double & > x )
            {
                if (verbose)
                    std::cout << x.second << " " << x.first[0] << " " << x.first[1]  << "\n";
                tsaved.push_back(x.second);
                ysaved.push_back(x.first);
              });

        times = tsaved;
        states = ysaved;
    }

    template <class T>
    void ReactorT<T>::dump(const std::string &csv, std::string sep)
    {
        /// Dump results in a file
        csvfile file(csv);
        file << "time" ;
        char buffer[2];
        for (int j=0; j< states[0].size()-1; ++j)
        {
            std::sprintf (buffer, "y%d", j);
            file << std::string(buffer);
        }
        file << "Temperature" << endrow;

        for (int i=0; i < times.size(); ++i)
        {
            file << times[i];
            for (double &status: states[i])
                file << status;
            file << endrow;
        }
    }
} // end namespace pkp
#endif /* model_hpp */
