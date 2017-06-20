//
//  runner.hpp
//  testing
//
//  Created by Michele Vascellari on 19.06.17.
//  Copyright © 2017 Michele Vascellari. All rights reserved.
//

#ifndef runner_hpp
#define runner_hpp

//#include <memory>
#include "model.hpp"

class Runner
{
protected:
    Model * model;
    enum models {sfor, c2sm};
    //std::unique_ptr<Model> model;
public:
    Runner(models modelType, dvector parameters)
    {
        switch (modelType)
        {
            case sfor:
	      model = new SFOR(parameters);
	      //model = std::make_unique<SFOR>(parameters);
            case c2sm:
	      model = new C2SM(parameters);
	      //model = std::make_unique<SFOR>(parameters);
        }
    }
    ~Runner()
    {//delete model;
      delete model;
    }
    void solve(dvector y0, double t0, double tEnd, double dt);
  //dvector 
    //std::unique_ptr<Model> getModel()
    //  {
    //    return model.get();
    //  }
};

#endif /* runner_hpp */
