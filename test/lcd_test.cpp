#include <bpg-v2/Common/LCDController.hpp>
#include <bpg-v2/Display/CFA634.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace std;

int main(void){

  string buf;
  const int lines   =  4;
  const int columns = 20;

  vector<string> modes;
  modes.push_back("CLP       ");
  modes.push_back("Barker 13 ");
  modes.push_back("Barker 11 ");
  modes.push_back("MRACF     ");

  boost::shared_ptr< CFA634 > lcd( new CFA634("/dev/ttyUSB0",lines,columns) );
  LCDController lcdController(lcd);

  while(buf != "start"){ cin >> buf; }
  lcdController.Mode(modes[0]);
  lcdController.Start();
  
  int b=50;
  int c=50;
  int modeCnt=0;

  while(buf != "quit"){
    cin >> buf;
    if(buf == "u"){
      b+=5;
      lcd->Brightness(b);
    }
    if(buf == "d"){
      b-=5;
      lcd->Brightness(b);
    }
    if(buf == "l"){
      c-=5;
      lcd->Contrast(c);
    }
    if(buf == "r"){
      c+=5; 
      lcd->Contrast(c);
    }
    if(buf == "s"){
      if(++modeCnt == modes.size())
	modeCnt = 0;
      lcdController.Mode(modes[modeCnt]);
    }
    cout << "contrast   = " << c << endl;
    cout << "brightness = " << b << endl;

  }

  return 0;
}

  

