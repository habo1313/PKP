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
#include "model.hpp"


class ModelFactory {
private:
public:
    //ModelFactory();
    //~ModelFactory();
    typedef std::unordered_map<std::string, std::function<Model*()>> registry_map;
    //typedef std::unordered_map<std::string, std::function<Model*(const dvector &par)>> registry_map_par;
    static Model * instantiate(const std::string& name);
    static Model * instantiate(const std::string& name, const dvector &par);
    static registry_map & registry();
    //static registry_map_par & registry_par();
};

template<typename T> struct ModelFactoryRegister
{
    ModelFactoryRegister(std::string name)
    {
        ModelFactory::registry()[name] = []() {return new T;};
        std::cout << "Registering Model class '" << name << "'\n";
    }
};

#endif /* ModelFactory_hpp */
