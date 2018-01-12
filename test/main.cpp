//
//  main.cpp
//  testing
//
//  Created by Michele Vascellari on 16.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include <iostream>

// #include <cmath>
// #include <string>
// #include <boost/numeric/odeint.hpp>

// yaml reader
#include <yaml-cpp/yaml.h>

// #include <functional>
#include "model.hpp"
#include "SFOR.hpp"
#include "C2SM.hpp"
#include "reactort.hpp"
#include <string.h>

template <typename T> void runReactor(ReactorT<T> reactor, YAML::Node config);

int main(int argc, char **argv)
{
    //dvector parameters = {1e6, 60e6, 0.1};
    std::cout << "Main program" << std::endl;

    //YAML::Node config = YAML::LoadFile(argv[1]);
    std::cout << "Read YAML file";

    YAML::Node config = YAML::LoadFile(argv[1]);

    std::cout << "...done" << '\n';
    // read model and parameters
    std::string modelName = config["model"]["type"].as<std::string>();
    //dvector parameters = config["model"]["parameters"].as<dvector>();

    // define reactor object
    if(modelName==std::string("SFOR"))
    {
        //model = Reactor::sfor;
        std::cout << "Create reactor with SFOR" << '\n';
        ReactorT<SFOR> reactor;
        runReactor(reactor, config);
    }
    else if(modelName==std::string("C2SM"))
    {
        //model = Reactor::c2sm;
        std::cout << "Create reactor with C2SM" << '\n';
        ReactorT<C2SM> reactor;
        runReactor(reactor, config);
    }
    else
    {
        std::cout << "Model " << argv[1] << " not defined" << std::endl;
        return -1;
    }

    return 0;
}

template <typename T> void runReactor(ReactorT<T> reactor, YAML::Node config)
{
    dvector parameters = config["model"]["parameters"].as<dvector>();
    reactor.setModelParameters(parameters);
    reactor.printParameters();

    // define parameters
    //dvector y = {0, 1000};
    double t = config["operating_conditions"]["t"].as<double>();
    double temperature = config["operating_conditions"]["T"].as<double>();
    //double t0 = 0.0;
    double dt = config["operating_conditions"]["dt"].as<double>();

    // solve
    std::cout << "Solve" << std::endl;
    reactor.solve(t, temperature, dt, false);

    // get solutions
    //std::vector<double> times = reactor.getTimes();
    //std::vector<dvector> states = reactor.getStates();
    reactor.dump("solution.csv");
}