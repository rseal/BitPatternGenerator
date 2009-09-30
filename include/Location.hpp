#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

struct Location{
  typedef unsigned int uint;
  Location(char& port_, uint& channel_):
    port(port_),channel(channel_){}
  char port;
  uint channel;
};


#endif
