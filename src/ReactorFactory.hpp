//
//  ReactorFactory.hpp
//  PKP
//
//  Created by <author> on 12/01/2018.
// TODO remove not necessary anymore
//
//

#ifndef ReactorFactory_hpp
#define ReactorFactory_hpp

#include <unordered_map>
#include <functional>
#include <memory>
#include "reactort.hpp"
#include "model.hpp"
#include "SFOR.hpp"
#include "C2SM.hpp"

namespace pkp{
    struct ModelFactory2{
        static std::shared_ptr<Model> create(const std::string &model_type, const dvector &parameters){
            typedef std::unordered_map<std::string,std::function<std::shared_ptr<Model>(const dvector &)>> registry_map;
            static registry_map mapping {
                    {"SFOR", [](const dvector &p){return std::make_shared<SFOR>(p);}},
                    {"C2SM", [](const dvector &p){return std::make_shared<C2SM>(p);}},
                };
            auto it = mapping.find(model_type);
            if (it != mapping.end()){
                return it->second(parameters);
            }
            else
                return nullptr;

        }
    };
} // end namespace pkp

#endif /* ReactorFactory_hpp */
