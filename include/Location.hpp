#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <vector>

using std::vector;

struct Location{
  typedef unsigned int uint;
  Location(char& port_, uint& channel_):
    port(port_),channel(channel_){}
  char port;
  uint channel;
  
  void Print(std::ostream& stream){
    stream << "Port: " << port << " Channel: " << channel << std::endl;
  }
};

namespace location{
  
};
typedef vector<Location> LocationVector;

#endif
