#ifndef KEYWORD_H
#define KEYWORD_H

#include <string>
#include <vector>

#include "Unit.hpp"
#include "Location.hpp"

using std::vector;
using std::string;

struct Keyword{

  typedef vector<Unit> UnitVector;
  string name_;
  string label_;
  bool set_;
  vector<Unit> unitVec_;
public:

  Keyword(const string& name):
    name_(name),set_(true){};

  void Set(const bool& state) {set_ = state;}
  const bool& Set() {return set_;}
  
  const string& Name() {return name_;}
  void Name(const string& name){name_ = name;}

  const string& Label() {return label_;}
  void Label(const string& label) {label_ = label;}

  UnitVector& UnitVectorRef() {return unitVec_;}

  const bool operator()(const string& id){
    return id == name_;
  }
    
};


#endif
