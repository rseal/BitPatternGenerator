#ifndef KEYWORD_H
#define KEYWORD_H

#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include "Unit.hpp"
#include "Location.hpp"
#include "Parameter.hpp"

using std::vector;
using std::string;
using namespace boost;
using std::cout;
using std::endl;

//using NonVirtual Interface (NVI)
class Keyword{


  vector<Unit> unitVec_;

  virtual void Detect(const string& token){};
  virtual void Verify(){};
protected:
  ParameterVector parameters_;
  bool set_;
  string name_;

public:

  explicit Keyword(const string& name): set_(false),name_(name){};

  void Process(const string& token){
    string str = token;
    erase_all(str," ");
    to_lower(str);
    Detect(str);
    //Verify();
  }

  virtual void Print() {};
  const string& operator()(){ return name_;}
  const bool Match(const string& id) { return id == name_;}
  const ParameterVector& GetParameterRef() { return parameters_;}
  
  template<typename T>
  const T GetParameter(const string& id){
    ParameterVector::const_iterator iter = 
      std::find_if(parameters_.begin(), parameters_.end(), 
		   bind(&Parameter::id, _1) == id);
    if(iter == parameters_.end()) throw std::runtime_error("Parameter " + id + " could not be found");
    return any_cast<T>(iter->value);
  }

  virtual ~Keyword(){};
};

typedef vector<Keyword> KeywordVector;
#endif
