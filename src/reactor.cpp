#include "reactor.hpp"
#include "model.hpp"
#include <iostream>
#include <functional>
#include <boost/numeric/odeint.hpp>
#include <fstream>

#include "csv.hpp"

namespace pkp{

    namespace pl = std::placeholders;

    using namespace boost::numeric::odeint;

    typedef runge_kutta_cash_karp54< dvector > error_stepper_type;
    typedef controlled_runge_kutta< error_stepper_type > controlled_stepper_type;

    void printv(const dvector &y, const double t)
    {
      std::cout << "t=" << t << " y=" << y[0] << std::endl;
    }

    Reactor::Reactor(const std::string& modelType, dvector parameters):
        model(ModelFactory2::create(modelType, parameters)){}

    Reactor::~Reactor(){}

    void Reactor::solve(double t, double T, double dt, bool verbose)
    {
        //
        //double T = 1000;
        isoThermal = true; // set isotherm to
        dvector y0 = model->getInitState();
        y0.push_back(T);
        dvector dydt(y0.size());

        // define integral function from model
        //auto fct = std::bind(&Model::calcRate, model, pl::_1 , pl::_2 , pl::_3);
        auto fct = std::bind(&Reactor::dydt, this, pl::_1 , pl::_2 , pl::_3);

        // double t0 = 0.0;

        //std::vector<double> ts = {t0};
        //std::vector<dvector> xs = {y0};

        // initialize push structure
        //push_back_state_and_time solution(xs, ts);

        // integrate
        //boost::numeric::odeint::integrate(fct, y0 , t0 , t,  dt, solution);

        dvector tsaved;
        std::vector<dvector> ysaved;

        // double last=1;
        controlled_stepper_type stepper = make_controlled< error_stepper_type >(1.0e-10 , 1.0e-6 );
        std::for_each(
            make_adaptive_time_iterator_begin(stepper, fct, y0, 0.0, t, dt),
            make_adaptive_time_iterator_end(stepper, fct, y0),
            [&tsaved, &ysaved, verbose]( std::pair< const dvector & , const double & > x )
            {
                if (verbose)
                    std::cout << x.second << " " << x.first[0] << " " << x.first[1]  << "\n";
                tsaved.push_back(x.second);
                ysaved.push_back(x.first);
            });
        // store solutions
        states = ysaved;
        times = tsaved;
    }

    void solve(std::vector<std::vector<double>> points, double dt, bool verbose)
    {
        //
    }

    void Reactor::dydt(const dvector &y, dvector &dydt, double t)
    {
        //size_t n = dydt.size();
        //double T = dydt.back();
        //double T = y[n-1];
        double T = y.back();
        model->calcRate(y, dydt, t, T);
        //dydt[n-1] = 0.0; // const temperature
        dTdt(y, dydt, t);
    }


    void Reactor::dump(const std::string &csv, std::string sep)
    {
        // std::ofstream file(csv);
        // for (int i=0; i < times.size(); ++i)
        //   {
        //     file << times[i];
        //     for (int j=0; j < states[i].size(); ++j)
        // 	file << sep << states[i][j];
        //     file << std::endl;
        //   }
        // file.close();
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
            for (int j=0; j < states[i].size(); ++j)
            {
                file << states[i][j];
            }
            file << endrow;
        }
    }

    void Reactor::dTdt(const dvector &y, dvector &dydt, double t)
    {
        //
        if (isoThermal)
            dydt[dydt.size()-1] = 0.0;
        else
        {
            //
        }
    }
}
