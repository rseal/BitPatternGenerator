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

//using NonVirtual Interface (NVI)
template<typename T>
class Keyword{

   virtual void Detect(const std::string& token){};
   virtual void Verify(){};
   protected:
   std::vector<T> parameters_;
   bool set_;
   const std::string name_;

   public:

   explicit Keyword(const std::string& name): set_(false),name_(name){};

   void Process(const std::string& token){
      //set_=false;
      std::string str = token;
      boost::erase_all(str," ");
      boost::to_lower(str);
      Detect(str);
   }

   virtual void Print() {};

   const std::vector<T>& GetTupleRef() {
      if(!set_) throw std::runtime_error("Keyword " + name_ + " was not found");
      return parameters_;
   }

   const bool& Set() const { return set_;}
   virtual ~Keyword(){};
};

#endif
