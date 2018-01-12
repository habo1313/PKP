//
//  model.cpp
//  testing
//
//  Created by Michele Vascellari on 20.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include "model.hpp"
#include <cmath>
#include <stdio.h>

void const Model::printParameters()
{
  std::cout << "Model:" << name  << '\n';
  for (size_t i = 0; i < parametersNames.size(); i++) {
    std::cout << parametersNames[i] << "\t" << parameters[i] <<  '\n';
  }
}

void Model::setParameters(const dvector &par)
{
    if (par.size() != parametersDefault.size())
        throw 0;
    parameters = par;
}

std::ostream& operator<< (std::ostream& stream, const Model & t)
{
    stream << "Model:" << t.name << std::endl;
    std::string message = "[";
    //stream << "[";
    for (size_t i = 0; i < t.parametersNames.size(); i++)
    {
        //stream << t.parametersNames[i] << "\t" << t.parameters[i] <<  std::endl;
        //stream << t.parametersNames[i] << "=" << t.parameters[i] << ", ";
        //std::string m = t.parametersNames[i] + " = " + t.parameters[i] + ", ";
        message += t.parametersNames[i];
        message += "=";
        //message += std::to_string(t.parameters[i]);

        std::string s(16, '\0');
        std::string format = t.parameters[i] < 1e5 ? "%5.3f" : "%5.3e";
        //char fmt[10];
        //strcpy(format, fmt);
        auto written = std::snprintf(&s[0], s.size(), format.c_str(),
            t.parameters[i]);
        s.resize(written);
        message += s + ", ";
    }
    message = message.substr(0, message.length()-2);
    message += "]";
    stream << message;
    return stream;
}
