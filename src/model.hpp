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

namespace pkp {

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
        // constructor
        Model(const dvector &par, const dvector &parDef, const std::string &model,
            const parVector parNames, const dvector istate);
        // distructor
        virtual ~Model(){}

        //
        size_t getNParameters() const {return parametersDefault.size();}
        // parameters
        void setParameters(const dvector & par);
        const dvector & getParameters() const {return parameters;}
        // default parameters
        const dvector & getParametersDefault() const {return parametersDefault;}
        std::string const getName(){return name;}
        // parameter names
        const parVector & getParametersNames() const {return parametersNames;}
        // init state
        const dvector & getInitState() const {return initState;}
        // print
        void const printParameters();
        friend std::ostream& operator<< (std::ostream& stream, const Model & t);

        // virtual methods
        virtual void calcRate(const dvector &y, dvector &dydt, double t, double T)=0;
    };

}//end namespace pkp

#endif /* model_hpp */
