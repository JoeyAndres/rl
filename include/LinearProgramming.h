/**
 * LinearProgramming.h
 */
#pragma once

#include "GlobalHeader.h"

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

namespace AI{
namespace Algorithm{
namespace LP{

class LinearProgramming{
 public:
  LinearProgramming(const std::vector<FLOAT>& objFunction,
                    const std::vector<vector<FLOAT> >& constraints);

 protected:
  mat _createSimplexMatrix(
      const std::vector<FLOAT>& objFunction,
      const std::vector<vector<FLOAT> >& constraints);
  
 protected:
  mat _simplexMatrix;  // !< arm table.
};

}  // LP
}  // Algorithm
}  // LP
