//
//  model.cpp
//  testing
//
//  Created by Michele Vascellari on 20.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include "model.hpp"
#include <cmath>

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
