// Copyright (c) 2009 Ryan Seal <rlseal -at- gmail.com>
//
// This file is part of Bit Pattern Generator (BPG) Software.
//
// BPG is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//  
// BPG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BPG.  If not, see <http://www.gnu.org/licenses/>.
#ifndef PARAMETER_H
#define PARAMETER_H

#include <boost/any.hpp>
#include <vector>
#include <functional>
#include <algorithm>

struct Parameter{

  std::string id;
  boost::any value;

  Parameter();
  Parameter(const std::string& id_, const boost::any& value_):
    id(id_), value(value_){};

  const bool operator()(const Parameter& p){return p.id==id;}
};

typedef std::vector<Parameter> ParameterVector;

namespace param{

  struct Exists{
    const std::string& value_;

    Exists(const std::string& value): value_(value){}

    const bool operator()(const Parameter& p){
      return value_ == p.id;
    }
  };

  static const Parameter& FindParameter(const std::vector<Parameter>& pv, const std::string& id){
    ParameterVector::const_iterator iter = find_if( pv.begin(),
					      pv.end(), 
					      Exists(id)
					      );
    
    if(iter == pv.end()) throw std::runtime_error("Parameter " + id + " could not be found");
    return *iter;
  };
}




#endif
