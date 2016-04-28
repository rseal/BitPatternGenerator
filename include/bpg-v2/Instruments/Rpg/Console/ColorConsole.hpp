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
#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <iostream>
#include <map>

struct ConsoleScheme
{
   typedef std::string Prompt;
   typedef int Color;

   public:
   ConsoleScheme(const Prompt& up, const Color&  uc, const Prompt& sp, 
         const Color&  sc):
      userPrompt(up), userColor(uc), systemPrompt(sp), systemColor(sc)
   {

   }

   Prompt userPrompt;
   Color  userColor;
   Prompt systemPrompt;
   Color  systemColor;
};


class ColorConsole
{
   typedef std::map<const int,std::string> ColorMap;
   typedef const int type;
   typedef std::string Prompt;
   typedef int Color;

   bool     useColor_;
   std::string   base_;
   Color    noColor_;
   ConsoleScheme consoleScheme_;
   ColorMap colorMap_;

   public:
   ColorConsole(): 
      useColor_(true), base_("\001\033["), noColor_(NC),
      consoleScheme_("user> ", WHITE, "sys> ", WHITE)
   {

      colorMap_[BLACK]  = "0;30m"; colorMap_[RED]     = "0;31m";
      colorMap_[GREEN]  = "0;32m"; colorMap_[BROWN]   = "0;33m";
      colorMap_[BLUE]   = "0;34m"; colorMap_[PURPLE]  = "0;35m";
      colorMap_[CYAN]   = "0;36m"; colorMap_[LGRAY]   = "0;37m";
      colorMap_[DGRAY]  = "1;30m"; colorMap_[LRED]    = "1;31m";
      colorMap_[LGREEN] = "1;32m"; colorMap_[YELLOW]  = "1;33m";
      colorMap_[LBLUE]  = "1;34m"; colorMap_[LPURPLE] = "1;35m";
      colorMap_[LCYAN]  = "1;36m"; colorMap_[WHITE]   = "1;37m"; 
      colorMap_[NC]     = "1;0m";
   }


   void Write(const std::string& input, const int& type = SYSTEM, 
         const bool& inputColor=false)
   {

      std::string prompt (type == SYSTEM ? consoleScheme_.systemPrompt :
            consoleScheme_.userPrompt);
      Color  col    (type == SYSTEM ? consoleScheme_.systemColor  :
            consoleScheme_.userColor);

      std::string colStr1(CreateColor(  useColor_ ? col : noColor_));
      std::string colStr2(CreateColor( inputColor ? col : noColor_));

      std::cout << colStr1 << prompt << colStr2 << input;
      std::cout.flush();
   }

   void Write(const Color& color, const std::string& input)
   {
      std::string colStr(CreateColor(useColor_ ? color : noColor_));
      std::cout << colStr << input;
      std::cout.flush();
   }

   void SystemPrompt(const std::string& prompt) { consoleScheme_.systemPrompt = prompt; }
   void UserPrompt(const std::string& prompt)   { consoleScheme_.userPrompt = prompt;   }
   void SystemColor(const Color& color)    { consoleScheme_.systemColor = color;   }
   void UserColor(const Color& color)      { consoleScheme_.userColor = color;     }
   void UseColor(const bool& useColor)     { useColor_ = useColor; }
   void SystemPrompt()                     { Write("",SYSTEM);     }
   void UserPrompt()                       { Write("",USER);       }

   const std::string CreateColor(const Color& color)
   {
      std::string result;

      ColorMap::iterator iter = colorMap_.find(color);

      if(iter != colorMap_.end())
         result = base_ + iter->second;

      return result;
   }

   enum {SYSTEM, USER};
   enum {BLACK,RED,GREEN,BROWN,BLUE,PURPLE,CYAN,LGRAY,
      DGRAY,LRED,LGREEN,YELLOW,LBLUE,LPURPLE,LCYAN,
      WHITE,NC };

   void Scheme(ConsoleScheme& consoleScheme) { consoleScheme_ = consoleScheme;}
};

#endif
