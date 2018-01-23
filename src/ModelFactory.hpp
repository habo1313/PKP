//
//  ModelFactory.hpp
//  PKP
//
//  Created by <author> on 03/01/2018.
//
//

#ifndef ModelFactory_hpp
#define ModelFactory_hpp

#include <unordered_map>
#include <functional>
#include <memory>
#include "model.hpp"
#include "SFOR.hpp"
#include "C2SM.hpp"

namespace pkp {
    class ModelFactory {
    private:
    public:
        typedef std::unordered_map<std::string, std::function<std::shared_ptr<Model>()>> registry_map;
        typedef std::unordered_map<std::string, std::function<std::shared_ptr<Model>(const dvector &)>> registry_map_par;
        static std::shared_ptr<Model> create(const std::string& name);
        static std::shared_ptr<Model> create(const std::string& name, const dvector& par);
        static registry_map & registry();
        static registry_map_par & registry_par();
    };

    template<typename T> struct ModelFactoryRegister
    {
        ModelFactoryRegister(std::string name)
        {
            ModelFactory::registry()[name] = []() {return std::make_shared<T>();};
            ModelFactory::registry_par()[name] = [](const dvector& par) {return std::make_shared<T>(par);};
            std::cout << "Registering Model class '" << name << "'\n";
        }
    };
}

#endif /* ModelFactory_hpp */
