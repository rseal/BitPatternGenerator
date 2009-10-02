#ifndef PARAMETER_H
#define PARAMETER_H

#include <boost/any.hpp>
#include <vector>


struct Parameter{

  string id;
  boost::any value;

  Parameter();
  Parameter(const string& id_, const boost::any& value_):
    id(id_), value(value_){};

  const string& operator()(){return id;}
};

typedef std::vector<Parameter> ParameterVector;

namespace param{
  const Parameter& Find(const ParameterVector& pv, const string& id){
    return *std::find_if(pv.begin(),pv.end(), bind(&Parameter::id, _1) == id);
  }
};




#endif
