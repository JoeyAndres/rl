rl
===========

Modularized various Reinforcement Learning Algorithm library. 
See test/include and test/src for examples.

Note: This is currently only built for Linux systems. 
Some threading libraries are linux specific (even the latest c++ standard which is supposed to be platform independent).

# Compilation

Dependency:

* boost_1_55_0 or greater.  
* g++-4.9 or greater due to utilization of -std++14 features. I'm working on replicating these features to avoid such high requirement.
* armadillo
* cppunit

1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`