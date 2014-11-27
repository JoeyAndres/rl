/**
 * LinearProgramming.cpp
 */

#include <cassert>

#include "LinearProgramming.h"

namespace AI{
namespace Algorithm{
namespace LP{

LinearProgramming::LinearProgramming(
    const std::vector<FLOAT>& objFunction, const std::vector<vector<FLOAT> >& constraints){  
  _simplexMatrix = _createSimplexMatrix(objFunction, constraints);
}

mat LinearProgramming::_createSimplexMatrix(
    const std::vector<FLOAT>& objFunction, const std::vector<vector<FLOAT> >& constraints){
  // Make sure all the constriants and objFunction is consistent.
  for(const vector<FLOAT>& constraint : constraints){
    assert(objFunction.size() == constraint.size()-1);
  }

  mat simplexMatrix(objFunction.size() + 2, 1 + constraints.size());

  vector<FLOAT> aux_vec;
  for(const vector<FLOAT>& constraint : constraints){
    for(const FLOAT& e : constraint){
      aux_vec.push_back(e);
    }
  }

  for(const FLOAT& e : objFunction){
    aux_vec.push_back(e);
  }

  cout << simplexMatrix << endl;

  return simplexMatrix;
}

}  // LP
}  // Algorithm
}  // LP
