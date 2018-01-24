//
//  main.cpp
//  testing
//
//  Created by Michele Vascellari on 16.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>

// google test
#include "gtest/gtest.h"

#include "model.hpp"
#include "reactor.hpp"

//#define private public


//using namespace test;

namespace pkp {

    class SFORTest : public ::testing::Test
    {
    protected:
      Model *model;
      dvector parameters = {1e7, 50e6, 0.5};

      virtual void SetUp()
      {
        model = new SFOR(parameters);
      }

      virtual void TearDown()
      {
        delete model;
      }
    };

    class C2SMTest : public ::testing::Test
    {
    protected:
      Model *model;

      virtual void SetUp()
      {
        model = new C2SM;
      }

      virtual void TearDown()
      {
        delete model;
      }
    };

    // prototypes
    double rate_sfor(const dvector &p, const double T, const double y);
    double arrhenius(const double A, const double E, const double T);
    double rate_c2sm(const dvector &p, const double T, const double s);


    // calc SFOR rate
    double rate_sfor(const dvector &p, const double T, const double y)
    {
        return arrhenius(p[0], p[1], T) * (p[2] - y);
    }

    double rate_c2sm(const dvector &p, const double T, const double s)
    {
        double k1 = arrhenius(p[0], p[1], T);
        double k2 = arrhenius(p[3], p[4], T);
        return (p[2] * k1 + p[5] * k2) * s;
    }


    double arrhenius(const double A, const double E, const double T)
    {
        return A * exp(-E/ Rgas /T);
    }


    TEST_F(SFORTest, getNParameters)
    {
      EXPECT_EQ(3, model->getNParameters());
      std::vector<std::string> par = {"A", "E", "y0"};
      EXPECT_EQ(par, model->getParametersNames());
    }

    TEST_F(SFORTest, setParameters)
    {
        dvector newParameters = {5e7, 40e6, 0.6};
        model->setParameters(newParameters);
        EXPECT_EQ(newParameters, model->getParameters());
    }

    TEST_F(SFORTest, getParameters)
    {
      EXPECT_EQ(parameters, model->getParameters());
    }

    TEST_F(SFORTest, rate)
    {
      double T = 1000;
      double v = 0.0;
      dvector y = {v, T};
      dvector dydt(2);
      model->calcRate(y, dydt, 0.0, T);
      EXPECT_EQ(dydt[0], rate_sfor(parameters, T, v));
    }

    TEST_F(SFORTest, getName)
    {
        EXPECT_EQ(model->getName(), "SFOR");
    }

    TEST_F(C2SMTest, rate)
    {
      double T = 1000;
      double v = 0.0;
      double s = 1.0;
      dvector y = {v, s, T};
      dvector dydt(3);
      model->calcRate(y, dydt, 0.0, T);
      EXPECT_EQ(dydt[0], rate_c2sm(model->getParameters(), T, s));
    }

    class ReactorTest : public ::testing::Test
    {
    protected:
      Reactor *reactor;
      dvector parameters = {1e7, 50e6, 0.5};

      virtual void SetUp()
      {
        reactor = new Reactor("SFOR", parameters);
      }

      virtual void TearDown()
      {
        delete reactor;
      }
    };

    TEST_F(ReactorTest, parameters)
    {
      EXPECT_EQ(parameters, reactor->getParameters());
    }


    TEST_F(ReactorTest, solve)
    {
      //dvector y0 = {0.0, 1000};
      //double t0 = 0;
      double tEnd = 0.05;
      double T = 1000;
      std::vector<dvector> oc {{0, T}, {tEnd, T}};
      reactor->setOperatingConditions(oc);
      double dt = 1e-6;
      reactor->solve(dt, false);
      reactor->dump("test.csv");
      std::vector<double> times = reactor->getTimes();
      std::vector<dvector> states = reactor->getStates();
      EXPECT_EQ(times.size(), states.size());
      EXPECT_EQ(states[0].size(), 2);
    }

    TEST_F(ReactorTest, setParameters)
    {
        dvector parameters = {1e7, 55e6, 0.5};
        reactor->setParameters(parameters);
        EXPECT_EQ(parameters, reactor->getParameters());
    }

    TEST_F(ReactorTest, operatingConditions)
    {
        auto oc0 = reactor->getOperatingConditions();
        EXPECT_EQ(oc0.size(), 0);
        std::vector<dvector> oc = {{0, 300}, {0.1, 1000}, {0.2, 1000}};
        reactor->setOperatingConditions(oc);
        EXPECT_EQ(reactor->getOperatingConditions(), oc);
        auto oc1 = reactor->getOperatingConditions();
        oc1.pop_back();
        EXPECT_NE(reactor->getOperatingConditions(), oc1);
    }

    TEST_F(ReactorTest, dTdt)
    {
        std::vector<dvector> oc = {{0, 300}, {0.1, 1000}, {0.2, 1000}};
        reactor->setOperatingConditions(oc);
        dvector y = {0, 450.};
        dvector dydt(2);
        double t0 = 0.05;
        reactor->dTdt(y, dydt, t0);
        size_t index = 0;
        double dTdt = (oc[index+1][1] - oc[index][1])/(oc[index+1][0]-oc[index][0]);
        EXPECT_EQ(dTdt, dydt.back());
    }


    TEST(ReactorTest2, dydt)
    {
        Reactor reactor("SFOR", {1e7, 50e6, 0.5});
        dvector parameters = reactor.getParameters();
        std::vector<dvector> oc {{0, 1000}, {0.1, 1000}};
        reactor.setOperatingConditions(oc);
        double T = 1000;
        dvector y = {0.0, T};
        dvector dydt(y.size());
        double rate = rate_sfor(parameters, T, 0);

        // check model rate
        double t=0;
        reactor.model->calcRate(y, dydt, t, T);
        EXPECT_EQ(rate, dydt[0]);

        //std::cout << "calc dydt" << '\n';
        reactor.dydt(y, dydt, t);
        EXPECT_EQ(rate, dydt[0]);
    }


    TEST(PushBackTest, pointer)
    {
      std::vector<dvector> state = {{0.0, 0.0}};
      std::vector<double> t = {0.0};
      push_back_state_and_time *push = new push_back_state_and_time(state, t);
      dvector state1 = {1.0, 1.0};
      double t1 = 1;
      (*push)(state1, t1);
      EXPECT_EQ(t1, push->m_times[1]);
      EXPECT_EQ(push->m_states[1], state1);
    }


    TEST(PushBackTest, parameters)
    {
      std::vector<dvector> state = {{0.0, 0.0}};
      std::vector<double> t = {0.0};

      push_back_state_and_time push(state, t);

      double t1 = 1;
      dvector state1 = {1.0, 1.0};
      push(state1, t1);
      EXPECT_EQ(push.m_states[1], state1);
      EXPECT_EQ(push.m_times[1], t1);
      //std::cout << "state[0]=" << push->m_states[0][0] << std::endl;

      //delete push;
    }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
