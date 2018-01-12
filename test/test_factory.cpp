#include "model.hpp"
#include "SFOR.hpp"
#include "ModelFactory.hpp"


int main(int argc, char* argv[])
{
    //ModelFactoryRegister<SFOR> add("SFOR");
    //SFOR sfor;
    dvector parameters = {1e6, 60e6, 0.1};
    Model *model = ModelFactory::instantiate("SFOR");
    model->setParameters(parameters);
    //model->printParameters();
    std::cout << *model << "\n";
    return 0;
}
