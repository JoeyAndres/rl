/* 
 * File:   TileCode_test.cpp
 * Author: jandres
 * 
 * Created on June 9, 2014, 9:17 AM
 */

#define BOOST_TEST_MODULE AI
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <iostream>

#include "TileCode.h"
#include "temp2/TileCode.h"

using namespace std;
using namespace AI;
using namespace AI::Algorithm;

BOOST_AUTO_TEST_SUITE(AI_TEST_SUITE)

BOOST_AUTO_TEST_CASE(TileCodeTest01) {
    vector<std::pair<AI::FLOAT, AI::FLOAT> > range(2);
    range[0] = std::pair<AI::FLOAT, AI::FLOAT>(0.0F, 6.0F);
    range[1] = std::pair<AI::FLOAT, AI::FLOAT>(0.0F, 6.0F);
    
    vector<AI::UINT> gridCount(2);
    gridCount[0] = 10;
    gridCount[1] = 10;
    
    TileCode<AI::FLOAT> tileCode(2,
                range,
                gridCount,
                8);
    
    vector<AI::FLOAT> featureSet(2);
    featureSet[0] = 0.1F;
    featureSet[1] = 0.1F;
    vector<AI::INT> tilings = tileCode.getFeatureVector(featureSet);
    for(AI::INT i : tilings){
        cout << i << " ";
    }
    cout << endl;    
    cout << endl;
    
    featureSet[0] = 5.99F;
    featureSet[1] = 5.99F;
    tilings = tileCode.getFeatureVector(featureSet);
    for(AI::INT i : tilings){
        cout << i << " ";
    }
    cout << endl;
}

BOOST_AUTO_TEST_CASE(TileCodeTest02CubeWorld) {
    vector<std::pair<AI::FLOAT, AI::FLOAT> > range(3);
    range[0] = std::pair<AI::FLOAT, AI::FLOAT>(0.0F, 6.0F);
    range[1] = std::pair<AI::FLOAT, AI::FLOAT>(0.0F, 6.0F);
    range[2] = std::pair<AI::FLOAT, AI::FLOAT>(0.0F, 6.0F);
    
    vector<AI::UINT> gridCount(3);
    gridCount[0] = 10;
    gridCount[1] = 10;
    gridCount[2] = 10;
    
    TileCode<AI::FLOAT> tileCode(3,
                range,
                gridCount,
                8);
    
    vector<AI::FLOAT> featureSet(3);
    featureSet[0] = 0.1F;
    featureSet[1] = 0.1F;
    featureSet[2] = 0.1F;
    vector<AI::INT> tilings = tileCode.getFeatureVector(featureSet);
    for(AI::INT i : tilings){
        cout << i << " ";
    }
    cout << endl;    
    cout << endl;
    
    featureSet[0] = 5.99F;
    featureSet[1] = 5.99F;
    featureSet[2] = 0.1F;
    tilings = tileCode.getFeatureVector(featureSet);
    for(AI::INT i : tilings){
        cout << i << " ";
    }
}

BOOST_AUTO_TEST_SUITE_END()