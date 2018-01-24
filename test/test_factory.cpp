#include "model.hpp"
#include "SFOR.hpp"
#include "ModelFactory.hpp"
#include "ReactorFactory.hpp"

using namespace pkp;

int main(int argc, char* argv[])
{
    //ModelFactoryRegister<SFOR> add("SFOR");
    //SFOR sfor;
    dvector parameters = {1e6, 60e6, 0.1};
    for (auto it:parameters){
      std::cout << it << std::endl;
    }

    auto model = ModelFactory2::create("SFOR", parameters);
    model->printParameters();

    auto model1 = ModelFactory::create("C2SM");
    model1->printParameters();

    auto model2 = ModelFactory::create("SFOR", parameters);
    model2->printParameters();

    std::cout << *model << "\n";
    std::cout << *model1 << "\n";
    return 0;
}
