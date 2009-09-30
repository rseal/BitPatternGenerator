////////////////////////////////////////////////////////////////////////////////
///\file Units.h
///
/// This file defines and implements the Units structure, which is responsible
/// for parsing various given units and returning time of type double.
///
///Author: Ryan Seal
///Modified: 01/26/09
////////////////////////////////////////////////////////////////////////////////
#ifndef UNITCONVERT_H
#define UNITCONVERT_H

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <map>

using std::string;
using std::cout;
using std::endl;
using std::map;
using namespace boost;

///\brief Parses various defined time units and returns time with double precision
struct UnitConvert{

public:


  static const double Convert(const string& token){
    
    typedef map<string, float> UnitMap;
    UnitMap unitMap;
    
    unitMap["mhz" ] = 1e6;
    unitMap["khz" ] = 1e3;
    unitMap["hz"  ] = 1e0;
    unitMap["nsec"] = 1e-9;
    unitMap["usec"] = 1e-6;
    unitMap["msec"] = 1e-3;
    unitMap["sec" ] = 1e0;
    unitMap["km"  ] = (2.0/3.0)*1e-6;
    unitMap["m"   ] = (2.0/3.0)*1e-3;

    string str = token;

    double multiplier = double();

    erase_all(str," ");
    to_lower(str);

    //search map for token and assign if found
    UnitMap::iterator iter = unitMap.find(str);
    
    if(iter != unitMap.end())
      multiplier = iter->second;
    
    return multiplier;	
  }
  
};

#endif
