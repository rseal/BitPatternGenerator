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
#ifndef ARG_H
#define ARG_H

#include <bpg-v2/clp/Option.hpp>
#include <iostream>
#include <vector>

namespace CLP{
    
    class Exception{
    public:
	virtual void PrintError() { 
	  std::cerr << "CLP Exception thrown" << std::endl;
	}
    };

    class NoArg: public Exception{
	std::string arg_;
    public:
	explicit NoArg(const std::string& arg): arg_(arg){}
	virtual void PrintError() { 
	    std::cerr << "CLP Exeption - argument " << arg_ << " not found" << std::endl;
	}
    };
}

class Arg: public Option{
    int numItems_;
   std::vector<std::string> list_;

public:
    Arg(const std::string& name, const std::string& helpDesc, const int& numItems, 
	const bool& required): Option(name,helpDesc,required), 
			       numItems_(numItems), list_(){}

    const int NumItems() { return numItems_;}


    const std::string Value(const int& index) {
	if(list_.empty() || (required_ && (index > list_.size())))
	    throw CLP::NoArg(name_);
	return list_.at(index);
    }

    void Add(std::vector<std::string> list) { list_ = list; Set(true);}

};

#endif
