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
#ifndef COMMANDARRAY_H
#define COMMANDARRAY_H

#include <bpg-v2/Instruments/Rpg/Command/Command.hpp>
#include <vector>
#include <iomanip>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/shared_ptr.hpp>

struct CommandArray 
{
   private:

      typedef std::vector<boost::shared_ptr<Command> > CommandList;
      CommandList commandList_;

   public:

      CommandArray(){};

      void Add(boost::shared_ptr<Command> command) { commandList_.push_back(command);}

      std::vector<std::string> Names() 
      {
         std::vector<std::string> names;

         CommandList::iterator iter = commandList_.begin();
         while(iter != commandList_.end()){
            //command alignment
            int pad = 10 - (*iter)->Name().size();
            std::string pstr;
            for(int i=0; i<pad; ++i) pstr.push_back(' ');
            //store command name and description
            names.push_back(pstr + (*iter)->Name() + " :" + (*iter)->Description() + "\n");
            ++iter;
         }
         return names;
      }

      bool Run(std::string token)
      {

         bool found = false;

         std::vector<std::string> argList;
         //remove redundant spaces and convert lower case
         boost::trim(token);
         boost::to_lower(token);

         //now using boost::tokenizer library to handle input parsing
         //default delimiters are space and any punctuation
         boost::tokenizer<> tok(token);
         boost::tokenizer<>::iterator iter = tok.begin();
         while(iter != tok.end())
            argList.push_back(*iter++);

         CommandList::iterator cmdIter = commandList_.begin();
         while(cmdIter != commandList_.end())
         {
            if((*cmdIter)->Name() == argList[0]){
               argList.erase(argList.begin());
               (*cmdIter)->Args(argList);
               (*cmdIter)->Execute();
               found = true;
               break;
            }
            ++cmdIter;
         }
         return found;
      }
};

#endif
