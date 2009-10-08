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
#ifndef KEYWORD_H
#define KEYWORD_H

#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>

#include <bpg-v2/Common/Unit.hpp>
#include <bpg-v2/Common/Location.hpp>
#include <bpg-v2/Common/Parameter.hpp>

using std::vector;
using std::string;
using namespace boost;
using std::cout;
using std::endl;

//using NonVirtual Interface (NVI)
template<typename T>
class Keyword{

  //  vector<Unit> unitVec_;

  virtual void Detect(const string& token){};
  virtual void Verify(){};
protected:
  vector<T> parameters_;
  bool set_;
  const string& name_;

public:

  explicit Keyword(const string& name): set_(false),name_(name){};

  void Process(const string& token){
    string str = token;
    erase_all(str," ");
    to_lower(str);
    Detect(str);
   }

  virtual void Print() {};
  const string& operator()(){ return name_;}
  const bool Match(const string& id) { return id == name_;}
  
  const vector<T>& GetTupleRef() const {
    if(!set_) throw std::runtime_error("Keyword " + name_ + " was not found");
    return parameters_;
  }

  const bool& Set() const { return set_;}
  const string& Name() const { return name_;}
  virtual ~Keyword(){};
};

//typedef vector<Keyword> KeywordVector;
#endif
