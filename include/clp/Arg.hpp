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
