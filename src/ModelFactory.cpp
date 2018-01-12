//
//  ModelFactory.cpp
//  PKP
//
//  Created by <author> on 03/01/2018.
//
//
#include "ModelFactory.hpp"
namespace pkp{
    //ModelFactory::ModelFactory()  {}
    //ModelFactory::~ModelFactory() {}

    std::shared_ptr<Model> ModelFactory::instantiate(const std::string& name)
    {
        auto it = ModelFactory::registry().find(name);
        //return it == ModelFactory::registry().end() ? nullptr : (it->second)();
        if (it != ModelFactory::registry().end())
            return it->second();
        else
            return nullptr;
    }

    // TODO fix it
    // std::shared_ptr<Model> ModelFactory::instantiate(const std::string& name, const dvector &par)
    // {
    //     auto it = ModelFactory::registry().find(name);
    //     return it == ModelFactory::registry().end() ? nullptr : (it->second)();
    // }

    ModelFactory::registry_map & ModelFactory::registry()
    {
        static registry_map impl;
        return impl;
    }
}
