#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <vector>

using namespace std;

int main(){

  typedef unsigned int uint;
  typedef boost::tuple<string,uint,uint> Tuple;
  vector<Tuple> vec;

  vector<string> old;
  vector<string> messages;
       old.push_back("   Mode:  CLP       ");
  messages.push_back("  RPG Version 2.0  ");
  
       old.push_back("Elapsed:  00:00:01  ");
  messages.push_back(" October 20, 2009  ");

       old.push_back("  Start:  12:12:00  ");
  messages.push_back(" ASPIRL Laboratory ");

       old.push_back(" System:  12:15:27  ");
  messages.push_back("   <Penn State>   ");
  
  uint size  = 20;
  uint start =  0;
  bool mark  = false;
  
  vector<string>::iterator niter = messages.begin();
  vector<string>::iterator oiter = old.begin();

  while(niter != messages.end()) {
    niter->resize(size,' ');

    //if no change in string then return
    if(niter != oiter) {
      cout << "newStr = " << *niter << "\n"
	   << "oldStr = " << *oiter << "\n" << endl;
    
      for(uint i=0; i<size; ++i){
	
	if(((*niter)[i] != (*oiter)[i]) && !mark){ 
	  start=i; 
	  cout << "start: " << start << " ";
	  mark=true;
	}

	if(((*niter)[i] == (*oiter)[i]) && mark){ 
	  vec.push_back(Tuple(niter->substr(start,i-start),start,i));
	  mark=false;
	  cout << "size: " << i << endl;
	  //cout <<"start : " << start << endl;
	  //cout <<"match: " << newStr.substr(start,i) << endl;
	}
      }

      if(mark)
	vec.push_back(Tuple(niter->substr(start,size-1),start,size-1));
    }


    ++niter;
    ++oiter;
  }

  cout << "RESULTS: " << endl;
  vector<Tuple>::iterator iter = vec.begin();
  while(iter != vec.end()){
    cout << iter->get<0>() << "   " << iter->get<1>() << "   " << iter->get<2>() << endl;
    ++iter;
  }

  return 0;

}
