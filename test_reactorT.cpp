// google test
#include "gtest/gtest.h"

#include "reactort.hpp"
#include "SFOR.hpp"
#include "model.hpp"

#include <iostream>


// class ReactorTest: public ::testing::Test
// {
// protected:
//     ReactorT<SFOR> reactor;
//
//     virtual void SetUp()
//     {
//         //
//         std::cout << "Setup" << '\n';
//     }
//
//     virtual void TearDown()
//     {
//       //delete model;
//       std::cout << "TearDown" << '\n';
//     }
// };
//
//
// TEST_F(ReactorTest, constructor)
// {
//     //EXPECT_EQ(3, model->getNParameters());
//     //EXPECT_EQ(sforParNames, model->getParametersNames());
//     //EXPECT_EQ(3, )
//     std::cout << "Test" << '\n';
// }

void printDvector(const dvector & v)
{
    for (auto it: v)
    {
         std::cout << it << " ";
    }
    std::cout << '\n';
}

int main(int argc, char const *argv[]) {
    dvector parameters = {1e7, 50e6, 0.5};
    ReactorT<SFOR> reactor(parameters);
    // auto param = reactor.getModelParameters();
    // for (auto it: param)
    // {
    //     std::cout << it << " ";
    // }
    // std::cout << "\n";
    //reactor.printParameters();

    //dvector y = {0, 700.0};
    //dvector y = {0};
    //dvector dydt(2);
    //double t=0;

    //reactor.dydt(y, dydt, t);
    //printDvector(dydt);
    reactor.solve(0.1, 1000.0, 1e-5, true);
    return 0;
}
