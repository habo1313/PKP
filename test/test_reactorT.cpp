// google test
#include "gtest/gtest.h"

#include "reactort.hpp"
#include "SFOR.hpp"
#include "model.hpp"

#include <iostream>

const dvector parameters = {1e7, 50e6, 0.5};

class ReactorTest: public ::testing::Test
{
protected:
    ReactorT<SFOR> reactor;

    virtual void SetUp()
    {
        //
        //std::cout << "Setup" << '\n';
    }

    virtual void TearDown()
    {
      //delete model;
      //std::cout << "TearDown" << '\n';
    }
};


// test if the reactor is constructed
TEST_F(ReactorTest, constructor)
{
    EXPECT_EQ(3, reactor.getModelParameters().size());
}

// test if the new model parameters are setted
TEST_F(ReactorTest, setModelParameters)
{
    //EXPECT_EQ(3, model->getNParameters());
    //EXPECT_EQ(sforParNames, model->getParametersNames());
    //EXPECT_EQ(3, )
    //std::cout << "Test" << '\n';
    reactor.setModelParameters(parameters);
    EXPECT_EQ(parameters, reactor.getModelParameters());
}

TEST_F(ReactorTest, solve)
{

  double tEnd = 0.05;
  double dt = 1e-6;
  double temperature = 1000;
  reactor.solve(tEnd, temperature, dt, true);
  reactor.dump("test.csv");
  std::vector<double> times = reactor.getTimes();
  std::vector<dvector> states = reactor.getStates();
  EXPECT_EQ(times.size(), states.size());
  EXPECT_EQ(times.back(), tEnd);
  //EXPECT_EQ(states[0].size(), sforInitState.size()+1);
}

// void printDvector(const dvector & v)
// {
//     for (auto it: v)
//     {
//          std::cout << it << " ";
//     }
//     std::cout << '\n';
// }

// int main(int argc, char const *argv[]) {
//     dvector parameters = {1e7, 50e6, 0.5};
//     ReactorT<SFOR> reactor(parameters);
//     // auto param = reactor.getModelParameters();
//     // for (auto it: param)
//     // {
//     //     std::cout << it << " ";
//     // }
//     // std::cout << "\n";
//     //reactor.printParameters();
//
//     //dvector y = {0, 700.0};
//     //dvector y = {0};
//     //dvector dydt(2);
//     //double t=0;
//
//     //reactor.dydt(y, dydt, t);
//     //printDvector(dydt);
//     reactor.solve(0.1, 1000.0, 1e-5, true);
//     reactor.dump("solution.csv");
//     return 0;
// }


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
