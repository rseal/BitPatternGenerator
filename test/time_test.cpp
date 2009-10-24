#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

int main(void){

  //need string stream for formatting
  stringstream ostr;
  
  //we just want to print the time
  //use 12-hour format with am/pm and timezone
  time_facet* tf   = new  time_facet("%r %z");
  ptime t1         = second_clock::local_time();
  ptime t2         = t1 + hours(3) + minutes(27);
  time_duration t3 = t2 - t1;

  //assign strings 
  //library linking required for these functions
  string s1 = to_simple_string(t1);
  string s2 = to_simple_string(t2);
  string s3 = to_simple_string(t3);
  
  //set custom formatting
  ostr.imbue(locale(ostr.getloc(),tf));

  //format time 1
  ostr << t1;
  s1 = ostr.str();
  
  //clear ostr contents
  ostr.str("");

  //format time 2
  ostr << t2;
  s2 = ostr.str();

  //format time 3
  ostr.str("");
  ostr << t3;
  s3 = ostr.str();

  
  cout << "time 1        = " << s1 << endl;
  cout << "time 2        = " << s2 << endl;
  cout << "time2 - time1 = " << s3 << endl;

  delete tf;

  return 0;
}
